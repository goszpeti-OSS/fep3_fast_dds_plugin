// include <iostream>

#include "reader_item_queue.h"

#include "converter.h"
#include "stream_item_topic/stream_item_topic.h"

#include <a_util/result.h>

#include <fep3/base/sample/data_sample.h>

std::shared_ptr<fep3::IStreamType> createStreamType(
    const fep3::ddstypes::StreamType& dds_streamtype, const SampleInfo& /*sample_info*/)
{
    auto streamtype = std::make_shared<fep3::base::StreamType>(dds_streamtype.metatype());
    for (auto dds_property: dds_streamtype.properties()) {
        streamtype->setProperty(
            dds_property.name().to_string(), dds_property.value(), dds_property.type().to_string());
    }
    return streamtype;
}

std::shared_ptr<fep3::IDataSample> createSample(const fep3::ddstypes::BusData& dds_sample,
                                                const SampleInfo& sample_info)
{
    auto sample = std::make_shared<fep3::base::DataSample>();
    sample->set(dds_sample.data().data(), dds_sample.data().size());
    sample->setTime(convertTimestamp(sample_info.source_timestamp));
    sample->setCounter(static_cast<uint32_t>(sample_info.no_writers_generation_count));
    return sample;
}

ReaderItemQueue::ReaderItemQueue(const std::shared_ptr<fep3::ILogger>& logger,
                                 const std::shared_ptr<StreamItemTopic>& topic)
    : _logger(logger), _topic(topic)
{
    // TODO: should be included in datareader profile
    SubscriberQos sqos = SUBSCRIBER_QOS_DEFAULT;
    // We can use the FEP system name as a partition
    sqos.partition().clear();
    sqos.partition().push_back(topic->getSystemName().c_str());
    _subscriber = topic->getDomainParticipant().create_subscriber(sqos, nullptr);

    createReader();
    DataReaderQos rqos;
    _subscriber->get_datareader_qos_from_profile(std::string(FEP3_QOS_STREAM_TYPE) + "::reader", rqos);
    _streamtype_reader = _subscriber->create_datareader(topic->getStreamTypeTopic(), rqos);
}

ReaderItemQueue::~ReaderItemQueue()
{
    _sample_reader->close();
    _streamtype_reader->close();
    _subscriber->delete_contained_entities();
    _subscriber->close();
}

void ReaderItemQueue::createReader()
{
    if (_sample_reader) {
        // We are calling into FastDDSSimulationBus::startBlockingReception to be released from the
        // waitset no synchronization needed because we are in the same thread
        if (_release_reader_conditions) {
            _release_reader_conditions();
        }

        // Now we need to close the old reader
        _sample_reader->close();
    }
    // at this point we are overriding the existing reader, but it will not be deleted
    // because it's still part of the ReadCondition. But we are not affected from the old
    // reader because we have closed him.

    DataReaderQos rqos;
    /*if (queue_capacity > 0) {
        rqos.resource_limits()
            .max_samples(static_cast<int32_t>(queue_capacity))
    }*/
    _subscriber->get_datareader_qos_from_profile(_topic->getQosProfile() + "::reader", rqos);
    _sample_reader = _subscriber->create_datareader(_topic->getSampleTopic(), rqos);
}

void ReaderItemQueue::setRecreateWaitSetCondition(
    const std::function<void()>& release_reader_conditions)
{
    _release_reader_conditions = release_reader_conditions;
}

size_t ReaderItemQueue::size() const
{
    try {
        return _sample_reader
            ->get_unread_count(); // extensions().datareader_cache_status().sample_count();
    }
    catch (eprosima::fastcdr::exception::Exception& exception) {
        logError(convertExceptionToResult(exception));
    }
    return 0;
}

size_t ReaderItemQueue::capacity() const
{
    try {
        return _sample_reader->get_qos().history().depth;
    }
    catch (eprosima::fastcdr::exception::Exception& exception) {
        logError(convertExceptionToResult(exception));
    }
    return 0;
}

void ReaderItemQueue::logError(const fep3::Result& res) const
{
    if (_logger) {
        if (_logger->isErrorEnabled()) {
            _logger->logError(a_util::result::toString(res));
        }
    }
}

bool ReaderItemQueue::pop(fep3::ISimulationBus::IDataReceiver& receiver)
{
    try {
        return popFrom(*_sample_reader, *_streamtype_reader, *_subscriber, receiver);
    }
    catch (eprosima::fastcdr::exception::Exception& exception) {
        logError(convertExceptionToResult(exception));
    }
    return false;
}

bool ReaderItemQueue::popFrom(DataReader& sample_reader,
                              DataReader& streamtype_reader,
                              const Subscriber& subscriber,
                              fep3::ISimulationBus::IDataReceiver& receiver)
{
    bool read_something = false;
    if (sample_reader.is_enabled()) {
        // TODO: no coherent access available?
        _subscriber->begin_access();
        LoanableSequence<fep3::ddstypes::BusData> samples;
        LoanableSequence<SampleInfo> sample_info;
        if (ReturnCode_t::RETCODE_OK == _sample_reader->take_next_instance(samples, sample_info)) {
            SampleInfo info = sample_info[0];

            if (info.valid_data && info.instance_state == ALIVE_INSTANCE_STATE) {
                fep3::ddstypes::BusData& sample = samples[0];
                receiver(createSample(sample, info));
                read_something = true;
            }
        }
        _sample_reader->return_loan(samples, sample_info);
    }
    if (streamtype_reader.is_enabled()) {
        LoanableSequence<fep3::ddstypes::StreamType> samples;
        LoanableSequence<SampleInfo> sample_info;
        if (ReturnCode_t::RETCODE_OK ==
            _streamtype_reader->take_next_instance(samples, sample_info)) {
            SampleInfo info = sample_info[0];

            if (info.valid_data && info.instance_state == ALIVE_INSTANCE_STATE) {
                read_something = true;
                fep3::ddstypes::StreamType& streamtype = samples[0];
                read_something = true;
                auto stream_type = createStreamType(streamtype, info);
                receiver(stream_type);
                if (_topic->updateStreamType(*stream_type)) {
                    // first read all samples
                    while (pop(receiver))
                        ;

                    // now recreate reader
                    createReader();
                }
            }
            _streamtype_reader->return_loan(samples, sample_info);
        }
        _subscriber->end_access();
    }
    return read_something;
}

bool ReaderItemQueue::popFrom(const std::shared_ptr<fep3::ISimulationBus::IDataReceiver>& receiver)
{
    bool read_something = false;
    if (_sample_reader->is_enabled()) {
        // TODO: no coherent access available?
        LoanableSequence<fep3::ddstypes::BusData> samples;
        LoanableSequence<SampleInfo> sample_info;
        if (ReturnCode_t::RETCODE_OK == _sample_reader->take_next_instance(samples, sample_info)) {
            SampleInfo info = sample_info[0];

            if (info.valid_data && info.instance_state == ALIVE_INSTANCE_STATE) {
                fep3::ddstypes::BusData& sample = samples[0];
                (*receiver.get())(createSample(sample, info));
                read_something = true;
            }
        }
        _sample_reader->return_loan(samples, sample_info);
    }
    if (_streamtype_reader->is_enabled()) {
        LoanableSequence<fep3::ddstypes::StreamType> samples;
        LoanableSequence<SampleInfo> sample_info;
        if (ReturnCode_t::RETCODE_OK ==
            _streamtype_reader->take_next_instance(samples, sample_info)) {
            SampleInfo info = sample_info[0];

            if (info.valid_data && info.instance_state == ALIVE_INSTANCE_STATE) {
                read_something = true;
                fep3::ddstypes::StreamType& streamtype = samples[0];
                auto stream_type = createStreamType(streamtype, info);
                (*receiver.get())(stream_type);
                if (_topic->updateStreamType(*stream_type)) {
                    // first read all samples
                    while (pop((*receiver.get())))
                        ;

                    // now recreate reader
                    createReader();
                }
            }
            _streamtype_reader->return_loan(samples, sample_info);
        }
    }
    return read_something;
}

fep3::Optional<fep3::Timestamp> ReaderItemQueue::getFrontTime() const
{
    SampleInfo info;
    while (ReturnCode_t::RETCODE_OK == _sample_reader->get_first_untaken_info(&info)) {
        return convertTimestamp(info.source_timestamp);
    }

    while (ReturnCode_t::RETCODE_OK == _streamtype_reader->get_first_untaken_info(&info)) {
        return convertTimestamp(info.source_timestamp);
    }
    return {};
}

ReadCondition* ReaderItemQueue::createSampleReadCondition(
    const std::shared_ptr<fep3::ISimulationBus::IDataReceiver>& receiver)
{
    // using new view state does not seem to emit the condition, when the same value is read as before
    // - but then FEP receives no new value
    auto condition = _sample_reader->create_readcondition(
        ANY_SAMPLE_STATE, ANY_VIEW_STATE, ALIVE_INSTANCE_STATE);
    return condition;
}

ReadCondition* ReaderItemQueue::createStreamTypeReadCondition(
    const std::shared_ptr<fep3::ISimulationBus::IDataReceiver>& receiver)
{
    auto condition = _streamtype_reader->create_readcondition(
        NOT_READ_SAMPLE_STATE, NEW_VIEW_STATE, ALIVE_INSTANCE_STATE);
    return condition;
}

void ReaderItemQueue::on_data_available(DataReader& /*reader*/)
{
}

void ReaderItemQueue::on_requested_deadline_missed(DataReader& /*reader*/,
                                                   const RequestedDeadlineMissedStatus& /*status*/)
{
    // std::cout << "           on_requested_deadline_missed" << std::endl;
}

void ReaderItemQueue::on_requested_incompatible_qos(
    DataReader& /*reader*/, const RequestedIncompatibleQosStatus& /*status*/)
{
    // std::cout << "           on_requested_incompatible_qos" << std::endl;
}

void ReaderItemQueue::on_sample_rejected(DataReader& /*reader*/,
                                         const SampleRejectedStatus& /*status*/)
{
    // std::cout << "           on_requested_incompatible_qos" << std::endl;
}

void ReaderItemQueue::on_liveliness_changed(DataReader& /*reader*/,
                                            const LivelinessChangedStatus& /*status*/)
{
    // std::cout << "           on_requested_incompatible_qos" << std::endl;
}

void ReaderItemQueue::on_subscription_matched(DataReader& /*reader*/,
                                              const SubscriptionMatchedStatus& /*status*/)
{
    // std::cout << "           on_subscription_matched" << std::endl;
}

void ReaderItemQueue::on_sample_lost(DataReader& /*reader*/, const SampleLostStatus& /*status*/)
{
    // std::cout << "           on_sample_lost" << std::endl;
}
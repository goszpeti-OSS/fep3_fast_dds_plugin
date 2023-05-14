


#include "stream_item_topic.h"
#include <fep3/base/stream_type/default_stream_type.h>


#include "stream_item_reader.h"
#include "stream_item_writer.h"

using namespace fep3;

StreamItemTopic::StreamItemTopic(eprosima::fastdds::dds::DomainParticipant& participant
    , const std::string& topic_name
    , const IStreamType& stream_type
    , const std::shared_ptr<fep3::ILogger> logger)
    : _participant(participant)
    , _topic_name(topic_name)
    , _stream_type(stream_type)
    , _logger(logger)
{
    _qos_profile = findQosProfile(stream_type);

    if (logger->isDebugEnabled())
    {
        logger->logDebug(a_util::strings::format("Using qos profile '%s' for topic '%s'.", _qos_profile.c_str(), _topic_name.c_str()));
    }
    // TODO Check nullptr 
    auto topic = _participant.create_topic(topic_name, "fep3::ddstypes::BusData", TOPIC_QOS_DEFAULT);
    _sample_topic = topic;
    _stream_type_topic = _participant.create_topic(topic_name + "_stream_type", "fep3::ddstypes::StreamType", TOPIC_QOS_DEFAULT);
}

std::string StreamItemTopic::GetTopic()
{
    return _topic_name;
}

bool StreamItemTopic::updateStreamType(const fep3::IStreamType& stream_type)
{
    if (!(stream_type == _stream_type))
    {
        auto qos_profile = findQosProfile(stream_type);
        if (qos_profile != _qos_profile)
        {
            if (_logger->isDebugEnabled())
            {
                _logger->logDebug(a_util::strings::format("Update qos profile for topic '%s' from '%s' to '%s'.", _topic_name.c_str(), _qos_profile.c_str(), qos_profile.c_str()));
            }

            _qos_profile = qos_profile;
            return true;
        }
    }
    return false;
}

bool StreamItemTopic::isBigStreamType(const fep3::IStreamType& stream_type)
{

    auto max_byte_size = stream_type.getProperty(fep3::base::arya::meta_type_prop_name_max_byte_size);
    if (!max_byte_size.empty()
        && std::stoi(max_byte_size) >= FEP3_TRANSPORT_LAYER_MAX_MESSAGE_SIZE)
    {
        return true;
    }

    // Need to compute size of all posible array types here. See FEPSDK-2934
    // Remove lines bellow just a approximation 
    if (stream_type.getMetaTypeName() == fep3::base::arya::meta_type_plain_array.getName())
    {
        auto max_array_size = stream_type.getProperty(fep3::base::arya::meta_type_prop_name_max_array_size);

        // Assume 8 Bytes for the biggest plain type
        if (!max_array_size.empty()
            && std::stoi(max_array_size) * 8 >= FEP3_TRANSPORT_LAYER_MAX_MESSAGE_SIZE)
        {
            return true;
        }
    }
    return false;
}

std::string StreamItemTopic::findQosProfile(const fep3::IStreamType& stream_type)
{
    auto qos_profile_name = stream_type.getMetaTypeName();

    if (isBigStreamType(stream_type))
    {
        std::string big_qos_profile_name = qos_profile_name + std::string("_big");

        if (containsProfile(big_qos_profile_name))
        {
            if (_logger->isDebugEnabled())
            {
                _logger->logDebug(a_util::strings::format("stream_type '%s' for topic '%s' is too big and needs to be fragmented. Using profile '%s'."
                    , qos_profile_name.c_str()
                    , _topic_name.c_str()
                    , big_qos_profile_name.c_str()));
            }

            return std::string("fep3::") + big_qos_profile_name;
        }
    }

    if (containsProfile(qos_profile_name))
    {
        return std::string("fep3::") + qos_profile_name;
    }
    else
    {
        if (_logger->isWarningEnabled())
        {
            _logger->logWarning(a_util::strings::format("MetaType '%s' not defined in USER_QOS_PROFILES.xml. Using '" FEP3_DEFAULT_QOS_PROFILE "'.", qos_profile_name.c_str()));
        }
    }

    return FEP3_DEFAULT_QOS_PROFILE;
}

bool StreamItemTopic::containsProfile(const std::string& profile_name)
{
    //auto qos_profiles = _qos_provider->extensions().qos_profiles("fep3");
    //return std::find(qos_profiles.begin(), qos_profiles.end(), profile_name) != qos_profiles.end();
    return true;
}

std::unique_ptr<ISimulationBus::IDataReader> StreamItemTopic::createDataReader
(size_t queue_capacity
    , const std::weak_ptr<fep3::base::SimulationDataAccessCollection<ReaderItemQueue>>& data_access_collection
)
{
    return std::make_unique<StreamItemDataReader>
        (this->shared_from_this()
            , queue_capacity
            , data_access_collection
            , _logger);
}

std::unique_ptr<ISimulationBus::IDataWriter> StreamItemTopic::createDataWriter(size_t queue_capacity)
{
    auto writer = std::make_unique<StreamItemDataWriter>(this->shared_from_this(), queue_capacity);
    writer->write(_stream_type);
    return writer;
}

eprosima::fastdds::dds::DomainParticipant& StreamItemTopic::getDomainParticipant()
{
    return _participant;
}

eprosima::fastdds::dds::Topic* StreamItemTopic::getSampleTopic()
{
    return _sample_topic;
}

eprosima::fastdds::dds::Topic* StreamItemTopic::getStreamTypeTopic()
{
    return _stream_type_topic;
}

//std::shared_ptr<dds::core::QosProvider> StreamItemTopic::getQosProvider()
//{
//    return _qos_provider;
//}

std::string StreamItemTopic::getQosProfile()
{
    return _qos_profile;
}


std::string StreamItemTopic::getSystemName()
{
    return _system_name;
}


// #include <rti/core/ListenerBinder.hpp>


#include "bus_info.h"

ParticipantBuiltinTopicDataListener::ParticipantBuiltinTopicDataListener(BusInfo* businfo)
        : _businfo(businfo)
    {

    }

 // NoOpDataReaderListener
void ParticipantBuiltinTopicDataListener::on_data_available(DataReader* reader)
{
    auto data = ::builtin::ParticipantBuiltinTopicData();
    SampleInfo info;
    while(ReturnCode_t::RETCODE_OK == reader->take_next_sample(&data, &info))//(data_values, seq, 1, NOT_READ_SAMPLE_STATE))
    {
        if (!info.valid_data)
        {
            continue;
        }
        // read participant name
        std::string name(data.user_data.begin(), data.user_data.end());

        _businfo->onUserDataReceived(name);
    }
}


BusInfo::ParticipantInfo::ParticipantInfo(const std::string & participant_name) :
    _participant_name(participant_name)
{

}

bool BusInfo::ParticipantInfo::parse(const std::string & json)
{
    const auto rawJsonLength = static_cast<int>(json.length());
    JSONCPP_STRING err;
    Json::Value root;
    const Json::CharReaderBuilder builder;
    const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
    if (!reader->parse(json.c_str(), json.c_str() + rawJsonLength, &root,
        &err))
    {
        return false;
    }

    _participant_name = root["participant_name"].asString();

    if (root["fep_version"].isObject())
    {
        _fep_version.major = root["fep_version"]["major"].asInt();
        _fep_version.minor = root["fep_version"]["minor"].asInt();
        _fep_version.patch = root["fep_version"]["patch"].asInt();
    }

    return true;
}

std::string BusInfo::ParticipantInfo::asJson() const
{
    Json::Value root;

    root["participant_name"] = _participant_name;

    Json::Value version;
    version["major"] = _fep_version.major;
    version["minor"] = _fep_version.minor;
    version["patch"] = _fep_version.patch;
    root["fep_version"] = version;

    Json::StreamWriterBuilder writer_builder;
    writer_builder["indentation"] = ""; // we want whitespace-less output
    return Json::writeString(writer_builder, root);
}

void BusInfo::ParticipantInfo::setParticipantName(const std::string& participant_name)
{
    _participant_name = participant_name;
}

void BusInfo::ParticipantInfo::setFepVersion(BusInfo::Version fep_version)
{
    _fep_version = fep_version;
}

std::string BusInfo::ParticipantInfo::getParticipantName() const
{
    return _participant_name;
}

BusInfo::Version BusInfo::ParticipantInfo::getFepVersion() const
{
    return _fep_version;
}


BusInfo::BusInfo():
    _listener(this)
{
    _own_participant_info = std::make_unique<BusInfo::ParticipantInfo>();
}

BusInfo::~BusInfo()
{
    //_listener_binder.reset();
}

void BusInfo::registerUserData(DomainParticipantQos * qos)
{
    //const DomainParticipantResourceLimits resource_limits_qos =
    //    qos.policy<DomainParticipantResourceLimits>();

    //const unsigned int max_participant_user_data =
    //    resource_limits_qos.participant_user_data_max_length();

    auto json = _own_participant_info->asJson();
    if (json.size() > 2048)
    {
        throw std::length_error("Internal error: max_participant_user_data are reached");
    }
    else
    {
        UserDataQosPolicy ud(eprosima::fastrtps::types::OctetSeq(json.begin(), json.end()));
        qos->user_data(ud);
    }
}

void BusInfo::registerParticipant(DomainParticipant & participant)
{
    // Then get builtin subscriber's datareader for participants.
    //std::vector<DataReader<ParticipantBuiltinTopicData>> participant_reader;
    //find<DataReader<ParticipantBuiltinTopicData>>(
    //    builtin_subscriber(participant),
    //    participant_topic_name(),
    //    std::back_inserter(participant_reader));

    //// Install our listener using ListenerBinder, a RAII that will take care
    //// of setting it to NULL and deleting it.
    //_listener_binder = std::make_unique<rti::core::ListenerBinder<DataReader<ParticipantBuiltinTopicData>>>(
    //    rti::core::bind_and_manage_listener(
    //        participant_reader[0],
    //        new ParticipantBuiltinTopicDataListener(this),
    //        dds::core::status::StatusMask::data_available()));

}

void BusInfo::unregisterParticipant() //DomainParticipant& /*participant*/)
{
    // _callback = nullptr;
    //_listener_binder.reset();
}

void BusInfo::onUserDataReceived(const std::string& user_data)
{
    std::unique_ptr< ParticipantInfo > participant_info = std::make_unique< ParticipantInfo >();

    if (participant_info->parse(user_data))
    {
        _participant_infos[participant_info->getParticipantName()] = std::move(participant_info);
        if (_callback != nullptr) {
            _callback();
        }
    }
}


std::map<std::string, std::shared_ptr< BusInfo::ParticipantInfo >> BusInfo::getParticipantInfos() const
{
    return _participant_infos;
}

BusInfo::ParticipantInfo* BusInfo::getOwnParticipantInfo() const
{
    return _own_participant_info.get();
}

void BusInfo::setUpdateCallback(const std::function<void()>& callback)
{
    _callback = callback;
}

ParticipantBuiltinTopicDataListener BusInfo::getListener()
{
    return _listener;
}

std::string BusInfo::asJson() const
{
    std::string json = "[";

    bool first = true;

    for (const auto entry : _participant_infos)
    {

        if (first)
        {
            first = false;
        }
        else
        {
            json += ", ";
        }

        json += entry.second->asJson();

    };
    json += "]";

    return json;
}

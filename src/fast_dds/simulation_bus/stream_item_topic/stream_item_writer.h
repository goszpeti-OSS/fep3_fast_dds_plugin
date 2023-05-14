

#pragma once

#include <fep3/components/simulation_bus/simulation_bus_intf.h>
#include "../fast_dds_include.h"
#include "stream_item_topic.h"

class StreamItemDataWriter
    : public fep3::ISimulationBus::IDataWriter
    , public DataWriterListener //<fep3::ddstypes::BusData>
{
public:
    StreamItemDataWriter(const std::shared_ptr<StreamItemTopic>& topic
        , size_t queue_capacity
    );
    ~StreamItemDataWriter();

    fep3::Result write(const fep3::IDataSample& data_sample) override;
    fep3::Result write(const fep3::IStreamType& stream_type) override;
    fep3::Result transmit() override;

    void createWriter();

protected:
    // <fep3::ddstypes::BusData>
    void on_offered_deadline_missed(
        DataWriter* writer
        , const OfferedDeadlineMissedStatus& status) override;

    void on_offered_incompatible_qos(DataWriter* writer
        , const OfferedIncompatibleQosStatus& status) override;

    void on_liveliness_lost(
        DataWriter* writer
        , const LivelinessLostStatus& status) override;

    void on_publication_matched(
        DataWriter* writer
        , const PublicationMatchedStatus& status) override;

private:

    eprosima::fastdds::dds::Publisher* _publisher = nullptr;
    std::shared_ptr<StreamItemTopic> _topic;
    DataWriter* _stream_type_writer = nullptr; // <fep3::ddstypes::StreamType>
    DataWriter* _sample_writer = nullptr; // <dds::core::BytesTopicType>

};





#include <fep3/base/sample/data_sample_intf.h>
#include <fep3/base/stream_type/stream_type_intf.h>
#include <fep3/components/simulation_bus/simulation_bus_intf.h>
#include <fep3/base/sample/data_sample.h>
#include <fep3/base/stream_type/default_stream_type.h>

#include <vector>

/**
 * @brief Basic receiver collecting all stream_types and samples
 */
struct TestSubmitter
{
public:
    std::vector<fep3::data_read_ptr<const fep3::IStreamType> > _stream_types;
    std::vector<fep3::data_read_ptr<const fep3::IDataSample> > _samples;
    std::unique_ptr<fep3::ISimulationBus::IDataWriter> _writer;
    fep3::ISimulationBus* _simulation_bus;
    std::string _topic;

    TestSubmitter(fep3::ISimulationBus* simulation_bus,
                  std::string topic,
                  fep3::base::StreamType stream_type)
        : _simulation_bus(simulation_bus), _topic(topic)
    {
        _writer = _simulation_bus->getWriter(topic, stream_type);
    }

    ~TestSubmitter()
    {
    }

    template <typename T>
    void addDataSample(const fep3::base::DataSampleType<T> data_sample)
    {
        _samples.push_back(std::make_shared<const fep3::base::DataSampleType<T> >(data_sample));
    }

    void addStreamType(const fep3::base::StreamTypeDDL stream_type)
    {
        _stream_types.push_back(std::make_shared<const fep3::base::StreamTypeDDL>(stream_type));
    }

    void changeStreamType(fep3::base::StreamType stream_type)
    {
        _writer = _simulation_bus->getWriter(_topic, stream_type);
    }

    void submitStreamTypes()
    {
        for (auto stream_type : _stream_types)
        {
            _writer->write(*stream_type.get());
        }
        _writer->transmit();
        _stream_types.clear();
    }

    void submitDataSamples()
    {
        for (auto data_sample : _samples)
        {
            _writer->write(*data_sample.get());
        }
        _writer->transmit();
        _samples.clear();
    }
};





#pragma once

#include <future>
#include <random>

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <fep3/components/configuration/configuration_service_intf.h>
#include <fep3/components/participant_info/participant_info_intf.h>
#include <fep3/components/simulation_bus/simulation_bus_intf.h>
#include <fep3/plugin/cpp/cpp_plugin_component_factory.h>
#include <fep3/cpp.h>
#include <fep3/components/configuration/mock/mock_configuration_service.h>
#include <fep3/components/logging/mock/mock_logging_service.h>
#include "helper/platform_dep_name.h"
#include "fast_dds/simulation_bus/fep_fast_dds_simulation_bus.h"

namespace fep3 {
    namespace mock {
        class MockComponents : public IComponents {
            MOCK_CONST_METHOD1(findComponent, IComponent* (const std::string&));
        };
    }

}

using namespace fep3;

static const std::string default_test_name = "default_test_system";

class TestConnextDDSSimulationBus
    : public ::testing::Test
{
public:
    static uint32_t randomDomainId()
    {
        std::random_device rd;
        std::mt19937 mt(rd());
        // the actual property is int32, so we cannot set the full value span of uint32
        std::uniform_int_distribution<uint32_t> dist(1, 200u);

        return dist(mt);
    }

    void SetUp() override
    {
        _factory = std::make_unique<fep3::plugin::cpp::CPPPluginComponentFactory<FastDDSSimulationBus>>();
    }

    void TearDownComponent(fep3::IComponent & component)
    {
        EXPECT_EQ(fep3::Result(), component.stop());
        EXPECT_EQ(fep3::Result(), component.relax());
        EXPECT_EQ(fep3::Result(), component.deinitialize());
    }

    std::unique_ptr<fep3::IComponent> createSimulationBusDep
        (uint32_t domain_id
         , const std::string& participant_name
         , const std::string& system_name = default_test_name
         ) const {
        return createSimulationBus(domain_id, makePlatformDepName(participant_name), makePlatformDepName(system_name));
    }

    std::unique_ptr<fep3::IComponent> createSimulationBus
        (uint32_t domain_id
        , const std::string& participant_name
        , const std::string& system_name = default_test_name
        ) const
    {
        auto simulation_bus =   _factory->createComponent(fep3::ISimulationBus::getComponentIID());
        if (!simulation_bus)
        {
            return nullptr;
        }

        std::shared_ptr<Components> components = std::make_shared<Components>(participant_name, system_name);
        EXPECT_EQ(fep3::Result(), simulation_bus->createComponent(components));

        // auto property_node = components->_configuration_service->getNode("fast_dds_simulation_bus");
        // if (!property_node)
        // {
        //    return nullptr;
        // }

        // if (auto property = std::dynamic_pointer_cast<fep3::base::arya::IPropertyWithExtendedAccess>(property_node->getChild("participant_domain")))
        // {
        //    property->setValue(std::to_string(domain_id));
        //    property->updateObservers();
        // }

        EXPECT_EQ(fep3::Result(), simulation_bus->initialize());
        EXPECT_EQ(fep3::Result(), simulation_bus->tense());
        EXPECT_EQ(fep3::Result(), simulation_bus->start());

        return simulation_bus;
    }

    void startReception(fep3::ISimulationBus* simulation_bus)
    {
        // stop any potentially running reception
        stopReception(simulation_bus);

        auto receiver_thread_iterator = _receiver_threads.cbegin();
        for(; receiver_thread_iterator != _receiver_threads.cend(); ++receiver_thread_iterator)
        {
            if(receiver_thread_iterator->first == simulation_bus)
            {
                break;
            }
        }
        if(receiver_thread_iterator == _receiver_threads.cend())
        {
            std::promise<void> blocking_reception_prepared;
            auto blocking_reception_prepared_result = blocking_reception_prepared.get_future();
            receiver_thread_iterator = _receiver_threads.emplace
                (_receiver_threads.cend()
                , simulation_bus
                , std::make_unique<std::thread>([simulation_bus, &blocking_reception_prepared]()
                    {
                        try
                        {
                            simulation_bus->startBlockingReception([&blocking_reception_prepared]()
                            {
                                blocking_reception_prepared.set_value();
                            });
                        }
                        catch (std::exception exception)
                        {
                            GTEST_FAIL();
                        }
                    })
                );
            // wait for the blocking reception to be prepared
            blocking_reception_prepared_result.get();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    void stopReception(fep3::ISimulationBus* simulation_bus)
    {
        simulation_bus->stopBlockingReception();
        for(auto& receiver_threads_entry : _receiver_threads)
        {
            if(receiver_threads_entry.first == simulation_bus)
            {
                if (receiver_threads_entry.second)
                {
                    receiver_threads_entry.second->join();
                    receiver_threads_entry.second.reset();
                }
            }
        }
    }

public:
    class ParticipantInfo : public fep3::base::Component < fep3::IParticipantInfo >
    {
    public:
        ParticipantInfo(const std::string & participant_name, const std::string & system_name)
            : _participant_name(participant_name)
            , _system_name(system_name)
        {

        }
        std::string getName() const override
        {
            return _participant_name;
        }

        std::string getSystemName() const override
        {
            return _system_name;
        }

    private:
        std::string _participant_name;
        std::string _system_name;
    };

    class Components: public fep3::IComponents
    {
    public:
        std::unique_ptr<fep3::mock::ConfigurationService<fep3::base::Component>> _configuration_service;
        std::unique_ptr<ParticipantInfo> _participant_info;
        std::unique_ptr<fep3::mock::LoggingService> _logging_service;
    public:
        Components(const std::string participant_name
            , const std::string system_name = default_test_name
            , std::shared_ptr<fep3::mock::LoggerMock> logging_mock = std::make_shared<::testing::NiceMock<fep3::mock::LoggerMock>>())
            : _participant_info(std::make_unique<ParticipantInfo>(participant_name, system_name))
            , _logging_service(std::make_unique<fep3::mock::LoggingService>(logging_mock))
        {
            auto base_comps = std::make_shared<testing::StrictMock<fep3::mock::MockComponents>>();
            std::weak_ptr<fep3::mock::MockComponents> weak_comps = base_comps;
            _configuration_service = std::make_unique<fep3::mock::ConfigurationService<fep3::base::Component>>();
            _configuration_service->createComponent(weak_comps);
            _configuration_service->initialize();
            _configuration_service->tense();
            _configuration_service->start();
        }

        fep3::IComponent* findComponent(const std::string& fep_iid) const
        {
            if (fep_iid == fep3::IConfigurationService::getComponentIID())
            {
                return _configuration_service.get();
            }
            else if (fep_iid == fep3::IParticipantInfo::getComponentIID())
            {
                return _participant_info.get();
            }
            else if (fep_iid == fep3::ILoggingService::getComponentIID())
            {
                return _logging_service.get();
            }
            return nullptr;
        }
    };

protected:
    std::unique_ptr<fep3::plugin::cpp::CPPPluginComponentFactory<FastDDSSimulationBus>> _factory;
    std::list<std::pair<fep3::ISimulationBus*, std::unique_ptr<std::thread>>> _receiver_threads;
};



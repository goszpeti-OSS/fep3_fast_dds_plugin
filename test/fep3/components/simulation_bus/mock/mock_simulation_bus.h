/**
 * @file
 * @copyright
 * @verbatim
Copyright @ 2021 VW Group. All rights reserved.

    This Source Code Form is subject to the terms of the Mozilla
    Public License, v. 2.0. If a copy of the MPL was not distributed
    with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

If it is not possible or desirable to put the notice in a particular file, then
You may include the notice in a location (such as a LICENSE file in a
relevant directory) where a recipient would be likely to look for such a notice.

You may add additional accurate notices of copyright ownership.

@endverbatim
 */


#pragma once

#include <gmock/gmock.h>

#include <fep3/components/simulation_bus/simulation_bus_intf.h>
#include <fep3/components/base/component.h>

namespace fep3
{
namespace mock
{

class DataReader
    : public ISimulationBus::IDataReader
{
public:
    ~DataReader() override = default;
    MOCK_CONST_METHOD0(size, size_t());
    MOCK_CONST_METHOD0(capacity, size_t());
    MOCK_METHOD1(pop, bool(ISimulationBus::IDataReceiver&));
    // mocking a method with default parameter requires a helper
    void reset(const std::shared_ptr<ISimulationBus::IDataReceiver>& receiver = {}) override
    {
        reset_(receiver);
    }
    MOCK_METHOD1(reset_, void(const std::shared_ptr<ISimulationBus::IDataReceiver>&));
    MOCK_CONST_METHOD0(getFrontTime, Optional<Timestamp>());
};

class DataReceiver
    : public ISimulationBus::IDataReceiver
{
public:

    MOCK_METHOD1(call, void(const data_read_ptr<const IStreamType>&));
    virtual void operator()(const data_read_ptr<const IStreamType>& type)
    {
        call(type);
    }
    MOCK_METHOD1(call, void(const data_read_ptr<const IDataSample>&));
    virtual void operator()(const data_read_ptr<const IDataSample>& sample)
    {
        call(sample);
    }
};

class DataWriter
    : public ISimulationBus::IDataWriter
{
public:
    MOCK_METHOD1(write, Result(const IDataSample&));
    MOCK_METHOD1(write, Result(const IStreamType&));
    MOCK_METHOD0(transmit, Result());
};

template<template<typename...> class component_base_type = fep3::base::Component>
class SimulationBus
    : public component_base_type<ISimulationBus>
{
public:
    MOCK_CONST_METHOD1(isSupported, bool(const IStreamType&));
    // with current version of gMock in the aev_testing package, move-only types are not supported with MSVC
    // , so we need workarounds as suggested here:
    // https://github.com/google/googletest/blob/master/googlemock/docs/cook_book.md#legacy-workarounds-for-move-only-types-legacymoveonly
    MOCK_METHOD2(getReader_, ISimulationBus::IDataReader*(const std::string&, const IStreamType&));
    std::unique_ptr<ISimulationBus::IDataReader> getReader(const std::string& name, const IStreamType& stream_type) override
    {
        return std::unique_ptr<ISimulationBus::IDataReader>(getReader_(name, stream_type));
    }
    MOCK_METHOD3(getReader_, ISimulationBus::IDataReader*(const std::string&, const IStreamType&, size_t));
    std::unique_ptr<ISimulationBus::IDataReader> getReader(const std::string& name, const IStreamType& stream_type, size_t queue_capacity) override
    {
        return std::unique_ptr<ISimulationBus::IDataReader>(getReader_(name, stream_type, queue_capacity));
    }
    MOCK_METHOD1(getReader_, ISimulationBus::IDataReader*(const std::string&));
    std::unique_ptr<ISimulationBus::IDataReader> getReader(const std::string& name) override
    {
        return std::unique_ptr<ISimulationBus::IDataReader>(getReader_(name));
    }
    MOCK_METHOD2(getReader_, ISimulationBus::IDataReader*(const std::string&, size_t));
    std::unique_ptr<ISimulationBus::IDataReader> getReader(const std::string& name, size_t queue_capacity) override
    {
        return std::unique_ptr<ISimulationBus::IDataReader>(getReader_(name, queue_capacity));
    }
    MOCK_METHOD2(getWriter_, ISimulationBus::IDataWriter*(const std::string&, const IStreamType&));
    std::unique_ptr<ISimulationBus::IDataWriter> getWriter(const std::string& name, const IStreamType& stream_type) override
    {
        return std::unique_ptr<ISimulationBus::IDataWriter>(getWriter_(name, stream_type));
    }
    MOCK_METHOD3(getWriter_, ISimulationBus::IDataWriter*(const std::string&, const IStreamType&, size_t));
    std::unique_ptr<ISimulationBus::IDataWriter> getWriter(const std::string& name, const IStreamType& stream_type, size_t queue_capacity) override
    {
        return std::unique_ptr<ISimulationBus::IDataWriter>(getWriter_(name, stream_type, queue_capacity));
    }
    MOCK_METHOD1(getWriter_, ISimulationBus::IDataWriter*(const std::string&));
    std::unique_ptr<ISimulationBus::IDataWriter> getWriter(const std::string& name) override
    {
        return std::unique_ptr<ISimulationBus::IDataWriter>(getWriter_(name));
    }
    MOCK_METHOD2(getWriter_, ISimulationBus::IDataWriter*(const std::string&, size_t));
    std::unique_ptr<ISimulationBus::IDataWriter> getWriter(const std::string& name, size_t queue_capacity) override
    {
        return std::unique_ptr<ISimulationBus::IDataWriter>(getWriter_(name, queue_capacity));
    }
    
    MOCK_METHOD1(startBlockingReception, void(const std::function<void()>&));
    MOCK_METHOD0(stopBlockingReception, void());
};

} // namespace mock
} // namespace fep3
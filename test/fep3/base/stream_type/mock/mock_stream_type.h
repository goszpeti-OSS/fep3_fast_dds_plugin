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

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <fep3/base/stream_type/stream_type_intf.h>

namespace fep3
{
namespace mock
{

class StreamType
    : public IStreamType
{
public:
    ~StreamType() = default;

    MOCK_CONST_METHOD0(getMetaTypeName, std::string());
    // interface IProperties
    MOCK_METHOD3(setProperty, bool(const std::string&, const std::string&, const std::string&));
    MOCK_CONST_METHOD1(getProperty, std::string(const std::string&));
    MOCK_CONST_METHOD1(getPropertyType, std::string(const std::string&));
    MOCK_CONST_METHOD1(isEqual, bool(const IProperties&));
    MOCK_CONST_METHOD1(copyTo, void(IProperties&));
    MOCK_CONST_METHOD0(getPropertyNames, std::vector<std::string>());
};

// gmock matchers
MATCHER_P(StreamTypeMatcher, other, "Equality matcher for IStreamType")
{
    return arg.getMetaTypeName() == other.getMetaTypeName();
}
MATCHER_P(StreamTypeSmartPtrMatcher, other, "Equality matcher for data_read_ptr<const IStreamType>")
{
    return
        arg->getMetaTypeName() == other->getMetaTypeName()
        && arg->isEqual(*other.get());
}


} // namespace mock
} // namespace fep3
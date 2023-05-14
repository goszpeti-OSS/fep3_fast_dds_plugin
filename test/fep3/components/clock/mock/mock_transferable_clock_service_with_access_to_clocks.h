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

#include "mock_clock_service.h"
#include <fep3/components/base/c_access_wrapper/transferable_component_base.h>

namespace fep3
{
namespace mock
{

struct TransferableClockServiceWithAccessToClocks
    : public ClockService<fep3::plugin::c::TransferableComponentBase>
{
private:
    fep3::Result registerClock(const std::shared_ptr<IClock>& clock) override
    {
        registered_clocks_.emplace_back(clock);
        // call the mocked method to enable setting of expectations
        return ClockService::registerClock(clock);
    }

public:
    std::list<::fep3::IClock*> getRegisteredClocks() const
    {
        std::list<::fep3::IClock*> clocks;
        for(const auto& clock : registered_clocks_)
        {
            clocks.push_back(clock.get());
        }
        return clocks;
    }
private:
    std::list<std::shared_ptr<::fep3::IClock>> registered_clocks_;
};

}
}

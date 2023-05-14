

#pragma once

#include <fep3/fep3_errors.h>
#include "fast_dds_include.h"

/**
 * Convert std timestamp into dds timestamp
 */

eprosima::fastrtps::Time_t convertTimestamp(const std::chrono::nanoseconds& timestamp);

/**
 * Convert dds timestamp into std timestamp
 */
std::chrono::nanoseconds convertTimestamp(const eprosima::fastrtps::rtps::Time_t& timestamp);

/**
 * Convert dds exception into fep3::Result
 */
fep3::Result convertExceptionToResult(const eprosima::fastrtps::rtps::Exception & exception);

/**
 * Convert std::exception into fep3::Result
 */
fep3::Result convertExceptionToResult(const std::exception& exception);

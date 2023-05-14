


#include "converter.h"

eprosima::fastrtps::Time_t convertTimestamp(const std::chrono::nanoseconds& timestamp)
{
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(timestamp);
    auto nanoseconds = timestamp - seconds;
    return eprosima::fastrtps::Time_t(static_cast<uint32_t>(seconds.count()),
                           static_cast<uint32_t>(nanoseconds.count()));
}

std::chrono::nanoseconds convertTimestamp(const eprosima::fastrtps::rtps::Time_t& timestamp)
{
    auto seconds = std::chrono::seconds(timestamp.seconds());
    auto nanoseconds = std::chrono::nanoseconds(timestamp.nanosec());
    return seconds + nanoseconds;
}

fep3::Result convertExceptionToResult(const eprosima::fastrtps::rtps::Exception& exception)
{
    RETURN_ERROR_DESCRIPTION(fep3::ERR_FAILED,
        "simulation bus: rti connext: %s",
        exception.what());
}

fep3::Result convertExceptionToResult(const std::exception& exception)
{
    RETURN_ERROR_DESCRIPTION(fep3::ERR_FAILED,
        "simulation bus: rti connext: %s",
        exception.what());
}
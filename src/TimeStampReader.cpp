#include "../include/TimeStampReader.h"
#include <string>
#include <algorithm>
#include <stdexcept>
int TimeStampReader::GetValueOfTimeStamp(std::string aTimeStamp)
{
    if(aTimeStamp.length() != 8) {
        return -1;
    }

    std::string hours(std::begin(aTimeStamp), std::begin(aTimeStamp) + 2);
    std::string mins(std::begin(aTimeStamp) + 3, std::end(aTimeStamp) - 3);
    std::string secs(std::end(aTimeStamp) - 2, std::end(aTimeStamp));

    int total_secs = 0;

    //! Evaluate value of hours in seconds
    try {
        auto hours_as_secs = std::stoi(hours) * 3600;
        if(hours_as_secs < 0 || hours_as_secs > 82800) {
            return -1;
        }
        total_secs += hours_as_secs;
    } catch(std::invalid_argument&) {
        return -1;
    } catch(std::out_of_range&) {
        return -1;
    }

    //! Evaluate value of mins in seconds
    try {
        auto mins_as_secs = std::stoi(mins) * 60;
        if(mins_as_secs < 0 || mins_as_secs > 3540) {
            return -1;
        }
        total_secs += mins_as_secs;
    } catch(std::invalid_argument&) {
        return -1;
    } catch(std::out_of_range&) {
        return -1;
    }

    try {
        auto secs_from_string = std::stoi(secs);
        if(secs_from_string < 0 || secs_from_string > 59) {
            return -1;
        }
        total_secs += secs_from_string;
    } catch(std::invalid_argument&) {
        return -1;
    } catch(std::out_of_range&) {
        return -1;
    }

    return total_secs;
}

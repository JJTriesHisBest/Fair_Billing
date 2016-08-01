#pragma once
#include <string>

class ITimeStampReader
{
public:
    virtual ~ITimeStampReader(){}
public:
    virtual int GetValueOfTimeStamp(std::string aTimeStamp) = 0;
};

class TimeStampReader : public ITimeStampReader
{
public:
    /** GetValueOfTimeStamp() returns -1 if the time stamp is invalid or a number >= 0 that represents the
        number of seconds through that billing day i.e. 00:00:34 returns 34, 00:01:20 returns 80, 10:10:10 returns 36610
    */
    int GetValueOfTimeStamp(std::string aTimeStamp) override; 
};
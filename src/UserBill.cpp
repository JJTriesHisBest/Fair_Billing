#include "UserBill.h"

UserBill::UserBill(std::string aName, unsigned int aTimeAtStartOfBill)
    : iName(aName)
    , iSessionCount(0)
    , iTotalTime(0)
    , iTimeAtStartOfBill(aTimeAtStartOfBill)
{

}

std::string UserBill::Name()
{
    return iName;
}

unsigned int UserBill::SessionCount()
{
    return iSessionCount;
}

unsigned int UserBill::TotalTime()
{
    return iTotalTime;
}

void UserBill::AddStartTime(unsigned int aTime)
{
    iSessionCount++;
    iStartTimes.push(aTime);
}

void UserBill::AddEndTime(unsigned int aTime)
{
    if(iStartTimes.empty()) {
        iSessionCount++;
        iTotalTime += aTime - iTimeAtStartOfBill;
    } else {
        iTotalTime += aTime - iStartTimes.front();
        iStartTimes.pop();
    }
}

void UserBill::ResolveUnfinishedSessions(unsigned int aEndTime) 
{
    while(iStartTimes.size()) {
        iTotalTime += aEndTime - iStartTimes.front();
        iStartTimes.pop();
    }
}
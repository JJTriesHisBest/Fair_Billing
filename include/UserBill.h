#pragma once

#include <string>
#include <queue>

class IUserBill 
{
public:
    virtual ~IUserBill(){}
public:
    virtual std::string Name() = 0;
    virtual unsigned int SessionCount() = 0;
    virtual unsigned int TotalTime() = 0;
    virtual void AddStartTime(unsigned int aTime) = 0;
    virtual void AddEndTime(unsigned int aTime) = 0;
    virtual void ResolveUnfinishedSessions(unsigned int aEndTime) = 0;
};

class UserBill : public IUserBill
{
public:
    UserBill(std::string aName, unsigned int aTimeAtStartOfBill);
public:
    std::string Name() override;
    unsigned int SessionCount() override;
    unsigned int TotalTime() override;
    void AddStartTime(unsigned int aTime) override;
    void AddEndTime(unsigned int aTime) override;
    void ResolveUnfinishedSessions(unsigned int aEndTime) override;
private:
    std::string iName;
    unsigned int iSessionCount;
    unsigned int iTotalTime;
    unsigned int iTimeAtStartOfBill;
    std::queue<unsigned int> iStartTimes;
};

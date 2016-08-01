#pragma once
#include "UserBill.h"
#include "TimeStampReader.h"
#include <string>
#include <memory>
class BillGenerator 
{
public:
    BillGenerator(const char* aPath);
public:
    void PrintBill();
private:
    void ProcessValidEntry(unsigned int aSecs, std::string aName, bool aIsBegin);
private:
    TimeStampReader iReadTime;
    unsigned int iTimeAtBeginningOfBill;
    unsigned int iMostRecentTime;
    bool iFirstValidEntryRead;
    std::vector<std::string> iEntries;
    std::vector<std::unique_ptr<UserBill>> iUsersToBill;

};
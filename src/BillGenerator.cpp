#include "../include/BillGenerator.h"
#include "../include/TimeStampReader.h"

#include <algorithm>
#include <fstream>
#include <array>
#include <cctype>
#include <iostream>
#include <memory>
BillGenerator::BillGenerator(const char* aPathToLog)
    : iMostRecentTime(0)
    , iFirstValidEntryRead(false)
{
    /**Load log file*/
    std::ifstream log;
    log.open(aPathToLog);
    for (std::string line; std::getline(log, line); ) {
        iEntries.emplace_back(line.begin(), line.end());
    }

    /**Do work with loaded entries*/
    for(auto entry : iEntries) {
        /** Make entry the string is three words long*/
        auto spaces = std::count(entry.begin(), entry.end(), ' ');
        if(spaces != 2) {
            continue; //There should only be two spaces in an entry
        }

        /**Evaluate TimeStamp*/
        int seconds = iReadTime.GetValueOfTimeStamp(entry.substr(0,8));
        if(seconds < static_cast<int>(iMostRecentTime)) {
            continue; //TimeStampReader returned an error (-1) or the time stamp is invalid (should always be further along than previous time stamp)
        }

        /**Evaluate Name*/
        auto end_of_name = entry.find_first_of(' ', 9);
        auto name = entry.substr(9, end_of_name - 9);
        bool isAlphaNumerical = true;
        for(char& c : name) {
            auto alnum = std::isalnum(c);
            if(alnum == 0) {
                isAlphaNumerical = false;
                break;
            }
        }
        if(!isAlphaNumerical) {
            continue; //A valid name is alphanumerical
        }

        /**Evaluate Begin/End */
        auto begin_end = entry.substr(end_of_name + 1); // +1 to compensate for space
        if(begin_end == "Start") {
            iMostRecentTime = static_cast<unsigned int>(seconds);
            if(!iFirstValidEntryRead) {
                iTimeAtBeginningOfBill = iMostRecentTime;
                iFirstValidEntryRead = true;
            }
            ProcessValidEntry(iMostRecentTime, name, true);
        } else if(begin_end == "End") {
                iMostRecentTime = static_cast<unsigned int>(seconds);
                if(!iFirstValidEntryRead) {
                    iTimeAtBeginningOfBill = iMostRecentTime;
                    iFirstValidEntryRead = true;
                }
                ProcessValidEntry(iMostRecentTime, name, false);
        } else {
                continue;
            }
    }

    /**Resolve unfinished sessions*/
    for(auto&& user : iUsersToBill) {
        user->ResolveUnfinishedSessions(iMostRecentTime);
    }
}

void BillGenerator::ProcessValidEntry(unsigned int aTime, std::string aName, bool aIsBegin)
{
    auto userToBill = std::find_if(iUsersToBill.begin(), iUsersToBill.end(), [&](auto&& user){
        return user->Name() == aName;
    });

    if (userToBill == iUsersToBill.end()) {
        iUsersToBill.emplace_back(new UserBill(aName, iTimeAtBeginningOfBill));
        userToBill = iUsersToBill.end() - 1;
    }

    aIsBegin ? (*userToBill)->AddStartTime(aTime) : (*userToBill)->AddEndTime(aTime);
}

void BillGenerator::PrintBill() 
{
    for(auto&& user : iUsersToBill) {
        std::cout << user->Name() << ' ' << user->SessionCount() << ' ' << user->TotalTime() << std::endl;
    }
}
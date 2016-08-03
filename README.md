# Fair_Billing
Technical challenge: Given a log file with a known format, parse information about customer usage to learn each customers total number of sessions and total time spent

Example of usage:
-----------------
Build the program on Ubuntu like so:
	gcc LogAnalyserMain.cpp src/* -std=c++14 -lstdc++ -o fairBilling

Run that program:
	./fairBilling input2.txt

Specification
=============

When presented with a log file like this example

    14:02:03 ALICE99 Start
    14:02:05 CHARLIE End
    14:02:34 ALICE99 End
    14:02:58 ALICE99 Start
    14:03:02 CHARLIE Start
    14:03:33 ALICE99 Start
    14:03:35 ALICE99 End
    14:03:37 CHARLIE End
    14:04:05 ALICE99 End
    14:04:23 ALICE99 End
    14:04:41 CHARLIE Start
    14:04:42 JJ End


Where the proper format for an entry is a timestamp formatted as HH:MM:SS,
the name is alphanumerical and of an arbitrary length, and the final field is always
either 'Start' or 'End'

A corrupt line, a line that is not an actual log entry, or anything that is improperly
formatted should be silently ignored by the program.

For each valid entry, the program will keep track of the number of users in the log, their total number of sessions, 
and the total time accumulated. 'Start' entries with no possible corresponding 'End' in the log will be assumed to end
at the final valid timestamp. 'End' entries with no corresponding 'Start' will be assumed to start
at the first valid timestamp.

The output of the program should have one row for each user, where the first column is the name, second the session count, and third the total time spent active.

For example, the above text would output

    ALICE99 4 240
    CHARLIE 3 38
    JJ 1 159

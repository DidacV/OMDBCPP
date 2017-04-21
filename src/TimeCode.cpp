/* 
 * File:   TimeCode.cpp
 * Author: Didac
 * 
 * Created on 14 April 2017, 13:32
 */
#include <sstream>
#include <iostream>
#include "TimeCode.h"

using namespace std;
TimeCode::TimeCode()
{
    
}

TimeCode::TimeCode(int day, int month, int year, int hour, int minute, int second)
{
    this->day = day;
    this->month = month;
    this->year = year;
    this->hour = hour;
    this->minute = minute;
    this->second = second;
}

TimeCode::TimeCode(const TimeCode& orig) {
}

TimeCode::~TimeCode() {
    //cout << "timecode destroyed" << endl;
}

std::istream& operator>>(std::istream &is, TimeCode &t)
{
    // parse a timestamp
    // it will be like: 03/03/2013T08:11:29Z
    // to find date stop at T, to find time stop at Z
    int day, month, year, hour, minute, second;
    char c;

    if(is >> day >> c >> month >> c >> year >> c)
    {
	if(is >> hour >> c >> minute >> c >> second >> c)
	{
	   t = TimeCode(day, month, year, hour, minute, second); 
	}
    }
    return is;
}

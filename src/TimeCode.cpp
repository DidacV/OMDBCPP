/* 
 * File:   TimeCode.cpp
 * Author: Didac
 * 
 * Created on 14 April 2017, 13:32
 */
#include <sstream>
#include <iostream>
#include <math.h>
#include "TimeCode.h"

using namespace std;

TimeCode::TimeCode(){}

TimeCode::TimeCode(int day, int month, int year, int hours, int minutes, int seconds)
{
    // If the year is 0, means we're dealing with seconds since epoch
    if (year == 0){
        year = EPOCH_YEAR;
        const int year_t[2][12] = {
                { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
                { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
        };

        int day_c = seconds  % SECS_DAY;
        int day_n = seconds / SECS_DAY;

        // Prepare for construct
        seconds = day_c % 60;
        minutes = (day_c % 3600) / 60;
        hours = day_c / 3600;
        while (day_n >= YEAR_SIZE(year)){
            day_n -= YEAR_SIZE(year);
            year++;
        }
        month = 0;
        while(day_n >= year_t[IS_LEAP_YEAR(year)][month]){
            day_n -= year_t[IS_LEAP_YEAR(year)][month];
            month++;
        }
        month += 1;
        day = day_n + 1;
    }

    this->day = day;
    this->month = month;
    this->year = year;
    this->hours = hours;
    this->minutes = minutes;
    this->seconds = seconds;
}

TimeCode::TimeCode(const TimeCode& orig) {
    this->day = orig.day;
    this->month = orig.month;
    this->year = orig.year;
    this->hours = orig.hours;
    this->minutes = orig.minutes;
    this->seconds = orig.seconds;
}

TimeCode::~TimeCode() {}

std::istream& operator>>(std::istream &is, TimeCode &t)
{
    int day, month, year, hour, minutes, second;
    char c;

    if(is >> day >> c >> month >> c >> year >> c)
    {
        if(is >> hour >> c >> minutes >> c >> second >> c)
        {
            //day = 0; month = 0; year = 0; hour = 0; minutes = 0; second = 1456269067;
            t = TimeCode(day, month, year, hour, minutes, second); 
        }
    }
    return is;
}

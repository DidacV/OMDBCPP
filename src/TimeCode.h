 /* 
 * File:   TimeCode.h
 * Author: Didac
 *
 * Created on 14 April 2017, 13:32
 */
#pragma once
#include <sstream>
#include <iomanip>


class TimeCode {
private:
    int day, month, year, hour, minute, second;
public:
    TimeCode();
    TimeCode(const TimeCode& orig);
    TimeCode(int day, int month, int year, int hour, int minute, int second);
    virtual ~TimeCode();
    
    //general getters
    inline int get_day() const;
    inline int get_year() const;
    inline int get_hour() const;
    inline int get_minute() const;
    inline int get_second() const;
    
    // get timestamp
    inline std::string get_timestamp() const;
    
    // overload operators
    friend bool operator>(const TimeCode &t, const TimeCode &_t);
    friend bool operator<(const TimeCode &t, const TimeCode &_t);
    friend std::ostream& operator<<(std::ostream &os, const TimeCode &t);
    
};

inline std::string TimeCode::get_timestamp() const
{
    std::stringstream ss;
    ss  << std::setw(2) << std::setfill('0') << day << ":"
        << std::setw(2) << std::setfill('0') << month << ":"
        << std::setw(4) << std::setfill('0') << year << ":" << "T"
        << std::setw(2) << std::setfill('0') << hour << ":"
        << std::setw(2) << std::setfill('0') << minute << ":"
        << std::setw(2) << std::setfill('0') << second << ":" << "Z";
    
    return ss.str();
    
    
}

inline bool operator<(const TimeCode &t, const TimeCode &_t)
{
    //return t.get_timestamp() < _t.get_timestamp();
    
    if(t.year == _t.year)
    {
	if (t.month == _t.month)
	{
	    if (t.day == _t.day)
	    {
		if (t.hour == _t.hour)
		{
		    if (t.minute == _t.minute)
		    {
			if (t.second == _t.second)
			{
			    return t.second == _t.second;
			}
			return t.second < _t.second;
		    }
		    return t.minute < _t.minute;
		}
		return t.hour < _t.hour;
	    }
	    return t.day < _t.day;
	}
	return t.month < _t.month;
    }
    return t.year < _t.year;
    
}

inline bool operator>(const TimeCode &t, const TimeCode &_t)
{
    if(t.year == _t.year)
    {
	if (t.month == _t.month)
	{
	    if (t.day == _t.day)
	    {
		if (t.hour == _t.hour)
		{
		    if (t.minute == _t.minute)
		    {
			if (t.second == _t.second)
			{
			    return t.second == _t.second;
			}
			return t.second > _t.second;
		    }
		    return t.minute > _t.minute;
		}
		return t.hour > _t.hour;
	    }
	    return t.day > _t.day;
	}
	return t.month > _t.month;
    }
    return t.year > _t.year;
    
}

inline std::ostream& operator<<(std::ostream &os, const TimeCode &t)
{
    return os << std::setw(2) << std::setfill('0') << t.day << ":"
              << std::setw(2) << std::setfill('0') << t.month << ":"
              << std::setw(4) << std::setfill('0') << t.year << ":" << "T"
              << std::setw(2) << std::setfill('0') << t.hour << ":"
              << std::setw(2) << std::setfill('0') << t.minute << ":"
              << std::setw(2) << std::setfill('0') << t.second << ":" << "Z";
}

std::istream& operator>>(std::istream &is, TimeCode &t);

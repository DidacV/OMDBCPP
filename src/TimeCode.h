 /* 
 * File:   TimeCode.h
 * Author: Didac
 *
 * Created on 14 April 2017, 13:32
 * Representation of time.
 * If an epoch is passed, the date will be calculated and viceversa.
 */
#pragma once
#include <sstream>
#include <iomanip>
#define EPOCH_YEAR 1970
#define IS_LEAP_YEAR(year) (!((year) % 4) && (((year) % 100) || !((year) % 400)))
#define SECS_DAY 86400
#define YEAR_SIZE(year) (IS_LEAP_YEAR(year) ? 366 : 365)

class TimeCode 
{
private:
    /*********  Private fields  **********/
    int day, month, year, hours, minutes, seconds;

    /*********  Private structures  **********/
	int days_year[13] = {
		0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365
	};
    int days_leap_year[13] = {
		0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366
	};
public:
    /*********  Constructors & destructor **********/
    TimeCode();
    TimeCode(const TimeCode& orig);
    TimeCode(int day, int month, int year, int hour, int minute, int second);
    virtual ~TimeCode();
    
    /*********  Getters  **********/
    inline int get_day() const;
    inline int get_year() const;
    inline int get_hour() const;
    inline int get_minute() const;
    inline int get_second() const;
    
    inline std::string get_timestamp() const;
    
    /*********  Overloading  **********/
    inline operator int() const;
    friend std::ostream& operator<<(std::ostream &os, const TimeCode &t);
};

inline TimeCode::operator int() const
{
	// Check how many leap years since 1970
    int leap_years = 0;
    int i = EPOCH_YEAR;
    for (;i < year; i++){
        if (IS_LEAP_YEAR(i))
            leap_years++;
    }

    // Could be improved further.
    if (IS_LEAP_YEAR(i)){
        return seconds + ((year - 1970) * 365 * 24 * 60 * 60) + 
                    ((day + days_year[month - 1]) * 24 * 60 * 60) + 
                    (hours * 60 * 60) +
                    (minutes * 60) + (leap_years * 24 * 60 * 60);
    } else {
        return seconds + ((year - 1970) * 365 * 24 * 60 * 60) + 
                    ((day - 1 + days_year[month - 1]) * 24 * 60 * 60) + 
                    (hours * 60 * 60) +
                    (minutes * 60) + (leap_years * 24 * 60 * 60);
    }

}

inline bool operator<(const TimeCode &t, const TimeCode &_t)
{
    return int(t) < int(_t);
}

inline bool operator>(const TimeCode &t, const TimeCode &_t)
{
    return int(t) > int(_t); 
}

inline bool operator>=(const TimeCode &t, const TimeCode &_t)
{
    return !(t < _t);
}

inline bool operator<=(const TimeCode &t, const TimeCode &_t)
{
    return !(t > _t);
}

inline bool operator==(const TimeCode &t, const TimeCode &_t)
{
    return int(t) == int(_t);
}

inline bool operator!=(const TimeCode &t, const TimeCode &_t)
{
    return !(t == _t);
}

inline TimeCode operator+(const TimeCode &t, const TimeCode &_t)
{
    //return true;
    return TimeCode(0,0,0,0,0, int(t) + int(_t));
}

inline TimeCode operator-(const TimeCode& t, const TimeCode &_t)
{
    return TimeCode(0,0,0,0,0, int(t) - int(_t));
}

inline TimeCode operator*(int n, const TimeCode& t)
{
    return TimeCode(0,0,0,0,0, n*int(t));
}

inline TimeCode operator*(const TimeCode& t, int n)
{
    return TimeCode(0,0,0,0,0, n*int(t));
}

inline TimeCode operator/(const TimeCode &t, int n)
{
    return TimeCode(0,0,0,0,0, int(t)/n);
}

inline int operator%(const TimeCode &t, int n)
{
    return int(t)%n;
}

inline std::ostream& operator<<(std::ostream &os, const TimeCode &t)
{
    return os << std::setw(2) << std::setfill('0') << t.day << "/"
              << std::setw(2) << std::setfill('0') << t.month << "/"
              << std::setw(4) << std::setfill('0') << t.year << "T"
              << std::setw(2) << std::setfill('0') << t.hours << ":"
              << std::setw(2) << std::setfill('0') << t.minutes << ":"
              << std::setw(2) << std::setfill('0') << t.seconds << ":" << "Z";
}

std::istream& operator>>(std::istream &is, TimeCode &t);

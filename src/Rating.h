/*
 * File: Rating.h
 * Author: Diego Viteri
 *
 * Created on 15 April 2017, 18:02
 * Represents a simple rating.
 */
#pragma once
#include "TimeCode.h"

class Rating {
private:
    /*********  Private fields  **********/
    TimeCode t;
    std::string name, movie_title;
    int rating;
public:
    /*********  Constructors & Destructor  **********/
    Rating();
    Rating(const Rating& orig);
    Rating(TimeCode &t, std::string name, std::string movie_title, int rating);
    virtual ~Rating();

    /*********  Getters & Setters  **********/
    inline std::string get_title() const;
    inline int get_rating() const;
    inline TimeCode get_timecode() const;
    
    /*********  Operators overloading  **********/
    friend bool operator<(const Rating &r, const Rating &_r);
    friend bool operator>(const Rating &r, const Rating &_r);
    friend bool operator==(const Rating &r, const Rating &_r);
    friend bool operator!=(const Rating &r, const Rating &_r);
    friend std::ostream& operator<<(std::ostream &os, const Rating &r);
    
};

inline bool operator<(const Rating &r, const Rating &_r)
{
    //return std::tie(r.t, _r.name) < std::tie(r.t, _r.name);
    return r.t < _r.t;
}

inline bool operator>(const Rating &r, const Rating &_r)
{
    //return std::tie(r.t, _r.name) > std::tie(r.t, _r.name);
    return r.t > _r.t;
}

inline bool operator==(const Rating &r, const Rating &_r)
{
    return std::tie(r.t, _r.name) == std::tie(r.t, _r.name);
}

inline bool operator!=(const Rating &r, const Rating &_r)
{
    //return std::tie(r.t, _r.name) > std::tie(r.t, _r.name);
    return !(r == _r);
}

inline TimeCode Rating::get_timecode() const { return t;}

inline int Rating::get_rating() const {return rating;}

inline std::string Rating::get_title() const { return movie_title; }

inline std::ostream& operator<<(std::ostream &os, const Rating &r)
{
    return os << r.t << "," << std::quoted(r.name) << ","
	      << std::quoted(r.movie_title) << "," <<  r.rating
	      << std::endl;
}

std::istream& operator>>(std::istream &is, Rating &r);

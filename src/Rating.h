/*
 * File: Rating.h
 * Author: Diego Viteri
 *
 * Created on 15 April 2017, 18:02
 */
#pragma once
#include "TimeCode.h"

class Rating {
private:
    TimeCode t;
    std::string name, movie_title;
    int rating;
public:
    Rating();
    Rating(const Rating& orig);
    Rating(TimeCode &t, std::string name, std::string movie_title, int rating);
    virtual ~Rating();
    inline std::string get_title() const;
    inline int get_rating() const;
    inline TimeCode get_timecode() const;
    
    friend bool operator<(const Rating &r, const Rating &_r);
    friend bool operator>(const Rating &r, const Rating &_r);
    //inline bool operator()(const Rating* r, const Rating* _r) const;
    friend std::ostream& operator<<(std::ostream &os, const Rating &r);
    
};

inline bool operator<(const Rating &r, const Rating &_r)
{
    return r.t < _r.t;
}

inline bool operator>(const Rating &r, const Rating &_r)
{
    return r.t > _r.t;
}

/*
inline bool operator()(const Rating* r, const Rating* _r)
{
    return *r->t < *_r->t; 
}
*/
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

/* 
 * File:   MovieDatabase.h
 * Author: Didac
 *
 * Created on 11 April 2017, 14:29
 */
#pragma once

#include "Movie.h"

class MovieDatabase {
private:
    std::vector<Movie> movie_list;
public:
    MovieDatabase();
    MovieDatabase(const MovieDatabase& orig);
    MovieDatabase(std::vector<Movie> movie_list);
    virtual ~MovieDatabase();
    
    inline void add_movies(const std::vector<Movie> &_movie_list);
    inline void add_movie(Movie &movie);
    inline int size() const;
    inline bool empty() const;
    
    //friend std::istream& operator>>(std::istream &is, MovieDatabase &mdb);
    inline friend std::ostream& operator<<(std::ostream &os, const MovieDatabase &mdb);
    inline Movie operator[](int i) const;
};



inline void MovieDatabase::add_movies(const std::vector<Movie> &_movie_list)
{
    int i = 0;
    for (;i < _movie_list.size(); i++)
    {
        movie_list.push_back(_movie_list[i]);
    }
}

inline void MovieDatabase::add_movie(Movie &movie)
{
    movie_list.push_back(movie);
}

inline int MovieDatabase::size() const {return movie_list.size();}
inline bool MovieDatabase::empty() const {return movie_list.empty();}

inline Movie MovieDatabase::operator [](int i) const {return movie_list[i];}

//std::istream& operator>>(std::istream &is, /*MovieDatabase &mdb*/ const std::shared_ptr<MovieDatabase> &mdb);
std::istream& operator>>(std::istream &is, /*MovieDatabase &mdb*/ MovieDatabase* &mdb);

inline std::ostream& operator<<(std::ostream &os, /*const MovieDatabase &mdb*/ const MovieDatabase &mdb)
{
    int i =0;
    for (; i < mdb.size() ; i++)
    {
        os << mdb[i];
    }
    
    return os;
}


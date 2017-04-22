/* 
 * File:   MovieDatabase.h
 * Author: Didac
 *
 * Created on 11 April 2017, 14:29
 */
#pragma once
#include <set>
#include "Movie.h"
#include "Ratings.h"

class MovieDatabase
{
private:
    std::vector<Movie> movie_list;
public:
    MovieDatabase();
    MovieDatabase(const MovieDatabase& orig);
    MovieDatabase(std::vector<Movie> movie_list);
    virtual ~MovieDatabase();

    template<typename Criteria, typename Compare>
    Movie retrieve(int pos, const Compare& comp, const Criteria& c) const;

    template<typename Compare>
    Movie retrieve(int pos, const Compare& comp) const;
    
    template<typename Compare = std::less<Movie>>
    void sort_mdb(const Compare& comp = Compare());


    void apply_ratings(const Ratings &rs);
    inline void add_movies(const std::vector<Movie> &_movie_list);
    inline void add_movie(const Movie &movie);
    inline int size() const;
    inline bool empty() const;

    
    inline friend std::ostream& operator<<(std::ostream &os, const MovieDatabase &mdb);
    inline Movie operator[](int i) const;
};

template<typename Compare>
void MovieDatabase::sort_mdb(const Compare& comp)
{
    if (!movie_list.empty())
    {
	std::sort(movie_list.begin(), movie_list.end(), comp);
    }
    else
    {
	std::cerr << "ERROR: Movie Database is empty" << std::endl;
    }
}


template<typename Criteria, typename Compare>
Movie MovieDatabase::retrieve(int pos, const Compare& comp, const Criteria& c) const
{
    if (movie_list.empty()) throw "ERROR: Movie Database is empty\n";
    
    std::multiset<Movie, decltype(comp)> sorted_set(comp);

    for (auto movie : movie_list)
    {
	if(c(&movie)) sorted_set.insert(movie);
    }
	/*
    for(auto const& e : sorted_set) {
        std::cout << e;
	}*/
    std::set<Movie>::iterator it = sorted_set.begin();

    if(pos > 0) std::advance(it, pos);

    return *it;
	
}

template<typename Compare>
Movie MovieDatabase::retrieve(int pos, const Compare& comp) const
{
    if (movie_list.empty()) throw "ERROR: Movie Database is empty\n";
    
    std::multiset<Movie, decltype(comp)> sorted_set(comp);

    for (auto movie : movie_list)
    {
        sorted_set.insert(movie);
    }
	/*
    for(auto const& e : sorted_set) {
        std::cout << e;
	}*/
    std::set<Movie>::iterator it = sorted_set.begin();

    if(pos > 0) std::advance(it, pos);

    return *it;
	
}

inline void MovieDatabase::add_movies(const std::vector<Movie> &_movie_list)
{
    int i = 0;
    for (;i < _movie_list.size(); i++)
    {
        movie_list.push_back(_movie_list[i]);
    }
}

inline void MovieDatabase::add_movie(const Movie &movie)
{
    movie_list.push_back(movie);
}

inline int MovieDatabase::size() const {return movie_list.size();}
inline bool MovieDatabase::empty() const {return movie_list.empty();}

//inline Movie& MovieDatabase::operator [](int i){return movie_list[i];};
inline Movie MovieDatabase::operator [](int i) const {return movie_list[i];}

//std::istream& operator>>(std::istream &is, /*MovieDatabase &mdb*/ const std::shared_ptr<MovieDatabase> &mdb);
std::istream& operator>>(std::istream &is, /*MovieDatabase &mdb*/ MovieDatabase* &mdb);

inline std::ostream& operator<<(std::ostream &os, const MovieDatabase &mdb)
{
    for_each(mdb.movie_list.begin(), mdb.movie_list.end(),
      [&os](const Movie& m){ os << m; });
    //os << "TEST" << std::endl;
    //std::cout << mdb.movie_titles.size() << std::endl;
    //for(auto& p: mdb.movie_titles)
    //{
//	p.second.set_total_rating();
        //std::cout << " " << p.first << " => " << p.second;
    //  }
	
    return os;
}


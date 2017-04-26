/*
 * File:   MovieDatabase.h
 * Author: Diego Viteri
 *
 * Created on 11 April 2017, 14:29
 *
 * Implementation of a database of movies.
 * The current implementation uses a vector as a container for the movies.
 * However, I also considered using a set, having in mind that the database could grow large.
 * I tested both set and vector. It didn't cause much of a difference.
 * If the database were to be large, it will benefit from the set, as insertion and deletion
 * is log2(N).
 * MovieDatabase could be easily adapted to a set if the data was to grow.
 */
#pragma once
#include "MovieException.h"
#include "Movie.h"
#include "Ratings.h"

class MovieDatabase
{
  private:
    // Internal comparator, 
    std::function<bool(Movie, Movie)> comp = [](Movie const &m, Movie const &_m){return (m < _m);};
    std::vector<Movie> movie_list;
  public:
    /*********  Constructors & Destructor  **********/
    MovieDatabase();
    MovieDatabase(const MovieDatabase &orig);
    MovieDatabase(std::vector<Movie> movie_list);
    virtual ~MovieDatabase();

    /*********  Generic queries  **********/
    bool add_movie(const Movie &movie);
    void delete_movie(const Movie &movie);
    inline int size() const;
    inline bool empty() const;

    Movie find_by_title(const std::string &title) const;

    /*********  Extra queries  **********/
    void apply_ratings(const Ratings &rs);
    
    //template <typename Criteria, typename Compare>
    //Movie retrieve(int pos, const Compare &comp, const Criteria &crit) const;

    template <typename Compare>
    Movie retrieve(const Compare &comp) const;

    template <typename Criteria>
    MovieDatabase extract_to(MovieDatabase &mdb, const Criteria &criteria) const;

    template <typename Compare>
    void sort(const Compare &comp);

    /*********  Operator overloading  **********/
    typedef std::vector<Movie>::const_iterator const_iterator;
    inline friend std::ostream &operator<<(std::ostream &os, const MovieDatabase &mdb);
    inline Movie operator[](int i) const;
};

/**
 * 
 * 
 *
 */
template <typename Compare>
void MovieDatabase::sort(const Compare &comp)
{
    // Set internal comparator to be replaced by given one.
    this->comp = comp; 
    
    if (!movie_list.empty()){
        std::sort(movie_list.begin(), movie_list.end(), comp);
    } else {
        std::cerr << "Couldn't sort: Movie Database is empty" << std::endl;
    }
}

/**
 * Extracts movies from this database to another one based on a criteria.
 * An implementation with a multiset was an alternative to extract and then sort,
 * since a multiset would be ordered as elements are inserted.
 * A multiset can accept custom comparison with decltype(). 
 * This alternative was tried, however for the purpose of this coursework and the size of the data,
 * I decided to use what was suggested in the coursework sheet.
 */
template <typename Criteria>
MovieDatabase MovieDatabase::extract_to(MovieDatabase &mdb, const Criteria &criteria) const
{
    if (movie_list.empty())
        throw MovieException(std::string("Original movie Database is empty"));
    
    // For each movie in movie list
    // Add those that meet to criteria to mdb parameter
    for (auto it = movie_list.begin(); it != movie_list.end(); ++it){
        if (criteria(*it))
            mdb.add_movie(*it);
    }
    
    return mdb;
}

/**
 * Does a binary search on the vector of movies
 * Returns a movie based on the comparison.
 * A multiset was considered.
 * Both were tested, there isn't much difference based on given data.
 */
template <typename Comp>
Movie MovieDatabase::retrieve(const Comp &comp) const
{
    
    if (movie_list.empty())
        throw MovieException(std::string("ERROR: Movie Database is empty\n"));

    auto it = movie_list[0];
    int i = 0;
    for(; i < movie_list.size(); i++){
        if(comp(it, movie_list[i])){
            it = movie_list[i];
        }
    }

    return it;
    
    /*
    std::multiset<Movie, decltype(comp)> sorted_set(comp);

    for (auto movie : movie_list){
        sorted_set.insert(movie);
    }
    
    for(auto const& e : sorted_set) {
        std::cout << e;
	}
    std::set<Movie>::iterator it = sorted_set.begin();
    
    if (pos > 0)
        std::advance(it, pos);

    return *it;
    */
}

inline int MovieDatabase::size() const { return movie_list.size(); }
inline bool MovieDatabase::empty() const { return movie_list.empty(); }

inline Movie MovieDatabase::operator[](int i) const 
{ 
    if (movie_list.empty())
        throw MovieException(std::string("Movie Database is empty"));

    if (i < 0) {
        throw MovieException(std::string("Index provided negative"));
    } else if (i > movie_list.size()) {
        throw MovieException(std::string("Index provided too large"));
    }
    return movie_list[i]; 
}

inline std::ostream &operator<<(std::ostream &os, const MovieDatabase &mdb)
{
    for (auto m : mdb.movie_list){
        os << m;
    }
    return os;
}

std::istream &operator>>(std::istream &is, MovieDatabase *&mdb);
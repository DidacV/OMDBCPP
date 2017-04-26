/*
 * File: Ratings.h
 * Author: Diego Viteri
 *
 * Created on 15 April 2017, 13:57
 * Implementation of a collection of ratings.
 * Uses an unordered multimap as an associative container for the ratings.
 * This is because many ratings are mapped to one movie. It is very efficient
 * when adding applying ratings to movies due to fast look up times.
 */
#pragma once
#include <unordered_map>
#include <set>
#include "Rating.h"
#include "TimeCode.h"
class Ratings
{
private:
    /*********  Private structures  **********/
    std::unordered_multimap<std::string, Rating> rating_list;
    typedef std::unordered_multimap<std::string, Rating>::const_iterator const_iterator;
    typedef std::pair<const_iterator, const_iterator> pair_iterator; 
public:
    /*********  Constructors & Destructor  **********/
    Ratings();
    Ratings(const Ratings& orig);
    ~Ratings();

    /*********  Queries  **********/
    template<typename Compare>
    Rating retrieve(Compare comp, int pos = 0) const;
    
    inline void add_rating(const Rating &r);
    inline int size() const;
    inline bool empty() const;
    
    inline const_iterator begin();
    inline const_iterator end();
    inline const_iterator find(const std::string &key);
    inline pair_iterator find_multiple(const std::string &key) const;

    /*********  Overloading  **********/
    friend std::ostream& operator<<(std::ostream &os, const Ratings &rs);
};

/**
 * A multiset is used to dump the ratings in an ordered fashion
 * based on a custom comparison.
 * A sorted vector and binary search was considered but it was very slow.
 */
template<typename Compare>
Rating Ratings::retrieve(Compare comp, int pos) const
{
    if (rating_list.empty()) throw "ERROR: Rating list is empty";

    // Retrieving a rating using a multiset. Much faster than a
    // sorted vector. (See below for vector implementation)
    std::multiset <Rating, decltype(comp)> sorted_set(comp);
    for (auto bucket : rating_list) {
	    // bucket.second == rating
	    sorted_set.insert(bucket.second);
    }

    auto it = sorted_set.begin();

    if(pos > 0)
        std::advance(it, pos);
    
    return *it;

    // Vector implementation to retrieve a rating
    // Turned out to be much slower than a multiset.
    /*
    std::vector<Rating> sorted_ratings;
    
    for (auto bucket : rating_list){
        auto it = std::lower_bound(sorted_ratings.begin(), sorted_ratings.end(), bucket.second, comp);
        if (it == sorted_ratings.end() || bucket.second < *it){
            //std::cout << bucket.second << std::endl;
            sorted_ratings.insert(it, bucket.second);
        }
    }
    if (pos >= 0)
        return sorted_ratings[pos];
    */
}

inline bool Ratings::empty() const { return rating_list.empty(); }

inline Ratings::const_iterator Ratings::begin()
{
    return rating_list.begin();
}

inline Ratings::const_iterator Ratings::end()
{
    return rating_list.end();
}

inline Ratings::const_iterator Ratings::find(const std::string &key)
{
    //std::cout << "TEST" << std::endl;
    //std::cout << key << std::endl;
    return rating_list.find(key);
}

inline Ratings::pair_iterator Ratings::find_multiple(const std::string &key) const
{
    return rating_list.equal_range(key);
}

inline void Ratings::add_rating(const Rating &r)
{
    rating_list.insert({r.get_title(), r});
}

inline int Ratings::size() const {return rating_list.size();}
inline std::ostream& operator<<(std::ostream &os, const Ratings &rs)
{
    for(auto& p: rs.rating_list)
    {
	    os << p.second;
    }
    return os;
}

std::istream& operator>>(std::istream &is, Ratings* &rs);

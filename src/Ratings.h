/*
 * File: Ratings.h
 * Author: Diego Viteri
 *
 * Created on 15 April 2017, 13:57
 */
#pragma once
//#include <algorithm>
//#include <vector>
#include <unordered_map>
//#include <map>
//#include <set>
#include "Rating.h"
#include "TimeCode.h"
//#include "MovieDatabase.h"
class Ratings
{
private:
    std::unordered_multimap<std::string, Rating> rating_list;
public:
    Ratings();
    Ratings(const Ratings& orig);
    ~Ratings();
    typedef std::unordered_multimap<std::string, Rating>::const_iterator const_iterator;
    typedef std::pair<const_iterator, const_iterator> pair_iterator; 

    template<typename Compare>
    auto retrieve(int pos, Compare comp) const;
    
    inline void add_rating(const Rating &r);
    inline int size() const;
    inline bool empty() const;
    
    inline const_iterator begin();
    inline const_iterator end();
    inline const_iterator find(const std::string &key);
    inline pair_iterator find_multiple(const std::string &key) const;

//inline Rating operator[](int i) const;
    friend std::ostream& operator<<(std::ostream &os, const Ratings &rs);
};


template<typename Compare>
auto Ratings::retrieve(int pos, Compare comp) const
{
    if (rating_list.empty()) throw "ERROR: Rating list is empty";

    
    
    std::multiset <Rating, decltype(comp)> sorted_set(comp);
    for (auto bucket : rating_list)
    {
	    // second = rating
	sorted_set.insert(bucket.second);
    }

    /*
    for(auto const& e : sorted_set) {
        std::cout << e << '\n';
	}
    */
    std::set<Rating>::iterator it = sorted_set.begin();
    if(pos > 0) std::advance(it, pos);
    return *it;
  
    
    
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
	//p.second.set_total_rating();
        std::cout << " " << p.first << " => " << p.second;
	//os << p.second;
    }
    return os;
}

std::istream& operator>>(std::istream &is, Ratings* &rs);

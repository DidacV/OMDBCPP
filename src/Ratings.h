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
#include <set>
#include "Rating.h"
#include "TimeCode.h"
//#include "MovieDatabase.h"
class Ratings
{
private:
    //std::multiset<Rating, std::less<Rating>> rating_list;
    //std::vector<Rating> rating_list;
    //std::unordered_multimap<std::string, Rating> rating_list;
    std::unordered_multimap<std::string, Rating> rating_list;
    //std::map<std::pair<TimeCode, std::string>, Rating> rating_list;
public:
    Ratings();
    Ratings(const Ratings& orig);
    ~Ratings();
    //typedef std::map<std::pair<TimeCode, std::string>, Rating>::const_iterator const_iterator;
    typedef std::unordered_multimap<std::string, Rating>::const_iterator const_iterator;
    //typedef std::multiset<Rating>::const_iterator const_iterator;
    typedef std::pair<const_iterator, const_iterator> pair_iterator; 
    //const_iterator const_iterator
    
    //void apply_ratings(MovieDatabase &db);

    template<typename Compare = std::less<Rating>>
    Rating retrieve(Compare comp = Compare(), int pos = 0) const;
    
    inline void add_rating(const Rating &r);
    inline int size() const;

    //template<typename L, template C = std::less<Rating>>
    //Rating retrieve(/*Func& criteria,*/ int pos = 0) const;
    
    inline const_iterator begin();
    inline const_iterator end();
    inline const_iterator find(const std::string &key);
    inline pair_iterator find_multiple(const std::string &key) const;

//inline Rating operator[](int i) const;
    friend std::ostream& operator<<(std::ostream &os, const Ratings &rs);
};


template<typename Compare>
Rating Ratings::retrieve(Compare comp, int pos) const
{
    std::set <Rating, decltype(comp)> sorted_set(comp);
    for (auto bucket : rating_list)
    {
        // second = rating
        sorted_set.insert(bucket.second);
    }
    
    for(auto const& e : sorted_set) {
        std::cout << e << '\n';
    }
}

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
    /*
    if (!rating_list.empty())
    {
        auto values = rating_list.equal_range(r.get_title());
	for (auto it = values.first; it != values.second; it++)
	{
	    //std::cout << it->second << std::endl;
	    //std::cout << "o o " << it->second.get_timecode() << std::endl;
	    //std::cout << "o   " << r.get_timecode() << std::endl;
	    //std::cout << (r.get_timecode() > it->second.get_timecode());
	    if (it->second.get_timecode() > r.get_timecode())
	    { // <-- Here add your sorting criteria
		//std::cout << "less" << std::endl;
		//rating_list.emplace_hint(it,r.get_title(),r);
		rating_list.insert(it, {r.get_title(), r});
		return;
	    //return
	    }
	}
    }
    */
    //rating_list.emplace(r.get_title(),r);
    rating_list.insert({r.get_title(), r});

    
    //std::cout << "3 " << r << std::endl;
    //rating_list.push_back(r);
    //rating_list.insert({r.get_title(), r});
    //ratings[0] = r;
    //std::cout << "4 " << rating_list[0] << std::endl;
}

//inline Rating Ratings::operator [](int i) const {return rating_list[i];}

inline int Ratings::size() const {return rating_list.size();}
inline std::ostream& operator<<(std::ostream &os, const Ratings &rs)
{
    //int i = 0;
    //for (; i < rs.size(); i++)
    //{
	//os << rs[i];
    //}
    //std::cout << rs.rating_list.size() << std::endl;
    for(auto& p: rs.rating_list)
    {
	//p.second.set_total_rating();
        std::cout << " " << p.first << " => " << p.second;
	//os << p.second;
    }
    return os;
}

std::istream& operator>>(std::istream &is, Ratings* &rs);

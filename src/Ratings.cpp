/*
 * File: Ratings.h
 * Author: Diego Viteri
 *
 * Created on 15 April 2017, 13:57
 */

#include <sstream>
#include <iostream>
#include <vector>
#include <set>
//#include "MovieDatabase.h"
#include "Ratings.h"

using namespace std;

Ratings::Ratings()
{
    //cout << "new ratings" << endl;
}

Ratings::Ratings(const Ratings& orig)
{
}

Ratings::~Ratings()
{
    //cout << "ratings destroyed" << endl;
}


/*template<typename Func, template C = std::less<Rating>>*/
/*
Rating Ratings::retrieve(int pos) const
{
    int i = 0;
    set<Rating, greater<Rating>> sorted_ratings;

    for(auto bucket : rating_list)
    {
	//cout << "test" << endl;
	sorted_ratings.insert(bucket.second);
    }

    for (auto it = sorted_ratings.begin(); it != sorted_ratings.end(); ++it)
    {
        cout << (*it);
    }
    cout << sorted_ratings.size() << endl;
    // 1 for each key
    /*
    for (auto key_it = rating_list.begin(); key_it != rating_list.end(); ++key_it)
    {
    // 2 get bucket
	// get range
	sorted_ratings.insert();
	
	//cout << key_it->second;
	//auto bucket_it = rating_list.equal_range(key_it->first);
	//auto r = *std::min_element(rating_list.cbegin(i), rating_list.cend(i));
	//std::cout << r.second;
	i++;
    }
    */
    // 3 find smallest in bucket 
    //std::vector<Rating>;

    // 4 sort vector or find smallest timecode and 6

    // 5 get first item from vector

    // 6 put that into new vector 
    /*
    const_iterator it = rating_list.cbegin();

    Rating r = it->second;
    while(it != rating_list.cend())
    {
	//const_iterator nx = next(it, 1);
	if (criteria(it->second, next(it, 1)->second))
	    r = it->second;
    }
    return r;
}
    */



/*
void Ratings::apply_ratings(MovieDatabase &db)
{
    int i = 0;
    for (; i < db.size(); i++)
    {
	int count = 0;
	int total = 0;
	//auto it = rs.find(movie_list[i].get_title());
	//auto it = rs.end();
	
	auto values = rating_list.equal_range(db[i].get_title());
	for (auto it = values.first; it != values.second; it++)
	{
	    //cout << it->first << " " << it->second << endl;
	    //cout << "test" << endl;
	    count++;
	    total += it->second.get_rating();
	}
        db[i].set_rating(count, total);
    }
}
*/
istream& operator>>(istream &is, Ratings* &rs)
{
    string line;
    stringstream ss;

    while(getline(is, line))
    {
	//cout << line << endl;
	Rating r;
	line.append("\n");
	ss.str(line);
	ss >> r;
	//cout << r;
	rs->add_rating(r);
    }
    
    return is;
}

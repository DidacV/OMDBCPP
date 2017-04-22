/* 
 * File:   MovieDatabase.cpp
 * Author: Didac
 * 
 * Created on 11 April 2017, 14:29
 */

#include <sstream>
#include <regex>
#include <iostream>
#include <iterator>
#include <typeinfo>
#include <set>

#include "MovieDatabase.h"
#include "Rating.h"
//#include "Movie"

//#include "Ratings.h"
using namespace std;

MovieDatabase::MovieDatabase() {
}

MovieDatabase::MovieDatabase(const MovieDatabase& orig) {
}

MovieDatabase::~MovieDatabase() {
    //std::cout<<"db destroyed"<<std::endl;
}

void MovieDatabase::apply_ratings(const Ratings &rs)
{
    int i = 0;
    for (; i < movie_list.size(); i++)
    {
	int count = 0;
	int total = 0;
	auto values = rs.find_multiple(movie_list[i].get_title());
	for (auto it = values.first; it != values.second; it++)
	{
	    count++;
	    total += it->second.get_rating();
	}
        movie_list[i].set_rating(count, total);
    }
}


/*
template<typename Compare>
auto MovieDatabase::retrieve(Compare comp, int pos) const
{
    int i = 0;

    // Greater can be replaced by the lambda function
    // Type = what to retrieve? Movie or rating
    // Comparison = ascending or descending [](x, y){x.title < y.title}
    //
    // first = *db[0];
    //set<Type, Comparison(Type, Type)> sorted_set;
    //
    //set<Movie, [&](){return (movie_list[0].get_title() < movie_list[1].get_title());}> sorted_set;
    set<Movie, comp> sorted_set;

	for (auto movie : movie_list)
	{
	    sorted_set.insert(movie);
	}
    
    
    /*
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
    */
//}

std::istream& operator>>(std::istream &is, /*MovieDatabase &mdb*/ MovieDatabase* &mdb)
{
    // regex re(R"(,\s*(?=([^"]*"[^"]*")*[^"]*$))");
    string line;
    stringstream ss;
    //int i = 0;
    
    while(getline(is, line))
    {
	//cout << line << endl;
        //Movie *movie = new Movie;
	Movie movie;
        // line = regex_replace(line, re, "\n");
	line.append("\n");
        ss.str(line);
        ss >> movie;
        // check if the movie is empty
	mdb->add_movie(movie);
        //xdelete(movie);
    }
    
    return is;
}

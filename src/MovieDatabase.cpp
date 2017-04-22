/* 
 * File:   MovieDatabase.cpp
 * Author: Didac
 * 
 * Created on 11 April 2017, 14:29
 */

#include <sstream>
#include <iostream>
#include <iterator>
#include <vector>
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
    if (rs.empty()) {cerr<<"ERROR: Couldn't apply ratings because rating list is empty"<<endl; return; }
    
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


std::istream& operator>>(std::istream &is, MovieDatabase* &mdb)
{
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

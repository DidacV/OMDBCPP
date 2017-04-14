/* 
 * File:   MovieDatabase.cpp
 * Author: Didac
 * 
 * Created on 11 April 2017, 14:29
 */

#include <sstream>
#include <regex>
#include <iostream>
#include "MovieDatabase.h"

using namespace std;

MovieDatabase::MovieDatabase() {
}

MovieDatabase::MovieDatabase(const MovieDatabase& orig) {
}

MovieDatabase::~MovieDatabase() {
    std::cout<<"db destroyed"<<std::endl;
}

std::istream& operator>>(std::istream &is, /*MovieDatabase &mdb*/ MovieDatabase* &mdb)
{
    regex re(R"(,\s*(?=([^"]*"[^"]*")*[^"]*$))");
    string line;
    stringstream ss;
    int i = 0;
    
    while(getline(is, line))
    {
        Movie *movie = new Movie;
        line = regex_replace(line, re, "\n");
        line.append("\n");
        ss.str(line);
        ss >> *movie;
        // check if the movie is empty
        mdb->add_movie(*movie);
        delete(movie);
    }
    
    return is;
}

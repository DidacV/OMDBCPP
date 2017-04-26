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
#include "Ratings.h"

using namespace std;

Ratings::Ratings(){}

Ratings::Ratings(const Ratings& orig)
{
    rating_list = orig.rating_list;
}

Ratings::~Ratings()
{
    rating_list.clear();
}

istream& operator>>(istream &is, Ratings* &rs)
{
    string line;

    int lines_in_file = 0, ratings_added = 0; // Used for log
    while(getline(is, line))
    {
        lines_in_file++;
        line.append("\n");
        stringstream ss;
        ss.str(line);

        Rating r;
        ss >> r;
        if (!ss.fail()){
            rs->add_rating(r);
            ratings_added++;
        } else {
            cerr << "Failed to create rating. At line: " << lines_in_file << " from file." << endl;
            ss.clear();
        }
    }

    clog << "Ratings in file: " << lines_in_file << endl
         << "Ratings added: " << ratings_added << endl;
    return is;
}

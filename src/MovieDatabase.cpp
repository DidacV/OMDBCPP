/* 
 * File:   MovieDatabase.cpp
 * Author: Diego Viteri
 * 
 * Created on 11 April 2017, 14:29
 */

#include <algorithm>
#include <sstream>
#include <iostream>
#include <iterator>
#include <vector>
#include <set>

#include "MovieDatabase.h"
#include "Rating.h"
using namespace std;

MovieDatabase::MovieDatabase(){}

MovieDatabase::MovieDatabase(const MovieDatabase &orig)
{
    movie_list = orig.movie_list;
}

MovieDatabase::~MovieDatabase()
{
    movie_list.clear();
}

/**
 * Adds a movie to the vector of movies. Maintains a sorted vector
 * to check for duplicate movies using std::lower_bound().
 * For custom comparison, it uses an internal function, which is
 * reassigned when the vector is sorted. 
 * This is to maintain the sorting even after the database is sorted 
 * in a different order, and therefore be able to check duplicates.
 */
bool MovieDatabase::add_movie(const Movie &movie)
{
    auto it = std::lower_bound(movie_list.begin(), movie_list.end(), movie, comp);
    if (it == movie_list.end() || movie < *it){
        movie_list.insert(it, movie);
        return true;
    } else {
        std::cerr << "'"+movie.get_title()+"'" + " already in database" << std::endl;
        return false;
    }
}

/**
* Deletes a movie, using internal comparison to find a movie
* Tested with upper bound and lower bound, however equal range 
* seemed to be faster.
*/
void MovieDatabase::delete_movie(const Movie &_m)
{
    if (movie_list.empty()) return;
    
    auto pr = std::equal_range(movie_list.begin(), movie_list.end(), _m, comp);
    movie_list.erase(pr.first, pr.second);
}

/**
* Finds a movie by title. Could be improved further.
*/
Movie MovieDatabase::find_by_title(const std::string &field) const
{
    if (movie_list.empty())
        throw MovieException(string("Movie Database is empty"));
    

    // Use std::find_if and lambda to search specific field
    auto movie_found = find_if(begin(movie_list), end(movie_list),
                            [&field](const Movie &m) {
                                //quoted(field);
                                return (m.get_title() == field);
                            });
    if (movie_found != movie_list.end())
        return *movie_found;
    else
        throw MovieException(string(field + " not found. Make sure you spelt the title correctly"));

}

/**
* Applies the ratings of the movies from a ratings database.
* It maps the title's of the movies to those of the ratings
* Ratings sends the matched ratings and then they're applied
*/
void MovieDatabase::apply_ratings(const Ratings &rs)
{
    if (rs.empty())
    {
        cerr << "ERROR: Couldn't apply ratings because rating list is empty" << endl;
        return;
    }

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

/** Operator overload:
 *  Receives a file and adds a movie to the database.
 *  Logs how many movies should've been added and how many were added.
 */
std::istream &operator>>(std::istream &is, MovieDatabase *&mdb)
{
    string line;      // Each line of file

    int lines_in_file = 0, movies_added = 0; // Used for log

    // Loop through file and for each line, create a movie.
    // If the movie didn't create, it won't be added to database.
    while (getline(is, line))
    {
        lines_in_file++;
        line.append("\n");

        Movie movie;

        istringstream ss; // Stream to pass to movie
        ss.str(line);
        ss >> movie;
        if (!ss.fail() && !movie.get_title().empty()){
            if(mdb->add_movie(movie))
                movies_added++;
        } else {
            cerr << "Failed to create movie. At line: " << lines_in_file << " from file." << endl;
            ss.clear();
        }
    }

    clog << "Movies in file: " << lines_in_file << endl
         << "Movies added: " << movies_added << endl;

    return is;
}

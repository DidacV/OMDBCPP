/* 
 * File:   newmain.cpp
 * Author: Didac
 *
 * Created on 10 April 2017, 20:24
 */
#include <vector>
#include <fstream>
#include <iostream>
#include "MovieDatabase.h"
#include "Ratings.h"
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    ifstream db_file("res/movies.txt");
    ifstream ratings_file("res/ratings.txt");
    //shared_ptr<MovieDatabase> db_ptr;
    //db_ptr = make_shared<MovieDatabase>();
    
    MovieDatabase *db_ptr = new MovieDatabase();
    Ratings *r_ptr = new Ratings();
    if (db_file.is_open())
    {
        db_file >> db_ptr;
	ratings_file >> r_ptr;
    }
    //r_ptr->apply_ratings(*db_ptr);
    db_ptr->apply_ratings(*r_ptr);
    //cout << r_ptr->size();
    //cout << *r_ptr;
    //cout << *db_ptr;
    //db_ptr->sort_mdb([](Movie const &m, Movie const &_m){return (m.get_date() > _m.get_date());});
    //cout << *db_ptr;
    //auto l = [](Rating const &r, Rating const &_r){ return (r < _r);};

    auto l = [](Movie const &r, Movie const &_r){ return (r.get_title().size() > _r.get_title().size());};

    cout << db_ptr->retrieve(l);
    //r_ptr->retrieve(l);
    
    //Rating r = r_ptr->retrieve([](Rating &r, Rating &_r){ return (r < _r);});
    //*[](const pair<string, Rating> &p, const pair<string, Rating> &_p)*/
	
    //cout << r;	
    
    //cout << *r_ptr;
    //cout << db_ptr->empty() << endl;;
    //cout << db_ptr->size() << endl;;
    //cout << ((*db_ptr)[0] > (*db_ptr)[1]) << endl;
    
    delete(db_ptr);
    delete(r_ptr);
    
    return 0;
}


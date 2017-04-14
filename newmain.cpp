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
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    ifstream db_file("movies.txt");
    
    //shared_ptr<MovieDatabase> db_ptr;
    //db_ptr = make_shared<MovieDatabase>();
    MovieDatabase *db_ptr = new MovieDatabase;
    
    if (db_file.is_open())
    {
        db_file >> db_ptr;
    }
    cout << *db_ptr;
    cout << db_ptr->empty() << endl;;
    cout << db_ptr->size() << endl;;
    cout << ((*db_ptr)[0] > (*db_ptr)[1]) << endl;
    
    delete(db_ptr);
    
    return 0;
}


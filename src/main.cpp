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
    
    MovieDatabase *db_ptr = new MovieDatabase();
    Ratings *r_ptr = new Ratings();

    cout<<"//**************          Building Log           *****************//"<<endl;

    if (db_file.is_open()) { db_file >> db_ptr; }
    else { cerr<<"Couldn't open movies.txt in res/movies.txt"<<endl; return 0;}
  
    if (ratings_file.is_open()) { ratings_file >> r_ptr; db_ptr->apply_ratings(*r_ptr); }
    else {cerr<<"Couldn't open ratings.txt in res/ratings.txt"<<endl;}

    cout<<"//*************************************************************//"<<endl;
    cout<<"//**************             Task 1           *****************//"<<endl;
    cout<<"//*************************************************************//"<<endl; 
    // sort() accepts a custom comparison to change the sorting
    // E.g: auto comp = [](Movie const &m, Movie const &_m){ return (m > _m); };
    //db_ptr->sort(comp);
    //db_ptr->sort(); 
    // Database is already sorted by default. So no sorting required.
    cout << *db_ptr << endl;


    cout<<"//*************************************************************//"<<endl;
    cout<<"//**************             Task 2           *****************//"<<endl;
    cout<<"//*************************************************************//"<<endl;

    // Set criteria to extract with
    auto criteria_t2 = [](const Movie &m){
        return (m.get_genres().find("Film-Noir") != string::npos);
        };

    // Set comparison to sort by
    auto comparison_t2 = [](const Movie &m, const Movie &_m){
        return (m.get_duration() > _m.get_duration());
        };
    
    // Create new database where task will take place
    // then extract, sort and display
    MovieDatabase *mdb2 = new MovieDatabase();
    try{
        db_ptr->extract_to(*mdb2, criteria_t2);
        mdb2->sort(comparison_t2);
        cout << (*mdb2)[2] << endl;
    } catch (MovieException &me) {
        cerr << "Couldn't find movie: " << me.what() << endl;
    }
    // Free memory
    delete(mdb2);

    cout<<"//*************************************************************//"<<endl;
    cout<<"//**************             Task 3           *****************//"<<endl;
    cout<<"//*************************************************************//"<<endl;
    
    auto criteria_t3 = [](const Movie &m)
	               {return (m.get_genres().find("Sci-Fi") != string::npos);};
    auto comparison_t3 = [](const Movie &m, const Movie &_m)
	               {return (m.get_avg_rating() > _m.get_avg_rating());};
    
    MovieDatabase *mdb3 = new MovieDatabase();
    try{
        db_ptr->extract_to(*mdb3, criteria_t3);
        mdb3->sort(comparison_t3);
        cout << (*mdb3)[9] << endl;
    } catch (MovieException &me) {
         cerr << me.what() << endl; 
    }
    
    cout<<"//*************************************************************//"<<endl;
    cout<<"//**************             Task 4           *****************//"<<endl;
    cout<<"//*************************************************************//"<<endl;
    
    auto comparison_t4 = [](Movie const &m, Movie const &_m)
	               {return (m.get_avg_rating() < _m.get_avg_rating());};
    //int pos_t3; // 
    try { 
        cout << db_ptr->retrieve(comparison_t4) << endl;
    } catch (MovieException &me) { 
        cerr << me.what() << endl; 
    }
    
    cout<<"//*************************************************************//"<<endl;
    cout<<"//**************             Task 5           *****************//"<<endl;
    cout<<"//*************************************************************//"<<endl;
    
    auto comparison_t5 = [](Movie const &m, Movie const &_m)
	                 {return (m.get_title().size() < _m.get_title().size());};

    try {
        cout << db_ptr->retrieve(comparison_t5) << endl; 
    } catch (MovieException &me) {
        cerr << me.what() << endl; 
    }
    
    cout<<"//*************************************************************//"<<endl;
    cout<<"//**************             Task 6           *****************//"<<endl;
    cout<<"//*************************************************************//"<<endl;
    
    auto comparison_t6 = [](Rating const &r, Rating const &_r)
	                 {return (r < _r);};

    try {
        cout << r_ptr->retrieve(comparison_t6, 100) << endl; 
    } catch (MovieException &me) {
        cerr << me.what() << endl; 
    }
    
    // Info
    cout << "Movies in database: " << db_ptr->size() << endl;
    cout << "Number of ratings: " << r_ptr->size() << endl;
    delete(db_ptr);
    delete(r_ptr);
    
    return 0;
}


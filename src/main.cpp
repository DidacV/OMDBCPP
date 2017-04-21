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

    cout<<"//*************************************************************//"<<endl;
    cout<<"//**************             Task 1           *****************//"<<endl;
    cout<<"//*************************************************************//"<<endl; 
    // sort_mdb accepts a custom comparison to change the sorting  
    // E.g: auto comp = [](Movie const &m, Movie const &_m)        
    //                    {return (m.get_date() > _m.get_date());}
    //db_ptr->sort_mdb(comp);
    db_ptr->sort_mdb(); 
    cout << *db_ptr << endl;


    cout<<"//*************************************************************//"<<endl;
    cout<<"//**************             Task 2           *****************//"<<endl;
    cout<<"//*************************************************************//"<<endl;
    // retrieve accepts a criteria, a custom comparison (optional)
    // and a position (optional) 
    auto criteria_t2 = [](Movie *m)
	               {return (m->get_genres().find("Film-Noir") != string::npos);};
    auto comparison_t2 = [](Movie const &m, Movie const &_m)
	                 {return (m.get_duration() > _m.get_duration());};
    int pos_t2 = 2; // Third (0 index)

    cout << db_ptr->retrieve(pos_t2, comparison_t2, criteria_t2) << endl;

    
    cout<<"//*************************************************************//"<<endl;
    cout<<"//**************             Task 3           *****************//"<<endl;
    cout<<"//*************************************************************//"<<endl;
    auto criteria_t3 = [](Movie *m)
	               {return (m->get_genres().find("Sci-Fi") != string::npos);};
    auto comparison_t3 = [](Movie const &m, Movie const &_m)
	               {return (m.get_avg_rating() > _m.get_avg_rating());};
    int pos_t3 = 9; // Tenth (0 index)
    
    cout << db_ptr->retrieve(pos_t3, comparison_t3, criteria_t3) << endl;

    
    cout<<"//*************************************************************//"<<endl;
    cout<<"//**************             Task 4           *****************//"<<endl;
    cout<<"//*************************************************************//"<<endl;
    auto comparison_t4 = [](Movie const &m, Movie const &_m)
	               {return (m.get_avg_rating() > _m.get_avg_rating());};
    //int pos_t3; // 

    cout << db_ptr->retrieve(0, comparison_t4) << endl;

    
    cout<<"//*************************************************************//"<<endl;
    cout<<"//**************             Task 5           *****************//"<<endl;
    cout<<"//*************************************************************//"<<endl;
    auto comparison_t5 = [](Movie const &m, Movie const &_m)
	                 {return (m.get_title().size() > _m.get_title().size());};

    cout << db_ptr->retrieve(0, comparison_t5) << endl;

    cout<<"//*************************************************************//"<<endl;
    cout<<"//**************             Task 6           *****************//"<<endl;
    cout<<"//*************************************************************//"<<endl;
    auto comparison_t6 = [](Rating const &r, Rating const &_r)
	                 {return (r < _r);};

    cout << r_ptr->retrieve(100, comparison_t6) << endl;
    /****************************************/
    /****             Task 6           ******/
    /****************************************/
    auto comp = [](Movie const &r, Movie const &_r){ return (r.get_duration() > _r.get_duration());};

    //auto criteria = [](Movie *m){return (m->get_genres().find("Sci-Fi")!=string::npos);};

    auto criteria = [](Movie *m){return (m->get_date() == 1984);};
    //cout << db_ptr->retrieve(criteria);
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


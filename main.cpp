#include <stdlib.h>
#include <iostream>
#include <fstream>

#include "Movie.h"
#include "MovieDatabase.h"

using namespace std;

int main(int argc, const char * argv[])
{
    // Sort movies in ascending order of release date and display on the console
    
    // Display the third longest Film-Noir
    
    // Display the tenth highest rated Sci-Fi Movie
    
    // Display the highest rated movie
    
    // Display the movie with the longest title
    
    // Find the chronologically 101st rating
    
    ifstream dbFile ("movies.txt");
    string line;
    MovieDatabase db;
    if (dbFile.is_open())
    {
        dbFile >> db;
    }
    dbFile.close();
    return 0;
}
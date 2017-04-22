/* 
 * File:   Movie.cpp
 * Author: Didac
 * 
 * Created on 27 March 2017, 17:11
 */


#include <bitset>
#include <iostream>
#include <sstream>


#include "Movie.h"
/**
 * Constructs a movie with given parameters
 * @param _name of the movie
 * @param _date of when movie was made
 * @param _ageRating of the movie (PG-13)
 * @param _genres of the movie (Action/Adventure)
 */
using namespace std;
Movie::Movie(string title, int date, string age_rating, string genres, 
        int duration, int avg_rating, int no_of_ratings)
{
    // Ensure the data you get is correct
    // Name is a string, can hold any characters
    // date should only have 4 numbers
    // age rating could be checked against an enum
    // genres could be a 
    this->title = title;
    this->date = date;
    this->age_rating = age_rating;
    
    string genre;
    istringstream genre_stream;
    genre_stream.str(genres);
    while (getline(genre_stream, genre, '/'))
    {
        if(genre=="Action") this->genre.Action = true;
        if(genre=="Adventure") this->genre.Adventure = true;
        if(genre=="Animation") this->genre.Animation = true;
        if(genre=="Biography") this->genre.Biography = true;
        if(genre=="Comedy") this->genre.Comedy = true;
        if(genre=="Crime") this->genre.Crime = true;
        if(genre=="Drama") this->genre.Drama = true;
        if(genre=="Family") this->genre.Family = true;
        if(genre=="Fantasy") this->genre.Fantasy = true;
        if(genre=="Film-Noir") this->genre.FilmNoir = true;
        if(genre=="Horror") this->genre.Horror = true;
        if(genre=="Music") this->genre.Music = true;
        if(genre=="Musical") this->genre.Musical = true;
        if(genre=="Mystery") this->genre.Mystery = true;
        if(genre=="Romance") this->genre.Romance = true;
        if(genre=="Sci-Fi") this->genre.SciFi = true;
        if(genre=="Thriller") this->genre.Thriller = true;
        if(genre=="War") this->genre.War = true;
        if(genre=="Western") this->genre.Western = true;
    }
    
    this->duration = duration;
    this->avg_rating = avg_rating;
    this->no_of_ratings = no_of_ratings;
}

Movie::Movie()
{
    
}

/**
 * Destructor
 */
Movie::~Movie() 
{
    //std::cout << "movie destroyed" << std::endl;
}

istream& operator>>(istream &input, Movie &movie)
{
    int date, duration, avg_rating, total_rating;
    string name, ageRating, genres;
    char c;
    
    if(input >> quoted(name) >> c >> date >> c)
    {
        if (input >> quoted(ageRating) >> c >> quoted(genres) >> c)
        {
            if (input >> duration >> c >> avg_rating >> c >> total_rating)
            {
                movie = Movie(name, date, ageRating, genres, duration, avg_rating, total_rating);
            }
        }
    } else {
        input.clear(ios_base::failbit);
    }
    return input;
}






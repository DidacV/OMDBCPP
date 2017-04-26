/* 
 * File:   Movie.cpp
 * Author: Diego Viteri
 * 
 * Created on 27 March 2017, 17:11
 */
#include <bitset>
#include <iostream>
#include <sstream>
#include "MovieException.h"
#include "Movie.h"

using namespace std;

Movie::Movie() {}

Movie::Movie(const Movie &orig)
{
    this->title = orig.title;
    this->date = orig.date;
    this->age_rating = orig.age_rating;
    this->genre = orig.genre;
    this->duration = orig.duration;
    this->avg_rating = orig.avg_rating;
    this->no_of_ratings = orig.no_of_ratings;
}

/** Constructs a movie with given parameters
 * Throws exception if it's not the correct date
 * Or any of the bit fields are not set
 */
Movie::Movie(string title, int date, string age_rating, string genres,
             int duration, float avg_rating, int no_of_ratings)
{
    this->title = title;
    // Simple check to see if it's a valid date.
    // Could check against current year if sensible.
    if (date < 1800 || date > 9999)
        throw MovieException(string("Invalid date."));
        //throw "ERROR: Couldn't create '" + title + "'. Invalid date.";
    this->date = date;

    // SETTING AGE RATING. Will throw an exception if it wasn't set
    bool rating_set = false; // To see if a rating has been set
    if (age_rating == "PG-13")
    {
        this->age_rating.PG13 = true;
        rating_set = true;
    }
    if (age_rating == "R")
    {
        this->age_rating.R = true;
        rating_set = true;
    }
    if (age_rating == "PG")
    {
        this->age_rating.PG = true;
        rating_set = true;
    }
    if (age_rating == "N/A")
    {
        this->age_rating.NA = true;
        rating_set = true;
    }
    if (age_rating == "NOT RATED")
    {
        this->age_rating.NR = true;
        rating_set = true;
    }
    if (age_rating == "UNRATED")
    {
        this->age_rating.UR = true;
        rating_set = true;
    }
    if (age_rating == "PASSED")
    {
        this->age_rating.PASS = true;
        rating_set = true;
    }
    if (age_rating == "G")
    {
        this->age_rating.G = true;
        rating_set = true;
    }
    if (age_rating == "APPROVED")
    {
        this->age_rating.APPR = true;
        rating_set = true;
    }
    if (age_rating == "M")
    {
        this->age_rating.M = true;
        rating_set = true;
    }
    if (age_rating == "X")
    {
        this->age_rating.X = true;
        rating_set = true;
    }
    if (age_rating == "TV-14")
    {
        this->age_rating.TV14 = true;
        rating_set = true;
    }
    if (!rating_set)
        throw MovieException(string("Age rating " + age_rating + " doesn't exist."));

    string genre;
    istringstream genre_stream;
    genre_stream.str(genres);
    while (getline(genre_stream, genre, '/'))
    {
        bool genre_set = false;
        if (genre == "Action")
        {
            this->genre.Action = true;
            genre_set = true;
        }
        if (genre == "Adventure")
        {
            this->genre.Adventure = true;
            genre_set = true;
        }
        if (genre == "Animation")
        {
            this->genre.Animation = true;
            genre_set = true;
        }
        if (genre == "Biography")
        {
            this->genre.Biography = true;
            genre_set = true;
        }
        if (genre == "Comedy")
        {
            this->genre.Comedy = true;
            genre_set = true;
        }
        if (genre == "Crime")
        {
            this->genre.Crime = true;
            genre_set = true;
        }
        if (genre == "Drama")
        {
            this->genre.Drama = true;
            genre_set = true;
        }
        if (genre == "Family")
        {
            this->genre.Family = true;
            genre_set = true;
        }
        if (genre == "Fantasy")
        {
            this->genre.Fantasy = true;
            genre_set = true;
        }
        if (genre == "Film-Noir")
        {
            this->genre.FilmNoir = true;
            genre_set = true;
        }
        if (genre == "History")
        {
            this->genre.History = true;
            genre_set = true;
        }
        if (genre == "Horror")
        {
            this->genre.Horror = true;
            genre_set = true;
        }
        if (genre == "Music")
        {
            this->genre.Music = true;
            genre_set = true;
        }
        if (genre == "Musical")
        {
            this->genre.Musical = true;
            genre_set = true;
        }
        if (genre == "Mystery")
        {
            this->genre.Mystery = true;
            genre_set = true;
        }
        if (genre == "Romance")
        {
            this->genre.Romance = true;
            genre_set = true;
        }
        if (genre == "Sci-Fi")
        {
            this->genre.SciFi = true;
            genre_set = true;
        }
        if (genre == "Thriller")
        {
            this->genre.Thriller = true;
            genre_set = true;
        }
        if (genre == "War")
        {
            this->genre.War = true;
            genre_set = true;
        }
        if (genre == "Western")
        {
            this->genre.Western = true;
            genre_set = true;
        }
        if (!genre_set)
            throw MovieException(string("Genre " + genre + " doesn't exist."));
    }

    this->duration = duration;
    this->avg_rating = avg_rating;
    this->no_of_ratings = no_of_ratings;
}

/**
 * Destructor
 */
Movie::~Movie(){}

istream &operator>>(istream &input, Movie &movie)
{
    int date, duration, total_rating;
    float avg_rating;
    string title, ageRating, genres;
    char c;

    // Checks if the inputs are correct, then tries to create a movie
    if (input >> quoted(title) >> c >> date >> c >> quoted(ageRating) >> c >> quoted(genres) >> c >> duration >> c >> avg_rating >> c >> total_rating){
        try{
            movie = Movie(title, date, ageRating, genres, duration, avg_rating, total_rating);
        } catch (const MovieException &me) {
            cerr << "Error: Failed to create " + title + ": " + me.what() << endl;
        }
    } else {
        input.clear(ios_base::failbit);
    }

    return input;
}


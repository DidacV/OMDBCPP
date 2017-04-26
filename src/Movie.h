/* 
 * File:   Movie.h
 * Author: Diego Viteri
 *
 * Created on 27 March 2017, 17:11
 * Represents a movie. Makes use of bitfields to represent
 * genres and age ratings. Overloads a set of operators which
 * were considered appropiate. However, this could easily be extended.
 */
#pragma once
#include <iomanip>

class Movie
{
  private:
    /*********  Private fields  **********/
    std::string title;
    float avg_rating;
    int date, duration, no_of_ratings;
    
    /*********  Private structures  **********/
    struct Genres // Bit field representing the genres
    {
        bool Action : 1, Adventure : 1, Fantasy : 1,
            Comedy : 1, Drama : 1, War : 1,
            Music : 1, Romance : 1, Western : 1,
            Mystery : 1, Thriller : 1, SciFi : 1,
            Animation : 1, Family : 1, Biography : 1,
            History: 1, Horror : 1, Musical : 1,
            Crime : 1, FilmNoir : 1;
    };
    Genres genre = {0};
    struct Age_ratings // Bit field representing age ratings
    {
        bool PG13 : 1, R : 1, PG : 1,
            NA : 1, NR : 1, UR : 1,
            PASS : 1, G : 1, APPR : 1,
            M : 1, X : 1, TV14 : 1;
    };
    Age_ratings age_rating = {0};

  public:
    /*********  Constructors & Destructor  **********/
    Movie();
    Movie(const Movie &orig);
    Movie(std::string title, int date, std::string age_rating, std::string genres,
          int duration, float avg_rating, int total_rating);
    virtual ~Movie();

    /*********  Getters & Setters  **********/
    inline std::string get_title() const;
    inline int get_date() const;
    inline std::string get_age_rating() const;
    inline std::string get_genres() const;
    inline int get_duration() const;
    inline float get_avg_rating() const;
    inline int get_no_of_ratings() const;

    inline void set_rating(const int &count, const int &total);
    /*********  Operators overloading  **********/
    friend bool operator>(const Movie &m, const Movie &_m);
    friend bool operator<(const Movie &m, const Movie &_m);
    friend bool operator==(const Movie &m, const Movie &_m);
    friend bool operator!=(const Movie &m, const Movie &_m);
    friend std::ostream &operator<<(std::ostream &os, const Movie &movie);
};

/** @return name of the movie */
inline std::string Movie::get_title() const { return title; }

/** @return date of the movie */
inline int Movie::get_date() const { return date; }

/** @return age rating of the movie */
inline std::string Movie::get_age_rating() const
{
    std::string age_rating_out;
    if (age_rating.PG13)
        age_rating_out.assign("PG-13");
    if (age_rating.R)
        age_rating_out.assign("R");
    if (age_rating.PG)
        age_rating_out.assign("PG");
    if (age_rating.NA)
        age_rating_out.assign("N/A");
    if (age_rating.NR)
        age_rating_out.assign("NOT RATED");
    if (age_rating.UR)
        age_rating_out.assign("UNRATED");
    if (age_rating.PASS)
        age_rating_out.assign("PASSED");
    if (age_rating.G)
        age_rating_out.assign("G");
    if (age_rating.APPR)
        age_rating_out.assign("APPROVED");
    if (age_rating.M)
        age_rating_out.assign("M");
    if (age_rating.X)
        age_rating_out.assign("X");
    if (age_rating.TV14)
        age_rating_out.assign("TV-14");
    return age_rating_out;
}

/** @return genres of the movie delimited by '/' */
inline std::string Movie::get_genres() const
{
    std::string genres_list;
    if (genre.Action)
        genres_list.append("Action/");
    if (genre.Adventure)
        genres_list.append("Adventure/");
    if (genre.Animation)
        genres_list.append("Animation/");
    if (genre.Biography)
        genres_list.append("Biography/");
    if (genre.Comedy)
        genres_list.append("Comedy/");
    if (genre.Crime)
        genres_list.append("Crime/");
    if (genre.Drama)
        genres_list.append("Drama/");
    if (genre.Family)
        genres_list.append("Family/");
    if (genre.Fantasy)
        genres_list.append("Fantasy/");
    if (genre.FilmNoir)
        genres_list.append("Film-Noir/");
    if (genre.Horror)
        genres_list.append("Horror/");
    if (genre.Music)
        genres_list.append("Music/");
    if (genre.Musical)
        genres_list.append("Musical/");
    if (genre.Mystery)
        genres_list.append("Mystery/");
    if (genre.Romance)
        genres_list.append("Romance/");
    if (genre.SciFi)
        genres_list.append("Sci-Fi/");
    if (genre.Thriller)
        genres_list.append("Thriller/");
    if (genre.War)
        genres_list.append("War/");
    if (genre.Western)
        genres_list.append("Western/");

    genres_list.pop_back();
    return genres_list;
}

/** @return duration of the movie */
inline int Movie::get_duration() const { return duration; }

/** @return average rating of the movie */
inline float Movie::get_avg_rating() const { return avg_rating; }

/** @return number of ratings of the movie */
inline int Movie::get_no_of_ratings() const { return no_of_ratings; }

/** Sets rating of movie. To be called by MovieDatabase's apply_ratings **/
inline void Movie::set_rating(const int &count, const int &total)
{
    no_of_ratings = count;
    avg_rating = (float)total / (float)count;
}

inline bool operator>(const Movie &m, const Movie &_m) 
{ 
    return std::tie(m.date, m.title) > std::tie(_m.date, _m.title);
}

inline bool operator<(const Movie &m, const Movie &_m) 
{ 
    return std::tie(m.date, m.title) < std::tie(_m.date, _m.title);
}

inline bool operator==(const Movie &m, const Movie &_m)
{ 
    return (m.title == _m.title); 
}
inline bool operator!=(const Movie &m, const Movie &_m) 
{ 
    return !(m == _m); 
}

inline std::ostream &operator<<(std::ostream &os, const Movie &movie)
{
    return os << std::quoted(movie.title) << ','
                  << movie.date << ','
                  << std::quoted(movie.get_age_rating()) << ','
                  << std::quoted(movie.get_genres()) << ','
                  << movie.duration << ','
                  << std::setprecision(2) << std::fixed << movie.avg_rating << ','
                  << movie.no_of_ratings << std::endl;
}

std::istream &operator>>(std::istream &input, Movie &m);
/* 
 * File:   Movie.h
 * Author: Didac
 *
 * Created on 27 March 2117, 17:11
 */
#pragma once
#include <iomanip>

class Movie {
private:
    struct Genres 
    { 
    bool Action : 1, Adventure : 1, Fantasy : 1, 
         Comedy : 1, Drama : 1, War : 1,
         Music : 1, Romance : 1, Western : 1,
         Mystery : 1, Thriller : 1, SciFi : 1, // Careful with Sci-Fi
         Animation : 1, Family : 1, Biography : 1,
         Horror : 1, Musical : 1, Crime : 1,
         FilmNoir : 1;
    };
    Genres genre = {0};
    std::string title, age_rating;
    int date, duration, avg_rating, no_of_ratings;
public:
    inline std::string get_title() const;
    inline int get_date() const;
    inline std::string get_age_rating() const;
    inline std::string get_genres() const;
    inline int get_duration() const;
    inline int get_avg_rating() const;
    inline int get_no_of_ratings() const;
    inline void set_rating(const int &count, const int &total);
    //inline void add_total_rating(); 
    //Movie(const Movie& orig);

    friend bool operator>(const Movie &m_a, const Movie &m_b);
    friend bool operator<(const Movie &m_a, const Movie &m_b);
    Movie();
    Movie(std::string title, int date, std::string age_rating, std::string genres, 
        int duration, int avg_rating, int total_rating);
    friend std::ostream& operator << (std::ostream &is, const Movie &movie);
    virtual ~Movie();

};

/** @return name of the movie */
inline std::string Movie::get_title() const{ return title; }

/** @return date of the movie */
inline int Movie::get_date() const { return date; }

/** @return age rating of the movie */
inline std::string Movie::get_age_rating() const { return age_rating; }

/** @return genres of the movie */
inline std::string Movie::get_genres() const 
{ 
    std::string genres_list;
    if(genre.Action) genres_list.append("Action/");
    if(genre.Adventure) genres_list.append("Adventure/");
    if(genre.Animation) genres_list.append("Animation/");
    if(genre.Biography) genres_list.append("Biography/");
    if(genre.Comedy) genres_list.append("Comedy/");
    if(genre.Crime) genres_list.append("Crime/");
    if(genre.Drama) genres_list.append("Drama/");
    if(genre.Family) genres_list.append("Family/");
    if(genre.Fantasy) genres_list.append("Fantasy/");
    if(genre.FilmNoir) genres_list.append("Film-Noir/");
    if(genre.Horror) genres_list.append("Horror/");
    if(genre.Music) genres_list.append("Music/");
    if(genre.Musical) genres_list.append("Musical/");
    if(genre.Mystery) genres_list.append("Mystery/");
    if(genre.Romance) genres_list.append("Romance/");
    if(genre.SciFi) genres_list.append("Sci-Fi/");
    if(genre.Thriller) genres_list.append("Thriller/");
    if(genre.War) genres_list.append("War/");
    if(genre.Western) genres_list.append("Western/");
    
    genres_list.pop_back();
    return genres_list;
}

/** @return duration of the movie */
inline int Movie::get_duration() const { return duration; }

inline int Movie::get_avg_rating() const { return avg_rating; }

inline int Movie::get_no_of_ratings() const{ return no_of_ratings; }

/** Sets rating of movie. To be called by MovieDatabase's apply_ratings **/
inline void Movie::set_rating(const int &count, const int &total)
{
    // how many and total
    //std::cout << count << " " << total << std::endl;
    no_of_ratings = count;
    avg_rating = total / count;
}

inline bool operator>(const Movie &m_a, const Movie &m_b) {return (m_a.date > m_b.date);}

inline bool operator<(const Movie &m_a, const Movie &m_b) {return (m_a.date < m_b.date);}

inline std::ostream& operator<<(std::ostream &output, const Movie &movie)
{
    // put "" between name, age rating, genres
    
    // put commas between each element
    char comma = ',';
    return output << std::quoted(movie.title) << comma
                    << movie.date << comma
                    << std::quoted(movie.age_rating) << comma
                    << std::quoted(movie.get_genres()) << comma
                    << movie.duration << comma
                    << movie.avg_rating << comma
                    << movie.no_of_ratings << std::endl;
}

std::istream& operator>>(std::istream &input, Movie &m);

#include <stdexcept>
#pragma once

class MovieException : public std::runtime_error
{
    public:
        MovieException(std::string s) : std::runtime_error(s) {}
};
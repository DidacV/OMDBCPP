/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StringSplitter.h
 * Author: Didac
 *
 * Created on 09 April 2017, 13:06
 */

#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#ifndef STRINGSPLITTER_H
#define STRINGSPLITTER_H

class StringSplitter
{
public:
    static std::vector<std::string> split(const std::string &s, char delim) {
        std::vector<std::string> elems;
        //split(s, delim, std::back_inserter(elems));
        return elems;
    }
};
#endif /* STRINGSPLITTER_H */


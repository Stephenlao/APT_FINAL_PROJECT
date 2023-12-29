#ifndef RATING_H
#define RATING_H

#include <vector>
#include<iostream>
#include <string>
#include <stdexcept>
using std::cout;
class Rating {
private:
    std::vector<int>* scores;
    std::vector<std::string>* comments;

public:
    Rating(std::vector<int>* scoresPtr = {}, std::vector<std::string>* commentsPtr = {});
    ~Rating(); 
    void addRating(int score, const std::string& comment);
    void displayRating();
    float avgRating() const;

};

#endif // RATING_H
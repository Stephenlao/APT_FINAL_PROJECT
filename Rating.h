#ifndef RATING_H
#define RATING_H

#include <vector>
#include<iostream>
#include <string>
#include <stdexcept>
using std::cout;
class Rating {
private:
    int score;
    std::string comment;

public:
    Rating(int scoresPtr = 0, std::string commentsPtr = "");
    // ~Rating(); 
    // void addRating(int score, const std::string& comment);
    // void displayRating();
    int getScore();
    std::string getComment();
    // float avgRating() const;

};

#endif // RATING_H

#ifndef RATING_H
#define RATING_H

#include <vector>
#include<iostream>
#include <string>
#include <stdexcept>
using std::cout;
class Rating {
private:
    float score;
    std::string comment;

public:
    Rating(float scoresPtr = 0, std::string commentsPtr = "");
    // ~Rating(); 
    // void addRating(int score, const std::string& comment);
    // void displayRating();
    float getScore();
    std::string getComment();
    // float avgRating() const;
    static void insertRating(std::string& line, const std::string& ratingTag, const std::string& ratingString);


};

#endif // RATING_H

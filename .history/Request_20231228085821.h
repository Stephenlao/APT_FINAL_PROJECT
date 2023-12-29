#ifndef REQUEST_H
#define REQUEST_H

#include <vector>
#include<iostream>
#include <string>
#include <stdexcept>
using std::cout;
class Request {
private:
    string hostName;
    std::vector<std::string>* comments;

public:
    Rating(std::vector<int>* scoresPtr = {}, std::vector<std::string>* commentsPtr = {});
    ~Rating(); 
    void addRating(int score, const std::string& comment);
    void displayRating();
    float avgRating() const;

};

#endif // REQUEST_H
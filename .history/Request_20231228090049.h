#ifndef REQUEST_H
#define REQUEST_H

#include <vector>
#include<iostream>
#include <string>
#include <stdexcept>
using std::cout;
using std::string;
class Request {
private:
    string hostName;
    string supporterName;
    string status;

public:
    
    void addRating(int score, const std::string& comment);
    void displayRating();
    float avgRating() const;

};

#endif // REQUEST_H
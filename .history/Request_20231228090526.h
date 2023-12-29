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
    string skill;
    string status;

public:
    Request(string hostName = "", string supporterName  = "", string skill = "", string status = "");
    void acceptRequest();
    void rejectRequest();
    void checkRequestStatus();

};

#endif // REQUEST_H
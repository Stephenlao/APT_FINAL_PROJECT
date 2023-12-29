#ifndef REQUEST_H
#define REQUEST_H

#include<iostream>
#include <string>
using std::cout;
using std::string;
class Request {
private:
    string requestID;
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
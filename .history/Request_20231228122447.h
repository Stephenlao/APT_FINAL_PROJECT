#ifndef REQUEST_H
#define REQUEST_H

#include<iostream>
#include <string>
using std::cout;
using std::string;
class Request {
private:
    string requestID;
    string hostID;
    string supporterID;
    string skill;
    enum status {Accepted, Rejected, Pending};

public:
    Request(string requestID = "", string hostID  = "", string supporterID, string skill = "", string status = "");
    void acceptRequest();
    void rejectRequest();
    void checkRequestStatus();

};

#endif // REQUEST_H
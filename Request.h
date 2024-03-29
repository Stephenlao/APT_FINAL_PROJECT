#ifndef REQUEST_H
#define REQUEST_H

#include "User.h"
#include<iostream>
#include <string>
using std::cout;
using std::string;
class Request {
private:
    string requestID;
    string hostID;
    string supporterID;
    string date;
    string skill;
    enum status {Accepted, Rejected, Pending};

public:
    Request(string requestID = "", string hostID  = "", string supporterID = "", string date = "" , string skill = "");
    void setStatus(status newStatus);
    void saveRequestDataToFile(string hostID, string supporterID, string skill, string timePeriod);
    bool isFileEmpty(std::ifstream &pfile);
    string getRequestID();
    void setRequestID(string requestID_val);
    void acceptRequest();
    void rejectRequest();
    void checkRequestStatus();

};

#endif // REQUEST_H
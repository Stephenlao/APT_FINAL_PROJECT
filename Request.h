#ifndef REQUEST_H
#define REQUEST_H

#include <iostream>
#include <string>
#include <vector>
using std::string;

class Request
{
public: 
    enum Status { Accepted, Rejected, Pending};

private:
    string requestID;
    string requestSkill;
    string hostID;
    string supporterID;
    string hostRating;
    string skillRating;
    string supportRating;
    std::vector<Request> bookingHistory; // Assume a vector to store booking history
    std::vector<Request> requestHistory;
    Status status; // Declaration of the status member

public:
    Request(std::string hostID ="", std::string supporterID ="", std::string requestID ="", 
    std::string requestSkill ="", std::string hostRating ="", std::string skillRating ="", std::string supportRating ="", Status status = Pending);
    void createRequest();
    void acceptRequest(std::string supporterID, std::string requestID);
    void rejectRequest(std::string supporterID, std::string hostID, std::string requestID);
    //void checkRequestStatus();

    void viewRequestHistory();
    void viewBookingHistory(std::string hostID);
};
#endif //REQUEST_H



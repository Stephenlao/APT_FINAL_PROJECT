#include "Request.h"
#include <iostream>
#include <string>
using std::string;

Request::Request(std::string hostID, std::string supporterID, std::string requestID, std::string requestSkill, 
    std::string hostRating, std::string skillRating, std::string supportRating, Status status)
    : hostID(hostID), supporterID(supporterID),requestID(requestID), requestSkill(requestSkill),
    hostRating(hostRating), skillRating(skillRating), supportRating(supportRating), status(status){}

void Request::viewRequestHistory() {
    // Filter the requests based on the supporter ID
}

void Request::viewBookingHistory(std::string hostID) {
    // Filter the requests based on the host ID
    std::vector<Request> filteredRequests;
    for (const auto& request : requestHistory) {
        if (request.hostID == hostID) {
            filteredRequests.push_back(request);
        }
    }
    // Print the filtered requests
    if (filteredRequests.empty()) {
        std::cout << "No booking history found for host ID: " << hostID << std::endl;
    } else {
        std::cout << "Booking history for host ID " << hostID << ":" << std::endl;
        for (const auto& request : filteredRequests) {
            // Print request details
        }
    }
}

void Request::createRequest() {
    // Logic to create a new request
}

void Request::acceptRequest(std::string supporterID, std::string requestID) {
    for (auto& request : requestHistory) {
        if (request.requestID == requestID) {
            if (request.status == Pending) {
                request.status = Accepted;
                std::cout << "Request with ID " << requestID << " has been accepted." << std::endl;
            } 
            return;
        }
    }
    std::cout << "Request with ID " << requestID << " not found." << std::endl;
}

void Request::rejectRequest(std::string supporterID, std::string hostID,std::string requestID) {
        for (auto& request : requestHistory) {
        if (request.requestID == requestID) {
            if (request.status == Pending) {
                request.status = Rejected;
                std::cout << "Request with ID " << requestID << " has been rejected." << std::endl;
            } else if (request.status == Accepted){
                std::cout << "The supporter has already accepted the request. The host cannot cancel the request anymore." << std::endl;
            }
            return;
        }
    }
    std::cout << "Request with ID " << requestID << " not found." << std::endl;
}


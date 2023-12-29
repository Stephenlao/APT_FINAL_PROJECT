#include <fstream>
#include <sstream>
#include "Request.h"
#include "User.h"
using std::fstream;
using std::string;
using std::getline;


Request::Request(string requestID_val ,string hostID_val, string supporterID_val, string skill_val)
    : requestID(requestID_val) ,hostID(hostID_val), supporterID(supporterID_val), skill(skill_val){};

void Request::createRequest(User& host, User& supporter){
    fstream myFile;
    myFile.open("requests.dat", std::ios::in);
    if (myFile.is_open())
    {
        
    }
}

void Request::setStatus(status newStatus){

}
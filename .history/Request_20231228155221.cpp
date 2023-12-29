#include <fstream>
#include <sstream>
#include "Request.h"
#include "User.h"
using std::fstream;
using std::string;
using std::getline;
using std::ifstream;


Request::Request(string requestID_val ,string hostID_val, string supporterID_val, string skill_val)
    : requestID(requestID_val) ,hostID(hostID_val), supporterID(supporterID_val), skill(skill_val){};

void Request::createRequest(User& host, User& supporter){
    fstream myFile;
    myFile.open("requests.dat", std::ios::app | std::ios::out);
    if (myFile.is_open())
    {
        std::ifstream inFile("requests.dat");
        if (User.isFileEmpty(inFile))
        {
            myFile << "requestID,hostID,\n";
        }
        inFile.close();
    }
}

void Request::setStatus(status newStatus){

}
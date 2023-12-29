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
        if (isFileEmpty(inFile))
        {
            myFile << "requestID,hostID,supporterID,Skill,status\n";
        }
        inFile.close();

       srand(time(NULL));             // Seed for random number generation
       int randomID = rand() % 10000; // Generate a random number
       string requestID = Request::getRe();
       requestID = "R" + std::to_string(randomID);
       Request::setRequestId(requestId);
    }
}

void Request::setRequestID(string requestID_val){
    this->requestID = requestID_val;
}

void Request::setStatus(status newStatus){

}

bool Request::isFileEmpty(std::ifstream &pfile)
{
    return pfile.peek() == std::fstream::traits_type::eof();
}
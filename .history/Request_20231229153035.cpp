#include <fstream>
#include <sstream>
#include <chrono>
#include <ctime>
#include "Request.h"
#include "User.h"
using std::fstream;
using std::string;
using std::getline;
using std::ifstream;


Request::Request(string requestID_val ,string hostID_val, string supporterID_val, string skill_val)
    : requestID(requestID_val) ,hostID(hostID_val), supporterID(supporterID_val), skill(skill_val){};

void Request::saveRequestDataToFile(string hostID, string supporterID, string skill){
    auto now = std::chrono::system_clock::now();

    // Convert the time point to a time_t object
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    // Convert the time_t object to a tm struct (localtime)
    std::tm* localTime = std::localtime(&currentTime);

    // Extract date components from the tm struct
    int year = localTime->tm_year + 1900; // Years since 1900
    int month = localTime->tm_mon + 1;    // Month (0-based, add 1)
    int day = localTime->tm_mday;         // Day of the month

    
    Request request;
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
       requestID = "R" + std::to_string(randomID);
       request.setRequestID(requestID);

       myFile << request.getRequestID() << "," << hostID << "," << supporterID << "," << skill << "," << "Pending" << "\n";
       cout << "You have created a request to book successfully!";
    } else {
        cout << "Can not open the file";
    }
     myFile.close();
}

string Request::getRequestID(){
    return requestID;
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
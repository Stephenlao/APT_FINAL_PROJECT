#include <fstream>
#include <sstream>
#include "Request.h"
using std::fstream;
using std::string;

Request::Request(string requestID_val ,string hostID_val, string supporterID_val, string skill_val)
    : requestID(requestID_val) ,hostID(hostID_val), supporterID(supporterID_val), skill(skill_val){};

void Request::setStatus(status newStatus){
    
}
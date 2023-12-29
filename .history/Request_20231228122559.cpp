#include <fstream>
#include <sstream>
#include "Request.h"

Request::Request(string requestID ,string hostID_val, string supporterID_val, string skill_val, string status_val)
    : hostName(hostName_val), supporterName(supporterName_val), skill(skill_val), status(status_val){};

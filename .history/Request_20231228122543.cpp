#include <fstream>
#include <sstream>
#include "Request.h"

Request::Request(string  ,string hostName_val, string supporterName_val, string skill_val, string status_val)
    : hostName(hostName_val), supporterName(supporterName_val), skill(skill_val), status(status_val){};

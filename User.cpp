#include "User.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include <vector>
#include "Skill.h"
#include "Rating.h"
#include "Request.h"
#include <limits>
using std::cin;
using std::cout;
using std::ctime;
using std::fstream;
using std::string;
using std::stringstream;
using std::vector;

User::User(string userId_val, string password_val)
    : userId(userId_val), password(password_val){};

void User::showInfo()
{
    cout << "UserID: " << userId << ", password: " << password << "\n";
}

// hash password function
unsigned long User::hashPassword(const std::string &password)
{
    unsigned long hash = 5381; // A prime number as initial hash value
    int c;

    for (auto str_iter = password.begin(); str_iter != password.end(); ++str_iter)
    {
        c = *str_iter;
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash;
}

bool User::checkValidatePassword(string pwd)
{
    if (pwd.length() < 8 || pwd.length() > 20)
    {
        return false; // Check length
    }

    bool hasLower = false, hasUpper = false, hasDigit = false, hasSpecial = false;

    // Check for lower case, upper case, and digit
    for (int i = 0; i < pwd.length(); i++)
    {
        if (islower(pwd[i]))
            hasLower = true;
        if (isupper(pwd[i]))
            hasUpper = true;
        if (isdigit(pwd[i]))
            hasDigit = true;
    }

    // Special characters
    char specialChar[] = {'!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '-', '+', '=', '<', '>', '?'};
    for (size_t i = 0; i < pwd.length(); i++)
    {
        for (size_t j = 0; j < sizeof(specialChar) / sizeof(char); j++)
        {
            if (pwd[i] == specialChar[j])
            {
                hasSpecial = true;
                break; // Break inner loop
            }
        }
    }
    // Check if all conditions are met
    return hasLower && hasUpper && hasDigit && hasSpecial;
}

bool User::isFileEmpty(std::ifstream &pfile)
{
    return pfile.peek() == std::fstream::traits_type::eof();
}

string User::createPassword()
{
    cout << "Password should have at least minimum 8 digits and maximum 20 digits\n "
         << "Have at least 1 upper character and lower character\n"
         << "Have at least 1 digit and contains special character:\n";

    string passwordInput;
    bool isValidPassword = false;

    while (!isValidPassword)
    {
        cout << "Enter your password: ";
        std::getline(cin, passwordInput);

        if (checkValidatePassword(passwordInput))
        {
            cout << "Create password successful!"
                 << "\n";
            isValidPassword = true;
        }
        else
        {
            cout << "Please follow the rule to create strong password!";
        }
    }
    string password = User::getPassword();
    password = std::to_string(hashPassword(passwordInput)); // Hashing the password

    // set password to attrs password to save in User class
    User::setPassword(password);
    return password;
}

string User::getUserId()
{
    return userId;
}

void User::setUserId(string userId_val)
{
    this->userId = userId_val;
}

string User::getPassword()
{
    return password;
}

void User::setPassword(string password_val)
{
    this->password = password_val;
};

Member::Member(string userId_val, string password_val,
               string userName_val, string fullName_val, string email_val,
               string phoneNumber_val, string homeAddress_val, string city_val,
               float creditPoint_val, bool isListed,vector<Skill*> skillsList_val, float minimumHostRatingScore_val, vector<string> historyBooking_val, vector<Rating> skillRating_val)

    : User(userId_val, password_val), userName(userName_val),
      fullName(fullName_val), email(email_val), phoneNumber(phoneNumber_val),
      homeAddress(homeAddress_val), city(city_val),
      isListed(false), skillsList(skillsList_val), minimumHostRatingScore(minimumHostRatingScore_val)
{

    // Allocate memory for creditPoint and assign the value
    creditPoint = new float(creditPoint_val);
};

vector<Skill*> Member::getSkillsLists() {
    return skillsList;
}


// Method to check if the member is listed
// void Member::setListedStatus(bool status) {

//         isListed = status;
// }

bool Member::isMemberListed() const {
    return isListed;
}

string Member::getUsername() const {
    return userName;
};




// Destructor to release memory allocated for creditPoint
Member::~Member()
{
    // delete creditPoint;
    for (auto skill : skillsList) {
            delete skill;
        }
};

// Define Member's function outside class

// function to check username is unique or not
bool Member::isUsernameUnique(const string &userName)
{
    fstream myFile("members.dat", std::ios::in);
    if (myFile.is_open())
    {

        string line, fileUserId, filePassword, fileUsername;
        while (getline(myFile, line))
        {
            stringstream ss(line);
            getline(ss, fileUserId, ',');
            getline(ss, filePassword, ',');
            getline(ss, fileUsername, ',');
            if (fileUsername == userName)
            {
                myFile.close();
                return false; // Username is not unique
            }
        }
        myFile.close();
        return true; // Username is unique
    }
    else
    {
        cout << "No data in file"
             << "\n";
        // std::cerr << "Cannot open file!\n";
        return false;
    }
}

void Member::saveDataToFile(const Member &member)
{
    fstream myFile;
    myFile.open("members.dat", std::ios::app | std::ios::out);
    if (myFile.is_open())
    {

        std::ifstream inFile("members.dat");
        if (isFileEmpty(inFile))
        {
            myFile << "userID,Password,UserName,FullName,Email,PhoneNumber,HomeAddress,City,CreditPoint,IsListed,,MinimumHostRating,SkillRating\n";
        }
        inFile.close();

        std::string creditPointStr = (member.creditPoint != nullptr) ? std::to_string(*member.creditPoint) : "0";
        std::string isListedStr = (member.isListed == false) ? "false" : "";
        std::string minimumHostRatingScoreStr = (member.minimumHostRatingScore == 0) ? "0" : "";



        myFile << member.userId << "," << member.password << "," << member.userName
               << "," << member.fullName << "," << member.email << "," << member.phoneNumber << ","
               << member.homeAddress << "," << member.city << "," << creditPointStr << "," << isListedStr << "," << minimumHostRatingScoreStr << "," << "\n";
    }
    else
    {
        std::cerr << "Unable to open file!"
                  << "\n";
        return;
    }
}




// Skill
// function to add skill to vector
void Member::createAndAddSkill(const std::string &skillName, float creditPerHour) {
    Skill* newSkill = new Skill(); // Use dynamic allocation
    if (newSkill->createSkill(skillName, creditPerHour)) { // Assume createSkill is a method of Skill
        skillsList.push_back(newSkill);
        std::cout << "Skill added: " << skillName << std::endl;
    }
    else {
        delete newSkill; // Free memory if not added
        std::cout << "Invalid skill creation!" << std::endl;
    }
}

//save skill to file
// function to check userID attrs whether equal userID in file
void Member::saveSkillsInFile(string userID) {
    std::fstream myFile;
    std::vector<std::string> fileLines;
    std::string line;

    myFile.open("members.dat", std::ios::in);
    if (!myFile) {
        std::cerr << "Unable to open file" << "\n";
        return;
    }

    while (std::getline(myFile, line)) {
        std::stringstream ss(line);
        std::string userId_val;
        std::getline(ss, userId_val, ',');

        if (userID == userId_val) {
            appendSkillsToLine(line); // Modify line if userID matches
        }

        fileLines.push_back(line); // Add the (possibly modified) line to the vector
    }
    myFile.close(); // Close the file after reading

    // Rewrite the file with updated content
    std::ofstream myFile1("members.dat", std::ios::out); // Open file in write mode
    if (!myFile1) {
        std::cerr << "Unable to open file for writing" << "\n";
        return;
    }

    for (const auto& fileLine : fileLines) {
        myFile1 << fileLine << std::endl; // Write each line back to the file
    }
    myFile1.close(); // Close the file after writing
}

// function to append skill to that user line
void Member::appendSkillsToLine(string& line) {
    if (skillsList.empty()) {
        return; // If there are no skills, don't modify the line
    }

    // Check if the line already contains skills in the expected format
    size_t skillsStart = line.find("[[");
    size_t skillsEnd = line.find_last_of("]]");

    if (skillsStart != string::npos && skillsEnd != string::npos) {
        // Skills array already exists, append new skills before the last "]]"
        line.insert(skillsEnd, ";" + formatSkills());
    } else {
        // No skills array present, create a new one
        line += "[" + formatSkills() + "]";
    }
}

// combine with appendSkillsToLine function
std::string Member::formatSkills() {
    std::string skillsString;
    for (size_t i = 0; i < skillsList.size(); ++i) {
        if (i > 0) {
            skillsString += ";";
        }
        const Skill* skill = skillsList[i];
        skillsString += "[" + skill->getSkillName() + "," + std::to_string(skill->getCreditPerHour()) + "]";
    }
    skillsList.clear();
    return skillsString;
}



// save isListed to file 
// function to check userID attrs whether equal userID in file
void Member::saveIsListedInFile(string userID, bool isListed_val) {
    std::fstream myFile;
    std::vector<std::string> fileLines;
    std::string line;

    myFile.open("members.dat", std::ios::in);
    if (!myFile) {
        std::cerr << "Unable to open file" << "\n";
        return;
    }

    while (std::getline(myFile, line)) {
        std::stringstream ss(line);
        std::string userId_val;
        std::getline(ss, userId_val, ',');

        if (userID == userId_val) {
            appendIsListedToLine(line, isListed_val); // Modify line if userID matches
        }

        fileLines.push_back(line); // Add the (possibly modified) line to the vector
    }
    myFile.close(); // Close the file after reading

    // Rewrite the file with updated content
    std::ofstream myFile1("members.dat", std::ios::out); // Open file in write mode
    if (!myFile1) {
        std::cerr << "Unable to open file for writing" << "\n";
        return;
    }

    for (const auto& fileLine : fileLines) {
        myFile1 << fileLine << std::endl; // Write each line back to the file
    }
    myFile1.close(); // Close the file after writing
}

// void Member::appendIsListedToLine(string& line, bool isListed_val) {
//     if (isListed_val) {
//         line += "true,";
//     } else {
//         line += "false,";
//     }
// }

// append isListed true/false to file
void Member::appendIsListedToLine(std::string& line, bool isListed_val) {
    // Find the last occurrence of "true" or "false" in the line
    size_t pos_true = line.rfind("true");
    size_t pos_false = line.rfind("false");

    // Determine the position to replace
    size_t pos_to_replace = (pos_true != std::string::npos) ? pos_true : pos_false;

    // Replace "true" with "false" or vice versa based on isListed_val
    if (pos_to_replace != std::string::npos) {
        if (isListed_val) {
            line.replace(pos_to_replace, 5, "true");
        } else {
            line.replace(pos_to_replace, 5, "false,");
        }
    }
}

std::vector<Skill*> Member::extractSkillNameAndPoint(const std::string& skillsStr) {
    std::vector<Skill*> skills;
    std::string trimmedStr = skillsStr.substr(2, skillsStr.length() - 4);
    std::stringstream skillStream(trimmedStr);
    std::string skillToken;

    while (std::getline(skillStream, skillToken, ';')) {
        size_t startPos = skillToken.find('[') + 1;
        size_t endPos = skillToken.find(']');
        std::string skillComponent = skillToken.substr(startPos, endPos - startPos);

        std::stringstream componentStream(skillComponent);
        std::string skillName;
        std::string skillPointStr;
        std::getline(componentStream, skillName, ',');
        std::getline(componentStream, skillPointStr);

        float skillPoint = std::stof(skillPointStr);
        skills.push_back(new Skill(skillName, skillPoint));
    }

    return skills;
}







// FIX THIS FUNCTION TO DELETE DEFAULT HOST RATING SCORE IN ORDER TO STORE NEW RATING SCORING 
void Member::deleteDefaultHostRatingScore(const std::string& userId) {
    std::fstream file;
    file.open("members.dat", std::ios::in);
    if (!file) {
        std::cerr << "Unable to open file\n";
        return;
    } else {
        std::stringstream newMemberData;
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string temp, hostRatingScore = "";
            std::getline(ss, temp, ','); // Assuming userID is the first element
            if (temp == userId) {
                newMemberData << temp << ','; // save userId into new stringstream
                // Copy all elements except the host rating score
                for (int i = 0; i < 9; i++) {
                    std::getline(ss, temp, ',');
                    newMemberData << temp << ",";
                }
                // Extract and skip the host rating score
                std::getline(ss, temp, ',');
                // Extract and update the skill information
                std::string skillData;
                std::getline(ss, skillData, '\n'); // Get the rest of the line which contains the skill data
                newMemberData << hostRatingScore << "," << skillData << "\n";
            } else {
                newMemberData << line << "\n"; // Keep line as it is
            }
        }
        file.close(); // Close the read mode

        // Open the same file in write mode to overwrite
        file.open("members.dat", std::ios::out | std::ios::trunc);
        if (!file.is_open()) {
            std::cerr << "Cannot open file!\n";
            return;
        }
        file << newMemberData.str(); // Write the modified content back
        file.close();

        std::cout << "Saved host rating score successfully.\n";
    }
}



void Member::saveMinimumHostRating(const std::string& filename, const std::string& userId) {
    std::string userResponse;
    float minimumHostRating = 0;

    // Ask the user if they want to enter a minimum host rating score
    std::cout << "Do you want to enter a minimum host rating score (yes/no): ";
    std::cin >> userResponse;

    // Process user response
    if (userResponse == "yes") {
        do {
            std::cout << "Enter score rating from 1 to 5: ";
            while (!(std::cin >> minimumHostRating)) {
                std::cout << "Invalid input. Enter a number from 1 to 5: ";
                std::cin.clear(); // clear bad input flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard input
            }
        } while (minimumHostRating < 1 || minimumHostRating > 5);
    } else if (userResponse != "no") {
        std::cout << "Invalid input. Only type yes or no." << std::endl;
        return;
    }

    std::ifstream inFile(filename);
    std::string line, updatedContent;
    bool updated = false;

    while (std::getline(inFile, line)) {
        std::string currentLine = line;
        std::stringstream ss(line);
        std::string part;
        std::getline(ss, part, ','); // Read the first part (ID)

        if (part == userId) {
            // Find the positions of the commas around the host rating score
          size_t scoreStart = currentLine.rfind(',', currentLine.find(",[["));
        size_t scoreEnd = currentLine.find(",[[", scoreStart);


            if (scoreStart != std::string::npos && scoreEnd != std::string::npos) {
                // Extract the parts of the string before and after the score
                std::string beforeScore = currentLine.substr(0, scoreStart);
                std::string afterScore = currentLine.substr(scoreEnd);

                // Replace the old score with the new score
                currentLine = beforeScore + std::to_string(minimumHostRating) + afterScore;

            }
            updated = true;
        }
        updatedContent += currentLine + "\n";
    }
    inFile.close();


    // Write the updated content back to the file
    if (updated) {
        std::ofstream outFile(filename);
        outFile << updatedContent;
        outFile.close();
    } else {
        std::cout << "User ID not found in the file." << std::endl;
    }

    
}

void Member::setDetail(const std::vector<std::string>& data, const std::string& skillRating) {
    if(data.size() >= 9){ // Ensure there are enough elements
            userId = data[0];
            password = data[1];
            userName = data[2];
            fullName = data[3];
            email = data[4];
            phoneNumber = data[5];
            homeAddress = data[6];
            city = data[7];
            *creditPoint = std::stoi(data[8]);
            isListed = (data.size() > 9 && data[9] == "true");
            // minimumHostRatingScore = std::stof(data[10]);

            // Now, parse and set the skill rating
            skillsList = extractSkillNameAndPoint(skillRating);  // You need to define this function
        }
}






void Member::showAllAvailableSupporters(const std::string& userID) {
    std::fstream myFile1("members.dat", std::ios::in);
    if (!myFile1) {
        std::cerr << "Unable to open file!" << "\n";
        return;
    }

    std::vector<std::string> data1;
    std::string line1;

    // First read: Look for the user's own data
    while(std::getline(myFile1,line1)) {
        std::stringstream ss1(line1);
        std::string userIdFile;
        std::getline(ss1, userIdFile, ',');
        if (userID == userIdFile) {
            data1.push_back(userIdFile);
            std::string temp;
            while(std::getline(ss1,temp,',')) {
                data1.push_back(temp);
            }
            break;
        }
    }

    myFile1.close(); // Clears the end-of-file condition
    // myFile.seekg(0, std::ios::beg); // Seeks back to the beginning of the file
  std::fstream myFile("members.dat", std::ios::in);
    if (!myFile) {
        std::cerr << "Unable to open file!" << "\n";
        return;
    }

    // Skip the first line (header)
    std::getline(myFile, line1); // Using line1 to skip header

    AvailableList availableList;
    std::string line;

    // Second read: Look for all available supporters
    while (std::getline(myFile, line)) {
        std::vector<std::string> data;
        Member tempMember; // Create a new temporary member object
        std::stringstream ss(line);
        std::string temp, skillRating;
        std::getline(ss, temp, ','); // Extracts the userId from the line

        if (temp == userID) {
            continue; // Skip this line as it matches the current user's ID
        }

        data.push_back(temp); // Push the first element (userId) as it's not the same as userID


        while (std::getline(ss, temp, ',')) {
            if (temp.find("[[") != std::string::npos) {
                skillRating = temp;
                break;
            } else {
                data.push_back(temp);
            }
        }

        if (!skillRating.empty()) {
            while (std::getline(ss, temp, ',')) {
                skillRating += "," + temp;
                if (temp.find("]]") != std::string::npos) {
                    break; // Found the end of the skill data
                }
            }
        }

        if (data1[9] == "false") {
            if (data.size() > 9 && data[9] == "true" && data[7] == data1[7]) {
                tempMember.setDetail(data, skillRating); // create object (supporter)
                availableList.addUser(tempMember); // add supporter to vector 
            }
        } else {
            if (data.size() > 9 && data[9] == "true" && data[7] == data1[7] && std::stoi(data[8]) <= std::stoi(data1[8])
            && std::stof(data[10]) <= std::stof(data1[10])) {
                tempMember.setDetail(data, skillRating);
                availableList.addUser(tempMember);
        }
    }    
}
    

    availableList.displayListedMembers();
    myFile.close();

    string input;
    string userNameOfSupporter;

    while(true) {
        cout << "\nFor more detail of supporter information (include listing skills) please choose number\n";
        cout << "Enter number (or press x to quit): ";
        cin >> input;


        if (input == "x" || input == "X") {
            std::cout << "Exiting..." << std::endl;
            break;
        }
        
        
        if(availableList.isValidNumber(input)) {
            int choiceNumber = std::stoi(input);
            userNameOfSupporter = availableList.getUserNameByOrderNumber(choiceNumber);
            availableList.showDetailSupporterDetail(userNameOfSupporter);
            // createRequest()
            // cout << availableList.getUserIdByOrderNumber(choiceNumber) << "real";
            Skill skillRequest = availableList.getRequestSkillName(userNameOfSupporter);

            // cout << "This is skill name" << skillRequest.getSkillName() << "This is skill credit" << skillRequest.getCreditPerHour();

            Request request;

            if(skillRequest.getSkillName() == "x"){
                break;
            }

            if(skillRequest.getSkillName() == ""){
                cout << "You are entering wrong syntax!" << "\n";
                break;
            }
            
            //Check user credit point
            if (checkCredit(skillRequest.getCreditPerHour())){             
                // Save the request to file
                request.saveRequestDataToFile(userID, getUserIdByName(userNameOfSupporter), skillRequest.getSkillName());
            } else {
                cout << "Don't have enough credit point to book." << "\n";
            }
            break;
        } else {
            cout << "Invalid input. Please enter a valid number or press x to quit.\n";
        }
    }

}

bool Member::SkillsExistOrNot(const std::string& userId) {
    fstream filePath;
    filePath.open("members.dat", std::ios::in);
    if (filePath) {
        std::string line;
        while (std::getline(filePath, line)) {
            std::istringstream iss(line);
            std::string fileUserId;
            getline(iss, fileUserId, ',');

            if (fileUserId == userId) {
                if (line.find("[[") != std::string::npos) {
                    return true; // Skills section exists
                } else {
                    return false; // Skills section does not exist
                }
            }
        }
    }
    return false; // UserId not found
}


string Member::isListedAsSupporterOrNot(const std::string& userId) {
    std::fstream myFile;
    myFile.open("members.dat", std::ios::in);
    if (!myFile) {
        std::cerr << "Unable to open file!" << "\n";
        return "0";
    }

    std::string line;
    string temp2,temp3,temp4,temp5,temp6,temp7,temp8,temp9,isListed_val;

    while (getline(myFile, line)) {
        std::istringstream iss(line);
        std::string fileUserId;
        getline(iss, fileUserId, ',');

        if (fileUserId == userId) {
            std::getline(iss, temp2, ',');
            std::getline(iss, temp3, ',');
            std::getline(iss, temp4, ',');
            std::getline(iss, temp5, ',');
            std::getline(iss, temp6, ',');
            std::getline(iss, temp7, ',');
            std::getline(iss, temp8, ',');
            std::getline(iss, temp9, ',');
            std::getline(iss,isListed_val, ',');
    }
    }
    return isListed_val;
}

bool Member::isListedValidation(const string& isListed) {
    if (isListed == "false") {
        return false;
    } else {
        return true;
    }
}

string Member::getUserIdByName(string userName){
    string userId;
    std::fstream myFile;
    string skillRating;
    myFile.open("members.dat", std::ios::in);
    if (!myFile) {
        std::cerr << "Unable to open file!" << "\n";
        return 0;
    }

    std::string line;
    // Skip the first line (header)
    std::getline(myFile, line);
    AvailableList availableList;


    while (std::getline(myFile, line)) {
        std::stringstream ss(line);
        std::string temp;
        std::vector<std::string> data;

        // Read data up to the skill data
        while (std::getline(ss, temp, ',')) {
            if (temp.find("[[") != std::string::npos) {
                // Found the beginning of the skill data
                skillRating = temp;
                break;
            } else {
                data.push_back(temp);
            }
        }

        // Continue reading the skill data
        if (!skillRating.empty()) {
            while (std::getline(ss, temp, ',')) {
                skillRating += "," + temp;
                if (temp.find("]]") != std::string::npos) {
                    break; // Found the end of the skill data
                }
            }
        }

        string userId_val, password_val, username_val,fullName_val,email_val, phoneNum_val,homeAddress_val,city_val,skillRating_val;
        int creditPoint1;
        // Check if the member is listed
        std::getline(ss, data[2]);

        // Process the data
        if (userName == data[2]) {
            userId_val = data[0];
            password_val = data[1];
            userName = data[2];
            fullName_val = data[3];
            email_val = data[4];
            phoneNum_val = data[5];
            homeAddress_val = data[6];
            city_val = data[7];
            // *creditPoint = (std::stoi(data[8]));
            userId = userId_val;
        }

    }

    myFile.close();

    return userId;
}
string Member::getUserNamedById(string userId){
    string userName;
    std::fstream myFile;
    string skillRating;
    myFile.open("members.dat", std::ios::in);
    if (!myFile) {
        std::cerr << "Unable to open file!" << "\n";
        return 0;
    }

    std::string line;
    // Skip the first line (header)
    std::getline(myFile, line);
    AvailableList availableList;


    while (std::getline(myFile, line)) {
        std::stringstream ss(line);
        std::string temp;
        std::vector<std::string> data;

        // Read data up to the skill data
        while (std::getline(ss, temp, ',')) {
            if (temp.find("[[") != std::string::npos) {
                // Found the beginning of the skill data
                skillRating = temp;
                break;
            } else {
                data.push_back(temp);
            }
        }

        // Continue reading the skill data
        if (!skillRating.empty()) {
            while (std::getline(ss, temp, ',')) {
                skillRating += "," + temp;
                if (temp.find("]]") != std::string::npos) {
                    break; // Found the end of the skill data
                }
            }
        }

        string userId_val, password_val, userName_val,fullName_val,email_val, phoneNum_val,homeAddress_val,city_val,skillRating_val;
        int creditPoint1;
        // Check if the member is listed
        std::getline(ss, data[2]);

        // Process the data
        if (userId == data[0]) {
            userId_val = data[0];
            password_val = data[1];
            userName_val = data[2];
            fullName_val = data[3];
            email_val = data[4];
            phoneNum_val = data[5];
            homeAddress_val = data[6];
            city_val = data[7];
            // *creditPoint = (std::stoi(data[8]));
            userName = userName_val;
        }

    }

    myFile.close();

    return userName;
}

bool Member::checkCredit(float creditPerHour){
    if ( creditPerHour <= getCreditPoint()){
        // float temp = 0;
        // temp = getCreditPoint() - creditPerHour;
        // setCreditPoint(temp);
        return true;
    } else {
        return false;
    }
}

float Member::getCreditPoint() const{
    return *creditPoint;
}

void Member::setCreditPoint(float newCreditPoint) {
    // Allocate memory for creditPoint if not allocated already
    if (!creditPoint) {
        creditPoint = new float;
    }
    // Set the value of creditPoint
    *creditPoint = newCreditPoint;
}

void Member::updateCreditInFile(string userId, float newCreditPoint){
    std::fstream myFile("members.dat", std::ios::in | std::ios::out);

    if (!myFile.is_open())
    {
        std::cerr << "There is no existence of account !"
                  << "\n";
        return;
    }

    std::vector<std::string> lines;
    std::string line;



    while (std::getline(myFile, line))
    {
        std::stringstream ss(line);
        std::string temp_userID, temp_password, temp_username, tempFullname, tempEmail, tempPhoneNumber, tempHomeAddress, tempCity, tempCreditPoint, restOfLine;
        std::getline(ss, temp_userID, ',');
        std::getline(ss, temp_password, ',');
        std::getline(ss, temp_username, ',');
        std::getline(ss, tempFullname, ',');
        std::getline(ss, tempEmail, ',');
        std::getline(ss, tempPhoneNumber, ',');
        std::getline(ss, tempHomeAddress, ',');
        std::getline(ss, tempCity, ',');
        std::getline(ss, tempCreditPoint, ',');
        std::getline(ss, restOfLine);

        if (temp_userID == userId)
        {
            float tempCreditPoint_val = std::stof(tempCreditPoint);
            tempCreditPoint_val = tempCreditPoint_val - newCreditPoint;
            std::string tempCreditPoint_str = std::to_string(tempCreditPoint_val);
            lines.push_back(temp_userID + "," + temp_password + "," + temp_username + "," + tempFullname + "," + tempEmail + "," + tempPhoneNumber + "," + tempHomeAddress + "," + tempCity + "," + tempCreditPoint_str + "," + restOfLine);
        }
        else
        {
            lines.push_back(line);
        }
    }

    myFile.clear();
    myFile.seekg(0, std::ios::beg);

    for (const auto &updatedLine : lines)
    {
        myFile << updatedLine << "\n";
    }
    myFile.close();
}

vector<string> Member::getHistoryBooking(string hostID){
    std::vector<std::string> result;
    std::vector<std::string> checkError;
    checkError.push_back("error");
    std::fstream myFile;
    myFile.open("requests.dat", std::ios::in);
    if (!myFile) {
        std::cerr << "Unable to open file!" << "\n";
        return checkError;
    }

    std::string line;
    // Skip the first line (header)
    std::getline(myFile, line);

    while (std::getline(myFile, line)) {
        std::stringstream ss(line);
        
        string requestId_val, hostId_val, supporterId_val, date_val, skill_val, status_val;

        std::getline(ss, requestId_val, ',');
        std::getline(ss, hostId_val, ',');
        std::getline(ss, supporterId_val, ',');
        std::getline(ss, date_val, ',');
        std::getline(ss, skill_val, ',');
        std::getline(ss, status_val, ',');
        // Process the data
        if (hostID == hostId_val && status_val != "Pending") {
            result.push_back("RequestID: " + requestId_val + ", Host: " + getUserNamedById(hostID) + ", Supporter: " + getUserNamedById(supporterId_val)+ ", Date: " + date_val + ", Skill: " + skill_val + ", Status: " + status_val);

        }

    }

    if (result.size() == 0){
        cout << "You did not have any booking before." << "\n";
        return checkError;
    }

    cout << "List of history bookings:" << "\n";
    for (size_t i = 0; i < result.size(); ++i) {
        std::cout << (i + 1) << ". " << result[i] << std::endl;
    }

    myFile.close();
    
  return result;
}

vector<string> Member::getCurrentBooking(string hostID){
    std::vector<std::string> result;
    std::vector<std::string> result_requestID;
    std::vector<std::string> checkError;
    checkError.push_back("error");
    std::fstream myFile;
    myFile.open("requests.dat", std::ios::in);
    if (!myFile) {
        std::cerr << "Unable to open file!" << "\n";
        return result ;
    }

    std::string line;
    // Skip the first line (header)
    std::getline(myFile, line);

    while (std::getline(myFile, line)) {
        std::stringstream ss(line);

        string requestId_val, hostId_val, supporterId_val, date_val, skill_val, status_val;
        
        std::getline(ss, requestId_val, ',');
        std::getline(ss, hostId_val, ',');
        std::getline(ss, supporterId_val, ',');
        std::getline(ss, date_val, ',');
        std::getline(ss, skill_val, ',');
        std::getline(ss, status_val, ',');
        // Process the data
        if (hostID == hostId_val && status_val == "Pending") {
            
            result.push_back("RequestID: " + requestId_val + ", Host: " + getUserNamedById(hostID) + ", Supporter: " + getUserNamedById(supporterId_val)+ ", Date: " + date_val + ", Skill: " + skill_val + ", Status: " + status_val);
            result_requestID.push_back(requestId_val);
        }

    }


    if (result.size() == 0){
        cout << "You did not have any booking before." << "\n";
        return checkError;
    }
    
    cout << "List of current booking:" << "\n";
    for (size_t i = 0; i < result.size(); ++i) {
        std::cout << (i + 1) << ". " << result[i] << std::endl;
    }

    myFile.close();
    
  return result_requestID;
}

void Member::cancelBooking(string requestID){

    if(requestID == "error"){
        cout << "Invalid input!\n" ;
    }

    if(requestID == "invalid"){
        cout << "Invalid input!\n" ;
    }

    std::fstream myFile("requests.dat", std::ios::in | std::ios::out);

    if (!myFile.is_open())
    {
        std::cerr << "There is no existence of host!"
                  << "\n";
        return;
    }

    std::vector<std::string> lines;
    std::string line;



    while (std::getline(myFile, line))
    {
        std::stringstream ss(line);
        string requestId_val, hostId_val, supporterId_val, date_val, skill_val, status_val;

        
        std::getline(ss, requestId_val, ',');
        std::getline(ss, hostId_val, ',');
        std::getline(ss, supporterId_val, ',');
        std::getline(ss, date_val, ',');
        std::getline(ss, skill_val, ',');
        std::getline(ss, status_val, ',');

        if (requestID == requestId_val)
        {
            lines.push_back(requestID + "," + hostId_val + "," + supporterId_val + "," + date_val + + "," + skill_val + "," +  "Cancel");
            cout << "Cancel request successfully!\n" << "\n";
        }
        else
        {
            
            lines.push_back(line);
            
        }
    }

    myFile.clear();
    myFile.seekg(0, std::ios::beg);
    myFile.close();

    std::fstream updateFile("requests.dat", std::ios::out | std::ios::trunc);

    if (!updateFile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    // // Check if the last line is empty and remove it if it is
    // if (!lines.empty() && lines.back().empty()) {
    //     lines.pop_back();
    // }
    
   for (const auto &updatedLine : lines)
    {   
            // cout << updatedLine << "\n";
            updateFile << updatedLine << "\n";
    }

    updateFile.close();
    return;
}


vector<string> Member::getHistoryRequest(string supporterID)
{
    std::vector<std::string> result;
    std::vector<std::string> checkError;
    checkError.push_back("error");
    std::fstream myFile;
    myFile.open("requests.dat", std::ios::in);
    if (!myFile) {
        std::cerr << "Unable to open file!" << "\n";
        return checkError;
    }

    std::string line;
    // Skip the first line (header)
    std::getline(myFile, line);

    while (std::getline(myFile, line)) {
        std::stringstream ss(line);
        
        string requestId_val, hostId_val, supporterId_val, date_val, skill_val, status_val;

        std::getline(ss, requestId_val, ',');
        std::getline(ss, hostId_val, ',');
        std::getline(ss, supporterId_val, ',');
        std::getline(ss, date_val, ',');
        std::getline(ss, skill_val, ',');
        std::getline(ss, status_val, ',');
        // Process the data
        if (supporterID == supporterId_val && status_val != "Pending") {
            result.push_back("RequestID: " + requestId_val + ", Host: " + getUserNamedById(hostId_val) + ", Supporter: " + getUserNamedById(supporterID)+ ", Date: " + date_val + ", Skill: " + skill_val + ", Status: " + status_val);

        }

    }

    if (result.size() == 0){
        cout << "You did not have any request before." << "\n";
        return checkError;
    }

    cout << "List of history requests:" << "\n";
    for (size_t i = 0; i < result.size(); ++i) {
        std::cout << (i + 1) << ". " << result[i] << std::endl;
    }

    myFile.close();
    
  return result;
}

vector<string> Member::getCurrentRequest(string supporterID)
{
    std::vector<std::string> result;
    std::vector<std::string> result_requestID;
    std::vector<std::string> checkError;
    checkError.push_back("error");
    std::fstream myFile;
    myFile.open("requests.dat", std::ios::in);
    if (!myFile) {
        std::cerr << "Unable to open file!" << "\n";
        return result ;
    }

    std::string line;
    // Skip the first line (header)
    std::getline(myFile, line);

    while (std::getline(myFile, line)) {
        std::stringstream ss(line);

        string requestId_val, hostId_val, supporterId_val, date_val, skill_val, status_val;
        
        std::getline(ss, requestId_val, ',');
        std::getline(ss, hostId_val, ',');
        std::getline(ss, supporterId_val, ',');
        std::getline(ss, date_val, ',');
        std::getline(ss, skill_val, ',');
        std::getline(ss, status_val, ',');
        // Process the data
        if (supporterID == supporterId_val && status_val == "Pending") {
            
            result.push_back("RequestID: " + requestId_val + ", Host: " + getUserNamedById(hostId_val) + ", Supporter: " + getUserNamedById(supporterID)+ ", Date: " + date_val + ", Skill: " + skill_val + ", Status: " + status_val);
            result_requestID.push_back(requestId_val);
        }
    }

    if (result.size() == 0){
        cout << "You did not have any pending request before." << "\n";
        return checkError;
    }
    
    cout << "List of current requests:" << "\n";
    for (size_t i = 0; i < result.size(); ++i) {
        std::cout << (i + 1) << ". " << result[i] << std::endl;
    }

    myFile.close();
    
  return result_requestID;
}

void Member::acceptRequest(string requestID)
{
    if(requestID == "error"){
        cout << "Invalid input!\n" ;
    }

    if(requestID == "invalid"){
        cout << "Invalid input!\n" ;
    }

    std::fstream myFile("requests.dat", std::ios::in | std::ios::out);

    if (!myFile.is_open())
    {
        std::cerr << "There is no existence of supporter yet!"
                  << "\n";
        return;
    }

    std::vector<std::string> lines;
    std::string line;



    while (std::getline(myFile, line))
    {
        std::stringstream ss(line);
        string requestId_val, hostId_val, supporterId_val, date_val, skill_val, status_val;

        
        std::getline(ss, requestId_val, ',');
        std::getline(ss, hostId_val, ',');
        std::getline(ss, supporterId_val, ',');
        std::getline(ss, date_val, ',');
        std::getline(ss, skill_val, ',');
        std::getline(ss, status_val, ',');

        if (requestID == requestId_val)
        {
            lines.push_back(requestID + "," + hostId_val + "," + supporterId_val + "," + date_val + + "," + skill_val + "," +  "Accepted");
            cout << "Accept the request successfully!\n" << "\n";
        }
        else
        {  
            lines.push_back(line);
        }
    }

    myFile.clear();
    myFile.seekg(0, std::ios::beg);
    myFile.close();

    std::fstream updateFile("requests.dat", std::ios::out | std::ios::trunc);

    if (!updateFile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    // // Check if the last line is empty and remove it if it is
    // if (!lines.empty() && lines.back().empty()) {
    //     lines.pop_back();
    // }
    
   for (const auto &updatedLine : lines)
    {   
            // cout << updatedLine << "\n";
            updateFile << updatedLine << "\n";
    }

    updateFile.close();
    return;
}

void Member::rejectRequest(string requestID)
{
    if(requestID == "error"){
        cout << "Invalid input!\n" ;
    }

    if(requestID == "invalid"){
        cout << "Invalid input!\n" ;
    }

    std::fstream myFile("requests.dat", std::ios::in | std::ios::out);

    if (!myFile.is_open())
    {
        std::cerr << "There is no existence of supporter yet!"
                  << "\n";
        return;
    }

    std::vector<std::string> lines;
    std::string line;



    while (std::getline(myFile, line))
    {
        std::stringstream ss(line);
        string requestId_val, hostId_val, supporterId_val, date_val, skill_val, status_val;

        
        std::getline(ss, requestId_val, ',');
        std::getline(ss, hostId_val, ',');
        std::getline(ss, supporterId_val, ',');
        std::getline(ss, date_val, ',');
        std::getline(ss, skill_val, ',');
        std::getline(ss, status_val, ',');

        if (requestID == requestId_val)
        {
            lines.push_back(requestID + "," + hostId_val + "," + supporterId_val + "," + date_val + + "," + skill_val + "," +  "Rejected");
            cout << "Reject the request successfully!\n" << "\n";
        }
        else
        {  
            lines.push_back(line);
        }
    }

    myFile.clear();
    myFile.seekg(0, std::ios::beg);
    myFile.close();

    std::fstream updateFile("requests.dat", std::ios::out | std::ios::trunc);

    if (!updateFile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    // // Check if the last line is empty and remove it if it is
    // if (!lines.empty() && lines.back().empty()) {
    //     lines.pop_back();
    // }
    
   for (const auto &updatedLine : lines)
    {   
            // cout << updatedLine << "\n";
            updateFile << updatedLine << "\n";
    }

    updateFile.close();
    return;
}

string Member::getRequestIDByOrder(vector<string> listOfRequestsID){
    string requestID = "error";
    string input;
    cout << "Please choose number of the specific request you want to cancel:\n";
    cout << "Enter number (or press x to quit): ";
    cin >> input;

    if (input == "x" || input == "X") {
        input = "x";
        std::cout << "Back to member menu" << std::endl ;
        return input;
    }

    int input_val = std::stoi(input);
    if(input_val > listOfRequestsID.size()){
        return "invalid";
    }
    for (size_t i = 0; i < listOfRequestsID.size(); i++) {
        if(input_val == i + 1 ){
            requestID = listOfRequestsID[i];
        }
    }

    return requestID;
}


// Rating
// void Member::addHostRating(int score, const std::string &comment)
// {

//     hostRating.addRating(score, comment);
// }

// void Member::addSupportRating(int score, const std::string &comment)
// {
//     supportRating.addRating(score, comment);
// }

// void Member::getHostRating()
// {
//     hostRating.displayRating();
// }

// void Member::getSupportRating()
// {
//     supportRating.displayRating();
// }
// float Member::getSpAvgRating()
// {
//     return supportRating.avgRating();
// }

// float Member::getHostAvgRating()
// {
//     return hostRating.avgRating();
// }

void Member::registerMember()
{
    fstream myFile;
    myFile.open("members.dat", std::ios::in);
    if (!myFile.is_open())
    {
        cout << "Enter username: ";
        std::getline(cin >> std::ws, userName);
    }
    else
    {
        // ask user to re-enter if username is duplicated
        bool uniqueUsername;
        do
        {
            cout << "Enter username: ";
            std::getline(cin >> std::ws, userName);
            uniqueUsername = isUsernameUnique(userName);
            if (!uniqueUsername)
            {
                cout << "This username is already exist. Please enter a different username\n ";
            }
        } while (!uniqueUsername);
    }

    cout << "Enter your full name: ";
    std::getline(cin >> std::ws, fullName);
    cout << "Enter your email: ";
    cin >> email;
    cout << "Enter your phone number: ";
    cin >> phoneNumber;
    cin.ignore(); // To consume the '\n' character
    cout << "Enter your home address: ";
    std::getline(cin >> std::ws, homeAddress);

    while (true)
    {
        cout << "Enter your city (Ha Noi or Sai Gon): ";
        std::getline(cin >> std::ws, city);

        // Convert city to lowercase for case-insensitive comparison
        for (auto &c : city)
        {
            c = tolower(c);
        }

        if (city == "ha noi" || city == "sai gon")
        {
            break; // Exit the loop if a valid city is entered
        }
        else
        {
            cout << "Invalid city. Please enter either 'Ha Noi' or 'Sai Gon'.\n";
        }
    }

    cout << "Do you accept to pay $20 to use the system? (yes/no): ";
    string response;
    std::getline(cin, response);
    if (response != "yes")
    {
        cout << "Registration cancelled.\n";
        return;
    }

    // Generating random user ID
    srand(time(NULL));             // Seed for random number generation
    int randomID = rand() % 10000; // Generate a random number
    string userId = User::getUserId();
    userId = "M" + std::to_string(randomID);
    User::setUserId(userId);

    // called method createpassword
    string password = User::createPassword();

    int initialPoint = 20;

    // allocated memory for credit point
    creditPoint = new float(initialPoint);

    cout << "Registration successful. Your user ID is: " << User::getUserId() << "\n";
    saveDataToFile(*this);

    // delete creditPoint to free up memory
    delete creditPoint;
}

void Member::showInfo()
{
    cout << "Member user name: " << userName << ", fullName: " << fullName
         << ", email: " << email << ", phoneNumber: " << phoneNumber << ", home address: " << homeAddress << ", city: " << city << " , credit point: " << *creditPoint << "\n";
}


void Member::showSupporterInfo() {
    std::cout << "Username: " << userName << " ,city: " << city << " , phone number: " << phoneNumber << "\n";
}

// This function is to read mem in file and save in each attrs
int Member::readDataInFileToCheckLogin(const string userNameIn, const string passwordIn)
{
    fstream myFile;
    // bool check;

    myFile.open("members.dat", std::ios::in);
    if (!myFile.is_open())
    {
        std::cerr << "Unable to open file!"
                  << "\n";
        return 2;
    }
    else
    {
        string line;
        while (std::getline(myFile, line))
        {
            // read each data to attrs
            stringstream ss(line);
            std::getline(ss, userId, ',');
            std::getline(ss, password, ',');
            std::getline(ss, userName, ',');
            std::getline(ss, fullName, ',');
            std::getline(ss, email, ',');
            std::getline(ss, phoneNumber, ',');
            std::getline(ss, homeAddress, ',');
            std::getline(ss, city, ',');
            ss >> *creditPoint;

            // check whether password is reset by admin
            if (userNameIn == userName)
            {
                if (password == "")
                {
                    cout << "Your password is reset by admin. Please create new password!"
                         << "\n";
                    return 0;
                }
            }

            // check if username and password is correct
            if (userNameIn == userName && std::to_string(hashPassword(passwordIn)) == password)
            {
                // showInfo();
                return 1;
                // break;
            }
        }

        cout << "Incorrect username or password!"
             << "\n";
        myFile.close();
    }
    return 2; // no matching username or password
}

int Member::loginMember()
{
    string usernameInput, passwordInput;
    cout << "Enter username: ";
    cin >> usernameInput;
    cout << "Enter password: ";
    cin >> passwordInput;
    int loginResult = readDataInFileToCheckLogin(usernameInput, passwordInput);
    // first check if username is empty or not return 0
    if (loginResult == 0)
    {
        return 0;
        // check username and password is equal or not
    }
    else if (loginResult == 1)
    {
        return 1;
    }
    // both password and username is not match
    return 2;
}

void Member::updatePasswordInFile()
{
    std::fstream myFile("members.dat", std::ios::in | std::ios::out);

    if (!myFile.is_open())
    {
        std::cerr << "There is no existence of account !"
                  << "\n";
        return;
    }

    std::vector<std::string> lines;
    std::string line;

    string username_val;
    cout << "Enter username: ";
    std::getline(cin >> std::ws, username_val);

    while (std::getline(myFile, line))
    {
        std::stringstream ss(line);
        std::string temp_userID, temp_password, temp_username, tempFullname, restOfLine;
        std::getline(ss, temp_userID, ',');
        std::getline(ss, temp_password, ',');
        std::getline(ss, temp_username, ',');
        std::getline(ss, tempFullname, ',');
        std::getline(ss, restOfLine);

        if (temp_username == username_val)
        {
            std::string curr_pass;
            std::cout << "Enter your current password: ";
            std::cin >> curr_pass;

            unsigned long hashedPassword = hashPassword(curr_pass);
            std::string hashedPasswordStr = std::to_string(hashedPassword);

            // check password is empty due to reset password by admin
            if (temp_password == "")
            {
                lines.push_back(temp_userID + "," + createPassword() + "," + temp_username + "," + tempFullname + "," + restOfLine);
                // check whether temp_password in file = curr_pass
            }
            else if (hashedPasswordStr == temp_password)
            {
                lines.push_back(temp_userID + "," + createPassword() + "," + temp_username + "," + tempFullname + "," + restOfLine);
            }
            else
            {
                std::cout << "Incorrect password!"
                          << "\n";
                return;
            }
        }
        else
        {
            lines.push_back(line);
        }
    }

    myFile.clear();
    myFile.seekg(0, std::ios::beg);

    for (const auto &updatedLine : lines)
    {
        myFile << updatedLine << "\n";
    }

    myFile.close();
    std::cout << "Password updated successfully.\n";
}

Admin::Admin(string adminId_val, string password_val, string adminName_val, string email_val)
    : User(adminId_val, password_val), adminName(adminName_val), email(email_val){};

// function to check username is unique or not
bool Admin::isAdminUserNameUnique()
{
    fstream myFile("admin.dat", std::ios::in);
    if (myFile.is_open())
    {

        string line, fileUserId, filePassword, fileAdminname;
        while (getline(myFile, line))
        {
            stringstream ss(line);
            getline(ss, fileUserId, ',');
            getline(ss, filePassword, ',');
            getline(ss, fileAdminname, ',');
            // check there is admin user name exist in file
            if (fileAdminname != "")
            {
                myFile.close();
                return false; // admin username exists
            }
        }
        myFile.close();
        return true; // Username is unique
    }
    else
    {
        cout << "Unable to open file"
             << "\n";
        return false;
    }
}

void Admin::registerAdmin()
{
    fstream myFile;
    myFile.open("admin.dat", std::ios::in);
    if (!myFile.is_open())
    {
        cout << "Enter admin name: ";
        std::getline(cin >> std::ws, adminName);
    }
    else
    {
        // check admin username if it is duplicated
        // quit system
        cout << "Enter admin name: ";
        std::getline(cin >> std::ws, adminName);
        if (!isAdminUserNameUnique())
        {
            cout << "There is only one admin in system!"
                 << "\n";
            return;
        }
    }

    cout << "Enter your email: ";
    cin >> email;

    // Generating random admin ID
    srand(time(NULL));             // Seed for random number generation
    int randomID = rand() % 10000; // Generate a random number
    string adminId = User::getUserId();
    adminId = "A" + std::to_string(randomID);
    User::setUserId(adminId);
    cin.ignore();

    cout << "Password should have at least minimum 8 digits and maximum 20 digits\n "
         << "Have at least 1 upper character and lower character\n"
         << "Have at least 1 digit and contains special character:\n";

    string passwordInput;
    bool isValidPassword = false;

    while (!isValidPassword)
    {
        cout << "Enter your password: ";
        std::getline(cin, passwordInput);

        if (checkValidatePassword(passwordInput))
        {
            cout << "Create password successful!"
                 << "\n";
            isValidPassword = true;
        }
        else
        {
            cout << "Please follow the rule to create strong password!";
        }
    }

    // save password to password attrs in User because password is in User class
    string password = User::getPassword();
    password = std::to_string(hashPassword(passwordInput)); // Hashing the password

    // set password to attrs password to save in User class
    User::setPassword(password);

    // Save to file
    fstream outFile("admin.dat", std::ios::app | std::ios::out); // Append mode
    if (outFile.is_open())
    {

        std::ifstream inFile("admin.dat");
        if (isFileEmpty(inFile))
        {
            outFile << "userID,Password,adminName,Email\n";
        }
        inFile.close();

        // save all attributes of admin in file
        outFile << adminId << "," << password << "," << adminName << ","
                << email << "\n";

        outFile.close();
    }
    else
    {
        cout << "Unable to open file.\n";
    }
    cout << "Registration successful. Your user ID is: " << User::getUserId() << "\n";
}

bool Admin::loginAdmin()
{
    string adminnameInput, passwordInput;
    cout << "Enter username: ";
    std::getline(cin >> std::ws, adminnameInput);
    cout << "Enter password: ";
    std::getline(cin >> std::ws, passwordInput);

    // Convert the password to a hash

    unsigned long hashedPassword = hashPassword(passwordInput);

    fstream inFile("admin.dat", std::ios::in);
    if (!inFile.is_open())
    {
        std::cerr << "Unable to open file.\n";
        return false;
    }

    string line;
    while (getline(inFile, line))
    {
        stringstream ss(line);
        // ignore the AdminID start with password, store in file
        getline(ss, userId, ',');
        getline(ss, password, ',');  // save password to filePassword
        getline(ss, adminName, ','); // save username to userName

        // Compare the username and hashed password
        if (adminnameInput == adminName && std::to_string(hashedPassword) == password)
        {
            // extract each information in admin.dat and save it in each attributes
            ss >> email;
            return true;
        }
    }
    inFile.close();
    return false;
}

void Admin::resetMemberPassword()
{
    fstream myFile;
    myFile.open("members.dat", std::ios::in);
    if (!myFile.is_open())
    {
        std::cerr << "Cannot open file path!"
                  << "\n";
        return;
    }

    // Skip the first line in file
    string line;
    if (!getline(myFile, line))
    {
        std::cerr << "Error or empty file.\n";
        return;
    }

    string temp1, temp2, username_val;
    vector<string> members;
    int order_num = 1;
    cout << "List of members:\n";
    while (getline(myFile, line))
    {
        stringstream ss(line);
        getline(ss, temp1, ',');
        getline(ss, temp2, ',');
        getline(ss, username_val, ',');
        members.push_back(line); // Store the whole line
        cout << "\t" << order_num++ << ". " << username_val << "\n";
    }
    myFile.close();

    // Ask admin to choose a user that admin want to reset password
    cout << "Enter the number of the user to reset password: ";
    int choice;
    cin >> choice;
    if (choice < 1 || choice > members.size())
    {
        std::cerr << "Invalid choice!\n";
        return;
    }

    // Reset password
    stringstream newMemberData;
    for (int i = 0; i < members.size(); i++)
    {
        if (i == choice - 1)
        { // User selected
            stringstream ss(members[i]);
            string temp, newPassword = "";
            getline(ss, temp, ',');              // M8289 get id of member
            newMemberData << temp << ",";        // write to newMemberData
            getline(ss, temp, ',');              // Old password
            newMemberData << newPassword << ","; // Reset password
            while (getline(ss, temp, ','))
            { // Rest of data
                newMemberData << temp << ",";
            }
            newMemberData.seekp(-1, newMemberData.cur); // Remove last comma
            newMemberData << "\n";
        }
        else
        {
            newMemberData << members[i] << "\n";
        }
    }

    // Write updated data back to file
    myFile.open("members.dat", std::ios::out | std::ios::trunc);
    if (!myFile.is_open())
    {
        std::cerr << "Cannot open file path!"
                  << "\n";
        return;
    }
    myFile << "userID,Password,UserName,FullName,Email,PhoneNumber,HomeAddress,City,CreditPoint,IsListed,,MinimumHostRating,SkillRating\n";
    myFile << newMemberData.str();
    myFile.close();

    cout << "Password reset successfully for user " << choice << ".\n";
}

string Admin::getAdminName()
{
    return adminName;
}

void Admin::setAdminName(string adminName_val)
{
    adminName = adminName_val;
}

string Admin::getEmail()
{
    return email;
}

void Admin::setEmail(string email_val)
{
    email = email_val;
}

void Admin::showInfo()
{
    cout << "Admin name: " << adminName << ", Email: " << email << "\n";
}



void Guest::viewSupporters() {
 
    fstream myFile("members.dat", std::ios::in);
    if (!myFile) {
        std::cerr << "Unable to open file!\n";
        return;
    }

    string line;
    getline(myFile, line); // Skip the header

    while (getline(myFile, line)) {
        string userId_val,fullName_val, email_val, phoneNumber_val, homeAddress_val, city_val, isListed_val;
        stringstream ss(line);
        vector<string> data;
        string temp;

        while (getline(ss, temp, ',')) {
            data.push_back(temp);
        }

        if (data.size() >= 10 && data[9] == "true") {
            userId_val = data[0];
            fullName_val = data[3];
            email_val = data[4];
            phoneNumber_val = data[5];
            homeAddress_val = data[6];
            city_val = data[7];
            isListed_val = data[9];

       
            cout << "Full name: " << fullName_val << " ,email: " << email_val 
                 << ", phone number: " << phoneNumber_val << ", Home address: " << homeAddress_val
                 << ", City: " << city_val << "\n\n";
        }
    }
    myFile.close();
}

void AvailableList::addUser(const Member &member) {
    if (member.isListed) {
        userList.push_back(new Member(member)); // Creates a new Member object and stores its raw pointer
    }
}

void AvailableList::displayListedMembers() {
 if (!userList.empty()) { // Check if the userList is not empty
        std::cout << "Listed Supporters:\n\n";
        cout << "cp: credit point\n";
        int orderNum = 1;
        for (Member* user : userList) { // Loop through each user in the userList
            cout << orderNum << ". ";
            user->showSupporterInfo(); // Displaying member information
            cout << "\n------------------------------------------------\n";
            orderNum++; // Increment order number for next member
        }
    } else { // If userList is empty, display a message indicating no supporters found
        cout << "\nSorry! Can not find any suitable supporters!" << "\n";
    }
}


string AvailableList::getUserNameByOrderNumber(int numberInput) {
    int currentOrder = 1;
    for (int i = 0; i < userList.size();i++) {
        if (currentOrder == numberInput) {
            return userList[i]->getUsername();
            break;
        }
        currentOrder ++;
    }
    cout << "There is no ordernumber exist!" << "\n";
    return "";
}

string AvailableList::getUserIdByOrderNumber(int numberInput) {
    int currentOrder = 1;
    for (int i = 0; i < userList.size();i++) {
        if (currentOrder == numberInput) {
            return userList[i]->getUserId();
            break;
        }
        currentOrder ++;
    }
    cout << "There is no ordernumber exist!" << "\n";
    return "";
}

// show all supporters info if correct ordernumber is entered
void AvailableList::showDetailSupporterDetail(string& userName) {
    std::fstream myFile;
    string skillRating;
    myFile.open("members.dat", std::ios::in);
    if (!myFile) {
        std::cerr << "Unable to open file!" << "\n";
        return;
    }

    std::string line;
    // Skip the first line (header)
    std::getline(myFile, line);
    AvailableList availableList;

    
    while (std::getline(myFile, line)) {
        std::stringstream ss(line);
        std::string temp;
        std::vector<std::string> data;

        // Read data up to the skill data
        while (std::getline(ss, temp, ',')) {
            if (temp.find("[[") != std::string::npos) {
                // Found the beginning of the skill data
                skillRating = temp;
                break;
            } else {
                data.push_back(temp);
            }
        }

        // Continue reading the skill data
        if (!skillRating.empty()) {
            while (std::getline(ss, temp, ',')) {
                skillRating += "," + temp;
                if (temp.find("]]") != std::string::npos) {
                    break; // Found the end of the skill data
                }
            }
        }

        string userId_val, password_val, username_val,fullName_val,email_val, phoneNum_val,homeAddress_val,city_val,skillRating_val;
        int creditPoint1;
        // Check if the member is listed
        std::getline(ss, data[2]);

        // Process the data
        if (userName == data[2]) {
            userId_val = data[0];
            password_val = data[1];
            userName = data[2];
            fullName_val = data[3];
            email_val = data[4];
            phoneNum_val = data[5];
            homeAddress_val = data[6];
            city_val = data[7];
            // *creditPoint = (std::stoi(data[8]));




            // Extract skills
            vector<Skill*> skillRatingSupporter = Member::extractSkillNameAndPoint(skillRating);



            std::cout << "\nSupporterID: " << userId_val << "\n"
                << "UserName: " << userName << "\n" 
                << "Full name:" << fullName_val << "\n" 
                << "Email: " << email_val << "\n" 
                << "Phone number: " << phoneNum_val << "\n" 
                << "Home address: " << homeAddress_val << "\n" 
                << "City: " << city_val << "\n";

            cout << "Skills: \n";
            for (size_t i = 0; i < skillRatingSupporter.size(); ++i) {
                 std::cout << i + 1 << ". Name: " << skillRatingSupporter[i]->getSkillName()
                  << " , Credit point per hour: " << skillRatingSupporter[i]->getCreditPerHour() << "\n";
            }
        }
    }
    myFile.close();

}

Skill AvailableList::getRequestSkillName(string& userName){
    std::vector<std::string> skill;
    Skill skillRequest;
    // string skillRequest;
    std::fstream myFile;
    string skillRating;
    myFile.open("members.dat", std::ios::in);
    if (!myFile) {
        std::cerr << "Unable to open file!" << "\n";
        return skillRequest;
    }

    std::string line;
    // Skip the first line (header)
    std::getline(myFile, line);
    AvailableList availableList;


    while (std::getline(myFile, line)) {
        std::stringstream ss(line);
        std::string temp;
        std::vector<std::string> data;

        // Read data up to the skill data
        while (std::getline(ss, temp, ',')) {
            if (temp.find("[[") != std::string::npos) {
                // Found the beginning of the skill data
                skillRating = temp;
                break;
            } else {
                data.push_back(temp);
            }
        }

        // Continue reading the skill data
        if (!skillRating.empty()) {
            while (std::getline(ss, temp, ',')) {
                skillRating += "," + temp;
                if (temp.find("]]") != std::string::npos) {
                    break; // Found the end of the skill data
                }
            }
        }

        string userId_val, password_val, username_val,fullName_val,email_val, phoneNum_val,homeAddress_val,city_val,skillRating_val;
        int creditPoint1;
        // Check if the member is listed
        std::getline(ss, data[2]);

        // Process the data
        if (userName == data[2]) {
            userId_val = data[0];
            password_val = data[1];
            userName = data[2];
            fullName_val = data[3];
            email_val = data[4];
            phoneNum_val = data[5];
            homeAddress_val = data[6];
            city_val = data[7];
            // *creditPoint = (std::stoi(data[8]));

            // Extract skills
            vector<Skill*> skillRatingSupporter = Member::extractSkillNameAndPoint(skillRating);        

            string input;
            cout << "\n" << "Please choose number of skill you want to book";
            cout << "\n" << "Enter number (or press x to quit): ";
            cin >> input;

            if (input == "x" || input == "X") {
                skillRequest.setSkillName("x");
                std::cout << "Exiting..." << std::endl ;
                return skillRequest;
                break;
            }
            int input_val = std::stoi(input);

            for (size_t i = 0; i < skillRatingSupporter.size(); ++i) {
                 if(input_val == i + 1 ){
                    // Creat skill request
                    skillRequest.createSkill(skillRatingSupporter[i]->getSkillName(), skillRatingSupporter[i]->getCreditPerHour());
                 }
            }
        }
    }
    myFile.close();
    return skillRequest;
}


// Add credit point to supporter and minus for host if request is accepted
std::pair<std::string, std::string> Member::getSupporterIdAndSkillNameInRequestDat(std::string requestID)
{
    if(requestID == "error" || requestID == "invalid")
    {
        std::cout << "Invalid input!\n";
        return std::make_pair("", ""); // Return an empty pair
    }

    std::fstream myFile("requests.dat", std::ios::in);
    if (!myFile.is_open())
    {
        std::cerr << "There is no existence of supporter yet!\n";
        return std::make_pair("", ""); // Return an empty pair
    }

    std::string line;
    while (std::getline(myFile, line))
    {
        std::stringstream ss(line);
        std::string requestId_val, hostId_val, supporterId_val, date_val, skill_val, status_val;

        std::getline(ss, requestId_val, ',');
        std::getline(ss, hostId_val, ',');
        std::getline(ss, supporterId_val, ',');
        std::getline(ss, date_val, ',');
        std::getline(ss, skill_val, ',');
        std::getline(ss, status_val, ',');

        if (requestID == requestId_val)
        {
            return std::make_pair(supporterId_val, skill_val); // Return the pair
        }
    }
    return std::make_pair("", ""); // Return an empty pair if no match is found
}


string Member::getHostIdInRequestDat(string requestID) {
       if(requestID == "error"){
        cout << "Invalid input!\n" ;
    }

    if(requestID == "invalid"){
        cout << "Invalid input!\n" ;
    }

    std::fstream myFile("requests.dat", std::ios::in | std::ios::out);

    if (!myFile.is_open())
    {
        std::cerr << "There is no existence of supporter yet!"
                  << "\n";
        return "";
    }

    std::vector<std::string> lines;
    std::string line;



    while (std::getline(myFile, line))
    {
        std::stringstream ss(line);
        string requestId_val, hostId_val, supporterId_val, date_val, skill_val, status_val;

        
        std::getline(ss, requestId_val, ',');
        std::getline(ss, hostId_val, ',');
        std::getline(ss, supporterId_val, ',');
        std::getline(ss, date_val, ',');
        std::getline(ss, skill_val, ',');
        std::getline(ss, status_val, ',');

        if (requestID == requestId_val)
        {
            return hostId_val;
        }
    }
    return "";
}


float Member::getConsumingPointOfSkillBySupporterId(std::string supporterID, std::string skillName) {
    std::fstream myFile;
    float consumingPoint;
    myFile.open("members.dat", std::ios::in);
    if (!myFile) {
        std::cerr << "Unable to open file!\n";
        return -1;
    }

    // Skip the header line
    std::string line;
    std::getline(myFile, line);
    std::vector<std::string> data1;
    data1.push_back(line); // Add the header line to data1

    while (std::getline(myFile, line)) {
        std::vector<std::string> data;
        std::stringstream ss(line);
        std::string temp, skillRating;
        float currentCreditPoint = 0.0f;
        float newCreditPoint = 0.0f;
        
        // Parse the line until skill data
        while (std::getline(ss, temp, ',')) {
            if (temp.find("[[") != std::string::npos) {
                skillRating = temp;
                break;
            } else {
                data.push_back(temp);
            }
        }

        // Continue parsing skill data
        if (!skillRating.empty()) {
            while (std::getline(ss, temp, ',')) {
                skillRating += "," + temp;
                if (temp.find("]]") != std::string::npos) {
                    break;
                }
            }
        }

        if (data[0] == supporterID) {
            consumingPoint = getSkillRating(skillRating, skillName);
            currentCreditPoint = std::stof(data[8]);
            newCreditPoint = currentCreditPoint + consumingPoint;
            data[8] = std::to_string(newCreditPoint); // Update the credit point in the vector
            cout << "Your current credit point: " << currentCreditPoint <<  " cp\n";
            cout << "Your credit point after accepted booking: " << newCreditPoint <<  " cp\n";
        }

        // Create a string from the updated data and add to data1
        std::stringstream updatedLine;
        for (size_t i = 0; i < data.size(); ++i) {
            updatedLine << data[i];
            // if (i < data.size() - 1) {
            updatedLine << ",";
            // }
        }
        updatedLine << skillRating; // Add the skill rating at the end
        data1.push_back(updatedLine.str());
    }
    myFile.close();

    // Write the updated data back to the file
    std::ofstream outFile("members.dat", std::ios::out | std::ios::trunc);
    if (!outFile) {
        std::cerr << "Unable to open file for writing!\n";
        return -2;
    }
    for (const auto& line : data1) {
        outFile << line << "\n";
    }
    outFile.close();
    return consumingPoint;
}

// get consuming point if skillName is match with skillName in file
float Member::getSkillRating(const std::string& skillData, const std::string& skillName) {
    std::string temp;
    std::stringstream ss(skillData);

    // Removing the initial '[[' and final ']]'
    if (skillData.size() > 2) {
        ss.ignore(2);
    }

    while (std::getline(ss, temp, ';')) {
        std::stringstream skillStream(temp);

        std::string extractedSkill;
        double rating = 0.0;

        // Getting skill name
        if (std::getline(skillStream, extractedSkill, ',')) {
            // Removing possible leading '['
            size_t start = extractedSkill.find('[');
            if (start != std::string::npos) {
                extractedSkill = extractedSkill.substr(start + 1);
            }

            // Getting rating
            if (extractedSkill == skillName && skillStream >> rating) {
                return rating; // Return the rating if skill matches
            }
        }
    }

    return -1; // Return -1 or any indicator for "not found"
}


void Member::getHostIdAndDeductCreditPoint(string hostID,float consumingPoint) {
    std::fstream myFile;
    myFile.open("members.dat", std::ios::in);
    if (!myFile) {
        std::cerr << "Unable to open file!\n";
        return;
    }

    // Skip the header line
    std::string line;
    std::getline(myFile, line);
    std::vector<std::string> data1;
    data1.push_back(line); // Add the header line to data1

    while (std::getline(myFile, line)) {
        std::vector<std::string> data;
        std::stringstream ss(line);
        std::string temp, skillRating;
        float currentCreditPoint = 0.0f;
        float newCreditPoint = 0.0f;
        
        // Parse the line until skill data
        while (std::getline(ss, temp, ',')) {
            if (temp.find("[[") != std::string::npos) {
                skillRating = temp;
                break;
            } else {
                data.push_back(temp);
            }
        }

        // Continue parsing skill data
        if (!skillRating.empty()) {
            while (std::getline(ss, temp, ',')) {
                skillRating += "," + temp;
                if (temp.find("]]") != std::string::npos) {
                    break;
                }
            }
        }

        if (data[0] == hostID) {
            currentCreditPoint = std::stof(data[8]);
            newCreditPoint = currentCreditPoint - consumingPoint;
            data[8] = std::to_string(newCreditPoint); // Update the credit point in the vector
        }

        // Create a string from the updated data and add to data1
        std::stringstream updatedLine;
        for (size_t i = 0; i < data.size(); ++i) {
            updatedLine << data[i];
            updatedLine << ",";
        }
        updatedLine << skillRating; // Add the skill rating at the end
        data1.push_back(updatedLine.str());
    }
    myFile.close();

    // Write the updated data back to the file
    std::ofstream outFile("members.dat", std::ios::out | std::ios::trunc);
    if (!outFile) {
        std::cerr << "Unable to open file for writing!\n";
        return;
    }
    for (const auto& line : data1) {
        outFile << line << "\n";
    }
    outFile.close();
}



bool AvailableList::isValidNumber(const std::string& str) {
    for (char const &c : str) {
        if (!std::isdigit(c)) return false;
    }
    return true;
}
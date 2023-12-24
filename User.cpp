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
               string phoneNumber_val, string homeAddress_val, string city_val, int creditPoint_val, bool isListed,vector<Skill*> skillsList_val)

    : User(userId_val, password_val), userName(userName_val),
      fullName(fullName_val), email(email_val), phoneNumber(phoneNumber_val),
      homeAddress(homeAddress_val), city(city_val),
      isListed(false), skillsList(skillsList_val)
{

    // Allocate memory for creditPoint and assign the value
    creditPoint = new int(creditPoint_val);
};



// Method to check if the member is listed
void Member::setListedStatus(bool status) {

        isListed = status;
    }

    bool Member::isMemberListed() const {
        return isListed;
    }



// Destructor to release memory allocated for creditPoint
Member::~Member()
{
    delete creditPoint;
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
            myFile << "userID,Password,UserName,FullName,Email,PhoneNumber,HomeAddress,City,CreditPoint,SkillRating,IsListed\n";
        }
        inFile.close();

        std::string creditPointStr = (member.creditPoint != nullptr) ? std::to_string(*member.creditPoint) : "0";

        myFile << member.userId << "," << member.password << "," << member.userName
               << "," << member.fullName << "," << member.email << "," << member.phoneNumber << ","
               << member.homeAddress << "," << member.city << "," << creditPointStr << "," << "\n";
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

void Member::appendIsListedToLine(string& line, bool isListed_val) {
    if (isListed_val) {
        line += ",true";
    } else {
        line += ",false";
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


void Member::showAllAvailableSupporters(std::vector<Member>& AList) {
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

        // Check if the member is listed
        std::getline(ss, temp);
        isListed = (temp == "true");

        // Process the data
        if (isListed && data.size() >= 8) {
            userId = data[0];
            password = data[1];
            userName = data[2];
            fullName = data[3];
            email = data[4];
            phoneNumber = data[5];
            homeAddress = data[6];
            city = data[7];
            *creditPoint = std::stoi(data[8]);

            // Extract skills
            skillsList = extractSkillNameAndPoint(skillRating);

            std::cout << userId << ", " << userName << ", " << password << ", " << fullName << ", " 
                      << email << ", " << phoneNumber << ", " << homeAddress << ", " << city << ", "
                      << *creditPoint << ", " << skillRating << "\n";

            // Add to the list if needed
            AList.push_back(Member(userId,password,userName,fullName,email,phoneNumber,homeAddress,city,*creditPoint,isListed,skillsList));
        }
    }
    myFile.close();
}




// Rating
void Member::addHostRating(int score, const std::string &comment)
{

    hostRating.addRating(score, comment);
}

void Member::addSupportRating(int score, const std::string &comment)
{
    supportRating.addRating(score, comment);
}

void Member::getHostRating()
{
    hostRating.displayRating();
}

void Member::getSupportRating()
{
    supportRating.displayRating();
}
float Member::getSpAvgRating()
{
    return supportRating.avgRating();
}

float Member::getHostAvgRating()
{
    return hostRating.avgRating();
}

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
    creditPoint = new int(initialPoint);

    cout << "Registration successful. Your user ID is: " << User::getUserId() << "\n";
    saveDataToFile(*this);

    // delete creditPoint to free up memory
    delete creditPoint;
}

void Member::showInfo()
{
    cout << "Member user name: " << userName << ", fullName: " << fullName
         << ", email: " << email << ", phoneNumber: " << phoneNumber << ", home address: " << homeAddress << ",city: " << city << " ,credit point: " << *creditPoint << "\n";
    // for (Skill* skill : skillsList)
    // {
    //     cout << "Skill name: "
    //          << "\t";
    //     skill->getSkillName();
    //     cout << "\n";

    //     cout << "Skill credit: " << skill->getCreditPerHour() << "\n";
    // }
}
// void Member::showSupportInfo() {
//     std::cout << "Member user name: " << userName << ", fullName: " << fullName
//          << ", email: " << email << ", phoneNumber: " << phoneNumber << ", home address: " << homeAddress << ",city: " << city << " ,credit point: " << *creditPoint << "\n";
//     for (Skill &skill : skillsList) {
//         std::cout << "Skill name: ";
//         skill.getSkillName() ;
//         cout << "\n";
//         std::cout << "Skill credit: " << skill.getCreditPerHour() << "\n";
//         // std::cout << "Minimum required host-rating score: " << skill.getMinimumHostRating() << "\n";
//     }
// }

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
    myFile << "userID,Password,UserName,FullName,Email,PhoneNumber,HomeAddress,City,CreditPoint\n";
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

void Guest::viewSupporters()
{
    fstream myFile;
    myFile.open("members.dat", std::ios::in);
    if (!myFile.is_open())
    {
        std::cerr << "Unable to open file!"
                  << "\n";
        return;
    }
    cout << "All supporters: "
         << "\n\n";
    string line;

    // Skip the first line
    if (!std::getline(myFile, line))
    {
        std::cerr << "Error or empty file.\n";
        return;
    }

    while (getline(myFile, line))
    {
        stringstream ss(line);
        string fullName_val, email_val, phoneNumber_val, homeAddress_val, city_val, temp1, temp2, temp3;
        getline(ss, temp1, ',');
        getline(ss, temp2, ',');
        getline(ss, temp3, ',');
        // ignore first three information in file which is
        // ID, password and username

        std::getline(ss, fullName_val, ',');
        std::getline(ss, email_val, ',');
        std::getline(ss, phoneNumber_val, ',');
        std::getline(ss, homeAddress_val, ',');
        std::getline(ss, city_val, ',');
        // only print these information only for guest
        cout << "Full name: " << fullName_val << " ,email: " << email_val << ",phone number: "
             << phoneNumber_val << ", Home address: " << homeAddress_val << ", City: " << city_val
             << "\n\n";
    }
    myFile.close();
};


// void AvailableList::addUser(const Member& member) {
//     if (member.isListed) {
//         userList.push_back(member);
//     }
// }

// void AvailableList::displayListedMembers() {
//     std::cout << "Listed Members:" << std::endl;
//     for (auto& user : userList) {
//         user.showSupportInfo(); 
//     }
// }


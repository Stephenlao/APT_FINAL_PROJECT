
#ifndef _USER_H_
#define _USER_H_

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include <vector>
#include "Skill.h"
#include "Rating.h"
#include <limits>
using std::cin;
using std::cout;
using std::ctime;
using std::fstream;
using std::string;
using std::stringstream;
using std::vector;

class User
{
protected:
    string userId;
    string password;

public:
    User(string userId_val = "", string password_val = "");
    void showInfo();
    // hash password function
    unsigned long hashPassword(const std::string &password);
    bool checkValidatePassword(string pwd);
    bool isFileEmpty(std::ifstream &pfile);
    string createPassword();
    string getUserId();
    void setUserId(string userId_val);
    string getPassword();
    void setPassword(string password_val);
};

class AvailableList;
class Member : public User
{
private:
    string userName;
    string fullName;
    string email;
    string phoneNumber;
    string homeAddress;
    string city;
    int *creditPoint;
    vector<Skill*> skillsList;
    Rating hostRating;
    Rating supportRating;
    bool isListed;
    float minimumHostRatingScore;


public:
    Member(string userId_val = "", string password_val = "",
           string userName_val = "", string fullName_val = "", string email_val = "",
           string phoneNumber_val = "", string homeAddress_val = "", string city_val = "", int creditPoint_val = 0, bool isListed = false, vector<Skill*> skillsList_val = {},float minimumHostRatingScore_val = 0);

    // Allocate memory for creditPoint and assign the value

    // Destructor to release memory allocated for creditPoint
    ~Member();

    bool isUsernameUnique(const string &userName);
    void registerMember();
    void showInfo();
    void saveDataToFile(const Member &member);
    int readDataInFileToCheckLogin(string userNameIn, string passwordIn);
    int loginMember();
    string getUserIdByName(string userName);
    void updatePasswordInFile();
    // Getter function for creditPoint
    int getCreditPoint() const;
    // Setter function for creditPoint
    void setCreditPoint(int newCreditPoint);
    string getUsername() const;


    // SKILL
    void createAndAddSkill(const std::string &skillName, float creditPerHour);
    void saveSkillsInFile(string userID);
    void appendSkillsToLine(string& line);
    void saveIsListedInFile(string userID,bool isListed_val);
    void appendIsListedToLine(string& line,bool isListed_val);
    string formatSkills();
    static std::vector<Skill*> extractSkillNameAndPoint(const std::string& skillsStr);
    void showAllAvailableSupporters(string hostID);
    vector<Skill*> getSkillsLists();
    bool SkillsExistOrNot(const std::string& userId);
    string isListedAsSupporterOrNot(const std::string& userId);
    bool isListedValidation(const string& isListed);
    void setDetail(const std::vector<std::string>& data, const std::string& skillRating);
    static std::string trim(const std::string& str);

    // REQUEST
    void createRequest(string skillRequest, string hostID, string supporterID);

    // Rating
    void addHostRating(int score, const std::string &comment);
    void addSupportRating(int score, const std::string &comment);
    void getHostRating();
    void getSupportRating();
    float getHostAvgRating();
    float getSpAvgRating();
    void setListedStatus(bool status);
    // Method to check if the member is listed
    bool isMemberListed() const ;    

    void showSupporterInfo();
    void saveMinimumHostRating(const std::string& filename, const string& userId);
    void deleteDefaultHostRatingScore(const std::string& userId);



    friend class AvailableList;
    };

    class Admin : public User
    {
    private:
        string adminName;
        string email;

    public:
        Admin(string adminId_val = "", string password_val = "", string adminName_val = "", string email_val = "");

        // function to check username is unique or not
        bool isAdminUserNameUnique();
        void registerAdmin();
        bool loginAdmin();
        void resetMemberPassword();
        string getAdminName();
        void setAdminName(string adminName_val);
        string getEmail();
        void setEmail(string email_val);
        void showInfo();
    };

    class Guest
    {
    public:
        void viewSupporters();
    };


// AvailableList class
    class AvailableList
    {
    public:
    AvailableList(){};
    std::vector<Member*> userList; 
    void addUser(const Member &member);
    void displayListedMembers();
    string getUserNameByOrderNumber(int numberInput);
    string getUserIdByOrderNumber(int numberInput);
    void showDetailSupporterDetail(string& userName, string hostID);
    bool isValidNumber(const std::string& str);
    Skill getRequestSkillName(string& userName);
    };


#endif

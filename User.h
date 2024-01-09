
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
    float *creditPoint;
    vector<Skill*> skillsList;
    // Rating hostRating;
    // Rating supportRating;
    bool isListed;
    float minimumHostRatingScore;
    vector<string> historyBooking;
    vector<Rating> skillRating;
    vector<Rating> supporterRating;
    vector<Rating> hostRating;
    float avgHostRating;





public:
    Member(string userId_val = "", string password_val = "",
       string userName_val = "", string fullName_val = "", string email_val = "",
       string phoneNumber_val = "", string homeAddress_val = "", string city_val = "",
       float creditPoint_val = 0, bool isListed = false, vector<Skill*> skillsList_val = {},
       float minimumHostRatingScore_val = 0, vector<string> historyBooking_val = {},
       vector<Rating> skillRating_val = {}, float avgHostRating = 0);

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
    string getUserNamedById(string userId);
    void updateCreditInFile(string userId, float newCreditPoint);
    void topUpCreditPoints(string userId, float additionalCreditPoint);
    void getCurrentCreditPoints(string userId);
    void updatePasswordInFile();
    // Getter function for creditPoint
    float getCreditPoint() const;
    // Setter function for creditPoint
    void setCreditPoint(float newCreditPoint);
    string getUsername() const;
    //Get avgRating
    float calculateAvgHostRating(string userID);
    void updateAvgHostRating();
    void saveAvgRatingToFile(const std::string& userID);
    float getHostRatingByUserID(const std::string &userID);
    void setAvgHostRating(float amount);
    float calculateAvgSupporterRating(string userID);
    void appendSupporterRatingToFile(const std::string& userID, float supporterRating);
    string findSupporterIDbyRequestID(const std::string& requestID);
    float calculateSkillRating(const std::string &supporterID, const std::string &skillName) ;

    // SKILL
    void createAndAddSkill(const std::string &skillName, float creditPerHour);
    void saveSkillsInFile(string userID);
    void appendSkillsToLine(string& line);
    void saveIsListedInFile(string userID,bool isListed_val);
    void appendIsListedToLine(string& line,bool isListed_val);
    string formatSkills();
    static std::vector<Skill*> extractSkillNameAndPoint(const std::string& skillsStr);
    void showAllAvailableSupporters(const string& userID);
    vector<Skill*> getSkillsLists();
    bool SkillsExistOrNot(const std::string& userId);
    string isListedAsSupporterOrNot(const std::string& userId);
    bool isListedValidation(const string& isListed);
    void setDetail(const std::vector<std::string>& data, const std::string& skillRating);
    static std::string trim(const std::string& str);

    // REQUEST
    bool checkCredit(float creditPerHour);
    void createRequest(string skillRequest, string hostID, string supporterID);
    vector<string> getHistoryBooking(string hostID);
    vector<string> getCurrentBooking(string hostID);
    string getRequestIDByOrder(vector<string> listOfRequestsID);
    void cancelBooking(string requestID);
    vector<string> getHistoryRequest(string supporterID);
    vector<string> getCurrentRequest(string supporterID);
    void acceptRequest(string requestID);
    void rejectRequest(string requestID);
    // Add credit point to supporter and minus for host if request is accepted
    std::pair<std::string, std::string> getSupporterIdAndSkillNameInRequestDat(string requestID);
    string getHostIdInRequestDat(string requestID);
    float getSkillRating(const std::string& skillData, const std::string& skillName);
    float getConsumingPointOfSkillBySupporterId(string supporterID, string skillName);
    void getHostIdAndDeductCreditPoint(string hostID,float consumingPoint);

    // Rating
    // void addHostRating(int score, const std::string &comment);
    // void addSupportRating(int score, const std::string &comment);
    // void getHostRating();
    // void getSupportRating();
    // float getHostAvgRating();
    // float getSpAvgRating();
    // void setListedStatus(bool status);

    // Method to check if the member is listed
    bool isMemberListed() const;    

    void showSupporterInfo();
    void saveMinimumHostRating(const std::string& filename, const string& userId);
    void deleteDefaultHostRatingScore(const std::string& userId);



    //RATING SCORE (SKILL,SUPPORTER AND HOST RATING)
    string getRequestIdByOrderNumber(const vector<string>& requestIdVct, int num);
    // SkillAndSupporterRating (Host role)
    void saveSkillAndSupporterRatingToFile(const std::vector<Rating>& skillRating_val,const std::vector<Rating>& supporterRating_val, const std::string& requestId);
    int isHostRatingExistOrNot(const std::string& requestId);
    void saveSkillAndSupporterRatingToFileV2(const std::vector<Rating>& skillRating_val, const std::vector<Rating>& supporterRating_val, const std::string& requestId);
    vector<Rating> getSkillRatingVct();
    vector<Rating> getSupporterRatingVct();
    // HostRating (Supporter role)
    void saveHostRatingToFile(const std::vector<Rating>& hostRating_val, const std::string& requestId);
    void saveHostRatingToFileV2(const std::vector<Rating>& hostRating_val, const std::string& requestId);
    int isSkillAndSupporterRatingExistOrNot(const std::string& requestId);
    vector<Rating> getHostRatingVct();
    // score and comment to all rating
    Rating addScoreAndComment();
    string checkStatus(const string& requestId);



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
    void showDetailSupporterDetail(string& userName);
    bool isValidNumber(const std::string& str);
    Skill getRequestSkillName(string& userName);
    };


#endif

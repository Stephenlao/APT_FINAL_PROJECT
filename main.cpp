#include <iostream>
#include "User.h"
#include "Skill.h"
#include <algorithm>
#include <cctype>
#include <climits>
using std::cin;
using std::cout;

void mainMenu();
void adminMenu(Admin &admin);
void LogInadminMenu();
void LogInRegMemberMenu();
void memberMenu(Member &member);
void hostMenu(Member &member);
void supporterMenu(Member &member);
void HostRatingMenu(Member &member,const string& requestId);
void SupporterRatingMenu(Member &member,const string& requestId);

void LogInadminMenu() {
    int choice;
    cout << "1.Register\n";
    cout << "2.Login\n";
    cout << "3.Back to main menu\n";
    cout << "Enter your choice: ";
    cin >> choice;
    Admin admin;
    switch (choice)
    {
    case 1:
        admin.registerAdmin();
        mainMenu();
        break;
    case 2:
        if (admin.loginAdmin())
        {
            adminMenu(admin);
        }
        else
        {
            cout << "Invalid adminName or password!"
                 << "\n";
        }
        mainMenu();
        break;
    case 3:
        mainMenu();
        break;
    default:
        cout << "Invalid choice!"
             << "\n";
        break;
    }
}

void adminMenu(Admin &admin) {
    int choice;
    cout << "\nAdmin menu\n";
    cout << "1.View admin information\n";
    cout << "2.Reset member password\n";
    cout << "3.Back to main menu\n";
    cout << "Enter your choice: ";
    cin >> choice;
    switch (choice)
    {
    case 1:
        admin.showInfo();
        mainMenu();
        break;
    case 2:
        admin.resetMemberPassword();
        mainMenu();
        break;
    case 3:
        mainMenu();
        break;
    default:
        cout << "Invalid choice!"
             << "\n";
        break;
    }
}

// ex for pull

void LogInRegMemberMenu()
{
    int choice;
    cout << "1.Register\n";
    cout << "2.Login\n";
    cout << "3.Create new password\n";
    cout << "4.Back to main menu\n";
    cout << "Enter your choice: ";
    cin >> choice;
    Member member;

    // Store the result of loginMember in a variable
    int loginResult;

    switch (choice)
    {
    case 1:
        member.registerMember();
        mainMenu();
        break;
    case 2:
        loginResult = member.loginMember();
        if (loginResult == 0)
        {
            mainMenu();
        }
        else if (loginResult == 1)
        {
            memberMenu(member);
        }
        else
        {
            mainMenu();
        }
        break;
    case 3:
        member.updatePasswordInFile();
        mainMenu();
        break;
    case 4:
        mainMenu();
        break;
    default:
        cout << "Invalid choice!"
             << "\n";
        break;
    }
}


vector <Member> availableList;
void memberMenu(Member &member)
{
    AvailableList availableList;
    string userNameOfSupporter;
    int choice;
    int choiceNumber;
    string skillName;
    float creditPerHour;
    cout << "\nMember menu:\n";
    cout << "1.View information\n";
    cout << "2.Add skills\n";
    cout << "3.Listed as supporter\n";
    cout << "4.View all available supporters\n";
    cout << "5.Host action\n";
    cout << "6.Supporter action\n";
    cout << "7.Back to main menu\n";
    cout << "Enter your choice: ";
    cin >> choice;
    string choice1;
    bool isListed;
    switch (choice)
    {
    case 1:
        member.showInfo();
        memberMenu(member);
        break;
    case 2:
        cout << "Enter your skill: ";
        std::getline(cin >> std::ws, skillName);

        cout << "Enter credit point per hour: ";
        cin >> creditPerHour;
        

        member.createAndAddSkill(skillName,creditPerHour);
        member.saveSkillsInFile(member.getUserId());
        memberMenu(member);
        break;
    case 3:
       while (true) {
        std::cout << "Do you want to listed yourself as a supporter (list/unlist): ";
        std::cin >> choice1;

        // Convert the input to lowercase for case-insensitive comparison
        std::transform(choice1.begin(), choice1.end(), choice1.begin(), ::tolower);

        string isListed_value = member.isListedAsSupporterOrNot(member.getUserId());
        // check skill is not exist and isListed = false
        // Check if the user doesn't have skills and is not listed as a supporter
        if (!member.SkillsExistOrNot(member.getUserId()) && !member.isListedValidation(isListed_value)) {
            cout << "You have not created skills yet! Please create skills before listing as a supporter!" << "\n";
            memberMenu(member);
            // No need for the choice1 check here as the action is independent of choice1
            break;

        // Check if the user has skills but is not listed as a supporter (False)
        } else if (member.SkillsExistOrNot(member.getUserId()) && !member.isListedValidation(isListed_value)) {
            if (choice1 == "list") {
                isListed = true;
                member.deleteDefaultHostRatingScore(member.getUserId());
                member.saveMinimumHostRating("members.dat",member.getUserId());
                // Do u want to enter minimum host rating score (yes/no)
                // if no continue the next
                // if yes let user to enter score rating from 1 to 5. If they enter any number not in range 1 to 5. Re-ask
                // save to minimumHostRating attrs
                // save to file last line
                break;
                // Code to list the member as a supporter should be added here
            } else {
                cout << "Quit!\n";
                memberMenu(member);
                break;
            }
          


            // The user has skills and is already listed as a supporter (True)
        } else {
            if (choice1 == "list") {
                cout << "You are already a supporter!" << "\n";
                memberMenu(member);
                break;
            } else {
                isListed = false;
                break;
                // Code to unlist the member should be added here
            }
          
        }
        std::cout << "Please type 'list' or 'unlist'." << std::endl;
}

        if (isListed) {
            member.saveIsListedInFile(member.getUserId(),isListed);
            cout << "Listed successfully!\n";
        } else {
            member.saveIsListedInFile(member.getUserId(),isListed);
            cout << "Unlist successfully!\n";
        };
        memberMenu(member);
        break;
    case 4:
    {

    member.showAllAvailableSupporters(member.getUserId());
    for (const auto &skillPtr : member.getSkillsLists()) {
        // No need to delete, as smart pointers manage memory automatically
    }
   
    memberMenu(member);
    break;
}
    case 5:
        hostMenu(member);
        memberMenu(member);

    case 6:
        supporterMenu(member);
        memberMenu(member);

    case 7:
        mainMenu();
        break;
    default:
        cout << "Invalid choice!"
             << "\n";
        break;
    }
}

void guestMenu()
{
    int choice;
    cout << "1. View supporters\n";
    cout << "2. Register member\n";
    cout << "3. Back to main menu\n";
    cout << "Enter your choice: ";
    cin >> choice;
    Guest guest;
    Member member;
    switch (choice)
    {
    case 1:
        guest.viewSupporters();
        mainMenu();
        break;
    case 2:
        member.registerMember();
        mainMenu();
        break;
    case 3:
        mainMenu();
        break;
    default:
        cout << "Invalid choice!"
             << "\n";
        break;
    }
}



void hostMenu(Member &member){
    int choice;
    cout << "Host menu:\n";
    cout << "1. View current booking requests\n";
    cout << "2. View history booking requests\n";
    cout << "Enter your choice: ";
    cin >> choice;
    vector<string> listOfRequestsID;
    vector<string> listOfHistoryRequest;
    string requestID;
    string input;
    int number;
    switch (choice)
    {
    case 1:
        listOfRequestsID = member.getCurrentBooking(member.getUserId());
        
        if (listOfRequestsID[0] == "error"){
            break;
        } else {
            requestID = member.getRequestIDByOrder(listOfRequestsID);
            member.cancelBooking(requestID);
            break;
        }
    case 2:
        listOfHistoryRequest = member.getHistoryBooking(member.getUserId());
        // if (listOfHistoryRequest[0] == "error"){
        //     break;
        // }

        cout << "Enter number for choosing rating supporter (or press x to quit): ";
        cin >> input;

        if (input == "x" || input == "X") {
            cout << "Exiting\n";
            break;
        };



        number = std::stoi(input);
        if (member.getRequestIdByOrderNumber(listOfHistoryRequest,number) == "") {
            cout << "Incorrect order number!\n";
            memberMenu(member);
            break;
        } else {
            string requestId_val = member.getRequestIdByOrderNumber(listOfHistoryRequest,number);
            if (member.checkStatus(requestId_val) == "Accepted" && member.isSkillAndSupporterRatingExistOrNot(requestId_val) == 1 ) {
                cout << "\n\nYou have already rating.Thank you!\n\n";
                memberMenu(member);
           
            } else if(member.checkStatus(requestId_val) == "Rejected") {
                cout << "\n\nSorry! this booking is rejected. You can not rating!\n\n";
                memberMenu(member);

            } else if(member.checkStatus(requestId_val) == "Accepted") {
                cout << "\nYou are eligible for rating!\n";
                HostRatingMenu(member,requestId_val);            
            } else {
                cout << "\n\nSorry! this booking is cancel. You can not rating!\n\n";
                memberMenu(member);
            }
            break;
        }
    default:
        cout << "Invalid choice!"
             << "\n";
        break;
    }
}

void supporterMenu(Member &member){
    int choice;
    cout << "Supporter menu:\n";
    cout << "1. View all current requests\n";
    cout << "2. View all history requests\n";
    cout << "Enter your choice: ";
    cin >> choice;
    vector<string> listOfRequestsID;
    vector<string> listOfHistoryRequest;
    string requestID;
    string action;
    string input;
    int number;
    switch (choice)
    {
    case 1:
        listOfRequestsID = member.getCurrentRequest(member.getUserId());
        
        if (listOfRequestsID[0] == "error"){
            break;
        } else {
            requestID = member.getRequestIDByOrder(listOfRequestsID);
            if (requestID == "x" || requestID == "X") {
                memberMenu(member);
            } else {
                cout << "Choose an action for this request (accept/reject): ";
                cin >> action;
                if (action == "accept") {
                // Update the status of the request to Accepted
                member.acceptRequest(requestID);
                std::pair<std::string, std::string> supporterIdAndSkill = member.getSupporterIdAndSkillNameInRequestDat(requestID);
                float consumingPoint = member.getConsumingPointOfSkillBySupporterId(supporterIdAndSkill.first, supporterIdAndSkill.second);
                string hostId = member.getHostIdInRequestDat(requestID);
                member.getHostIdAndDeductCreditPoint(hostId,consumingPoint);
                break;
                } else if (action == "reject") {
                // Update the status of the request to Rejected
                member.rejectRequest(requestID);
                break;
                } else {
                std::cout << "Invalid action. Please choose 'accept' or 'reject'." << std::endl;
                }   
                break;

            }
            

        }
    case 2:
    // debug getHistoryRequest
        listOfHistoryRequest = member.getHistoryRequest(member.getUserId());
        if (listOfHistoryRequest[0] == "error"){
            break;
        }

        cout << "Enter number for choosing rating supporter (or press x to quit): ";
        cin >> input;

        if (input == "x" || input == "X") {
            cout << "Exiting...\n";
            break;
        }

        number = std::stoi(input);
        if (member.getRequestIdByOrderNumber(listOfHistoryRequest,number) == "") {
            cout << "Incorrect order number!\n";
            memberMenu(member);
            break;
        } else {
            string requestId_val = member.getRequestIdByOrderNumber(listOfHistoryRequest,number);
            if (member.checkStatus(requestId_val) == "Accepted" && member.isHostRatingExistOrNot(requestId_val) == 1) {
                cout << "\n\nYou have already rated.Thank you!\n\n";
                memberMenu(member);
              
            } else if(member.checkStatus(requestId_val) == "Rejected") {
                cout << "\n\nSorry! this booking is rejected. You can not rating!\n\n";
                memberMenu(member);
            } else if (member.checkStatus(requestId_val) == "Accepted") {
                cout << "\n\nYou are eligible for rating!\n\n";
                SupporterRatingMenu(member,requestId_val);
            } else  {
                cout << "\n\nSorry! this rating is cancel. You can not rating!\n\n";
                memberMenu(member);
            }
            break;
        }
        break;
    default:
        cout << "Invalid choice!"
             << "\n";
        break;
    }
}

void HostRatingMenu(Member &member,const string& requestId) {
    int choice;
    cout << "Host Rating menu:\n";
    cout << "1. Skill and Supporter rating\n";
    cout << "2. Back to member menu\n";
    cout << "Enter your choice: ";
    cin >> choice;
    Rating skillRating;
    Rating supporterRating;
    vector<Rating> skillRatingVct;
    vector<Rating> supporterRatingVct;

    switch (choice)
    {
    case 1:
        // check whether skill and supporter is whether create if yes => not allow to user enter twice
        if (member.isSkillAndSupporterRatingExistOrNot(requestId) == 2) {
            // if host rating has already exist
            if (member.isHostRatingExistOrNot(requestId) == 1) {
                cout << "Skill rating V2\n";
                skillRating = member.addScoreAndComment();
                skillRatingVct = member.getSkillRatingVct();
                skillRatingVct.push_back(skillRating);
                cout << "\n";

                cout << "Supporter rating V2\n";
                supporterRating = member.addScoreAndComment();
                supporterRatingVct = member.getSupporterRatingVct();
                supporterRatingVct.push_back(supporterRating);
                member.saveSkillAndSupporterRatingToFileV2(skillRatingVct,supporterRatingVct,requestId);
                cout << "\n\n";
                HostRatingMenu(member,requestId);

        } else {
                cout << "Skill rating\n";
                skillRating = member.addScoreAndComment();
                skillRatingVct = member.getSkillRatingVct();
                skillRatingVct.push_back(skillRating);
                cout << "\n";

                cout << "Supporter rating\n";
                supporterRating = member.addScoreAndComment();
                supporterRatingVct = member.getSupporterRatingVct();
                supporterRatingVct.push_back(supporterRating);
                member.saveSkillAndSupporterRatingToFile(skillRatingVct,supporterRatingVct,requestId);
                cout << "\n\n";
                HostRatingMenu(member,requestId);
            }
        } else {
            cout << "\nSorry rating is implemeted once only. You have already rating this supporter!\n\n";
            HostRatingMenu(member,requestId);
        }
        break;
    case 2:
        memberMenu(member);
        break;
    default:
        cout << "Invalid choice!\n";
        memberMenu(member);
        break;
    }
}



void SupporterRatingMenu(Member &member,const string& requestId) {
    int choice;
    cout << "Supporter Rating menu:\n";
    cout << "1. Host rating\n";
    cout << "2. Back to member menu\n";
    cout << "Enter your choice: ";
    cin >> choice;
    Rating hostRating;
    vector<Rating> hostRatingVct;

    switch (choice)
    {
    case 1:
        if (member.isHostRatingExistOrNot(requestId) == 2) {
            // skill and supporter rating is exist
            if (member.isSkillAndSupporterRatingExistOrNot(requestId) == 1) {
                hostRating = member.addScoreAndComment();
                hostRatingVct = member.getHostRatingVct();
                hostRatingVct.push_back(hostRating);
                member.saveHostRatingToFile(hostRatingVct,requestId);
                cout << "\n\n";
                SupporterRatingMenu(member,requestId);
                // if skill and supporter rating is not exist
            } else {
                hostRating = member.addScoreAndComment();
                hostRatingVct = member.getHostRatingVct();
                hostRatingVct.push_back(hostRating);
                member.saveHostRatingToFileV2(hostRatingVct,requestId);
                cout << "\n\n";
                SupporterRatingMenu(member,requestId);
            }
        } else {
            cout << "\nSorry rating is implemeted once only.You have already rating this host!\n\n";
            SupporterRatingMenu(member,requestId);
        }
        
       
        break;
    case 2:
        memberMenu(member);
        break;
    default:
        cout << "Invalid choice!\n";
        memberMenu(member);
        break;
    }
};


void mainMenu()
{
    int choice;
    bool running = true; // Flag to keep the menu running

    while (running) // Loop to keep showing the menu
    {
        cout << "Use the app as 1. Guest      2. Member       3. Admin        4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        // Clear the input buffer to handle invalid input
        if (cin.fail())
        {
            cin.clear(); // Clear the error flags
            cin.ignore(INT_MAX, '\n'); // Ignore the remaining input
            cout << "Invalid input! Please enter a number." << "\n";
            continue; // Skip the rest of the loop and start over
        }

        switch (choice)
        {
            case 1:
                guestMenu();
                break;

            case 2:
                LogInRegMemberMenu();
                break;

            case 3:
                LogInadminMenu();
                break;

            case 4:
                cout << "Exiting the application.\n";
                running = false; // Stop the loop to exit the application
                exit(0);
                break;

            default:
                cout << "Invalid choice! Please try again." << "\n";
                break; // No need to call mainMenu() again
        }
    }
}



int main()
{
    mainMenu();
}
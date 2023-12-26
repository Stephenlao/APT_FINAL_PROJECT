#include <iostream>
#include "User.h"
#include "Skill.h"
#include <algorithm>
#include <cctype>
using std::cin;
using std::cout;

void mainMenu();
void adminMenu(Admin &admin);
void LogInadminMenu();
void LogInRegMemberMenu();
void memberMenu(Member &member);

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
    cout << "5.Back to main menu\n";
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
        std::cout << "Do you want to listed yourself as a supporter (yes/no): ";
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
            if (choice1 == "yes") {
                isListed = true;
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
            if (choice1 == "yes") {
                cout << "You are already a supporter!" << "\n";
                memberMenu(member);
                break;
            } else {
                isListed = false;
                break;
                // Code to unlist the member should be added here
            }
          
        }
        std::cout << "Please type 'yes' or 'no'." << std::endl;
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

    member.showAllAvailableSupporters();
    for (const auto &skillPtr : member.getSkillsLists()) {
        // No need to delete, as smart pointers manage memory automatically
    }
   
    memberMenu(member);
    break;
}

    case 5:
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
void mainMenu()
{
    int choice;
    cout << "Use the app as 1. Guest      2. Member       3. Admin        4. Exit\n";
    cout << "Enter choice: ";
    cin >> choice;
    Member member;

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
        exit(0);
    default:
        cout << "Invalid choice!"
             << "\n";
        break;
    }
}

int main()
{
    mainMenu();
    // Member mem1("tuananh", "tuananh", "tuananh", "tuananh", "tuananh@example.com", "1234567890", "123 Street, City", "Sai Gon", 20);
    // Member mem2("tom", "tom", "tom", "tom Name", "tuananh@example.com", "1234567890", "123 Street, City", "Sai Gon", 20);
    // Member mem3("tit", "tom", "tom", "tom Name", "tuananh@example.com", "1234567890", "123 Street, City", "Sai Gon", 20);

    // mem1.showInfo();
    // mem1.createAndAddSkill("C++", 200);
    // mem1.createAndAddSkill("Java", 200);
    // mem1.createAndAddSkill("ReactJS", 200);

    // mem1.showInfo();
    // mem1.addHostRating(5, "Verygood");
    // mem1.addHostRating(3, "Normal");
    // mem1.addHostRating(1, "Bad");
    // mem1.addSupportRating(4, "Good");
    // mem1.addSupportRating(1, "OK");
    // cout << "Host Rating: "
    //      << "\n";
    // mem1.getHostRating();
    // cout << "Support Rating: "
    //      << "\n";

    // mem1.getSupportRating();

    // cout << "Support avg rating: " << mem1.getSpAvgRating() << "\n";
    // mem1.setListedStatus(true);
    // mem2.setListedStatus(true);
    // mem3.setListedStatus(true);
    // AvailableList list1;
    // list1.addUser(mem1);
    // list1.addUser(mem2);
    // // list1.addUser(mem3);

    // list1.displayListedMembers();
}
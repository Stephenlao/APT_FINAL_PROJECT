#include <iostream>
#include "User.cpp"
using std::cin;
using std::cout;

void mainMenu();

void guestMenu() {
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
        cout << "Invalid choice!" << "\n";
        break;
    }
}

void memberMenu() {
    int choice;
    cout << "1.Register\n";
    cout << "2.Login\n";
    cout << "3.Create new password\n";
    cout << "4.Back to main menu\n";
    cout << "Enter your choice: ";
    cin >> choice;
    Member member;
    switch (choice)
    {
    case 1:
        member.registerMember();
        mainMenu();
        break;
    case 2:
        int loginStatus;
        loginStatus = member.loginMember();
        if (loginStatus == 0) {
            cout << "Your password is reset by admin. Please go to main menu and create a new password!" << "\n";
        } else if (loginStatus == 1) {
            member.showInfo();
        } else {
            cout << "Incorrect username or password" << "\n";
        }
        mainMenu();
        exit(0);
    case 3:
        member.createNewPassword();
        mainMenu();
        break;
    case 4:
        mainMenu();
        break;
    default:
        cout << "Invalid choice!" << "\n";
        break;
    }
}


void adminMenu() {
    int choice;
    cout << "1.Register\n";
    cout << "2.Login\n";
    cout << "3.Reset member password\n";
    cout << "4.Back to main menu\n";
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
        if (admin.loginAdmin()) {
            admin.showInfo();
        } else {
            cout << "Invalid adminName or password!" << "\n"; 
        }
        mainMenu();
        break;
    case 3:
        admin.resetMemberPassword();
        mainMenu();
        break;
    case 4:
        mainMenu();
        break;
    default:
        cout << "Invalid choice!" << "\n";
        break;
    }

}


void mainMenu() {
    int choice;
        cout << "Use the app as 1. Guest      2. Member       3. Admin        4. Exit\n";
        cout <<  "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            guestMenu();
            break;

        case 2:
            memberMenu();
            break;
        
        case 3:
            adminMenu();
            break;
        case 4:
            cout << "Exiting the application.\n";
            exit(0);
        default:
            cout << "Invalid choice!" << "\n";
            break;
        }

}
int main() {
    mainMenu();
}

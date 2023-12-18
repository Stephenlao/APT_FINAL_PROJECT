#include <iostream>
#include "User.cpp"
using std::cout;
using std::cin;
void mainMenu();

void adminMenu() {
    int choice;
    cout << "1.Login\n";
    cout << "2.Reset member password\n";
    cout << "3.Back to main menu\n";
    cout << "Enter your choice: ";
    cin >> choice;
    Admin admin;
    switch (choice)
    {
    case 1:
        if (admin.loginAdmin()) {
            admin.showInfo();
        } else {
            cout << "Invalid adminName or password!" << "\n"; 
        }
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
        member.loginMember();
        mainMenu();
    case 3:
        member.updatePasswordInFile();
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
void mainMenu() {
    int choice;
        cout << "Use the app as 1. Guest      2. Member       3. Admin        4. Exit\n";
        cout <<  "Enter choice: ";
        cin >> choice;
        Member member;

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
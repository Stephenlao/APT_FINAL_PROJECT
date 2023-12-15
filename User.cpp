#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
using std::cin;
using std::cout;
using std::string;
using std::ctime;
using std::fstream;
using std::stringstream;


class User {
    private:
        string userId;
        string password;
    public:
        User(string userId_val = "", string password_val = "")
        : userId(userId_val), password(password_val) {};

        void showInfo() {
            cout << "UserID: " << userId <<  ", password: " << password << "\n"; 
        }


        // hash password function

        unsigned long hashPassword(const std::string& password) {
            unsigned long hash = 5381; // A prime number as initial hash value
            int c;

            for (auto str_iter = password.begin(); str_iter != password.end(); ++str_iter) {
                c = *str_iter;
                hash = ((hash << 5) + hash) + c; // hash * 33 + c
            }
            return hash;
        }


        bool checkValidatePassword(string pwd) {
            if (pwd.length() < 8 || pwd.length() > 20) {
                return false; // Check length
            }

            bool hasLower = false, hasUpper = false, hasDigit = false, hasSpecial = false;

            // Check for lower case, upper case, and digit
            for (int i = 0; i < pwd.length(); i++) {
                if (islower(pwd[i])) hasLower = true;
                if (isupper(pwd[i])) hasUpper = true;
                if (isdigit(pwd[i])) hasDigit = true;
            }

            // Special characters
            char specialChar[] = {'!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '-', '+', '=', '<', '>', '?'};
            for (size_t i = 0; i < pwd.length(); i++) {
                for (size_t j = 0; j < sizeof(specialChar)/sizeof(char); j++) {
                    if (pwd[i] == specialChar[j]) {
                        hasSpecial = true;
                        break; // Break inner loop
                    }
                }
            }
            // Check if all conditions are met
            return hasLower && hasUpper && hasDigit && hasSpecial;
        }

        bool isFileEmpty(std::ifstream& pfile) {
            return pfile.peek() == std::fstream::traits_type::eof();
        }


        string getUserId() {
            return userId;
        }

        void setUserId(string userId_val) {
            userId = userId_val;
        }

        string getPassword() {
            return password;
        }

        void setPassword(string password_val) {
            password = password_val;
        }

};

class Member : public User {
    private:
        string userName;
        string fullName;
        string email;
        string phoneNumber;
        string homeAddress;
        int creditPoint;
    
    public:
        Member(string userId_val = "", string password_val = "",
        string userName_val = "", string fullName_val = "", string email_val = "",
        string phoneNumber_val = "", string homeAddress_val = "", int creditPoint_val = 0)

        : User(userId_val,password_val), userName(userName_val),
        fullName(fullName_val), email(email_val), phoneNumber(phoneNumber_val),
        homeAddress(homeAddress_val), creditPoint(creditPoint_val) {};

        void showInfo() {
            // User::showInfo();
            cout << "Member user name: " << userName << ", fullName: " << fullName
            << ", email: " << email << ", phoneNumber: " << phoneNumber << 
            ", home address: " << homeAddress << " ,credit point: " << creditPoint << "\n";
        }

       

        void registerMember() {
            cout << "Enter username: ";
            std::getline(cin >> std::ws, userName);
            cout << "Enter your full name: ";
            std::getline(cin >> std::ws, fullName);
            cout << "Enter your email: ";
            cin >> email;
            cout << "Enter your phone number: ";
            cin >> phoneNumber;
            cin.ignore(); // To consume the '\n' character
            cout << "Enter your home address: ";
            std::getline(cin >> std::ws, homeAddress);

            cout << "Do you accept to pay $20 to use the system? (yes/no): ";
            string response;
            std::getline(cin, response);
            if (response != "yes") {
                cout << "Registration cancelled.\n";
                return;
            }

            // Generating random user ID
            srand(time(NULL)); // Seed for random number generation
            int randomID = rand() % 10000; // Generate a random number
            string userId = User::getUserId();
            userId = "M" + std::to_string(randomID);
            User::setUserId(userId);


            cout << "Password should have at least minimum 8 digits and maximum 20 digits\n "
                <<  "Have at least 1 upper character and lower character\n"
                <<  "Have at least 1 digit and contains special character:\n";

            string passwordInput;
            bool isValidPassword = false;

            while(!isValidPassword) {
                cout << "Enter your password: ";
                std::getline(cin, passwordInput);

            if (checkValidatePassword(passwordInput)) {
                cout << "Create password successful!" << "\n";
                isValidPassword = true;
            } else {
                cout << "Please follow the rule to create strong password!";
            }
        }


            string password = User::getPassword();
            password = std::to_string(hashPassword(passwordInput)); // Hashing the password

            // set password to attrs password to save in User class
            User::setPassword (password);


            creditPoint = 20; // Setting initial credit points


            // Save to file
            fstream outFile("members.dat", std::ios::app | std::ios::out); // Append mode
            if (outFile.is_open()) {

                std::ifstream inFile("members.dat");
                if (isFileEmpty(inFile)) {
                    outFile << "userID,Password,UserName,FullName,Email,PhoneNumber,HomeAddress,CreditPoint\n";
                }
                inFile.close();

                outFile << userId << "," << password<< "," << userName << "," 
                << fullName << "," << email << "," << phoneNumber << "," 
                << homeAddress << "," << creditPoint << "\n";

                outFile.close();
            } else {
                cout << "Unable to open file.\n";
            }

            cout << "Registration successful. Your user ID is: " << User::getUserId() << "\n";
        }        



        void loginMember() {
            string usernameInput, passwordInput;
            cout << "Enter username: ";
            cin >> usernameInput;
            cout << "Enter password: ";
            cin >> passwordInput;

            // Convert the password to a hash

            unsigned long hashedPassword = hashPassword(passwordInput);

            fstream inFile("members.dat", std::ios::in);
            if (!inFile.is_open()) {
                std::cerr << "Unable to open file.\n";
                return;
            }

            string line, filePassword, temp;
            while (getline(inFile, line)) {
                stringstream ss(line);
                // ignore the memeberID start with password store in file
                getline(ss, temp, ',');
                getline(ss, filePassword, ','); // save password to filePassword
                getline(ss, userName, ','); // save username to userName


                // Compare the username and hashed password
                if (usernameInput == userName && std::to_string(hashedPassword) == filePassword) {
                    // extract each information in members.dat and save it in each attributes
                    getline(ss, fullName, ',');
                    getline(ss, email, ',');
                    getline(ss, phoneNumber, ',');
                    getline(ss, homeAddress, ',');
                    ss >> creditPoint;
                    return;
                    // return true;
                }
            }
            // return false;
        }
        };


class Admin : public User {
    private:
        string adminName;
        string email;
    public:
        Admin(string adminId_val = "", string password_val = "", string adminName_val = "", string email_val = "")
        : User(adminId_val,password_val), adminName(adminName_val), email(email_val) {};


        void registerAdmin() {
            cout << "Enter admin name: ";
            std::getline(cin >> std::ws, adminName);
            cout << "Enter your email: ";
            cin >> email;


            // Generating random admin ID
            srand(time(NULL)); // Seed for random number generation
            int randomID = rand() % 10000; // Generate a random number
            string adminId = User::getUserId();
            adminId = "A" + std::to_string(randomID);
            User::setUserId(adminId);
            cin.ignore();


            cout << "Password should have at least minimum 8 digits and maximum 20 digits\n "
                <<  "Have at least 1 upper character and lower character\n"
                <<  "Have at least 1 digit and contains special character:\n";

            string passwordInput;
            bool isValidPassword = false;

            while(!isValidPassword) {
                cout << "Enter your password: ";
                std::getline(cin, passwordInput);

            if (checkValidatePassword(passwordInput)) {
                cout << "Create password successful!" << "\n";
                isValidPassword = true;
            } else {
                cout << "Please follow the rule to create strong password!";
            }
        }

            // save password to password attrs in User because password is in User class
            string password = User::getPassword();
            password = std::to_string(hashPassword(passwordInput)); // Hashing the password

            // set password to attrs password to save in User class
            User::setPassword (password);


            // Save to file
            fstream outFile("admin.dat", std::ios::app | std::ios::out); // Append mode
            if (outFile.is_open()) {

                std::ifstream inFile("admin.dat");
                if (isFileEmpty(inFile)) {
                    outFile << "userID,Password,adminName,Email\n";
                }
                inFile.close();

                outFile << adminId << "," << password<< "," << adminName << "," 
                 << email << "\n";

                outFile.close();
            } else {
                cout << "Unable to open file.\n";
            }
            cout << "Registration successful. Your user ID is: " << User::getUserId() << "\n";
        }        

    void loginAdmin() {
        string adminnameInput, passwordInput;
        cout << "Enter username: ";
        std::getline(cin >> std::ws, adminnameInput);
        cout << "Enter password: ";
        std::getline(cin >> std::ws, passwordInput);

        // Convert the password to a hash

        unsigned long hashedPassword = hashPassword(passwordInput);

        fstream inFile("admin.dat", std::ios::in);
        if (!inFile.is_open()) {
            std::cerr << "Unable to open file.\n";
            return;
        }

        string line, filePassword, temp;
        while (getline(inFile, line)) {
            stringstream ss(line);
            // ignore the AdminID start with password, store in file
            getline(ss, temp, ',');
            getline(ss, filePassword, ','); // save password to filePassword
            getline(ss, adminName, ','); // save username to userName


            // Compare the username and hashed password
            if (adminnameInput == adminName && std::to_string(hashedPassword) == filePassword) {
                // extract each information in admin.dat and save it in each attributes
                ss >> email;
                return;
                // return true;
            }
        }

        // return false;
    }

    string getAdminName() {
        return adminName;
    }

    void setAdminName(string adminName_val) {
        adminName = adminName_val;
    }

    string getEmail() {
        return email;
    } 

    void setEmail(string email_val) {
        email = email_val;
    }

    void showInfo() {
        cout << "Admin name: " << adminName << ", Email: " << email << "\n";
    }
};


class Guest : public User {
    public:
        Guest(string guestId_val = "", string password_val = "")
        : User(guestId_val,password_val) {};

        void viewSupporters() {
            fstream myFile;
            myFile.open("members.dat", std::ios::in);
            if (!myFile.is_open()) {
                std::cerr << "Unable to open file!" << "\n";
                return;
            }
            cout << "All supporters: " << "\n\n";
            string line;

            // Skip the first line
            if (!std::getline(myFile, line)) {
                std::cerr << "Error or empty file.\n";
                return;
            }

            while(getline(myFile, line)) {
                stringstream ss(line);
                string fullName, email, phoneNumber, homeAddress, creditPoint, temp1,temp2,temp3;
                getline(ss, temp1, ',');
                getline(ss, temp2, ',');
                getline(ss, temp3, ',');
                // ignore first three information in file which is 
                // ID, password and username

                getline(ss, fullName, ',');
                getline(ss, email, ',');
                getline(ss, phoneNumber, ',');
                getline(ss, homeAddress, ',');
                getline(ss, creditPoint, ',');
                // only print these information only for guest
                cout << "Full name: " << fullName << " ,email: " << email << ",phone number: "
                << phoneNumber <<", Home address: " << homeAddress << ", Credit point: " << creditPoint << "\n\n";   
            }
        };
};


// things to do:
// 1. add title in members.dat: FINISH
// 2. validate password (password should have min 8 digits to max 20 digits, contains special characters, digits, num,
// upper, lowercase,etc...: FINISH
// 3. login() method: FINISH
// 4. Member view all his/her information: FINISH
// 5. A non member can register to become a member (info recorded in file): ALMOST FINISH (GUEST CAN REGISTER TO BECOME MEMBER)
// 6. A non-member view all supporters detail: FINISH
// 7. An admin can login with predefined username and password,
// and can reset password for any member: PENDING
// 8. Fix while loop main menu



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
    cout << "3.Back to main menu\n";
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
        member.showInfo();
        mainMenu();
        exit(0);
    case 3:
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
        admin.loginAdmin();
        admin.showInfo();
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
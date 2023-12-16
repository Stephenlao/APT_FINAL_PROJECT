#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include <vector>
using std::cin;
using std::cout;
using std::string;
using std::ctime;
using std::fstream;
using std::stringstream;
using std::vector;


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
            this->userId = userId_val;
        }

        string getPassword() {
            return password;
        }

        void setPassword(string password_val) {
            this->password = password_val;
        }

};

class Member : public User {
    private:
        string userName;
        string fullName;
        string email;
        string phoneNumber;
        string homeAddress;
        string city;
        int creditPoint;
    
    public:
        Member(string userId_val = "", string password_val = "",
        string userName_val = "", string fullName_val = "", string email_val = "",
        string phoneNumber_val = "", string homeAddress_val = "", string city_val = "", int creditPoint_val = 0)

        : User(userId_val,password_val), userName(userName_val),
        fullName(fullName_val), email(email_val), phoneNumber(phoneNumber_val),
        homeAddress(homeAddress_val), city(city_val), creditPoint(creditPoint_val) {};

        void showInfo() {
            // User::showInfo();
            cout << "Member user name: " << userName << ", fullName: " << fullName
            << ", email: " << email << ", phoneNumber: " << phoneNumber << 
            ", home address: " << homeAddress << ",city: " << city << " ,credit point: " << creditPoint << "\n";
        }

        string createPassword() {
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
            User::setPassword(password);
            return password;

        }

        // function to check username is unique or not
        bool isUsernameUnique(const string& userName) {
            fstream myFile("members.dat", std::ios::in);
            if (!myFile.is_open()) {
                std::cerr << "Cannot open file!\n";
                return false;
            }

            string line, fileUserId, filePassword, fileUsername;
            while (getline(myFile, line)) {
                stringstream ss(line);
                getline(ss, fileUserId, ',');
                getline(ss, filePassword, ',');
                getline(ss, fileUsername, ',');
                if (fileUsername == userName) {
                    myFile.close();
                    return false; // Username is not unique
                }
            }
            myFile.close();
            return true; // Username is unique
        }


        void registerMember() {
            bool uniqueUsername;
            do
            {
                cout << "Enter username: ";
                std::getline(cin >> std::ws, userName);
                uniqueUsername = isUsernameUnique(userName);
                if (!uniqueUsername) {
                    cout << "This username is already exist. Please enter a different username\n ";
                }            
            } 
            while (!uniqueUsername);
            
         
            cout << "Enter your full name: ";
            std::getline(cin >> std::ws, fullName);
            cout << "Enter your email: ";
            cin >> email;
            cout << "Enter your phone number: ";
            cin >> phoneNumber;
            cin.ignore(); // To consume the '\n' character
            cout << "Enter your home address: ";
            std::getline(cin >> std::ws, homeAddress);

            while (true) {
                cout << "Enter your city (Ha Noi or Sai Gon): ";
                std::getline(cin >> std::ws, city);

                // Convert city to lowercase for case-insensitive comparison
                for (auto &c : city) {
                    c = tolower(c);
                }

                if (city == "ha noi" || city == "sai gon") {
                    break; // Exit the loop if a valid city is entered
                } else {
                    cout << "Invalid city. Please enter either 'Ha Noi' or 'Sai Gon'.\n";
                }
            }

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

            // called method createpassword
            string password = createPassword();

            creditPoint = 20; // Setting initial credit points


            // Save to file
            fstream outFile("members.dat", std::ios::app | std::ios::out); // Append mode
            if (outFile.is_open()) {

                std::ifstream inFile("members.dat");
                if (isFileEmpty(inFile)) {
                    outFile << "userID,Password,UserName,FullName,Email,PhoneNumber,HomeAddress,City,CreditPoint\n";
                }
                inFile.close();

                outFile << userId << "," << password<< "," << userName << "," 
                << fullName << "," << email << "," << phoneNumber << "," 
                << homeAddress << "," << city << "," << creditPoint << "\n";

                outFile.close();
            } else {
                cout << "Unable to open file.\n";
            }

            cout << "Registration successful. Your user ID is: " << User::getUserId() << "\n";
        }        



        int loginMember() {
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
                return 3;
            }

            string line, filePassword, userId;
            while (getline(inFile, line)) {
                stringstream ss(line);
                // ignore the memeberID start with password store in file
                getline(ss, userId, ',');
                getline(ss, filePassword, ','); // save password to filePassword
                getline(ss, userName, ','); // save username to userName


                // tell member that his/her password is reset try to 
                // create new one
                if (usernameInput == userName) {
                    if (filePassword == "") {
                        return 0;
                    }
                }
                
                // Compare the username and hashed password
                if (usernameInput == userName && std::to_string(hashedPassword) == filePassword) {
                    // extract each information in members.dat and save it in each attributes
                    getline(ss, fullName, ',');
                    getline(ss, email, ',');
                    getline(ss, phoneNumber, ',');
                    getline(ss, homeAddress, ',');
                    getline(ss, city, ',');
                    ss >> creditPoint;
                    return 1;
                }
            }
            inFile.close();
            return 2;
        }


        void createNewPassword() {
        string username_val;
        cout << "Please enter username: ";
        std::getline(cin >> std::ws, username_val);
        
        string password;
        fstream myFile;
        myFile.open("members.dat", std::ios::in);
        if (!myFile.is_open()) {
            std::cerr << "Cannot open file!" << "\n";
            return;
        }

        string line;
        bool userNameExists = false;
        bool correctPassword = false;
        bool incorrectPassword = false;
        bool emptyPassword = false;

        while (std::getline(myFile, line)) {
            stringstream ss(line);
            string temp_userID, temp_password, temp_username;
            std::getline(ss, temp_userID, ',');
            std::getline(ss, temp_password, ',');
            std::getline(ss, temp_username, ',');
            if (temp_username == username_val) {
                userNameExists = true;
                string curr_pass;
                cout << "Enter your current password: ";
                cin >> curr_pass;

                unsigned long hashedPassword = hashPassword(curr_pass);
                std::string hashedPasswordStr = std::to_string(hashedPassword);

                if (temp_password == "") {
                    emptyPassword = true;
                } else if (hashedPasswordStr == temp_password) {
                    correctPassword = true;
                } else {
                    incorrectPassword = true;
                }
                break;
            }
        }
        myFile.close();

        if (!userNameExists) {
            cout << "Username does not exist!" << "\n";
            return;
        } else if (incorrectPassword) {
            cout << "Incorrect password!" << "\n";
            return;
        } else if (emptyPassword || correctPassword) {
            cout << "Please create a new password:\n";
            password = createPassword();  // Assuming createPassword() is defined and returns a new password
        }

        // Now, update the password in the file
        fstream myFile1;
        myFile1.open("members.dat", std::ios::in);
        if (!myFile1.is_open()) {
            std::cerr << "Cannot open file path!" << "\n";
            return;
        }

        vector<string> lines;
        while (getline(myFile1, line)) {
            stringstream ss(line);
            string tempId, tempPassword, tempUsername, tempFullname, restOfLine;
            getline(ss, tempId, ',');
            getline(ss, tempPassword, ',');
            getline(ss, tempUsername, ',');
            getline(ss, tempFullname, ',');
            getline(ss, restOfLine);

            if (tempUsername == username_val) {
                string updatedLine = tempId + "," + password + "," + tempUsername + "," + tempFullname + "," + restOfLine;
                lines.push_back(updatedLine);
            } else {
                lines.push_back(line);
            }
        }
        myFile1.close();

        // Write the updated data back to the file
        fstream outFile;
        outFile.open("members.dat", std::ios::out | std::ios::trunc);
        if (!outFile.is_open()) {
            std::cerr << "Cannot open file path!" << "\n";
            return;
        }
        for (const auto& updatedLine : lines) {
            outFile << updatedLine << "\n";
        }
        outFile.close();

        cout << "Password updated successfully.\n";
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

    bool loginAdmin() {
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
            return false;
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
                return true;
            }
        }
        inFile.close();
        return false;
    }


   void resetMemberPassword() {
        fstream myFile;
        myFile.open("members.dat", std::ios::in);
        if (!myFile.is_open()) {
            std::cerr << "Cannot open file path!" << "\n";
            return;
        }

        // Skip the first line in file
        string line;
        if (!getline(myFile, line)) {
            std::cerr << "Error or empty file.\n";
            return;
        }

        string temp1, temp2, username_val;
        vector<string> members;
        int order_num = 1;
        cout << "List of members:\n";
        while (getline(myFile, line)) {
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
        if (choice < 1 || choice > members.size()) {
            std::cerr << "Invalid choice!\n";
            return;
        }

        // Reset password
        stringstream newMemberData;
        for (int i = 0; i < members.size(); i++) {
            if (i == choice - 1) { // User selected
                stringstream ss(members[i]);
                string temp, newPassword = "";
                getline(ss, temp, ','); // M8289 get id of member
                newMemberData << temp << ","; // write to newMemberData
                getline(ss, temp, ','); // Old password
                newMemberData << newPassword << ","; // Reset password
                while (getline(ss, temp, ',')) { // Rest of data
                    newMemberData << temp << ",";
                }
                newMemberData.seekp(-1, newMemberData.cur); // Remove last comma
                newMemberData << "\n";
            } else {
                newMemberData << members[i] << "\n";
            }
        }

        // Write updated data back to file
        myFile.open("members.dat", std::ios::out | std::ios::trunc);
        if (!myFile.is_open()) {
            std::cerr << "Cannot open file path!" << "\n";
            return;
        }
        myFile <<"userID,Password,UserName,FullName,Email,PhoneNumber,HomeAddress,City,CreditPoint\n";
        myFile << newMemberData.str();
        myFile.close();

        cout << "Password reset successfully for user " << choice << ".\n";
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


class Guest {
    public:
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
                string fullName_val, email_val, phoneNumber_val, homeAddress_val,city_val,creditPoint_val, temp1,temp2,temp3;
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
                std::getline(ss, creditPoint_val, ',');
                // only print these information only for guest
                cout << "Full name: " << fullName_val << " ,email: " << email_val << ",phone number: "
                << phoneNumber_val <<", Home address: " << homeAddress_val << ", City: " << city_val 
                << ", Credit point: " << creditPoint_val << "\n\n";   
            }
        };
};
#ifndef USER_AUTH_H
#define USER_AUTH_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

struct UserInfo {
    std::string username;
    std::string password;
    bool isAdmin;
    int customerId;
};

class UserAuth {
private:
    const std::string USERS_FILE = "users.csv";
    UserInfo currentUser;

private:
    std::string hashPassword(const std::string& password) const {
        unsigned long hash = 5381;
        for (char c : password) {
            hash = ((hash << 5) + hash) + c; // hash * 33 + c
        }
        return std::to_string(hash);
    }

    void initializeAdminIfNeeded() {
        std::ifstream file(USERS_FILE);
        if (!file.good()) {
            // File doesn't exist, create it with admin
            registerUser("admin", "admin123", -1, true);
        } else {
            std::string line;
            bool adminFound = false;
            while (std::getline(file, line)) {
                std::stringstream ss(line);
                std::string username;
                std::getline(ss, username, ',');
                if (username == "admin") {
                    adminFound = true;
                    break;
                }
            }
            if (!adminFound) {
                registerUser("admin", "admin123", -1, true);
            }
        }
        file.close();
    }

public:
    UserAuth() : currentUser{"", "", false, -1} {
        initializeAdminIfNeeded();  // Add this line to constructor
    }
    
    bool login(const std::string& username, const std::string& password);
    bool registerUser(const std::string& username, const std::string& password, int customerId, bool isAdmin = false);
    bool isAdmin() const { return currentUser.isAdmin; }
    int getCurrentCustomerId() const { return currentUser.customerId; }
};

#endif
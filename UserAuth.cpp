#include "UserAuth.h"

bool UserAuth::login(const std::string& username, const std::string& password) {
    std::ifstream file(USERS_FILE);
    std::string line;
    
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string storedUsername, storedPassword, isAdminStr, customerIdStr;
        
        getline(ss, storedUsername, ',');
        getline(ss, storedPassword, ',');
        getline(ss, isAdminStr, ',');
        getline(ss, customerIdStr, ',');
        
        if (username == storedUsername && password == storedPassword) {
            currentUser.username = username;
            currentUser.password = password;
            currentUser.isAdmin = (isAdminStr == "1");
            currentUser.customerId = std::stoi(customerIdStr);
            return true;
        }
    }
    return false;
}

bool UserAuth::registerUser(const std::string& username, const std::string& password, int customerId, bool isAdmin) {
    // Check if username already exists
    std::ifstream checkFile(USERS_FILE);
    std::string line;
    while (std::getline(checkFile, line)) {
        std::stringstream ss(line);
        std::string existingUsername;
        getline(ss, existingUsername, ',');
        if (username == existingUsername) {
            return false;
        }
    }
    checkFile.close();

    // Add new user
    std::ofstream file(USERS_FILE, std::ios::app);
    if (file.is_open()) {
        file << username << "," << password << "," << (isAdmin ? "1" : "0") << "," << customerId << "\n";
        file.close();
        return true;
    }
    return false;
}
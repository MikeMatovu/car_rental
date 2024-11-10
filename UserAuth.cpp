#include "UserAuth.h"

bool UserAuth::registerUser(const std::string& username, const std::string& password, int customerId, bool isAdmin) {
    // Check if username exists
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

    // Hash password and save
    std::string hashedPassword = hashPassword(password);
    std::ofstream file(USERS_FILE, std::ios::app);
    if (file.is_open()) {
        file << username << "," << hashedPassword << "," 
             << (isAdmin ? "1" : "0") << "," << customerId << "\n";
        file.close();
        return true;
    }
    return false;
}

bool UserAuth::login(const std::string& username, const std::string& password) {
    std::ifstream file(USERS_FILE);
    std::string line;
    
    std::string hashedAttempt = hashPassword(password);
    
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string storedUsername, storedHash, isAdminStr, customerIdStr;
        
        getline(ss, storedUsername, ',');
        getline(ss, storedHash, ',');
        getline(ss, isAdminStr, ',');
        getline(ss, customerIdStr, ',');
        
        if (username == storedUsername && hashedAttempt == storedHash) {
            currentUser.username = username;
            currentUser.password = storedHash;
            currentUser.isAdmin = (isAdminStr == "1");
            currentUser.customerId = std::stoi(customerIdStr);
            return true;
        }
    }
    return false;
}
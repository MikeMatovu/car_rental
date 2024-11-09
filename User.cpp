#include "User.h"

User::User(int id, std::string n, std::string addr, std::string contact)
    : userID(id)
    , name(n)
    , address(addr)
    , contactInfo(contact) {}

int User::getID() const {
    return userID;
}

void User::viewProfile() const {
    std::cout << "ID: " << userID 
              << ", Name: " << name 
              << ", Address: " << address 
              << ", Contact: " << contactInfo 
              << std::endl;
}
#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>

class User {
protected:
    int userID;
    std::string name;
    std::string address;
    std::string contactInfo;

public:
    User(int id, std::string n, std::string addr, std::string contact);
    
    int getID() const;
    std::string getName() const { return name; }
    std::string getAddress() const { return address; }
    std::string getContact() const { return contactInfo; }
    void viewProfile() const;
};

#endif
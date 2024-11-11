#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "User.h"
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

class Customer : public User {
private:
    int currentRental = -1;

public:
    Customer(int id, std::string n, std::string addr, std::string contact);
    
    void bookCar(int carID);
    void returnCar();
    bool hasRentedCar() const;
    int getCurrentRental() const;
    
    void saveToCSV(std::ofstream& file) const;
    static Customer createFromCSV(const std::string& line);
};

#endif
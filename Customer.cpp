#include "Customer.h"

Customer::Customer(int id, std::string n, std::string addr, std::string contact) 
    : User(id, n, addr, contact) {}

void Customer::bookCar(int carID) { 
    currentRental = carID; 
}

void Customer::returnCar() { 
    currentRental = -1; 
}

bool Customer::hasRentedCar() const { 
    return currentRental != -1; 
}

int Customer::getCurrentRental() const { 
    return currentRental; 
}

void Customer::saveToCSV(std::ofstream& file) const {
    file << getID() << "," 
         << getName() << "," 
         << getAddress() << "," 
         << getContact() << "," 
         << currentRental << "\n";
}

Customer Customer::createFromCSV(const std::string& line) {
    std::stringstream ss(line);
    std::string item;
    std::vector<std::string> row;
    
    while (std::getline(ss, item, ',')) {
        row.push_back(item);
    }
    
    Customer customer(std::stoi(row[0]), row[1], row[2], row[3]);
    if (row.size() > 4 && row[4] != "-1") {
        customer.bookCar(std::stoi(row[4]));
    }
    return customer;
}
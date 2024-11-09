#include "Car.h"

Car::Car(int id, std::string m, std::string mdl, int yr, double price) 
    : carID(id), make(m), model(mdl), year(yr), pricePerDay(price), available(true) {}

void Car::viewDetails() const {
    std::cout << "ID: " << carID 
              << ", Make: " << make 
              << ", Model: " << model 
              << ", Year: " << year 
              << ", Price per day: UGX" << pricePerDay 
              << ", Available: " << (available ? "Yes" : "No") 
              << std::endl;
}

void Car::saveToCSV(std::ofstream& file) const {
    if (file.is_open()) {
        file << std::to_string(carID) << "," 
             << make << "," 
             << model << "," 
             << std::to_string(year) << "," 
             << std::to_string(pricePerDay) << "," 
             << (available ? "1" : "0") << ","
             << getType() << "\n";
    }
}

int Car::getCarID() const { 
    return carID; 
}

bool Car::isAvailable() const { 
    return available; 
}

void Car::rentCar() { 
    available = false; 
}

void Car::returnCar() { 
    available = true; 
}

double Car::getPricePerDay() const { 
    return pricePerDay; 
}

void Car::updatePrice(double newPrice) {
    pricePerDay = newPrice;
}
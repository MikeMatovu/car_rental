// #ifndef CAR_TYPES_H
// #define CAR_TYPES_H

// #include "Car.h"
// #include <string>

// // Derived Class for Sedan
// class Sedan : public Car {
// public:
//     Sedan(int id, std::string m, std::string mdl, int yr, double price) 
//         : Car(id, m, mdl, yr, price) {}

//     void viewDetails() const override {
//         std::cout << "[Sedan] ";
//         Car::viewDetails();
//     }
    
//     std::string getType() const override {
//         return "Sedan";
//     }
// };

// // Derived Class for SUV
// class SUV : public Car {
// public:
//     SUV(int id, std::string m, std::string mdl, int yr, double price) 
//         : Car(id, m, mdl, yr, price) {}

//     void viewDetails() const override {
//         std::cout << "[SUV] ";
//         Car::viewDetails();
//     }
    
//     std::string getType() const override {
//         return "SUV";
//     }
// };

// // Derived Class for Truck
// class Truck : public Car {
// public:
//     Truck(int id, std::string m, std::string mdl, int yr, double price) 
//         : Car(id, m, mdl, yr, price) {}

//     void viewDetails() const override {
//         std::cout << "[Truck] ";
//         Car::viewDetails();
//     }
    
//     std::string getType() const override {
//         return "Truck";
//     }
// };

// #endif
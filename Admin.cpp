#include "Admin.h"
#include "CarTypes.h"
#include <iostream>


Admin::Admin(int id, std::string n, std::string addr, std::string contact)
    : User(id, n, addr, contact) {}

void Admin::addCar(std::vector<Car*>& cars) {
    int id, year, type;
    std::string make, model;
    double price;
    
    std::cout << "\nAdd New Car\n";
    std::cout << "Enter Car ID: ";
    std::cin >> id;
    std::cin.ignore();
    
    std::cout << "Enter Make: ";
    std::getline(std::cin, make);
    
    std::cout << "Enter Model: ";
    std::getline(std::cin, model);
    
    std::cout << "Enter Year: ";
    std::cin >> year;
    
    std::cout << "Enter Price per Day: ";
    std::cin >> price;
    
    std::cout << "Enter Car Type (1: Sedan, 2: SUV, 3: Truck): ";
    std::cin >> type;
    
    Car* newCar = nullptr;
    switch(type) {
        case 1:
            newCar = new Sedan(id, make, model, year, price);
            break;
        case 2:
            newCar = new SUV(id, make, model, year, price);
            break;
        case 3:
            newCar = new Truck(id, make, model, year, price);
            break;
        default:
            std::cout << "Invalid car type!\n";
            return;
    }
    
    cars.push_back(newCar);

     std::ofstream outFile("cars.csv", std::ios::app);
    if (outFile.is_open()) {
        newCar->saveToCSV(outFile);
        outFile.close();
    }

    std::cout << "Car added successfully!\n";
}


void Admin::updateCar(std::vector<Car*>& cars) {
    int id;
    std::cout << "\nEnter Car ID to update: ";
    std::cin >> id;
    
    for(auto& car : cars) {
        if(car->getCarID() == id) {
            double newPrice;
            std::cout << "Enter new price per day: ";
            std::cin >> newPrice;
            car->updatePrice(newPrice);
            std::cout << "Car updated successfully!\n";
            return;
        }
    }
    std::cout << "Car not found!\n";
}

void Admin::removeCar(std::vector<Car*>& cars) {
    int id;
    std::cout << "\nEnter Car ID to remove: ";
    std::cin >> id;
    
    for(auto it = cars.begin(); it != cars.end(); ++it) {
        if((*it)->getCarID() == id) {
            delete *it;  // Free the memory
            cars.erase(it);
            std::cout << "Car removed successfully!\n";
            return;
        }
    }
    std::cout << "Car not found!\n";
}

void Admin::viewAllCars(const std::vector<Car*>& cars) const {
    std::cout << "\nAll Cars in Fleet:\n";
    std::cout << "----------------------------------------\n";
    for(const auto& car : cars) {
        car->viewDetails();
    }
}
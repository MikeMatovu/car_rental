#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
#include "Car.h"
#include <vector>

class Admin : public User {
public:
    Admin(int id, std::string n, std::string addr, std::string contact);
    void addCar(std::vector<Car*>& cars);
    void updateCar(std::vector<Car*>& cars);
    void removeCar(std::vector<Car*>& cars);
    void viewAllCars(const std::vector<Car*>& cars) const;
};

#endif
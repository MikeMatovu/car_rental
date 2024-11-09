#ifndef CAR_H
#define CAR_H

#include <string>
#include <iostream>
#include <fstream> 

class Car {
protected:
    int carID;
    std::string make;
    std::string model;
    int year;
    double pricePerDay;
    bool available;

public:
    Car(int id, std::string m, std::string mdl, int yr, double price);
    virtual ~Car() = default;

    virtual void viewDetails() const;
    virtual std::string getType() const = 0;
    
    int getCarID() const;
    bool isAvailable() const;
    void rentCar();
    void returnCar();
    double getPricePerDay() const;
    void updatePrice(double newPrice);

    virtual void saveToCSV(std::ofstream& file) const;
    static Car* createFromCSV(const std::string& line);
};

#endif
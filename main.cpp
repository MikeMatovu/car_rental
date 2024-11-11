#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <cstring>
#include <sstream>
#include <algorithm>
#include "UserAuth.h"
#include "Car.h"
#include "RentalTransaction.h"
#include "User.h"
#include "Admin.h"
#include "CarTypes.h"
#include "Customer.h"
using namespace std;

// Forward declarations
class CarRentalSystem;
void adminMenu(Admin& admin, vector<Car*>& cars);
void customerMenu(CarRentalSystem& system, int customerID);

// System Class
class CarRentalSystem {
    const string CARS_FILE = "cars.csv";
private:
    vector<Car*> cars;
    vector<Customer> customers;
    vector<Admin> admins;
    int transactionCounter = 0;

private:
    const string CUSTOMERS_FILE = "customers.csv";

void saveCustomersToFile() {
    ofstream file(CUSTOMERS_FILE);
    if (file.is_open()) {
        for (const auto& customer : customers) {
            customer.saveToCSV(file);
        }
        file.close();
    }
}

void loadCustomersFromFile() {
    ifstream file(CUSTOMERS_FILE);
    string line;
    
    while (getline(file, line)) {
        customers.push_back(Customer::createFromCSV(line));
    }
    file.close();
}

private:
    int nextCustomerId = 1000; 


public:
    void addCustomer(const string& name, const string& addr, const string& contact) {
        customers.push_back(Customer(nextCustomerId++, name, addr, contact));
    }

    int getLastCustomerId() const {
        return nextCustomerId - 1;
    }

public:
    CarRentalSystem() {
        loadCustomersFromFile();
        loadCarsFromFile();
        if (cars.empty()) {
            loadSampleData();
        }
    }

    ~CarRentalSystem() {
        saveCarsToFile();
        saveCustomersToFile();
        for(auto car : cars) {
            delete car;
        }
    }

    vector<Car*>& getCars() { return cars; }

    void saveCarsToFile() {
        ofstream file(CARS_FILE);
        if (file.is_open()) {
            for (const auto& car : cars) {
                car->saveToCSV(file);
            }
            file.close();
        }
    }

    void loadCarsFromFile() {
        ifstream file(CARS_FILE);
        string line;
        
        while (getline(file, line)) {
            stringstream ss(line);
            string item;
            vector<string> row;
            
            while (getline(ss, item, ',')) {
                row.push_back(item);
            }
            
            if (row.size() >= 7) {
                int id = stoi(row[0]);
                string make = row[1];
                string model = row[2];
                int year = stoi(row[3]);
                double price = stod(row[4]);
                string type = row[6];
                
                Car* car = nullptr;
                if (type == "Sedan") {
                    car = new Sedan(id, make, model, year, price);
                } else if (type == "SUV") {
                    car = new SUV(id, make, model, year, price);
                } else if (type == "Truck") {
                    car = new Truck(id, make, model, year, price);
                }
                   if (car) {
                    if (row[5] == "0") car->rentCar();
                    cars.push_back(car);
                }
            }
        }
        file.close();
    }


    void loadSampleData() {
        cars.push_back(new Sedan(1, "Toyota", "Camry", 2020, 50.0));
        cars.push_back(new SUV(2, "Honda", "CRV", 2021, 60.0));
        cars.push_back(new Truck(3, "Ford", "F-150", 2019, 75.0));
        customers.push_back(Customer(1, "John Doe", "123 Elm St", "555-1234"));
        admins.push_back(Admin(100, "Admin User", "456 Oak St", "555-5678"));
    }

    void viewAvailableCars() const {
        cout << "\nAvailable Cars:\n";
        for (const auto &car : cars) {
            if (car->isAvailable()) {
                car->viewDetails();
            }
        }
    }

        bool rentCar(int customerID, int carID, int days) {
        // Find the customer
        auto customerIt = std::find_if(customers.begin(), customers.end(),
            [customerID](const Customer& c) { return c.getID() == customerID; });
            
        if (customerIt == customers.end() || customerIt->hasRentedCar()) {
            return false;
        }

        // Find the car
        for(auto& car : cars) {
            if(car->getCarID() == carID && car->isAvailable()) {
                car->rentCar();
                customerIt->bookCar(carID);
                
                // Create and save transaction
                time_t now = time(0);
                time_t returnDate = now + (days * 24 * 60 * 60);
                double amount = days * car->getPricePerDay();
                
                RentalTransaction transaction(transactionCounter++, carID, 
                    customerID, now, returnDate, amount);
                transaction.saveToCSV();
                
                saveCustomersToFile(); 
                saveCarsToFile();     
                return true;
            }
        }
        return false;
    }

    Customer* findCustomer(int customerID) {
        for (auto &cust : customers) {
            if (cust.getID() == customerID) return &cust;
        }
        return nullptr;
    }

    void returnCar(int customerID) {
        auto customer = findCustomer(customerID);
        if (customer && customer->hasRentedCar()) {
            int carID = customer->getCurrentRental();
            for (auto &car : cars) {
                if (car->getCarID() == carID) {
                    car->returnCar();
                    customer->returnCar();
                    saveCustomersToFile();
                    saveCarsToFile();
                    cout << "Car returned successfully.\n";
                    return;
                }
            }
        } else {
            cout << "Customer has no rented car.\n";
        }
    }
};

void customerMenu(CarRentalSystem& system, int customerID) {
    // Implement customer menu functionality here
    while (true) {
        cout << "\nCar Rental System Menu\n";
        cout << "1. View Available Cars\n";
        cout << "2. Book a Car\n";
        cout << "3. Return a Car\n";
        cout << "4. View Rental History\n";
        cout << "5. Logout\n";
        cout << "Choose an option: ";

        int choice;
        cin >> choice;
         switch(choice) {
            case 1:
                system.viewAvailableCars();
                break;

            case 2: {
                system.viewAvailableCars();
                int carID, days;
                cout << "Enter Car ID to rent: ";
                cin >> carID;
                cout << "Enter number of days: ";
                cin >> days;
                system.rentCar(customerID, carID, days);  // Use the passed customerId
                break;
            }
             case 3: {
                int customerID;
                cout << "Enter your Customer ID: ";
                cin >> customerID;
                system.returnCar(customerID);
                break;
            }

            case 4: {
                ifstream file("rental_history.csv");
                string line;
                cout << "\nRental History:\n";
                while (getline(file, line)) {
                    stringstream ss(line);
                    string item;
                    vector<string> row;
                    
                    while (getline(ss, item, ',')) {
                        row.push_back(item);
                    }
                    
                    if (row.size() >= 6) {
                        RentalTransaction transaction(
                            stoi(row[0]),  // transactionID
                            stoi(row[1]),  // carID
                            stoi(row[2]),  // customerID
                            stoll(row[3]), // startDate
                            stoll(row[4]), // endDate
                            stod(row[5])   // amount
                        );
                        transaction.viewTransactionDetails();
                    }
                }
                file.close();
                break;
            }

            case 5:
                cout << "Logging out...\n";
                return;

            default:
                cout << "Invalid option!\n";
        }
    }
}
// Admin menu function implementation
void adminMenu(Admin& admin, vector<Car*>& cars) {
    while(true) {
        cout << "\nAdmin Menu\n";
        cout << "1. View All Cars\n";
        cout << "2. Add New Car\n";
        cout << "3. Update Car\n";
        cout << "4. Remove Car\n";
        cout << "5. View Rental History\n";
        cout << "6. Logout\n";
        cout << "Choose an option: ";

        int choice;
        cin >> choice;

        switch(choice) {
            case 1:
                admin.viewAllCars(cars);
                break;
            case 2:
                admin.addCar(cars);
                break;
            case 3:
                admin.updateCar(cars);
                break;
            case 4:
                admin.removeCar(cars);
                break;
            case 5: {
                ifstream file("rental_history.csv");
                string line;
                cout << "\nRental History:\n";
                while (getline(file, line)) {
                    cout << line << endl;
                }
                file.close();
                break;
            }
            case 6: {
                cout << "Logging out...\n";
                return;
            }
            default:
                cout << "Invalid option!\n";
                break;
        }
    }
}

// Main function to interact with the Car Rental System
int main() {

    CarRentalSystem system;
    UserAuth auth;
    string username, password;
    bool loggedIn = false;

    while (!loggedIn) {
        cout << "\nWelcome to Car Rental System\n";
        cout << "1. Login\n";
        cout << "2. Register\n";
        cout << "3. Exit\n";
        cout << "Choose an option: ";

        int choice;
        cin >> choice;
        cin.ignore();

        switch(choice) {
            case 1: {
                cout << "Username: ";
                getline(cin, username);
                cout << "Password: ";
                getline(cin, password);

                if (auth.login(username, password)) {
                    cout << "Login successful!\n";
                    if (auth.isAdmin()) {
                        // Admin menu
                        Admin admin(1, "Admin", "Admin Address", "Admin Contact");
                        adminMenu(admin, system.getCars());
                    } else {
                        // Customer menu with the correct customer ID
                        customerMenu(system, auth.getCurrentCustomerId());
                    }
                } else {
                    cout << "Invalid credentials!\n";
                }
                break;
            }
            case 2: {
                cout << "Enter new username: ";
                getline(cin, username);
                cout << "Enter new password: ";
                getline(cin, password);
                cout << "Enter your name: ";
                string name;
                getline(cin, name);
                cout << "Enter your address: ";
                string address;
                getline(cin, address);
                cout << "Enter your contact number: ";
                string contact;
                getline(cin, contact);

                system.addCustomer(name, address, contact);
                int newCustomerId = system.getLastCustomerId();
                
                if (auth.registerUser(username, password, newCustomerId)) {
                    cout << "Registration successful! Your Customer ID is " << newCustomerId << ". Please login.\n";
                } else {
                    cout << "Username already exists!\n";
                }
                break;
            }
            case 3:
                return 0;
        }
    }


       return 0;
}




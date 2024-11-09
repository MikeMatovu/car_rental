#ifndef RENTAL_TRANSACTION_H
#define RENTAL_TRANSACTION_H

#include <string>
#include <iostream>
#include <fstream>
#include <ctime>

class RentalTransaction {
private:
    int transactionID;
    int carID;
    int customerID;
    time_t rentalStartDate;
    time_t rentalEndDate;
    double amount;

    std::string formatDate(time_t date) const;
    int calculateDays() const;

public:
    RentalTransaction(int tID, int cID, int custID, time_t start, time_t end, double amt);
    void saveToCSV() const;
    void viewTransactionDetails() const;
};

#endif
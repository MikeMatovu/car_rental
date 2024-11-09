#include "RentalTransaction.h"
#include <iomanip>

RentalTransaction::RentalTransaction(int tID, int cID, int custID, time_t start, time_t end, double amt)
    : transactionID(tID)
    , carID(cID)
    , customerID(custID)
    , rentalStartDate(start)
    , rentalEndDate(end)
    , amount(amt) {}

void RentalTransaction::saveToCSV() const {
    std::ofstream file("rental_history.csv", std::ios::app);
    file << transactionID << "," 
         << carID << "," 
         << customerID << ","
         << rentalStartDate << "," 
         << rentalEndDate << "," 
         << amount << "\n";
    file.close();
}

void RentalTransaction::viewTransactionDetails() const {
    std::cout << "\n=== Transaction Details ===\n"
              << "Transaction ID: #" << transactionID << "\n"
              << "Car ID: #" << carID << "\n"
              << "Customer ID: #" << customerID << "\n"
              << "Rental Period: \n"
              << "  Start: " << formatDate(rentalStartDate)
              << "  End:   " << formatDate(rentalEndDate)
              << "Duration: " << calculateDays() << " days\n"
              << "Total Amount: UGX " << std::fixed << std::setprecision(2) << amount << "\n"
              << "========================\n";
}

std::string RentalTransaction::formatDate(time_t date) const {
         char buffer[26];
    #ifdef _WIN32
        ctime_s(buffer, sizeof(buffer), &date);
    #else
        ctime_r(&date, buffer);
    #endif
        return std::string(buffer);
}

int RentalTransaction::calculateDays() const {
    return static_cast<int>((rentalEndDate - rentalStartDate) / (60 * 60 * 24));
}
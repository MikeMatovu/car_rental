# Car Rental System

A C++ console application for managing car rentals with separate interfaces for administrators and customers.

## Key Features

🚗 **For Customers**
- Browse available cars
- Rent cars with flexible duration
- Return rented cars
- View personal rental history
- User registration and authentication

👨‍💼 **For Administrators**
- Manage car fleet (add, update, remove)
- View all transactions
- Set rental prices
- Monitor car availability

## Getting Started

### Prerequisites
- C++ compiler (GCC 4.9 or later)
- CodeBlocks IDE (optional)
- Git (for cloning)

### Installation

1. Clone the repository

`git clone https://github.com/MikeMatovu/car_rental.git`

2. Compile the project

`g++ .cpp -o car_rental`


Or open `car_rental.cbp` in CodeBlocks and build the project.

### Default Admin Account
- Username: admin
- Password: admin123

## Usage

1. Run the compiled executable
2. Choose Login/Register
3. Access features based on account type:
   - Customers can rent/return cars
   - Admins can manage the car fleet

## Project Structure

- `main.cpp` - Core system and menus
- `Car.h/cpp` - Base vehicle class
- `CarTypes.h` - Vehicle type definitions
- `Admin.h/cpp` - Admin functionality
- `User.h/cpp` - Base user class
- `RentalTransaction.h/cpp` - Rental records

## Data Storage

The system uses CSV files for persistent storage:
- users.csv - User credentials
- cars.csv - Vehicle inventory
- rental_history.csv - Transaction records

## License

This project is licensed under the free licence. You are free to use the code as you wish
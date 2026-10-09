#pragma once

#include <stdexcept>
#include <string>

class Customer {
private:
    int id;
    std::string name;
    std::string phone;

public:
    Customer(int id, const std::string& name, const std::string& phone)
        : id(id), name(name), phone(phone) {
        if (id <= 0) {
            throw std::invalid_argument("Customer ID must be positive.");
        }

        if (name.empty()) {
            throw std::invalid_argument("Customer name cannot be empty.");
        }

        if (phone.empty()) {
            throw std::invalid_argument("Customer phone cannot be empty.");
        }
    }

    int getId() const {
        return id;
    }

    const std::string& getName() const {
        return name;
    }

    const std::string& getPhone() const {
        return phone;
    }
};

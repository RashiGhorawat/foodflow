#pragma once

#include <string>
#include <stdexcept>

class MenuItem {
private:
    int id;
    std::string name;
    double price;
    bool available;

public:
    MenuItem(int id, const std::string& name, double price)
        : id(id), name(name), price(price), available(true) {
        if (id <= 0) {
            throw std::invalid_argument("Menu item ID must be positive.");
        }

        if (name.empty()) {
            throw std::invalid_argument("Menu item name cannot be empty.");
        }

        if (price < 0) {
            throw std::invalid_argument("Price cannot be negative.");
        }
    }

    int getId() const {
        return id;
    }

    const std::string& getName() const {
        return name;
    }

    double getPrice() const {
        return price;
    }

    bool isAvailable() const {
        return available;
    }

    void setAvailable(bool status) {
        available = status;
    }
};

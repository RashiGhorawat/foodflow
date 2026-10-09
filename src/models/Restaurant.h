#pragma once
#include <iostream>

#include "MenuItem.h"
#include <string>
#include <vector>
#include <stdexcept>

class Restaurant {
private:
    int id;
    std::string name;
    std::vector<MenuItem> menu;

public:
    Restaurant(int id, const std::string& name)
        : id(id), name(name) {
        if (id <= 0) {
            throw std::invalid_argument("Restaurant ID must be positive.");
        }

        if (name.empty()) {
            throw std::invalid_argument("Restaurant name cannot be empty.");
        }
    }

    int getId() const {
        return id;
    }

    const std::string& getName() const {
        return name;
    }

    void addMenuItem(const MenuItem& item) {
        for (const auto& existing : menu) {
            if (existing.getId() == item.getId()) {
                throw std::invalid_argument("Menu item ID already exists.");
            }
        }

        menu.push_back(item);
    }

    void showMenu() const {
        std::cout << "\nMenu - " << name << "\n";

        if (menu.empty()) {
            std::cout << "No items on the menu yet.\n";
            return;
        }

        for (const auto& item : menu) {
            std::cout << item.getId() << ". "
                      << item.getName() << " - Rs. "
                      << item.getPrice();

            if (!item.isAvailable()) {
                std::cout << " (Currently unavailable)";
            }

            std::cout << '\n';
        }
    }
};

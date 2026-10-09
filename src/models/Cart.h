#pragma once

#include "MenuItem.h"
#include <iostream>
#include <stdexcept>
#include <vector>

class Cart {
private:
    struct CartItem {
        MenuItem item;
        int quantity;
    };

    int restaurantId = -1;
    std::vector<CartItem> items;

public:
    void addItem(const MenuItem& item, int quantity, int sourceRestaurantId) {
        if (sourceRestaurantId <= 0) {
            throw std::invalid_argument("Invalid restaurant ID.");
        }

        if (!item.isAvailable()) {
            throw std::invalid_argument("This item is currently unavailable.");
        }

        if (quantity <= 0) {
            throw std::invalid_argument("Quantity must be greater than zero.");
        }

        if (restaurantId != -1 && restaurantId != sourceRestaurantId) {
            throw std::invalid_argument(
                "Your cart already contains items from another restaurant."
            );
        }

        for (auto& cartItem : items) {
            if (cartItem.item.getId() == item.getId()) {
                cartItem.quantity += quantity;
                return;
            }
        }

        restaurantId = sourceRestaurantId;
        items.push_back({item, quantity});
    }

    void removeItem(int itemId) {
        for (auto it = items.begin(); it != items.end(); ++it) {
            if (it->item.getId() == itemId) {
                items.erase(it);

                if (items.empty()) {
                    restaurantId = -1;
                }

                return;
            }
        }

        throw std::invalid_argument("Item not found in cart.");
    }

    double getTotal() const {
        double total = 0.0;

        for (const auto& cartItem : items) {
            total += cartItem.item.getPrice() * cartItem.quantity;
        }

        return total;
    }

    bool isEmpty() const {
        return items.empty();
    }

    int getRestaurantId() const {
        return restaurantId;
    }

    void showCart() const {
        std::cout << "\nYour cart\n";

        if (items.empty()) {
            std::cout << "Your cart is empty.\n";
            return;
        }

        for (const auto& cartItem : items) {
            std::cout << cartItem.item.getName()
                      << " x " << cartItem.quantity
                      << " = Rs. "
                      << cartItem.item.getPrice() * cartItem.quantity
                      << '\n';
        }

        std::cout << "Total: Rs. " << getTotal() << '\n';
    }
};

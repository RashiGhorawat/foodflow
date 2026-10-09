#pragma once

#include "../models/Order.h"
#include "../models/Customer.h"
#include <memory>
#include <stdexcept>
#include <vector>

class OrderService {
private:
    int nextOrderId = 1;
    std::vector<std::shared_ptr<Order>> orders;

public:
    std::shared_ptr<Order> placeOrder(const Customer& customer, const Cart& cart) {
        if (cart.isEmpty()) {
            throw std::invalid_argument("Cannot place an order with an empty cart.");
        }

        auto order = std::make_shared<Order>(
            nextOrderId++,
            customer.getId(),
            cart.getRestaurantId(),
            cart.getTotal()
        );

        orders.push_back(order);
        return order;
    }

    const std::vector<std::shared_ptr<Order>>& getOrders() const {
        return orders;
    }
};

#pragma once

#include "Cart.h"
#include "../observers/OrderObserver.h"
#include <stdexcept>
#include <string>
#include <vector>

enum class OrderStatus {
    Placed,
    Confirmed,
    Preparing,
    OutForDelivery,
    Delivered,
    Cancelled
};

class Order {
private:
    int id;
    int customerId;
    int restaurantId;
    double total;
    OrderStatus status;
    std::vector<OrderObserver*> observers;

public:
    Order(int id, int customerId, int restaurantId, double total)
        : id(id),
          customerId(customerId),
          restaurantId(restaurantId),
          total(total),
          status(OrderStatus::Placed) {
        if (id <= 0 || customerId <= 0 || restaurantId <= 0) {
            throw std::invalid_argument(
                "Order, customer, and restaurant IDs must be positive."
            );
        }

        if (total <= 0) {
            throw std::invalid_argument(
                "Order total must be positive."
            );
        }
    }

    int getId() const {
        return id;
    }

    int getCustomerId() const {
        return customerId;
    }

    int getRestaurantId() const {
        return restaurantId;
    }

    double getTotal() const {
        return total;
    }

    OrderStatus getStatus() const {
        return status;
    }

    std::string getStatusName() const {
        switch (status) {
            case OrderStatus::Placed:
                return "Placed";
            case OrderStatus::Confirmed:
                return "Confirmed";
            case OrderStatus::Preparing:
                return "Preparing";
            case OrderStatus::OutForDelivery:
                return "Out for delivery";
            case OrderStatus::Delivered:
                return "Delivered";
            case OrderStatus::Cancelled:
                return "Cancelled";
        }

        return "Unknown";
    }

    void addObserver(OrderObserver* observer) {
        if (observer == nullptr) {
            throw std::invalid_argument(
                "Observer cannot be null."
            );
        }

        observers.push_back(observer);
    }

    void notifyObservers() const {
        for (auto* observer : observers) {
            observer->onStatusChanged(
                getId(),
                getStatusName()
            );
        }
    }

    void updateStatus(OrderStatus nextStatus) {
        bool valid = false;

        switch (status) {
            case OrderStatus::Placed:
                valid = nextStatus == OrderStatus::Confirmed ||
                        nextStatus == OrderStatus::Cancelled;
                break;

            case OrderStatus::Confirmed:
                valid = nextStatus == OrderStatus::Preparing ||
                        nextStatus == OrderStatus::Cancelled;
                break;

            case OrderStatus::Preparing:
                valid = nextStatus == OrderStatus::OutForDelivery;
                break;

            case OrderStatus::OutForDelivery:
                valid = nextStatus == OrderStatus::Delivered;
                break;

            case OrderStatus::Delivered:
            case OrderStatus::Cancelled:
                valid = false;
                break;
        }

        if (!valid) {
            throw std::invalid_argument(
                "Invalid order status transition."
            );
        }

        status = nextStatus;
        notifyObservers();
    }
};
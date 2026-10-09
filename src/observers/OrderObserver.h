#pragma once

#include <iostream>
#include <string>

class OrderObserver {
public:
    virtual ~OrderObserver() = default;

    virtual void onStatusChanged(
        int orderId,
        const std::string& status
    ) = 0;
};

class CustomerNotification : public OrderObserver {
public:
    void onStatusChanged(
        int orderId,
        const std::string& status
    ) override {
        std::cout << "[Notification] Order #"
                  << orderId << " is now "
                  << status << ".\n";
    }
};

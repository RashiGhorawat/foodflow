#pragma once

#include <iostream>
#include <string>

class PaymentStrategy {
public:
    virtual ~PaymentStrategy() = default;

    virtual bool pay(double amount) = 0;
};

class UPIPayment : public PaymentStrategy {
public:
    bool pay(double amount) override {
        std::cout << "Processing UPI payment of Rs. "
                  << amount << '\n';

        std::cout << "UPI payment successful.\n";
        return true;
    }
};

class CardPayment : public PaymentStrategy {
public:
    bool pay(double amount) override {
        std::cout << "Processing card payment of Rs. "
                  << amount << '\n';

        std::cout << "Card payment successful.\n";
        return true;
    }
};

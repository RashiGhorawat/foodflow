
#pragma once
#include <iostream>

class PaymentStrategy {
public:
    virtual ~PaymentStrategy() = default;

    virtual bool pay(double amount) = 0;
};

class UPIPayment : public PaymentStrategy {
private:
    bool shouldSucceed;

public:
    explicit UPIPayment(bool success = true)
        : shouldSucceed(success) {}

    bool pay(double amount) override {
        std::cout << "Processing UPI payment of Rs. "
                  << amount << '\n';

        if (!shouldSucceed) {
            std::cout << "UPI payment failed.\n";
            return false;
        }

        std::cout << "UPI payment successful.\n";
        return true;
    }
};

class CardPayment : public PaymentStrategy {
private:
    bool shouldSucceed;

public:
    explicit CardPayment(bool success = true)
        : shouldSucceed(success) {}

    bool pay(double amount) override {
        std::cout << "Processing card payment of Rs. "
                  << amount << '\n';

        if (!shouldSucceed) {
            std::cout << "Card payment failed.\n";
            return false;
        }

        std::cout << "Card payment successful.\n";
        return true;
    }
};

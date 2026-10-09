#pragma once

#include "../strategies/PaymentStrategy.h"
#include <stdexcept>

class PaymentService {
public:
    bool processPayment(double amount, PaymentStrategy& strategy) {
        if (amount <= 0) {
            throw std::invalid_argument(
                "Payment amount must be greater than zero."
            );
        }

        return strategy.pay(amount);
    }
};


#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "../src/models/MenuItem.h"
#include "../src/models/Cart.h"
#include "../src/models/Customer.h"
#include "../src/models/Order.h"
#include "../src/services/OrderService.h"
#include "../src/services/PaymentService.h"
#include "../src/strategies/PaymentStrategy.h"

int passed = 0;
int failed = 0;

void check(bool condition, const std::string& name) {
    if (condition) {
        std::cout << "[PASS] " << name << '\n';
        ++passed;
    } else {
        std::cout << "[FAIL] " << name << '\n';
        ++failed;
    }
}

template <typename Function>
void checkThrows(Function action, const std::string& name) {
    try {
        action();
        check(false, name);
    } catch (const std::exception&) {
        check(true, name);
    }
}

class TestObserver : public OrderObserver {
public:
    std::vector<std::string> updates;

    void onStatusChanged(int orderId, const std::string& status) override {
        updates.push_back(
            "Order #" + std::to_string(orderId) + " " + status
        );
    }
};

int main() {
    std::cout << "\nRunning FoodFlow tests...\n\n";

    MenuItem paneer(101, "Paneer Tikka", 249.0);
    MenuItem biryani(102, "Veg Biryani", 199.0);

    check(paneer.getPrice() == 249.0,
          "Menu item stores its price");

    checkThrows(
        [] { MenuItem invalid(0, "Invalid Item", 100.0); },
        "Menu item rejects an invalid ID"
    );

    checkThrows(
        [] { MenuItem invalid(103, "Invalid Item", -10.0); },
        "Menu item rejects a negative price"
    );

    Cart cart;
    cart.addItem(paneer, 2, 1);
    cart.addItem(biryani, 1, 1);

    check(cart.getTotal() == 697.0,
          "Cart calculates the correct total");

    checkThrows(
        [&] { cart.addItem(paneer, 0, 1); },
        "Cart rejects a zero quantity"
    );

    checkThrows(
        [&] { cart.addItem(biryani, 1, 2); },
        "Cart rejects items from another restaurant"
    );

    MenuItem unavailable(104, "Unavailable Dish", 150.0);
    unavailable.setAvailable(false);

    checkThrows(
        [&] { cart.addItem(unavailable, 1, 1); },
        "Cart rejects unavailable items"
    );

    Customer customer(1, "Aarav", "9876543210");
    OrderService service;
    Cart emptyCart;

    checkThrows(
        [&] { service.placeOrder(customer, emptyCart); },
        "Cannot place an order with an empty cart"
    );

    auto failedOrder = service.placeOrder(customer, cart);

    PaymentService paymentService;
    UPIPayment failedUPI(false);

    bool paymentResult = paymentService.processPayment(
        failedOrder->getTotal(), failedUPI
    );

    check(!paymentResult,
          "Failed payment returns false");

    check(failedOrder->getStatus() == OrderStatus::Placed,
          "Failed payment leaves order unconfirmed");

    auto order = service.placeOrder(customer, cart);
    TestObserver observer;
    order->addObserver(&observer);

    check(order->getStatus() == OrderStatus::Placed,
          "New order starts in Placed status");

    order->updateStatus(OrderStatus::Confirmed);
    order->updateStatus(OrderStatus::Preparing);

    check(order->getStatus() == OrderStatus::Preparing,
          "Order can move through valid status transitions");

    check(observer.updates.size() == 2,
          "Observer receives status change notifications");

    checkThrows(
        [&] { order->updateStatus(OrderStatus::Delivered); },
        "Order rejects an invalid status transition"
    );

    auto placedOrder = service.placeOrder(customer, cart);

    placedOrder->updateStatus(OrderStatus::Cancelled);

    check(placedOrder->getStatus() == OrderStatus::Cancelled,
          "Placed order can be cancelled");

    checkThrows(
        [&] { placedOrder->updateStatus(OrderStatus::Confirmed); },
        "Cancelled order cannot be confirmed"
    );

    auto confirmedOrder = service.placeOrder(customer, cart);

    confirmedOrder->updateStatus(OrderStatus::Confirmed);
    confirmedOrder->updateStatus(OrderStatus::Cancelled);

    check(confirmedOrder->getStatus() == OrderStatus::Cancelled,
          "Confirmed order can be cancelled");

    auto preparingOrder = service.placeOrder(customer, cart);

    preparingOrder->updateStatus(OrderStatus::Confirmed);
    preparingOrder->updateStatus(OrderStatus::Preparing);

    checkThrows(
        [&] { preparingOrder->updateStatus(OrderStatus::Cancelled); },
        "Preparing order cannot be cancelled"
    );

    TestObserver cancellationObserver;
    auto observedOrder = service.placeOrder(customer, cart);

    observedOrder->addObserver(&cancellationObserver);
    observedOrder->updateStatus(OrderStatus::Cancelled);

    check(
        cancellationObserver.updates.size() == 1 &&
        cancellationObserver.updates[0].find("Cancelled") != std::string::npos,
        "Observer receives cancellation notification"
    );

    std::cout << "\n-----------------------------\n";
    std::cout << "Passed: " << passed << '\n';
    std::cout << "Failed: " << failed << '\n';
    std::cout << "-----------------------------\n";

    return failed == 0 ? 0 : 1;
}

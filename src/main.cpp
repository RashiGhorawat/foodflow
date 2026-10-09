#include <iostream>
#include "models/Restaurant.h"
#include "models/Customer.h"
#include "models/Cart.h"
#include "services/OrderService.h"
#include "services/PaymentService.h"
#include "observers/OrderObserver.h"

int main() {
    Restaurant restaurant(1, "Delhi Kitchen");

    restaurant.addMenuItem(MenuItem(101, "Paneer Tikka", 249.0));
    restaurant.addMenuItem(MenuItem(102, "Veg Biryani", 199.0));

    Customer customer(1, "Aarav", "9876543210");

    Cart cart;
    cart.addItem(MenuItem(101, "Paneer Tikka", 249.0), 2, restaurant.getId());
    cart.addItem(MenuItem(102, "Veg Biryani", 199.0), 1, restaurant.getId());

    OrderService orderService;
    auto order = orderService.placeOrder(customer, cart);

    CustomerNotification notification;
    order->addObserver(&notification);

    std::cout << "Customer: " << customer.getName() << '\n';
    std::cout << "Order ID: " << order->getId() << '\n';
    std::cout << "Order total: Rs. " << order->getTotal() << '\n';
    std::cout << "Order status: " << order->getStatusName() << "\n\n";

    PaymentService paymentService;
    UPIPayment upi(false);

    bool paymentSuccessful =
        paymentService.processPayment(order->getTotal(), upi);

   if (paymentSuccessful) {
    order->updateStatus(OrderStatus::Confirmed);
    order->updateStatus(OrderStatus::Preparing);
} else {
    std::cout << "Order was not confirmed because payment failed.\n";
}

    std::cout << "\nFinal status: " << order->getStatusName() << '\n';

    return 0;
}

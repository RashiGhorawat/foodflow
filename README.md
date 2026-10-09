# FoodFlow

A C++ food delivery system built to explore object-oriented design and low-level system design concepts.

FoodFlow models a basic food-ordering workflow: customers add menu items to a cart, place orders, make a simulated payment, and receive notifications when the order status changes.

## Features

- Restaurant menus and menu item availability
- Customer and shopping cart models
- Cart total calculation and restaurant consistency checks
- Order placement and status transition validation
- Simulated UPI and card payment strategies
- Observer-based order status notifications
- Automated tests for core behavior and edge cases

## Design Concepts

- **Encapsulation:** Models manage their own data and validation.
- **Composition:** A restaurant maintains its menu.
- **Strategy pattern:** Payment methods share a common interface.
- **Observer pattern:** Subscribers are notified when order status changes.
- **Separation of responsibilities:** Order creation and payment processing are handled by separate services.

## Tech Stack

- C++17
- CMake
- CTest

## Build and Run

```bash
cmake -S . -B build
cmake --build build
./build/foodflow
```

## Run Tests

```bash
./build/test_foodflow
ctest --test-dir build --output-on-failure
```

## Current Scope

FoodFlow is an in-memory learning project. Data is not persisted after the program exits, and payments are simulated rather than processed through a real payment provider.

The project focuses on domain modeling, business rules, design patterns, and testable C++ code rather than a web or mobile interface.

## Future Improvements

- Preserve an itemized snapshot in each order
- Add a delivery assignment strategy
- Improve payment failure and cancellation handling
- Expand automated test coverage
- Document class relationships and checkout flow with UML diagrams
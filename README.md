# FoodFlow

FoodFlow is a C++ food delivery system built as a learning project to practise object-oriented programming and low-level design (LLD).

It models a basic food ordering workflow, including restaurant menus, shopping carts, order placement, simulated payments, order status updates, and customer notifications.

## Features

- Restaurant menus with item availability checks
- Shopping carts with quantity validation and total calculation
- Prevention of mixing items from different restaurants in one cart
- Order placement with basic validation
- Simulated UPI and card payments
- Order status transition validation
- Order cancellation rules
- Observer-based notifications when order status changes
- Automated tests for core business rules and edge cases

## Design Concepts

- **Encapsulation:** Models keep their data and validation logic together.
- **Composition:** A restaurant maintains its menu items.
- **Strategy pattern:** UPI and card payments use a common payment interface.
- **Observer pattern:** Observers receive notifications when an order's status changes.
- **Separation of responsibilities:** Order creation and payment processing are handled by separate services.

## Tech Stack

- C++17
- CMake
- CTest

## Project Structure

```text
foodflow/
├── src/
│   ├── models/
│   ├── services/
│   ├── strategies/
│   ├── observers/
│   └── main.cpp
├── tests/
│   └── test_foodflow.cpp
├── docs/
│   └── diagrams/
│       ├── class-diagram.md
│       └── checkout-flow.md
├── CMakeLists.txt
├── .gitignore
└── README.md
```

## Build and Run

Make sure CMake and a C++17-compatible compiler are installed.

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

## Design Documentation

- [UML Class Diagram](docs/diagrams/class-diagram.md)
- [Checkout Flow](docs/diagrams/checkout-flow.md)

GitHub can render the Mermaid diagrams in these files.

## Current Limitations

- Data is stored in memory and is lost when the program exits.
- Payments are simulated; no real payment provider is connected.
- The project does not include a web or mobile interface.
- Order creation and payment processing are separate steps in the current demo.

## Possible Improvements

- Add a dedicated checkout service to coordinate order placement and payment.
- Improve payment failure and order lifecycle handling.
- Add more automated tests for card payments and invalid inputs.
- Add order history and persistent storage.
- Improve UML documentation as the design evolves.
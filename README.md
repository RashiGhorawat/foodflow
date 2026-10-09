# FoodFlow — Food Delivery System

FoodFlow is a food delivery application project built to practise **C++ object-oriented programming, low-level design (LLD), and React frontend development**.

The project models a simplified food ordering workflow, from browsing restaurant menus and managing a cart to placing orders, processing simulated payments, and tracking order status. It includes a C++ implementation of the core business rules and a separate React frontend demo.

## Features

### C++ Core

- Restaurant menus with item availability checks
- Shopping cart with quantity validation and total calculation
- Prevention of mixing items from different restaurants in one cart
- Order placement with basic validation
- Simulated UPI and card payments
- Order status transition validation
- Order cancellation rules
- Observer-based notifications when order status changes
- Automated tests for core business rules and edge cases

### React Frontend

- Browse sample restaurants and menu items
- Search restaurants
- Add and remove items from the cart
- Prevent mixing items from different restaurants
- Enter customer and delivery details at checkout
- Simulate a payment and display order confirmation
- View order history and cancel eligible orders
- Persist supported demo data in browser local storage
- Responsive layout for different screen sizes

## Design Concepts

- **Encapsulation:** Models keep related data and validation logic together.
- **Composition:** A restaurant maintains its menu items.
- **Strategy pattern:** UPI and card payments use a common payment interface.
- **Observer pattern:** Observers receive notifications when an order's status changes.
- **Separation of responsibilities:** Order creation and payment processing are handled by separate services.
- **Business rule validation:** The application checks cart contents, quantities, payment outcomes, and order status transitions.

## Tech Stack

**C++ Core**
- C++17
- CMake
- CTest

**Frontend**
- React
- JavaScript
- Vite
- CSS
- Browser local storage for demo persistence

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
├── frontend/
│   ├── src/
│   │   ├── App.jsx
│   │   ├── App.css
│   │   ├── index.css
│   │   └── main.jsx
│   ├── index.html
│   ├── package.json
│   └── vite.config.js
├── CMakeLists.txt
├── .gitignore
└── README.md
```

## Run the C++ Application

Make sure CMake and a C++17-compatible compiler are installed.

From the project root:

```bash
cmake -S . -B build
cmake --build build
./build/foodflow
```

## Run the C++ Tests

From the project root:

```bash
ctest --test-dir build --output-on-failure
```

To run the test executable directly:

```bash
./build/test_foodflow
```

## Run the React Frontend

Make sure Node.js and npm are installed.

From the project root:

```bash
cd frontend
npm install
npm run dev
```

Open the local URL printed by Vite, usually `http://localhost:5173`.

To verify a production build:

```bash
npm run build
```

## Design Documentation

- [UML Class Diagram](docs/diagrams/class-diagram.md)
- [Checkout Flow](docs/diagrams/checkout-flow.md)

GitHub can render the Mermaid diagrams in these files.

## Current Limitations

- The C++ core and React frontend are separate implementations; the frontend does not currently call the C++ code through an API.
- The frontend uses sample restaurant and menu data.
- Payments are simulated; no real payment provider is connected.
- Browser demo data is stored locally and is not shared across devices.
- There is no backend API, user authentication, or database integration.
- The C++ application stores its data in memory, so that data is lost when the program exits.

## Possible Improvements

- Connect the React frontend to a backend API.
- Add persistent storage using a database.
- Coordinate order creation and payment through a dedicated checkout service.
- Add user authentication and customer accounts.
- Improve payment failure and order lifecycle handling.
- Expand automated tests for additional business rules and edge cases.
- Improve UML documentation as the design evolves.

## Project Goal

FoodFlow is a learning project focused on understanding and demonstrating object-oriented design, common design patterns, business rule validation, testing, and frontend development. It is not intended to process real orders or payments.
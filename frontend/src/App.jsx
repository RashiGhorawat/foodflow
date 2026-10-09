
import { useEffect, useState } from "react";
import "./App.css";

const restaurants = [
  {
    id: 1,
    name: "Burger Barn",
    cuisine: "Burgers and Fast Food",
    rating: 4.5,
    time: "20–30 min",
    emoji: "🍔",
    menu: [
      { id: 101, name: "Classic Burger", price: 149, emoji: "🍔", description: "Grilled patty with fresh vegetables" },
      { id: 102, name: "Cheese Burger", price: 179, emoji: "🍔", description: "Classic burger with extra cheese" },
      { id: 103, name: "French Fries", price: 89, emoji: "🍟", description: "Crispy golden potato fries" },
      { id: 104, name: "Chocolate Shake", price: 99, emoji: "🥤", description: "Creamy chocolate milkshake" },
    ],
  },
  {
    id: 2,
    name: "Pizza Corner",
    cuisine: "Pizza and Italian",
    rating: 4.3,
    time: "25–35 min",
    emoji: "🍕",
    menu: [
      { id: 201, name: "Margherita Pizza", price: 199, emoji: "🍕", description: "Cheese, tomato and fresh herbs" },
      { id: 202, name: "Farmhouse Pizza", price: 279, emoji: "🍕", description: "Loaded with fresh vegetables" },
      { id: 203, name: "Garlic Bread", price: 119, emoji: "🥖", description: "Toasted bread with garlic butter" },
      { id: 204, name: "Pasta Alfredo", price: 189, emoji: "🍝", description: "Creamy white sauce pasta" },
    ],
  },
  {
    id: 3,
    name: "Wok Express",
    cuisine: "Chinese and Asian",
    rating: 4.4,
    time: "20–30 min",
    emoji: "🍜",
    menu: [
      { id: 301, name: "Veg Hakka Noodles", price: 159, emoji: "🍜", description: "Stir-fried noodles with vegetables" },
      { id: 302, name: "Veg Fried Rice", price: 149, emoji: "🍚", description: "Fried rice with seasonal vegetables" },
      { id: 303, name: "Spring Rolls", price: 109, emoji: "🥢", description: "Crispy vegetable rolls" },
      { id: 304, name: "Chilli Paneer", price: 199, emoji: "🥘", description: "Paneer tossed in spicy sauce" },
    ],
  },
];

const money = (amount) => `₹${amount.toFixed(2)}`;

function readSavedData(key, fallback) {
  try {
    const saved = localStorage.getItem(key);
    return saved ? JSON.parse(saved) : fallback;
  } catch {
    return fallback;
  }
}

function App() {
  const [search, setSearch] = useState("");
  const [selectedRestaurant, setSelectedRestaurant] = useState(null);
  const [cart, setCart] = useState(() => readSavedData("foodflow-cart", []));
  const [orders, setOrders] = useState(() => readSavedData("foodflow-orders", []));
  const [page, setPage] = useState("home");
  const [message, setMessage] = useState("");
  const [customerName, setCustomerName] = useState("");
  const [address, setAddress] = useState("");
  const [paymentMethod, setPaymentMethod] = useState("UPI");
  const [confirmedOrder, setConfirmedOrder] = useState(null);

  useEffect(() => {
    localStorage.setItem("foodflow-cart", JSON.stringify(cart));
  }, [cart]);

  useEffect(() => {
    localStorage.setItem("foodflow-orders", JSON.stringify(orders));
  }, [orders]);

  const filteredRestaurants = restaurants.filter((restaurant) =>
    `${restaurant.name} ${restaurant.cuisine}`
      .toLowerCase()
      .includes(search.toLowerCase().trim())
  );

  const cartRestaurant =
    cart.length > 0
      ? restaurants.find((restaurant) => restaurant.id === cart[0].restaurantId)
      : null;

  const subtotal = cart.reduce(
    (total, item) => total + item.price * item.quantity,
    0
  );

  const deliveryFee = cart.length > 0 ? 30 : 0;
  const total = subtotal + deliveryFee;
  const cartCount = cart.reduce((count, item) => count + item.quantity, 0);

  function showMessage(text) {
    setMessage(text);
    window.setTimeout(() => setMessage(""), 3000);
  }

  function openMenu(restaurant) {
    setSelectedRestaurant(restaurant);
    setPage("menu");
    window.scrollTo({ top: 0, behavior: "smooth" });
  }

  function addToCart(restaurant, food) {
    if (cart.length > 0 && cart[0].restaurantId !== restaurant.id) {
      showMessage("Your cart has items from another restaurant. Clear it before switching.");
      return;
    }

    setCart((currentCart) => {
      const existingItem = currentCart.find((item) => item.id === food.id);

      if (existingItem) {
        return currentCart.map((item) =>
          item.id === food.id
            ? { ...item, quantity: item.quantity + 1 }
            : item
        );
      }

      return [
        ...currentCart,
        {
          ...food,
          quantity: 1,
          restaurantId: restaurant.id,
          restaurantName: restaurant.name,
        },
      ];
    });

    showMessage(`${food.name} added to cart`);
  }

  function changeQuantity(itemId, change) {
    setCart((currentCart) =>
      currentCart
        .map((item) =>
          item.id === itemId
            ? { ...item, quantity: item.quantity + change }
            : item
        )
        .filter((item) => item.quantity > 0)
    );
  }

  function clearCart() {
    setCart([]);
  }

  function placeOrder(event) {
    event.preventDefault();

    if (!customerName.trim() || !address.trim()) {
      showMessage("Please enter your name and delivery address.");
      return;
    }

    if (cart.length === 0) {
      showMessage("Your cart is empty.");
      return;
    }

    const order = {
      id: `FF${Date.now().toString().slice(-8)}`,
      customerName: customerName.trim(),
      address: address.trim(),
      restaurantName: cartRestaurant.name,
      items: cart.map((item) => ({ ...item })),
      subtotal,
      deliveryFee,
      total,
      paymentMethod,
      status: "Order placed",
      createdAt: new Date().toLocaleString(),
    };

    setOrders((currentOrders) => [order, ...currentOrders]);
    setConfirmedOrder(order);
    setCart([]);
    setPage("confirmation");
    window.scrollTo({ top: 0, behavior: "smooth" });
  }

  function cancelOrder(orderId) {
    setOrders((currentOrders) =>
      currentOrders.map((order) =>
        order.id === orderId && order.status === "Order placed"
          ? { ...order, status: "Cancelled" }
          : order
      )
    );
  }

  function goHome() {
    setPage("home");
    setSelectedRestaurant(null);
    window.scrollTo({ top: 0, behavior: "smooth" });
  }

  return (
    <div className="app">
      <header className="navbar">
        <button className="brand" onClick={goHome}>
          🍊 FoodFlow
        </button>

        <nav className="nav-actions">
          <button className="nav-link" onClick={goHome}>Home</button>
          <button className="nav-link" onClick={() => setPage("orders")}>
            My Orders
          </button>
          <button className="primary-button cart-button" onClick={() => setPage("cart")}>
            My Cart ({cartCount})
          </button>
        </nav>
      </header>

      {message && <div className="toast" role="status">{message}</div>}

      {page === "home" && (
        <>
          <section className="hero">
            <div className="hero-content">
              <span className="eyebrow">GOOD FOOD, WITHOUT THE FUSS</span>
              <h1>Good food,<br />good mood.</h1>
              <p>Find your next favourite meal, made fresh and delivered to you.</p>
              <input
                className="search-input"
                type="search"
                placeholder="Search restaurants or cuisines..."
                value={search}
                onChange={(event) => setSearch(event.target.value)}
                aria-label="Search restaurants"
              />
              <span className="demo-note">A student-built food delivery demo</span>
            </div>
            <div className="hero-food" aria-hidden="true">🍕</div>
          </section>

          <main className="content">
            <div className="section-heading">
              <div>
                <h2>Explore restaurants</h2>
                <p>Something tasty is just around the corner.</p>
              </div>
              <span className="result-count">
                {filteredRestaurants.length} places
              </span>
            </div>

            <div className="restaurant-grid">
              {filteredRestaurants.map((restaurant) => (
                <article className="restaurant-card" key={restaurant.id}>
                  <div className="restaurant-art">{restaurant.emoji}</div>
                  <div className="restaurant-info">
                    <div className="card-title-row">
                      <h3>{restaurant.name}</h3>
                      <span className="rating">★ {restaurant.rating}</span>
                    </div>
                    <p>{restaurant.cuisine}</p>
                    <span className="delivery-time">◷ {restaurant.time}</span>
                    <button
                      className="primary-button full-button"
                      onClick={() => openMenu(restaurant)}
                    >
                      View menu
                    </button>
                  </div>
                </article>
              ))}
            </div>

            {filteredRestaurants.length === 0 && (
              <div className="empty-state">
                <span>🔎</span>
                <h3>No restaurants found</h3>
                <p>Try another restaurant name or cuisine.</p>
                <button className="secondary-button" onClick={() => setSearch("")}>
                  Clear search
                </button>
              </div>
            )}
          </main>
        </>
      )}

      {page === "menu" && selectedRestaurant && (
        <main className="content page-content">
          <button className="back-button" onClick={goHome}>← All restaurants</button>
          <div className="menu-heading">
            <div className="menu-emoji">{selectedRestaurant.emoji}</div>
            <div>
              <h1>{selectedRestaurant.name}</h1>
              <p>{selectedRestaurant.cuisine} · ★ {selectedRestaurant.rating}</p>
              <p>Estimated delivery: {selectedRestaurant.time}</p>
            </div>
          </div>

          <h2 className="subheading">Menu</h2>
          <div className="menu-list">
            {selectedRestaurant.menu.map((food) => (
              <article className="menu-item" key={food.id}>
                <div className="food-emoji">{food.emoji}</div>
                <div className="food-details">
                  <h3>{food.name}</h3>
                  <p>{food.description}</p>
                  <strong>{money(food.price)}</strong>
                </div>
                <button
                  className="add-button"
                  onClick={() => addToCart(selectedRestaurant, food)}
                >
                  + Add
                </button>
              </article>
            ))}
          </div>
          <button className="primary-button page-cart-button" onClick={() => setPage("cart")}>
            View cart ({cartCount})
          </button>
        </main>
      )}

      {page === "cart" && (
        <main className="content page-content narrow-content">
          <button className="back-button" onClick={goHome}>← Continue browsing</button>
          <h1>Your cart</h1>

          {cart.length === 0 ? (
            <div className="empty-state">
              <span>🛒</span>
              <h2>Your cart is empty</h2>
              <p>Pick something delicious from one of our restaurants.</p>
              <button className="primary-button" onClick={goHome}>Explore restaurants</button>
            </div>
          ) : (
            <>
              <p className="cart-restaurant">Ordering from <strong>{cartRestaurant.name}</strong></p>
              <div className="cart-list">
                {cart.map((item) => (
                  <div className="cart-item" key={item.id}>
                    <span className="cart-food-emoji">{item.emoji}</span>
                    <div className="cart-item-details">
                      <h3>{item.name}</h3>
                      <p>{money(item.price)} each</p>
                    </div>
                    <div className="quantity-control">
                      <button onClick={() => changeQuantity(item.id, -1)} aria-label={`Remove one ${item.name}`}>−</button>
                      <span>{item.quantity}</span>
                      <button onClick={() => changeQuantity(item.id, 1)} aria-label={`Add one ${item.name}`}>+</button>
                    </div>
                    <strong>{money(item.price * item.quantity)}</strong>
                  </div>
                ))}
              </div>

              <div className="bill">
                <div><span>Subtotal</span><span>{money(subtotal)}</span></div>
                <div><span>Delivery fee</span><span>{money(deliveryFee)}</span></div>
                <div className="bill-total"><strong>Total</strong><strong>{money(total)}</strong></div>
              </div>

              <div className="cart-actions">
                <button className="secondary-button" onClick={clearCart}>Clear cart</button>
                <button className="primary-button" onClick={() => setPage("checkout")}>
                  Proceed to checkout
                </button>
              </div>
            </>
          )}
        </main>
      )}

      {page === "checkout" && (
        <main className="content page-content narrow-content">
          <button className="back-button" onClick={() => setPage("cart")}>← Back to cart</button>
          <h1>Checkout</h1>

          {cart.length === 0 ? (
            <div className="empty-state">
              <h2>Your cart is empty</h2>
              <button className="primary-button" onClick={goHome}>Browse restaurants</button>
            </div>
          ) : (
            <div className="checkout-layout">
              <form className="checkout-form" onSubmit={placeOrder}>
                <h2>Delivery details</h2>
                <label htmlFor="customer-name">Your name</label>
                <input
                  id="customer-name"
                  value={customerName}
                  onChange={(event) => setCustomerName(event.target.value)}
                  placeholder="Enter your name"
                  required
                />

                <label htmlFor="delivery-address">Delivery address</label>
                <textarea
                  id="delivery-address"
                  value={address}
                  onChange={(event) => setAddress(event.target.value)}
                  placeholder="Hostel, room number, street..."
                  rows="3"
                  required
                />

                <h2>Payment method</h2>
                <label className="payment-option">
                  <input
                    type="radio"
                    value="UPI"
                    checked={paymentMethod === "UPI"}
                    onChange={(event) => setPaymentMethod(event.target.value)}
                  />
                  UPI (demo)
                </label>
                <label className="payment-option">
                  <input
                    type="radio"
                    value="Card"
                    checked={paymentMethod === "Card"}
                    onChange={(event) => setPaymentMethod(event.target.value)}
                  />
                  Card (demo)
                </label>
                <p className="demo-warning">
                  Demo only: no payment details are collected and no real payment is processed.
                </p>
                <button className="primary-button full-button" type="submit">
                  Place demo order · {money(total)}
                </button>
              </form>

              <aside className="checkout-summary">
                <h2>Order summary</h2>
                <p>{cartRestaurant.name}</p>
                {cart.map((item) => (
                  <div className="summary-row" key={item.id}>
                    <span>{item.quantity} × {item.name}</span>
                    <span>{money(item.price * item.quantity)}</span>
                  </div>
                ))}
                <div className="summary-row"><span>Delivery</span><span>{money(deliveryFee)}</span></div>
                <div className="summary-row summary-total"><strong>Total</strong><strong>{money(total)}</strong></div>
              </aside>
            </div>
          )}
        </main>
      )}

      {page === "confirmation" && confirmedOrder && (
        <main className="content page-content narrow-content">
          <div className="confirmation-card">
            <div className="confirmation-icon">✓</div>
            <h1>Order placed!</h1>
            <p>Thanks, {confirmedOrder.customerName}. Your demo order has been recorded.</p>
            <div className="order-number">Order #{confirmedOrder.id}</div>
            <div className="bill confirmation-bill">
              <div><span>Restaurant</span><span>{confirmedOrder.restaurantName}</span></div>
              <div><span>Payment method</span><span>{confirmedOrder.paymentMethod} (demo)</span></div>
              <div><span>Delivery address</span><span>{confirmedOrder.address}</span></div>
              <div className="bill-total"><strong>Total</strong><strong>{money(confirmedOrder.total)}</strong></div>
            </div>
            <p className="demo-warning">This is a local demo confirmation, not a real delivery order.</p>
            <button className="primary-button" onClick={() => setPage("orders")}>View my orders</button>
            <button className="text-button" onClick={goHome}>Back to home</button>
          </div>
        </main>
      )}

      {page === "orders" && (
        <main className="content page-content">
          <h1>My orders</h1>
          <p className="page-description">Your order history saved in this browser.</p>

          {orders.length === 0 ? (
            <div className="empty-state">
              <span>🧾</span>
              <h2>No orders yet</h2>
              <p>Your placed demo orders will appear here.</p>
              <button className="primary-button" onClick={goHome}>Explore restaurants</button>
            </div>
          ) : (
            <div className="orders-list">
              {orders.map((order) => (
                <article className="order-card" key={order.id}>
                  <div className="order-card-header">
                    <div>
                      <span className="order-number">Order #{order.id}</span>
                      <h2>{order.restaurantName}</h2>
                      <p>{order.createdAt}</p>
                    </div>
                    <span className={`order-status ${order.status === "Cancelled" ? "cancelled" : ""}`}>
                      {order.status}
                    </span>
                  </div>
                  <div className="order-foods">
                    {order.items.map((item) => (
                      <p key={item.id}>{item.quantity} × {item.name}</p>
                    ))}
                  </div>
                  <div className="order-card-footer">
                    <strong>{money(order.total)}</strong>
                    {order.status === "Order placed" && (
                      <button className="secondary-button cancel-button" onClick={() => cancelOrder(order.id)}>
                        Cancel order
                      </button>
                    )}
                  </div>
                </article>
              ))}
            </div>
          )}
        </main>
      )}

      <footer className="footer">
        <strong>🍊 FoodFlow</strong>
        <p>Made as a learning project · React frontend · Demo data only</p>
      </footer>
    </div>
  );
}

export default App;

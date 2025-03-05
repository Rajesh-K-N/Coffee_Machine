# Coffee Machine Simulation

## Overview

This project consists of a digital coffee machine simulation implemented in two different ways:

1. **Web-Based Coffee Machine (Python + Flask)**: A Flask-based web application that simulates a coffee machine with asynchronous operations.
2. **Console-Based Coffee Machine (C Language)**: A command-line coffee machine simulation written in C, providing a menu-driven interface for user interaction.

## Features

### Web-Based Coffee Machine (app.py)

- Built using Flask
- Supports operations like:
  - Power On/Off
  - Filling Water, Beans, and Milk
  - Brewing different types of coffee (Espresso, Americano, Latte, Cappuccino, Mocha)
  - Cleaning and Maintenance
- Uses a background thread for asynchronous operations
- Provides a REST API with endpoints:
  - `/` (Home page)
  - `/status` (Get machine status)
  - `/operate` (Post an operation request)

### Console-Based Coffee Machine (coffee\_machine.c)

- Menu-driven CLI application written in C
- Features include:
  - Power toggling
  - Filling resources (water, beans, milk)
  - Brewing coffee with resource checks
  - Cleaning and maintenance
- Uses `Sleep()` for a realistic simulation of operations

## Installation

### Web-Based (Flask App)

1. Install dependencies:
   ```sh
   pip install flask
   ```
2. Run the application:
   ```sh
   python app.py
   ```
3. Open `http://127.0.0.1:5000/` in a browser.

### Console-Based (C Program)

1. Compile the program (Windows):
   ```sh
   gcc coffee_machine.c -o coffee_machine.exe
   ```
2. Run the executable:
   ```sh
   ./coffee_machine.exe
   ```

## Usage

### Web Application

- Use the web interface to perform operations.
- You can also send API requests using a tool like Postman or Curl.

### Console Application

- Follow the on-screen menu to operate the coffee machine.
- Select coffee types, refill resources, and perform maintenance as needed.

## Future Enhancements

- Improve UI for the web application
- Add real-time status updates
- Implement a database for tracking usage history
- Add multi-threading support for the C version

## Author

This project was developed as a learning exercise in Python (Flask) and C programming.

Rajesh K N

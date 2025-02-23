# Calculator with Extended Operations

## Overview
This project is a command-line calculator implemented in C++ that supports both binary and unary operations. It includes standard arithmetic operations (addition, subtraction, multiplication, division) as well as advanced functions like trigonometric operations (sine, cosine, tangent), square, cubic, and exponential calculations. Additionally, the calculator offers an option to convert trigonometric input values from degrees to radians.

## Features
- **Smart Pointers:**  
  Uses `std::unique_ptr` for automatic memory management of operation objects.

- **Function Pointers:**  
  Employs function pointers to decouple the computation logic from the operation classes.

- **Binary & Unary Operations:**  
  Supports both binary operations (e.g., `+`, `-`, `*`, `/`) and unary operations (e.g., `sin`, `cos`, `tan`, `square`, `cubic`, `exp`).

- **User Interaction:**  
  Interactive command-line interface prompting for operation selection and operand input. For trigonometric functions, users can choose whether to input values in degrees, with an automatic conversion to radians.

## File Structure
- **main.cpp:**  
  Contains the complete source code of the calculator, including:
  - Operation classes (`Operation`, `BinaryOperation`, `UnaryOperation`)
  - Implementation of arithmetic and advanced functions
  - Command-line interface for user interaction

## Requirements
- A C++ compiler supporting C++11 or later (e.g., g++, clang++).

## Build and Run Instructions

1. **Compile the Code:**

   Open a terminal in the project directory and compile using a C++11 (or later) compliant compiler. For example, with `g++`:

   ```bash
   g++ -std=c++11 calc.cpp -o calc
   ```

2. **Run the Executable:**

   Execute the compiled program:

   ```bash
   ./calc
   ```

## Usage
- When you run the calculator, it displays a list of available operations:
  - **Binary:** `+`, `-`, `*`, `/`
  - **Unary:** `sin`, `cos`, `tan`, `square`, `cubic`, `exp`
- Enter the desired operation symbol or type `exit` to quit.
- For binary operations, the program will prompt for two operands.
- For unary operations:
  - The program will prompt for a single operand.
  - If the chosen operation is trigonometric (`sin`, `cos`, or `tan`), you'll be asked whether the input value is in degrees. If yes, the program converts the value to radians before computation.
- The result of the operation is then displayed, and you can choose to perform another calculation.

## Extensibility
- **Adding New Operations:**  
  Extend the base `Operation` class and create new derived classes for additional operations. Register new operations with the `Calculator` class using smart pointers.
  
- **Enhanced User Interface:**  
  Modify the command-line interface to support more complex expressions or additional interactive features.

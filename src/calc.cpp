/******************************
Date: 05.Feb.2025
Author: Harish Natarajan Ravi
Email: harrish.nr@gmail.com
******************************/

#include <iostream>
#include <memory>
#include <vector>
#include <stdexcept>
#include <cmath>
#include <string>

using namespace std;

// Constant for converting degrees to radians.
const double PI = 3.14159265358979323846;

// Function pointer typedefs for binary and unary operations.
typedef double (*BinaryFunc)(double, double);
typedef double (*UnaryFunc)(double);

// Binary operation functions
double add(double a, double b) {
    return a + b;
}

double subtract(double a, double b) {
    return a - b;
}

double multiply(double a, double b) {
    return a * b;
}

double divide(double a, double b) {
    if (b == 0.0) {
        throw runtime_error("Division by zero error");
    }
    return a / b;
}

// Unary operation functions for trigonometry, square, cubic, and exponential.
double sine(double a) {
    return sin(a);
}

double cosine(double a) {
    return cos(a);
}

double tangent(double a) {
    return tan(a);
}

double square(double a) {
    return a * a;
}

double cubic(double a) {
    return a * a * a;
}

double exponential(double a) {
    return exp(a);
}

// Base Operation class
class Operation {
protected:
    string symbol; // Identifier for the operation (e.g., "+", "sin", "square")
public:
    Operation(const string& sym) : symbol(sym) {}
    virtual ~Operation() {}
    string getSymbol() const { return symbol; }
    
    // Execute the operation given a vector of operands.
    virtual double execute(const vector<double>& args) const = 0;
};

// BinaryOperation class for operations requiring two operands.
class BinaryOperation : public Operation {
private:
    BinaryFunc func;
public:
    BinaryOperation(const string& sym, BinaryFunc f)
        : Operation(sym), func(f) {}
    
    double execute(const vector<double>& args) const override {
        if (args.size() != 2) {
            throw runtime_error("Binary operation requires 2 operands");
        }
        return func(args[0], args[1]);
    }
};

// UnaryOperation class for operations requiring one operand.
class UnaryOperation : public Operation {
private:
    UnaryFunc func;
public:
    UnaryOperation(const string& sym, UnaryFunc f)
        : Operation(sym), func(f) {}
    
    double execute(const vector<double>& args) const override {
        if (args.size() != 1) {
            throw runtime_error("Unary operation requires 1 operand");
        }
        return func(args[0]);
    }
};

// Calculator class manages a collection of operations using smart pointers.
class Calculator {
private:
    vector<std::unique_ptr<Operation>> operations;
public:
    // Register a new operation.
    void addOperation(unique_ptr<Operation> op) {
        operations.push_back(move(op));
    }
    
    // Retrieve an operation by its symbol.
    const Operation* getOperation(const string& sym) const {
        for (const auto& op : operations) {
            if (op->getSymbol() == sym)
                return op.get();
        }
        return nullptr;
    }
    
    // Perform a calculation with the given operator symbol and operands.
    double calculate(const std::string& sym, const vector<double>& args) const {
        const Operation* op = getOperation(sym);
        if (!op) {
            throw runtime_error("Operation not found: " + sym);
        }
        return op->execute(args);
    }
};

int main() {
    Calculator calc;
    
    // Register binary operations.
    calc.addOperation(make_unique<BinaryOperation>("+", add));
    calc.addOperation(make_unique<BinaryOperation>("-", subtract));
    calc.addOperation(make_unique<BinaryOperation>("*", multiply));
    calc.addOperation(make_unique<BinaryOperation>("/", divide));
    
    // Register unary operations.
    calc.addOperation(make_unique<UnaryOperation>("sin", sine));
    calc.addOperation(make_unique<UnaryOperation>("cos", cosine));
    calc.addOperation(make_unique<UnaryOperation>("tan", tangent));
    calc.addOperation(make_unique<UnaryOperation>("square", square));
    calc.addOperation(make_unique<UnaryOperation>("cubic", cubic));
    calc.addOperation(make_unique<UnaryOperation>("exp", exponential));
    
    string opSymbol;
    char continueChoice = 'y';
    
    cout << "The Calculator!\n";
    cout << "Available operations:\n";
    cout << "Binary: +, -, *, /\n";
    cout << "Unary: sin, cos, tan, square, cubic, exp\n\n";
    
    while (continueChoice == 'y' || continueChoice == 'Y') {
        cout << "Enter an operation symbol (or type 'exit' to quit): ";
        cin >> opSymbol;
        
        if (opSymbol == "exit") {
            break;
        }
        
        // Get the operation object.
        const Operation* op = calc.getOperation(opSymbol);
        if (!op) {
            cerr << "Operation not found. Please try again.\n";
            continue;
        }
        
        // Determine if the operation is binary or unary.
        vector<double> operands;
        if (dynamic_cast<const BinaryOperation*>(op)) {
            double a, b;
            cout << "Enter the first operand: ";
            cin >> a;
            cout << "Enter the second operand: ";
            cin >> b;
            operands.push_back(a);
            operands.push_back(b);
        } else if (dynamic_cast<const UnaryOperation*>(op)) {
            double a;
            cout << "Enter the operand: ";
            cin >> a;
            
            // For trigonometric functions, ask if the input is in degrees.
            if (opSymbol == "sin" || opSymbol == "cos" || opSymbol == "tan") {
                char unitChoice;
                cout << "Is the value in degrees? (y/n): ";
                cin >> unitChoice;
                if (unitChoice == 'y' || unitChoice == 'Y') {
                    a = a * (PI / 180.0); // Convert degrees to radians.
                }
            }
            
            operands.push_back(a);
        } else {
            std::cerr << "Unknown operation type.\n";
            continue;
        }
        
        try {
            double result = calc.calculate(opSymbol, operands);
            cout << "Result: " << result << "\n";
        } catch (const std::exception& e) {
            cerr << "Error: " << e.what() << "\n";
        }
        
        cout << "\nDo you want to perform another operation? (y/n): ";
        cin >> continueChoice;
        cout << "\n";
    }
    
    cout << "Thank you!\n";
    return 0;
}

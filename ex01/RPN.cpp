#include "RPN.hpp"
#include <sstream>
#include <stdexcept>

RPN::RPN() {}

RPN::~RPN() {}

RPN::RPN(const RPN& other) : _stack(other._stack) {}

RPN& RPN::operator=(const RPN& other) {
    if (this != &other) {
        _stack = other._stack;
    }
    return *this;
}

bool RPN::isOperator(const std::string& token) {
    return token == "+" || token == "-" || token == "*" || token == "/";
}

bool RPN::isNumber(const std::string& token) {
    if (token.empty()) return false;

    // Vérifier si c'est un chiffre unique (0-9)
    if (token.length() == 1 && token[0] >= '0' && token[0] <= '9') {
        return true;
    }

    return false;
}

int RPN::performOperation(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) throw std::runtime_error("Division by zero");
            return a / b;
        default: throw std::runtime_error("Unknown operator");
    }
}

int RPN::evaluate(const std::string& expression) {
    // Vider la pile au début
    while (!_stack.empty()) {
        _stack.pop();
    }

    std::istringstream iss(expression);
    std::string token;

    while (iss >> token) {
        if (isNumber(token)) {
            // Convertir le caractère en nombre
            int num = token[0] - '0';
            _stack.push(num);
        }
        else if (isOperator(token)) {
            if (_stack.size() < 2) {
                throw std::runtime_error("Not enough operands");
            }

            // Attention à l'ordre : le dernier empilé est le deuxième opérande
            int b = _stack.top(); _stack.pop();
            int a = _stack.top(); _stack.pop();

            int result = performOperation(a, b, token[0]);
            _stack.push(result);
        }
        else {
            throw std::runtime_error("Invalid token: " + token);
        }
    }

    if (_stack.size() != 1) {
        throw std::runtime_error("Invalid expression");
    }

    return _stack.top();
}

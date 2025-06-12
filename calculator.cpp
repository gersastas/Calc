#include "calculator.h"
#include <unordered_map>
#include <functional>
#include <limits>

bool ReadNumber(Number& result) {
    std::cin >> result;
    if (std::cin.fail()) {
        std::cerr << "Error: Numeric operand expected" << std::endl;
        return false;
    }
    return true;
}

bool RunCalculatorCycle() {
    Number value = 0.0;
    Number memoryValue = 0.0;
    bool memorySet = false;

    if (!ReadNumber(value)) {
        return false;
    }

    // Карта бинарных операций
    std::unordered_map<std::string, std::function<Number(Number, Number)>> operations = {
        {"+", [](Number a, Number b) { return a + b; }},
        {"-", [](Number a, Number b) { return a - b; }},
        {"*", [](Number a, Number b) { return a * b; }},
        {"/", [](Number a, Number b) {
            return (b == 0) ? std::numeric_limits<Number>::infinity() : a / b;
        }},
        {"**", [](Number a, Number b) { return std::pow(a, b); }},
        {":", [](Number, Number b) { return b; }} // Замена значения
    };

    std::string token;
    while (std::cin >> token) {
        if (token == "q") {
            break;
        } else if (token == "=") {
            std::cout << value << std::endl;
        } else if (operations.contains(token)) {
            Number operand = 0.0;
            if (!ReadNumber(operand)) {
                return false;
            }
            value = operations[token](value, operand);
        } else if (token == "c") {
            value = 0;
        } else if (token == "s") {
            memoryValue = value;
            memorySet = true;
        } else if (token == "l") {
            if (!memorySet) {
                std::cerr << "Error: Memory is empty" << std::endl;
                return false;
            }
            value = memoryValue;
        } else {
            std::cerr << "Error: Unknown token " << token << std::endl;
            return false;
        }
    }

    return true;
}

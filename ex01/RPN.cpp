#include "RPN.hpp"

RPN::RPN() {}

RPN::RPN(const RPN& other) : _operandStack(other._operandStack) {}

RPN& RPN::operator=(const RPN& other)
{
    if (this != &other)
        _operandStack = other._operandStack;
    return *this;
}

RPN::~RPN() {}

bool RPN::_isOperator(const std::string& token) const
{
    return token == "+" || token == "-" || token == "*" || token == "/";
}

bool RPN::_isValidNumber(const std::string& token) const
{
    if (token.empty())
        return false;
    
    size_t start = 0;
    if (token[0] == '-' || token[0] == '+')
    {
        if (token.length() == 1)
            return false;
        start = 1;
    }
    
    for (size_t i = start; i < token.length(); ++i)
    {
        if (!std::isdigit(token[i]))
            return false;
    }

    char* endptr;
    long num = std::strtol(token.c_str(), &endptr, 10);
    if (*endptr != '\0')
        return false;
    
    return num >= 0 && num <= 9;
}

int RPN::_performOperation(int operand1, int operand2, const std::string& op) const
{
    if (op == "+")
        return operand1 + operand2;
    else if (op == "-")
        return operand1 - operand2;
    else if (op == "*")
        return operand1 * operand2;
    else if (op == "/")
    {
        if (operand2 == 0)
            throw std::runtime_error("Error: division by zero");
        return operand1 / operand2;
    }
    throw std::runtime_error("Error: invalid operator");
}

void RPN::_clearStack()
{
    while (!_operandStack.empty())
        _operandStack.pop();
}

int RPN::calculate(const std::string& expression)
{
    _clearStack();
    
    std::istringstream iss(expression);
    std::string token;
    
    while (iss >> token)
    {
        if (_isValidNumber(token))
        {
            int num = std::atoi(token.c_str());
            _operandStack.push(num);
        }
        else if (_isOperator(token))
        {
            if (_operandStack.size() < 2)
                throw std::runtime_error("Error: insufficient operands");
            
            int operand2 = _operandStack.top();
            _operandStack.pop();
            int operand1 = _operandStack.top();
            _operandStack.pop();
            
            int result = _performOperation(operand1, operand2, token);
            _operandStack.push(result);
        }
        else
        {
            throw std::runtime_error("Error: invalid token");
        }
    }
    
    if (_operandStack.size() != 1)
        throw std::runtime_error("Error: invalid expression");
    
    return _operandStack.top();
}

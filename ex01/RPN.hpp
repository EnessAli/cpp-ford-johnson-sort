#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <stack>
# include <string>
# include <sstream>
# include <cstdlib>

class RPN
{
private:
    std::stack<int> _operandStack;
    
    bool    _isOperator(const std::string& token) const;
    bool    _isValidNumber(const std::string& token) const;
    int     _performOperation(int operand1, int operand2, const std::string& op) const;
    void    _clearStack();

public:
    RPN();
    RPN(const RPN& other);
    RPN& operator=(const RPN& other);
    ~RPN();

    int     calculate(const std::string& expression);
};

#endif

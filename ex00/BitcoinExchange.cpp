#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : _exchangeRates(other._exchangeRates) {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
    if (this != &other)
        _exchangeRates = other._exchangeRates;
    return *this;
}

BitcoinExchange::~BitcoinExchange() {}

std::string BitcoinExchange::_trim(const std::string& str) const
{
    size_t start = str.find_first_not_of(" \t\r\n");
    if (start == std::string::npos)
        return "";
    size_t end = str.find_last_not_of(" \t\r\n");
    return str.substr(start, end - start + 1);
}

bool BitcoinExchange::_isLeapYear(int year) const
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool BitcoinExchange::_parseDate(const std::string& date, int& year, int& month, int& day) const
{
    if (date.length() != 10 || date[4] != '-' || date[7] != '-')
        return false;
    
    std::string yearStr = date.substr(0, 4);
    std::string monthStr = date.substr(5, 2);
    std::string dayStr = date.substr(8, 2);
    
    char* endptr;
    year = std::strtol(yearStr.c_str(), &endptr, 10);
    if (*endptr != '\0') return false;
    
    month = std::strtol(monthStr.c_str(), &endptr, 10);
    if (*endptr != '\0') return false;
    
    day = std::strtol(dayStr.c_str(), &endptr, 10);
    if (*endptr != '\0') return false;
    
    return true;
}

bool BitcoinExchange::_isValidDate(const std::string& date) const
{
    int year, month, day;
    
    if (!_parseDate(date, year, month, day))
        return false;
    
    if (year < 2009 || year > 2025)
        return false;
    
    if (month < 1 || month > 12)
        return false;
    
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (_isLeapYear(year))
        daysInMonth[1] = 29;
    
    if (day < 1 || day > daysInMonth[month - 1])
        return false;
    
    return true;
}

bool BitcoinExchange::_isValidValue(double value) const
{
    return value >= 0 && value <= 1000;
}

double BitcoinExchange::_findExchangeRate(const std::string& date) const
{
    std::map<std::string, double>::const_iterator it = _exchangeRates.find(date);
    if (it != _exchangeRates.end())
        return it->second;

    std::map<std::string, double>::const_iterator lower = _exchangeRates.lower_bound(date);
    if (lower == _exchangeRates.begin())
        return -1;
    
    --lower;
    return lower->second;
}

bool BitcoinExchange::loadDatabase(const std::string& filename)
{
    std::ifstream file(filename.c_str());
    if (!file.is_open())
    {
        std::cerr << "Error: could not open database file." << std::endl;
        return false;
    }
    
    std::string line;
    bool firstLine = true;
    
    while (std::getline(file, line))
    {
        if (firstLine)
        {
            firstLine = false;
            continue;
        }
        
        size_t commaPos = line.find(',');
        if (commaPos == std::string::npos)
            continue;
        
        std::string date = _trim(line.substr(0, commaPos));
        std::string valueStr = _trim(line.substr(commaPos + 1));
        
        if (!_isValidDate(date))
            continue;
        
        char* endptr;
        double value = std::strtod(valueStr.c_str(), &endptr);
        if (*endptr != '\0')
            continue;
        
        _exchangeRates[date] = value;
    }
    
    file.close();
    return true;
}

void BitcoinExchange::processInputFile(const std::string& filename)
{
    std::ifstream file(filename.c_str());
    if (!file.is_open())
    {
        std::cerr << "Error: could not open file." << std::endl;
        return;
    }
    
    std::string line;
    bool firstLine = true;
    
    while (std::getline(file, line))
    {
        if (firstLine)
        {
            firstLine = false;
            continue;
        }
        
        if (line.empty())
            continue;
        
        size_t pipePos = line.find('|');
        if (pipePos == std::string::npos)
        {
            std::cerr << "Error: bad input => " << _trim(line) << std::endl;
            continue;
        }
        
        std::string date = _trim(line.substr(0, pipePos));
        std::string valueStr = _trim(line.substr(pipePos + 1));
        
        if (!_isValidDate(date))
        {
            std::cerr << "Error: bad input => " << date << std::endl;
            continue;
        }
        
        char* endptr;
        double value = std::strtod(valueStr.c_str(), &endptr);
        if (*endptr != '\0')
        {
            std::cerr << "Error: bad input => " << valueStr << std::endl;
            continue;
        }
        
        if (value < 0)
        {
            std::cerr << "Error: not a positive number." << std::endl;
            continue;
        }
        
        if (!_isValidValue(value))
        {
            std::cerr << "Error: too large a number." << std::endl;
            continue;
        }
        
        double rate = _findExchangeRate(date);
        if (rate < 0)
        {
            std::cerr << "Error: no valid exchange rate found for date." << std::endl;
            continue;
        }
        
        double result = value * rate;
        std::cout << date << " => " << value << " = " << result << std::endl;
    }
    
    file.close();
}

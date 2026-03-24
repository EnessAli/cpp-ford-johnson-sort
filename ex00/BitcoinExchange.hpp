#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <fstream>
# include <sstream>
# include <map>
# include <string>
# include <cstdlib>

class BitcoinExchange
{
private:
    std::map<std::string, double> _exchangeRates;
    
    bool    _isValidDate(const std::string& date) const;
    bool    _isValidValue(double value) const;
    bool    _parseDate(const std::string& date, int& year, int& month, int& day) const;
    bool    _isLeapYear(int year) const;
    double  _findExchangeRate(const std::string& date) const;
    std::string _trim(const std::string& str) const;

public:
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange& other);
    BitcoinExchange& operator=(const BitcoinExchange& other);
    ~BitcoinExchange();

    bool    loadDatabase(const std::string& filename);
    void    processInputFile(const std::string& filename);
};

#endif

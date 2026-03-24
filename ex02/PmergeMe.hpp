#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <vector>
# include <deque>
# include <string>
# include <cstdlib>
# include <ctime>
# include <sys/time.h>

class PmergeMe
{
private:
    std::vector<int>    _vectorData;
    std::deque<int>     _dequeData;

    void    _fordJohnsonSort(std::vector<int>& arr);
    void    _mergeInsertSort(std::vector<int>& arr, int start, int end);
    void    _insertionSort(std::vector<int>& arr, int start, int end);
    void    _merge(std::vector<int>& arr, int start, int mid, int end);

    void    _fordJohnsonSort(std::deque<int>& arr);
    void    _mergeInsertSort(std::deque<int>& arr, int start, int end);
    void    _insertionSort(std::deque<int>& arr, int start, int end);
    void    _merge(std::deque<int>& arr, int start, int mid, int end);

    bool    _isValidNumber(const std::string& str) const;
    double  _getTime() const;
    void    _printSequence(const std::vector<int>& arr, const std::string& prefix) const;
    void    _printSequence(const std::deque<int>& arr, const std::string& prefix) const;

public:
    PmergeMe();
    PmergeMe(const PmergeMe& other);
    PmergeMe& operator=(const PmergeMe& other);
    ~PmergeMe();

    bool    parseInput(int argc, char* argv[]);
    void    sortAndDisplay();
};

#endif

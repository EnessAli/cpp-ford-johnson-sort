#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& other) : _vectorData(other._vectorData), _dequeData(other._dequeData) {}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
    if (this != &other)
    {
        _vectorData = other._vectorData;
        _dequeData = other._dequeData;
    }
    return *this;
}

PmergeMe::~PmergeMe() {}

double PmergeMe::_getTime() const
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000.0 + tv.tv_usec;
}

bool PmergeMe::_isValidNumber(const std::string& str) const
{
    if (str.empty())
        return false;
    
    for (size_t i = 0; i < str.length(); ++i)
    {
        if (!std::isdigit(str[i]))
            return false;
    }
    
    char* endptr;
    long num = std::strtol(str.c_str(), &endptr, 10);
    if (*endptr != '\0' || num <= 0 || num > 2147483647)
        return false;
    
    return true;
}

void PmergeMe::_printSequence(const std::vector<int>& arr, const std::string& prefix) const
{
    std::cout << prefix;
    for (size_t i = 0; i < arr.size() && i < 10; ++i)
    {
        std::cout << arr[i];
        if (i < arr.size() - 1 && i < 9)
            std::cout << " ";
    }
    if (arr.size() > 10)
        std::cout << " [...]";
    std::cout << std::endl;
}

void PmergeMe::_printSequence(const std::deque<int>& arr, const std::string& prefix) const
{
    std::cout << prefix;
    for (size_t i = 0; i < arr.size() && i < 10; ++i)
    {
        std::cout << arr[i];
        if (i < arr.size() - 1 && i < 9)
            std::cout << " ";
    }
    if (arr.size() > 10)
        std::cout << " [...]";
    std::cout << std::endl;
}

 Vector implementations
void PmergeMe::_insertionSort(std::vector<int>& arr, int start, int end)
{
    for (int i = start + 1; i <= end; i++)
    {
        int key = arr[i];
        int j = i - 1;
        
        while (j >= start && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

void PmergeMe::_merge(std::vector<int>& arr, int start, int mid, int end)
{
    std::vector<int> left(arr.begin() + start, arr.begin() + mid + 1);
    std::vector<int> right(arr.begin() + mid + 1, arr.begin() + end + 1);
    
    int i = 0, j = 0, k = start;
    
    while (i < static_cast<int>(left.size()) && j < static_cast<int>(right.size()))
    {
        if (left[i] <= right[j])
            arr[k++] = left[i++];
        else
            arr[k++] = right[j++];
    }
    
    while (i < static_cast<int>(left.size()))
        arr[k++] = left[i++];
    
    while (j < static_cast<int>(right.size()))
        arr[k++] = right[j++];
}

void PmergeMe::_mergeInsertSort(std::vector<int>& arr, int start, int end)
{
    if (end - start <= 10)
    {
        _insertionSort(arr, start, end);
        return;
    }
    
    int mid = start + (end - start) / 2;
    _mergeInsertSort(arr, start, mid);
    _mergeInsertSort(arr, mid + 1, end);
    _merge(arr, start, mid, end);
}

void PmergeMe::_fordJohnsonSort(std::vector<int>& arr)
{
    if (arr.size() <= 1)
        return;
    
    _mergeInsertSort(arr, 0, arr.size() - 1);
}

void PmergeMe::_insertionSort(std::deque<int>& arr, int start, int end)
{
    for (int i = start + 1; i <= end; i++)
    {
        int key = arr[i];
        int j = i - 1;
        
        while (j >= start && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

void PmergeMe::_merge(std::deque<int>& arr, int start, int mid, int end)
{
    std::deque<int> left(arr.begin() + start, arr.begin() + mid + 1);
    std::deque<int> right(arr.begin() + mid + 1, arr.begin() + end + 1);
    
    int i = 0, j = 0, k = start;
    
    while (i < static_cast<int>(left.size()) && j < static_cast<int>(right.size()))
    {
        if (left[i] <= right[j])
            arr[k++] = left[i++];
        else
            arr[k++] = right[j++];
    }
    
    while (i < static_cast<int>(left.size()))
        arr[k++] = left[i++];
    
    while (j < static_cast<int>(right.size()))
        arr[k++] = right[j++];
}

void PmergeMe::_mergeInsertSort(std::deque<int>& arr, int start, int end)
{
    if (end - start <= 10)
    {
        _insertionSort(arr, start, end);
        return;
    }
    
    int mid = start + (end - start) / 2;
    _mergeInsertSort(arr, start, mid);
    _mergeInsertSort(arr, mid + 1, end);
    _merge(arr, start, mid, end);
}

void PmergeMe::_fordJohnsonSort(std::deque<int>& arr)
{
    if (arr.size() <= 1)
        return;
    
    _mergeInsertSort(arr, 0, arr.size() - 1);
}

bool PmergeMe::parseInput(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "Error: no input provided" << std::endl;
        return false;
    }
    
    for (int i = 1; i < argc; ++i)
    {
        if (!_isValidNumber(argv[i]))
        {
            std::cerr << "Error" << std::endl;
            return false;
        }
        
        int num = std::atoi(argv[i]);
        _vectorData.push_back(num);
        _dequeData.push_back(num);
    }
    
    return true;
}

void PmergeMe::sortAndDisplay()
{
    _printSequence(_vectorData, "Before: ");

    std::vector<int> vectorCopy = _vectorData;
    double startTime = _getTime();
    _fordJohnsonSort(vectorCopy);
    double endTime = _getTime();
    double vectorTime = endTime - startTime;

    std::deque<int> dequeCopy = _dequeData;
    startTime = _getTime();
    _fordJohnsonSort(dequeCopy);
    endTime = _getTime();
    double dequeTime = endTime - startTime;

    _printSequence(vectorCopy, "After:  ");

    std::cout << "Time to process a range of " << _vectorData.size() 
              << " elements with std::vector : " << vectorTime << " us" << std::endl;
    std::cout << "Time to process a range of " << _dequeData.size() 
              << " elements with std::deque  : " << dequeTime << " us" << std::endl;
}

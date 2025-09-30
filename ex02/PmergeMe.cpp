
#include "PmergeMe.hpp"
#include <cmath>
#include <sys/time.h>
#include <cstdlib>
#include <iostream>
#include <cctype>

PmergeMe::PmergeMe() {}

PmergeMe::~PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& other) : _vectorData(other._vectorData), _dequeData(other._dequeData) {}

PmergeMe& PmergeMe::operator=(const PmergeMe& other) {
    if (this != &other) {
        _vectorData = other._vectorData;
        _dequeData = other._dequeData;
    }
    return *this;
}

bool PmergeMe::isValidNumber(const std::string& str) {
    if (str.empty()) return false;

    for (size_t i = 0; i < str.length(); i++) {
        if (!isdigit(str[i])) return false;
    }

    long num = std::atol(str.c_str());
    return num > 0 && num <= 2147483647;
}

bool PmergeMe::parseInput(int argc, char* argv[]) {
    if (argc < 2) return false;

    for (int i = 1; i < argc; i++) {
        if (!isValidNumber(argv[i])) {
            std::cerr << "Error" << std::endl;
            return false;
        }

        int num = std::atoi(argv[i]);
        _vectorData.push_back(num);
        _dequeData.push_back(num);
    }

    return true;
}

void PmergeMe::insertionSortVector(std::vector<int>& arr, int left, int right, Statistics& stats) {
    int n = right - left + 1; //taille du tab
    if (n <= 1) return;
    
    static const int order[] = {1, 3, 2, 5, 4, 7, 6, 9, 8, 11, 10, 13, 12, 15, 14, 17, 16, 19, 18, 21, 20};
    
    for (int i = 0; i < 21 && order[i] < n; i++) {
        int idx = order[i];  // idx = 1 -> 3 -> 2.........
        
        int key = arr[left + idx]; // index de element a  insere
        stats.movements++;
        int j = left + idx - 1; //trouve ou insere
        
        while (j >= left && (stats.comparisons++, arr[j] > key)) { //decal les element plus grand
            arr[j + 1] = arr[j];
            stats.movements++;
            j--;
        }
        arr[j + 1] = key; //inesertion
        stats.movements++;
    }
}

void PmergeMe::mergeVector(std::vector<int>& arr, int left, int mid, int right, Statistics& stats) {
    std::vector<int> leftArr(arr.begin() + left, arr.begin() + mid + 1);
    std::vector<int> rightArr(arr.begin() + mid + 1, arr.begin() + right + 1);

    stats.movements += leftArr.size() + rightArr.size();

    int i = 0, j = 0, k = left;

    while (i < (int)leftArr.size() && j < (int)rightArr.size()) {
        stats.comparisons++;
        if (leftArr[i] <= rightArr[j]) {
            arr[k++] = leftArr[i++];
        } else {
            arr[k++] = rightArr[j++];
        }
        stats.movements++;
    }

    while (i < (int)leftArr.size()) {
        arr[k++] = leftArr[i++];
        stats.movements++;
    }

    while (j < (int)rightArr.size()) {
        arr[k++] = rightArr[j++];
        stats.movements++;
    }
}

void PmergeMe::fordJohnsonSortVector(std::vector<int>& arr, Statistics& stats) {
    int n = arr.size();
    if (n <= 1) return;

    const int THRESHOLD = 10;

    if (n <= THRESHOLD) {
        insertionSortVector(arr, 0, n - 1, stats);
        return;
    }

    int mid = n / 2;

    std::vector<int> left(arr.begin(), arr.begin() + mid);
    std::vector<int> right(arr.begin() + mid, arr.end());

    stats.movements += left.size() + right.size();

    fordJohnsonSortVector(left, stats);
    fordJohnsonSortVector(right, stats);

    std::copy(left.begin(), left.end(), arr.begin());
    std::copy(right.begin(), right.end(), arr.begin() + mid);
    stats.movements += left.size() + right.size();

    mergeVector(arr, 0, mid - 1, n - 1, stats);
}

void PmergeMe::insertionSortDeque(std::deque<int>& arr, int left, int right, Statistics& stats) {
    int n = right - left + 1;
    if (n <= 1) return;
    
    static const int order[] = {1, 3, 2, 5, 4, 7, 6, 9, 8, 11, 10, 13, 12, 15, 14, 17, 16, 19, 18, 21, 20};
    
    for (int i = 0; i < 21 && order[i] < n; i++) {
        int idx = order[i];
        
        int key = arr[left + idx];
        stats.movements++;
        int j = left + idx - 1;
        
        while (j >= left && (stats.comparisons++, arr[j] > key)) {
            arr[j + 1] = arr[j];
            stats.movements++;
            j--;
        }
        arr[j + 1] = key;
        stats.movements++;
    }
}

void PmergeMe::mergeDeque(std::deque<int>& arr, int left, int mid, int right, Statistics& stats) {
    std::deque<int> leftArr(arr.begin() + left, arr.begin() + mid + 1);
    std::deque<int> rightArr(arr.begin() + mid + 1, arr.begin() + right + 1);

    stats.movements += leftArr.size() + rightArr.size();

    int i = 0, j = 0, k = left;

    while (i < (int)leftArr.size() && j < (int)rightArr.size()) {
        stats.comparisons++;
        if (leftArr[i] <= rightArr[j]) {
            arr[k++] = leftArr[i++];
        } else {
            arr[k++] = rightArr[j++];
        }
        stats.movements++;
    }

    while (i < (int)leftArr.size()) {
        arr[k++] = leftArr[i++];
        stats.movements++;
    }

    while (j < (int)rightArr.size()) {
        arr[k++] = rightArr[j++];
        stats.movements++;
    }
}

void PmergeMe::fordJohnsonSortDeque(std::deque<int>& arr, Statistics& stats) {
    int n = arr.size();
    if (n <= 1) return;

    const int THRESHOLD = 10;

    if (n <= THRESHOLD) {
        insertionSortDeque(arr, 0, n - 1, stats);
        return;
    }

    int mid = n / 2;

    std::deque<int> left(arr.begin(), arr.begin() + mid);
    std::deque<int> right(arr.begin() + mid, arr.end());

    stats.movements += left.size() + right.size();

    fordJohnsonSortDeque(left, stats);
    fordJohnsonSortDeque(right, stats);

    std::copy(left.begin(), left.end(), arr.begin());
    std::copy(right.begin(), right.end(), arr.begin() + mid);
    stats.movements += left.size() + right.size();

    mergeDeque(arr, 0, mid - 1, n - 1, stats);
}

void PmergeMe::sort() {
    struct timeval start, end;

    std::cout << "Before: ";
    for (size_t i = 0; i < _vectorData.size() && i < 5; i++) {
        std::cout << _vectorData[i] << " ";
    }
    if (_vectorData.size() > 5) {
        std::cout << "[...]";
    }
    std::cout << std::endl;

    _vectorStats.reset();
    _dequeStats.reset();

    std::vector<int> vectorCopy = _vectorData;
    gettimeofday(&start, NULL);
    fordJohnsonSortVector(vectorCopy, _vectorStats);
    gettimeofday(&end, NULL);

    double vectorTime = (end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec);

    std::deque<int> dequeCopy = _dequeData;
    gettimeofday(&start, NULL);
    fordJohnsonSortDeque(dequeCopy, _dequeStats);
    gettimeofday(&end, NULL);

    double dequeTime = (end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec);

    std::cout << "After: ";
    for (size_t i = 0; i < vectorCopy.size() && i < 5; i++) {
        std::cout << vectorCopy[i] << " ";
    }
    if (vectorCopy.size() > 5) {
        std::cout << "[...]";
    }
    std::cout << std::endl;

    std::cout << "Time to process a range of " << _vectorData.size()
              << " elements with std::vector : " << std::fixed << vectorTime << " us" << std::endl;
    std::cout << "Time to process a range of " << _dequeData.size()
              << " elements with std::deque : " << std::fixed << dequeTime << " us" << std::endl;

    std::cout << std::endl << "=== ALGORITHM EFFICIENCY ANALYSIS ===" << std::endl;

    std::cout << "std::vector statistics:" << std::endl;
    std::cout << "  - Comparisons: " << _vectorStats.comparisons << std::endl;
    std::cout << "  - Movements: " << _vectorStats.movements << std::endl;
    std::cout << "  - Total operations: " << (_vectorStats.comparisons + _vectorStats.movements) << std::endl;

    std::cout << "std::deque statistics:" << std::endl;
    std::cout << "  - Comparisons: " << _dequeStats.comparisons << std::endl;
    std::cout << "  - Movements: " << _dequeStats.movements << std::endl;
    std::cout << "  - Total operations: " << (_dequeStats.comparisons + _dequeStats.movements) << std::endl;

    long n = _vectorData.size();
    long theoretical_ford_johnson = n * (long)(log(n) / log(2)) - n + 1;  
    long theoretical_mergesort = n * (long)(log(n) / log(2));  
    long theoretical_quicksort = n * (long)(log(n) / log(2));
    long theoretical_bubble = (n * (n - 1)) / 2;

    std::cout << std::endl << "Theoretical complexity comparison (for n=" << n << "):" << std::endl;
    std::cout << "  - Ford-Johnson (theory): ~" << theoretical_ford_johnson << " comparison" << std::endl;
    std::cout << "  - Standard merge sort: ~" << theoretical_mergesort << " comparison" << std::endl;
    std::cout << "  - Standard quick sort: ~" << theoretical_quicksort << " comparison" << std::endl;
    std::cout << "  - Bubble sort: ~" << theoretical_bubble << " comparison" << std::endl;

    std::cout << std::endl << "Ford-Johnson timing (lower is better):" << std::endl;
    std::cout << "  - Vector implementation: " << std::fixed << vectorTime << " us" << std::endl;
    std::cout << "  - Deque implementation: " << std::fixed << dequeTime << " us" << std::endl;

}

void PmergeMe::displayResults() {
    sort();
}

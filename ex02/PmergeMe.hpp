
#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <ctime>
#include <cmath>
#include <string>


class PmergeMe {
private:
    std::vector<int> _vectorData;
    std::deque<int> _dequeData;

    struct Statistics {
        long comparisons;
        long movements;

        Statistics() : comparisons(0), movements(0) {}
        void reset() { comparisons = 0; movements = 0; }
    };

    mutable Statistics _vectorStats;
    mutable Statistics _dequeStats;

    void fordJohnsonSortVector(std::vector<int>& arr, Statistics& stats);
    void insertionSortVector(std::vector<int>& arr, int left, int right, Statistics& stats);
    void mergeVector(std::vector<int>& arr, int left, int mid, int right, Statistics& stats);

    void fordJohnsonSortDeque(std::deque<int>& arr, Statistics& stats);
    void insertionSortDeque(std::deque<int>& arr, int left, int right, Statistics& stats);
    void mergeDeque(std::deque<int>& arr, int left, int mid, int right, Statistics& stats);

    bool isValidNumber(const std::string& str);

public:
    PmergeMe();
    ~PmergeMe();
    PmergeMe(const PmergeMe& other);
    PmergeMe& operator=(const PmergeMe& other);

    bool parseInput(int argc, char* argv[]);
    void sort();
    void displayResults();
};

#endif

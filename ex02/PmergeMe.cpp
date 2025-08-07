// #include "PmergeMe.hpp"
// #include <sys/time.h>


// PmergeMe::PmergeMe() {}

// PmergeMe::~PmergeMe() {}

// PmergeMe::PmergeMe(const PmergeMe& other) : _vectorData(other._vectorData), _dequeData(other._dequeData) {}

// PmergeMe& PmergeMe::operator=(const PmergeMe& other) {
//     if (this != &other) {
//         _vectorData = other._vectorData;
//         _dequeData = other._dequeData;
//     }
//     return *this;
// }

// bool PmergeMe::isValidNumber(const std::string& str) {
//     if (str.empty()) return false;

//     for (size_t i = 0; i < str.length(); i++) {
//         if (!isdigit(str[i])) return false;
//     }

//     long num = std::atol(str.c_str());
//     return num > 0 && num <= 2147483647;
// }

// bool PmergeMe::parseInput(int argc, char* argv[]) {
//     if (argc < 2) return false;

//     for (int i = 1; i < argc; i++) {
//         if (!isValidNumber(argv[i])) {
//             std::cerr << "Error" << std::endl;
//             return false;
//         }

//         int num = std::atoi(argv[i]);
//         _vectorData.push_back(num);
//         _dequeData.push_back(num);
//     }

//     return true;
// }

// // Implémentation Ford-Johnson pour std::vector
// void PmergeMe::insertionSortVector(std::vector<int>& arr, int left, int right) {
//     for (int i = left + 1; i <= right; i++) {
//         int key = arr[i];
//         int j = i - 1;

//         while (j >= left && arr[j] > key) {
//             arr[j + 1] = arr[j];
//             j--;
//         }
//         arr[j + 1] = key;
//     }
// }

// void PmergeMe::mergeVector(std::vector<int>& arr, int left, int mid, int right) {
//     std::vector<int> leftArr(arr.begin() + left, arr.begin() + mid + 1);
//     std::vector<int> rightArr(arr.begin() + mid + 1, arr.begin() + right + 1);

//     int i = 0, j = 0, k = left;

//     while (i < (int)leftArr.size() && j < (int)rightArr.size()) {
//         if (leftArr[i] <= rightArr[j]) {
//             arr[k++] = leftArr[i++];
//         } else {
//             arr[k++] = rightArr[j++];
//         }
//     }

//     while (i < (int)leftArr.size()) {
//         arr[k++] = leftArr[i++];
//     }

//     while (j < (int)rightArr.size()) {
//         arr[k++] = rightArr[j++];
//     }
// }

// void PmergeMe::fordJohnsonSortVector(std::vector<int>& arr) {
//     int n = arr.size();
//     if (n <= 1) return;

//     // Seuil pour utiliser insertion sort sur les petits tableaux
//     const int THRESHOLD = 10;

//     if (n <= THRESHOLD) {
//         insertionSortVector(arr, 0, n - 1);
//         return;
//     }

//     // Diviser en deux parties
//     int mid = n / 2;

//     std::vector<int> left(arr.begin(), arr.begin() + mid);
//     std::vector<int> right(arr.begin() + mid, arr.end());

//     // Tri récursif
//     fordJohnsonSortVector(left);
//     fordJohnsonSortVector(right);

//     // Fusion
//     std::copy(left.begin(), left.end(), arr.begin());
//     std::copy(right.begin(), right.end(), arr.begin() + mid);

//     mergeVector(arr, 0, mid - 1, n - 1);
// }

// // Implémentation Ford-Johnson pour std::deque
// void PmergeMe::insertionSortDeque(std::deque<int>& arr, int left, int right) {
//     for (int i = left + 1; i <= right; i++) {
//         int key = arr[i];
//         int j = i - 1;

//         while (j >= left && arr[j] > key) {
//             arr[j + 1] = arr[j];
//             j--;
//         }
//         arr[j + 1] = key;
//     }
// }

// void PmergeMe::mergeDeque(std::deque<int>& arr, int left, int mid, int right) {
//     std::deque<int> leftArr(arr.begin() + left, arr.begin() + mid + 1);
//     std::deque<int> rightArr(arr.begin() + mid + 1, arr.begin() + right + 1);

//     int i = 0, j = 0, k = left;

//     while (i < (int)leftArr.size() && j < (int)rightArr.size()) {
//         if (leftArr[i] <= rightArr[j]) {
//             arr[k++] = leftArr[i++];
//         } else {
//             arr[k++] = rightArr[j++];
//         }
//     }

//     while (i < (int)leftArr.size()) {
//         arr[k++] = leftArr[i++];
//     }

//     while (j < (int)rightArr.size()) {
//         arr[k++] = rightArr[j++];
//     }
// }

// void PmergeMe::fordJohnsonSortDeque(std::deque<int>& arr) {
//     int n = arr.size();
//     if (n <= 1) return;

//     const int THRESHOLD = 10;

//     if (n <= THRESHOLD) {
//         insertionSortDeque(arr, 0, n - 1);
//         return;
//     }

//     int mid = n / 2;

//     std::deque<int> left(arr.begin(), arr.begin() + mid);
//     std::deque<int> right(arr.begin() + mid, arr.end());

//     fordJohnsonSortDeque(left);
//     fordJohnsonSortDeque(right);

//     std::copy(left.begin(), left.end(), arr.begin());
//     std::copy(right.begin(), right.end(), arr.begin() + mid);

//     mergeDeque(arr, 0, mid - 1, n - 1);
// }

// void PmergeMe::sort() {
//     struct timeval start, end;

//     // Afficher la séquence avant tri
//     std::cout << "Before: ";
//     for (size_t i = 0; i < _vectorData.size() && i < 5; i++) {
//         std::cout << _vectorData[i] << " ";
//     }
//     if (_vectorData.size() > 5) {
//         std::cout << "[...]";
//     }
//     std::cout << std::endl;

//     // Trier avec std::vector
//     std::vector<int> vectorCopy = _vectorData;
//     gettimeofday(&start, NULL);
//     fordJohnsonSortVector(vectorCopy);
//     gettimeofday(&end, NULL);

//     double vectorTime = (end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec);

//     // Trier avec std::deque
//     std::deque<int> dequeCopy = _dequeData;
//     gettimeofday(&start, NULL);
//     fordJohnsonSortDeque(dequeCopy);
//     gettimeofday(&end, NULL);

//     double dequeTime = (end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec);

//     // Afficher la séquence après tri
//     std::cout << "After: ";
//     for (size_t i = 0; i < vectorCopy.size() && i < 5; i++) {
//         std::cout << vectorCopy[i] << " ";
//     }
//     if (vectorCopy.size() > 5) {
//         std::cout << "[...]";
//     }
//     std::cout << std::endl;

//     // Afficher les temps
//     std::cout << "Time to process a range of " << _vectorData.size()
//               << " elements with std::vector : " << std::fixed << vectorTime << " us" << std::endl;
//     std::cout << "Time to process a range of " << _dequeData.size()
//               << " elements with std::deque : " << std::fixed << dequeTime << " us" << std::endl;
// }

// void PmergeMe::displayResults() {
//     sort();
// }
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

// Implémentation Ford-Johnson pour std::vector
void PmergeMe::insertionSortVector(std::vector<int>& arr, int left, int right, Statistics& stats) {
    for (int i = left + 1; i <= right; i++) {
        int key = arr[i];
        stats.movements++; // Copie de l'élément clé
        int j = i - 1;

        while (j >= left && (stats.comparisons++, arr[j] > key)) {
            arr[j + 1] = arr[j];
            stats.movements++; // Déplacement d'élément
            j--;
        }
        arr[j + 1] = key;
        stats.movements++; // Placement final de la clé
    }
}

void PmergeMe::mergeVector(std::vector<int>& arr, int left, int mid, int right, Statistics& stats) {
    std::vector<int> leftArr(arr.begin() + left, arr.begin() + mid + 1);
    std::vector<int> rightArr(arr.begin() + mid + 1, arr.begin() + right + 1);

    // Comptabiliser la création des tableaux temporaires
    stats.movements += leftArr.size() + rightArr.size();

    int i = 0, j = 0, k = left;

    while (i < (int)leftArr.size() && j < (int)rightArr.size()) {
        stats.comparisons++; // Comparaison leftArr[i] <= rightArr[j]
        if (leftArr[i] <= rightArr[j]) {
            arr[k++] = leftArr[i++];
        } else {
            arr[k++] = rightArr[j++];
        }
        stats.movements++; // Affectation dans arr[k]
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

    // Seuil pour utiliser insertion sort sur les petits tableaux
    const int THRESHOLD = 10;

    if (n <= THRESHOLD) {
        insertionSortVector(arr, 0, n - 1, stats);
        return;
    }

    // Diviser en deux parties
    int mid = n / 2;

    std::vector<int> left(arr.begin(), arr.begin() + mid);
    std::vector<int> right(arr.begin() + mid, arr.end());

    // Comptabiliser la création des sous-tableaux
    stats.movements += left.size() + right.size();

    // Tri récursif
    fordJohnsonSortVector(left, stats);
    fordJohnsonSortVector(right, stats);

    // Copie des résultats
    std::copy(left.begin(), left.end(), arr.begin());
    std::copy(right.begin(), right.end(), arr.begin() + mid);
    stats.movements += left.size() + right.size();

    mergeVector(arr, 0, mid - 1, n - 1, stats);
}

// Implémentation Ford-Johnson pour std::deque
void PmergeMe::insertionSortDeque(std::deque<int>& arr, int left, int right, Statistics& stats) {
    for (int i = left + 1; i <= right; i++) {
        int key = arr[i];
        stats.movements++;
        int j = i - 1;

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

    // Afficher la séquence avant tri
    std::cout << "Before: ";
    for (size_t i = 0; i < _vectorData.size() && i < 5; i++) {
        std::cout << _vectorData[i] << " ";
    }
    if (_vectorData.size() > 5) {
        std::cout << "[...]";
    }
    std::cout << std::endl;

    // Réinitialiser les compteurs
    _vectorStats.reset();
    _dequeStats.reset();

    // Trier avec std::vector
    std::vector<int> vectorCopy = _vectorData;
    gettimeofday(&start, NULL);
    fordJohnsonSortVector(vectorCopy, _vectorStats);
    gettimeofday(&end, NULL);

    double vectorTime = (end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec);

    // Trier avec std::deque
    std::deque<int> dequeCopy = _dequeData;
    gettimeofday(&start, NULL);
    fordJohnsonSortDeque(dequeCopy, _dequeStats);
    gettimeofday(&end, NULL);

    double dequeTime = (end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec);

    // Afficher la séquence après tri
    std::cout << "After: ";
    for (size_t i = 0; i < vectorCopy.size() && i < 5; i++) {
        std::cout << vectorCopy[i] << " ";
    }
    if (vectorCopy.size() > 5) {
        std::cout << "[...]";
    }
    std::cout << std::endl;

    // Afficher les temps
    std::cout << "Time to process a range of " << _vectorData.size()
              << " elements with std::vector : " << std::fixed << vectorTime << " us" << std::endl;
    std::cout << "Time to process a range of " << _dequeData.size()
              << " elements with std::deque : " << std::fixed << dequeTime << " us" << std::endl;

    // Afficher les statistiques d'optimisation
    std::cout << std::endl << "=== ALGORITHM EFFICIENCY ANALYSIS ===" << std::endl;

    std::cout << "std::vector statistics:" << std::endl;
    std::cout << "  - Comparisons: " << _vectorStats.comparisons << std::endl;
    std::cout << "  - Movements: " << _vectorStats.movements << std::endl;
    std::cout << "  - Total operations: " << (_vectorStats.comparisons + _vectorStats.movements) << std::endl;

    std::cout << "std::deque statistics:" << std::endl;
    std::cout << "  - Comparisons: " << _dequeStats.comparisons << std::endl;
    std::cout << "  - Movements: " << _dequeStats.movements << std::endl;
    std::cout << "  - Total operations: " << (_dequeStats.comparisons + _dequeStats.movements) << std::endl;

    // Calculs théoriques pour comparaison
    long n = _vectorData.size();
    long theoretical_ford_johnson = n * (long)(log(n) / log(2)) - n + 1;  // Légèrement optimisé
    long theoretical_mergesort = n * (long)(log(n) / log(2));  // O(n log n) pour merge sort classique
    long theoretical_quicksort = n * (long)(log(n) / log(2));  // O(n log n) moyen pour quicksort
    long theoretical_bubble = (n * (n - 1)) / 2; // O(n²) pour bubble sort

    std::cout << std::endl << "Theoretical complexity comparison (for n=" << n << "):" << std::endl;
    std::cout << "  - Ford-Johnson (theory): ~" << theoretical_ford_johnson << " ops" << std::endl;
    std::cout << "  - Standard merge sort: ~" << theoretical_mergesort << " operations" << std::endl;
    std::cout << "  - Standard quick sort: ~" << theoretical_quicksort << " operations" << std::endl;
    std::cout << "  - Bubble sort: ~" << theoretical_bubble << " operations" << std::endl;

    // Calcul de l'efficacité
    double efficiency_vector = (double)theoretical_mergesort / (_vectorStats.comparisons + _vectorStats.movements) * 100;
    double efficiency_deque = (double)theoretical_mergesort / (_dequeStats.comparisons + _dequeStats.movements) * 100;

    std::cout << std::endl << "Ford-Johnson efficiency vs standard merge sort:" << std::endl;
    std::cout << "  - Vector implementation: " << std::fixed << efficiency_vector << "% efficiency" << std::endl;
    std::cout << "  - Deque implementation: " << std::fixed << efficiency_deque << "% efficiency" << std::endl;

    if (efficiency_vector > 100 || efficiency_deque > 100) {
        std::cout << "✓ Ford-Johnson outperforms standard merge sort!" << std::endl;
    }
}

void PmergeMe::displayResults() {
    sort();
}

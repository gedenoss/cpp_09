#include "BitcoinExchange.hpp"
#include <climits>
#include <iostream>
#include <cstdlib>
#include <fstream>


BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : _database(other._database) {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
    if (this != &other) {
        _database = other._database;
    }
    return *this;
}

std::string BitcoinExchange::trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

bool BitcoinExchange::isValidDate(const std::string& date) {
    if (date.length() != 10 || date[4] != '-' || date[7] != '-')
        return false;

    // Vérifier que tous les caractères sont des chiffres sauf les tirets
    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue;
        if (!isdigit(date[i])) return false;
    }

    int year = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day = std::atoi(date.substr(8, 2).c_str());

    if (year < 2009 || year > 2024) return false;
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;

    return true;
}

bool BitcoinExchange::isValidValue(double value) {
    return value >= 0 && value <= 1000;
}

bool BitcoinExchange::loadDatabase(const std::string& filename) {
    std::ifstream file(filename.c_str());
    if (!file.is_open()) return false;

    std::string line;
    std::getline(file, line); // Skip header

    while (std::getline(file, line)) {
        size_t pos = line.find(',');
        if (pos == std::string::npos) continue;

        std::string date = trim(line.substr(0, pos));
        std::string rateStr = trim(line.substr(pos + 1));

        if (isValidDate(date)) {
            double rate = std::atof(rateStr.c_str());
            _database[date] = rate;
        }
    }

    file.close();
    return !_database.empty();
}

bool BitcoinExchange::init(const std::string& databaseFile) {
    return loadDatabase(databaseFile);
}

double BitcoinExchange::getRate(const std::string& date) {
    // Utilise lower_bound pour trouver la première date >= à celle recherchée
    std::map<std::string, double>::iterator it = _database.lower_bound(date);

    // Si on trouve exactement la date
    if (it != _database.end() && it->first == date) {
        return it->second;
    }

    // Sinon, on prend la date précédente
    if (it != _database.begin()) {
        --it;
        return it->second;
    }

    // Aucune date antérieure trouvée
    return -1;
}

void BitcoinExchange::processFile(const std::string& inputFile) {
    std::ifstream file(inputFile.c_str());
    if (!file.is_open()) {
        std::cerr << "Error: could not open file." << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line); // Skip header

    while (std::getline(file, line)) {
        size_t pos = line.find(" | ");
        if (pos == std::string::npos) {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }

        std::string date = trim(line.substr(0, pos));
        std::string valueStr = trim(line.substr(pos + 3));

        if (!isValidDate(date)) {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }

        double value = std::atof(valueStr.c_str());

        if (value < 0) {
            std::cerr << "Error: not a positive number." << std::endl;
            continue;
        }

        if (value > 1000) {
            std::cerr << "Error: too large a number." << std::endl;
            continue;
        }

        double rate = getRate(date);
        if (rate == -1) {
            std::cerr << "Error: no data available for this date." << std::endl;
            continue;
        }

        std::cout << date << " => " << value << " = " << (value * rate) << std::endl;
    }

    file.close();
}

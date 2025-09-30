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

    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue;
        if (!isdigit(date[i])) return false;
    }

    int month = std::atoi(date.substr(5, 2).c_str());
    int day = std::atoi(date.substr(8, 2).c_str());

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
    std::getline(file, line);

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
    std::map<std::string, double>::iterator it = _database.lower_bound(date);

    if (it != _database.end() && it->first == date) {
        return it->second;
    }

    if (it != _database.begin()) {
        --it;
        return it->second;
    }

    return it->second;
}

void BitcoinExchange::processFile(const std::string& inputFile) {
    std::ifstream file(inputFile.c_str());
    if (!file.is_open()) {
        std::cerr << "Error: could not open file." << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line);

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
        bool validNumber = !valueStr.empty();
        for (size_t i = 0; i < valueStr.size(); ++i) {
            if (std::isalpha(static_cast<unsigned char>(valueStr[i]))) {
                validNumber = false;
                break;
            }
        }
        if (!validNumber) {
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

        std::cout << date << " => " << value << " = " << (value * rate) << std::endl;
    }

    file.close();
}

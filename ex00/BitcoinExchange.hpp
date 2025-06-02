#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>

class BitcoinExchange {
private:
    std::map<std::string, double> _database;

    bool isValidDate(const std::string& date);
    bool isValidValue(double value);
    std::string trim(const std::string& str);
    bool loadDatabase(const std::string& filename);

public:
    BitcoinExchange();
    ~BitcoinExchange();
    BitcoinExchange(const BitcoinExchange& other);
    BitcoinExchange& operator=(const BitcoinExchange& other);

    bool init(const std::string& databaseFile);
    void processFile(const std::string& inputFile);
    double getRate(const std::string& date);
};

#endif

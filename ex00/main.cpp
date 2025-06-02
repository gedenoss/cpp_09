#include "BitcoinExchange.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Error: could not open file." << std::endl;
        return 1;
    }

    BitcoinExchange exchange;

    // Charger la base de données (supposée être data.csv dans le même répertoire)
    if (!exchange.init("data.csv")) {
        std::cerr << "Error: could not load database." << std::endl;
        return 1;
    }

    exchange.processFile(argv[1]);

    return 0;
}

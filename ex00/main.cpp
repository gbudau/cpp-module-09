#include "BitcoinExchange.hpp"
#include <iostream>

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cout << "Error: could not open file.\n";
    return 1;
  }
  try {
    BitcoinExchange bitcoin_exchange;
    bitcoin_exchange.Exchange(argv[1]);
  } catch (const std::exception &e) {
    std::cout << e.what() << "\n";
    return 1;
  }
  return 0;
}

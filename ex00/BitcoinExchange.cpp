#include "BitcoinExchange.hpp"
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <time.h>

BitcoinExchange::BitcoinExchange(const std::string &database_path) {
  std::ifstream file_stream(database_path.c_str());
  if (!file_stream) {
    throw std::runtime_error("Error: could not open file.");
  }

  std::string line;
  std::getline(file_stream, line);
  if (line != "date,exchange_rate") {
    throw std::runtime_error("Error: invalid data file.");
  }

  while (std::getline(file_stream, line)) {
    DataRowPair row_pair = ParseDataRow_(line);
    if (row_pair.second < 0) {
      throw std::runtime_error("Error: invalid data file.");
    }
    database_[row_pair.first] = row_pair.second;
  }
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &src) {
  database_ = src.GetDatabase();
}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &rhs) {
  if (this != &rhs) {
    database_ = rhs.GetDatabase();
  }
  return *this;
}

void BitcoinExchange::Exchange(std::string input_path) const {
  std::ifstream file_stream(input_path.c_str());
  if (!file_stream) {
    throw std::runtime_error("Error: could not open file.");
  }

  std::string line;
  size_t i = 0;

  while (std::getline(file_stream, line)) {
    if (i == 0 && line == "date | value") {
      // No op when the first line is "date | value"
    } else {
      ParseInputRow_(line);
    }
    i++;
  }
}

BitcoinExchange::Database BitcoinExchange::GetDatabase() const {
  return database_;
}

BitcoinExchange::DataRowPair
BitcoinExchange::ParseDataRow_(const std::string &line) const {
  std::time_t date;
  float exchange_rate;

  const size_t date_end = line.find(',');
  if (date_end == std::string::npos) {
    throw std::runtime_error("Error: invalid data file.");
  }
  try {
    date = DateToSecondsSinceEpoch_(line.substr(0, date_end));
    exchange_rate = ParseFloat_(line.substr(date_end + 1));
  } catch (const std::exception &) {
    throw std::runtime_error("Error: invalid data file.");
  }
  return std::make_pair(date, exchange_rate);
}

void BitcoinExchange::ParseInputRow_(const std::string &line) const {
  const std::string delimiter = " | ";
  std::time_t date;
  float bitcoins;
  std::string date_str;

  const size_t date_end = line.find(delimiter);

  if (date_end == std::string::npos) {
    std::cout << "Error: bad input => " << line << '\n';
    return;
  }
  try {
    date_str = line.substr(0, date_end);
    date = DateToSecondsSinceEpoch_(date_str);
    bitcoins = ParseFloat_(line.substr(date_end + delimiter.size()));
  } catch (const std::exception &) {
    std::cout << "Error: bad input => " << line << '\n';
    return;
  }
  if (bitcoins <= 0) {
    std::cout << "Error: not a positive number.\n";
    return;
  }
  if (bitcoins >= 1000) {
    std::cout << "Error: too large a number.\n";
    return;
  }
  const float result = bitcoins * GetExchangeRate_(date);
  std::cout << date_str << " => " << bitcoins << " = " << result << '\n';
}

std::time_t
BitcoinExchange::DateToSecondsSinceEpoch_(const std::string &date) const {
  struct tm time;
  std::memset(&time, 0, sizeof(struct tm));
  const char *ret = strptime(date.c_str(), "%Y-%m-%d", &time);
  if (ret == NULL || *ret != '\0') {
    throw std::runtime_error("Error: invalid date.");
  }
  return mktime(&time);
}

float BitcoinExchange::ParseFloat_(const std::string &str) const {
  float f;
  std::stringstream date_stream(str);
  date_stream >> f;
  if (!date_stream.eof() || date_stream.fail()) {
    throw std::runtime_error("Error: invalid string.");
  }
  return f;
}

float BitcoinExchange::GetExchangeRate_(const std::time_t &date) const {
  BitcoinExchange::Database::const_iterator it = database_.lower_bound(date);
  return it != database_.end() ? it->second : 0;
}

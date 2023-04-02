#ifndef BITCOIN_EXCHANGE_HPP_
#define BITCOIN_EXCHANGE_HPP_

#ifndef DATASET
#define DATASET "data.csv"

#include <ctime>
#include <functional>
#include <map>
#include <string>
#include <utility>

class BitcoinExchange {
private:
  typedef std::map<std::time_t, float, std::greater<std::time_t>> Database;
  typedef std::pair<std::time_t, float> DataRowPair;
  Database database_;
  DataRowPair ParseDataRow_(const std::string &line) const;
  void ParseInputRow_(const std::string &line) const;
  std::time_t DateToSecondsSinceEpoch_(const std::string &date) const;
  float ParseFloat_(const std::string &str) const;
  float GetExchangeRate_(const std::time_t &date) const;

public:
  explicit BitcoinExchange(const std::string &database_path = DATASET);
  BitcoinExchange(BitcoinExchange const &src);
  ~BitcoinExchange();
  BitcoinExchange &operator=(BitcoinExchange const &rhs);
  void Exchange(std::string input_path) const;
  Database GetDatabase() const;
};

#endif // DATASET
#endif // BITCOIN_EXCHANGE_HPP_

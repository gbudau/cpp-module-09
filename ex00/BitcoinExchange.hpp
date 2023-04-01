#ifndef BITCOIN_EXCHANGE_HPP_
#define BITCOIN_EXCHANGE_HPP_

#ifndef DATASET
#define DATASET "data.csv"

#include <ctime>
#include <map>
#include <string>

class BitcoinExchange {
private:
  typedef std::time_t DateSecondsSinceEpoch;
  typedef float BitcoinPrice;
  typedef std::map<DateSecondsSinceEpoch, BitcoinPrice> Database;
  typedef std::pair<DateSecondsSinceEpoch, BitcoinPrice> DataRowPair;
  Database database_;
  DataRowPair ParseDataRow_(const std::string &line) const;
  void ParseInputRow_(const std::string &line) const;
  std::time_t DateToSecondsSinceEpoch_(const std::string &date) const;
  float ParseFloat_(const std::string &str) const;
  float GetExchangeRate_(const std::time_t &date) const;

public:
  BitcoinExchange(const std::string &database_path = DATASET);
  BitcoinExchange(BitcoinExchange const &src);
  ~BitcoinExchange();
  BitcoinExchange &operator=(BitcoinExchange const &rhs);
  void Exchange(std::string input_path) const;
  Database GetDatabase() const;
};

#endif // DATASET
#endif // BITCOIN_EXCHANGE_HPP_

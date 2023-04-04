#ifndef RPN_HPP_
#define RPN_HPP_

#include <stack>
#include <string>
#include <utility>

class RPN {
private:
  typedef std::pair<double, double> NumbersPair;
  int ParseNumber_(const std::string &token) const;
  NumbersPair GetNumbers_(std::stack<double> *s) const;

public:
  RPN();
  RPN(RPN const &src);
  ~RPN();
  RPN &operator=(RPN const &rhs);
  double CalculateExpression(const std::string &expression) const;
};

#endif // RPN_HPP_

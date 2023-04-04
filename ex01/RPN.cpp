#include "RPN.hpp"
#include <sstream>
#include <stdexcept>

RPN::RPN() {}

RPN::RPN(RPN const &) {}

RPN::~RPN() {}

RPN &RPN::operator=(RPN const &) { return *this; }

double RPN::CalculateExpression(const std::string &expression) const {
  std::stack<double> stack;
  std::stringstream stream(expression);
  std::string token;

  while (std::getline(stream, token, ' ')) {
    if (token == "+") {
      const NumbersPair pair = GetNumbers_(&stack);
      const double n = pair.second + pair.first;
      stack.push(n);
    } else if (token == "-") {
      const NumbersPair pair = GetNumbers_(&stack);
      const double n = pair.second - pair.first;
      stack.push(n);
    } else if (token == "*") {
      const NumbersPair pair = GetNumbers_(&stack);
      const double n = pair.second * pair.first;
      stack.push(n);
    } else if (token == "/") {
      const NumbersPair pair = GetNumbers_(&stack);
      if (pair.first == 0) {
        throw std::runtime_error("Error: division by zero");
      }
      const double n = pair.second / pair.first;
      stack.push(n);
    } else if (token != "") {
      const double n = ParseNumber_(token);
      if (n >= 10) {
        throw std::runtime_error("Error: Numbers must be less than 10");
      }
      stack.push(n);
    }
  }
  if (stack.size() != 1) {
    throw std::runtime_error("Error: Invalid expression");
  }
  return stack.top();
}

int RPN::ParseNumber_(const std::string &token) const {
  int n;
  std::stringstream stream(token);
  stream >> n;
  if (!stream.eof() || stream.fail()) {
    throw std::runtime_error("Error: invalid string.");
  }
  return n;
}

RPN::NumbersPair RPN::GetNumbers_(std::stack<double> *s) const {
  if (s->size() < 2) {
    throw std::runtime_error("Error: invalid expression");
  }
  const double a = s->top();
  s->pop();
  const double b = s->top();
  s->pop();
  return std::make_pair(a, b);
}

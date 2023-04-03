#include "RPN.hpp"
#include <iostream>

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cout << "Error\n";
    return 1;
  }
  try {
    RPN rpn;
    std::cout << rpn.CalculateExpression(argv[1]) << '\n';
  } catch (const std::exception &) {
    std::cout << "Error\n";
    return 1;
  }
  return 0;
}

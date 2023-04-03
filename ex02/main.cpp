#include "PmergeMe.hpp"
#include <iostream>

int main(int argc, char **argv) {
  try {
    PmergeMe pmerge_me;
    pmerge_me.SortArgs(&argv[1], argc - 1);
  } catch (const std::exception &) {
    std::cout << "Error\n";
    return 1;
  }
  return 0;
}

#include "PmergeMe.hpp"
#include <deque>
#include <iostream>
#include <stdexcept>
#include <vector>

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(PmergeMe const &) {}

PmergeMe::~PmergeMe() {}

PmergeMe &PmergeMe::operator=(PmergeMe const &) { return *this; }

void PmergeMe::SortArgs(char **const &argv, const int &argc) const {
  std::vector<int> args;

  for (int i = 0; i < argc; i++) {
    const int n = ParseNumber_(argv[i]);
    if (n <= 0) {
      throw std::runtime_error("Error: argument must be a positive integer");
    }
    args.push_back(n);
  }

  std::vector<int> v(args.begin(), args.end());
  std::deque<int> d(args.begin(), args.end());

  const long double time_elapsed_vector = MergeInsertSort(v);
  const long double time_elapsed_deque = MergeInsertSort(d);

  std::cout << "Before: " << ContainerItems(args) << '\n';
  std::cout << "After:  " << ContainerItems(v) << '\n';
  DisplayExecutionTime("std::vector", v.size(), time_elapsed_vector);
  DisplayExecutionTime("std::deque", d.size(), time_elapsed_deque);

  CheckEqual(args, v, d);
}

int PmergeMe::ParseNumber_(const std::string &token) const {
  int n;
  std::stringstream stream(token);
  stream >> n;
  if (!stream.eof() || stream.fail()) {
    throw std::runtime_error("Error: invalid string.");
  }
  return n;
}

void PmergeMe::DisplayExecutionTime(const std::string &container_name,
                                    const size_t container_size,
                                    const long double time_elapsed_usec) const {
  std::cout << "Time to process a range of " << container_size
            << " elements with " << container_name << " : " << time_elapsed_usec
            << " usec\n";
}

#ifndef PMERGE_ME_HPP_
#define PMERGE_ME_HPP_

#include "algorithm.hpp"
#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <sys/time.h>
#include <vector>

class PmergeMe {
private:
  int ParseNumber_(const std::string &token) const;
  template <class Container>
  std::string ContainerItems(const Container &c) const;
  template <class Container> long double MergeInsertSort(Container &c) const;
  void DisplayExecutionTime(const std::string &container_name,
                            const size_t container_size,
                            const long double time_elapsed_usec) const;
  template <class ContArgs, class Cont1, class Cont2>
  void CheckEqual(const ContArgs &args, const Cont1 &c1, const Cont2 &c2) const;

public:
  PmergeMe();
  PmergeMe(PmergeMe const &src);
  ~PmergeMe();
  PmergeMe &operator=(PmergeMe const &rhs);
  void SortArgs(char **const &args, const int &argc) const;
};

template <class Container>
inline std::string PmergeMe::ContainerItems(const Container &c) const {
  std::stringstream s;
  for (size_t i = 0; i < c.size(); ++i) {
    s << c[i];
    if (i < c.size() - 1) {
      s << ' ';
    }
  }
  return s.str();
}

template <class Container>
inline long double PmergeMe::MergeInsertSort(Container &c) const {
  timespec start_time, end_time;

  clock_gettime(CLOCK_MONOTONIC, &start_time);
  merge_insert_sort(c.begin(), c.end());
  clock_gettime(CLOCK_MONOTONIC, &end_time);

  //  Return execution time in microseconds
  return (end_time.tv_sec * 1e9L + end_time.tv_nsec -
          (start_time.tv_sec * 1e9L + start_time.tv_nsec)) /
         1000;
}

template <class ContArgs, class Cont1, class Cont2>
inline void PmergeMe::CheckEqual(const ContArgs &args, const Cont1 &c1,
                                 const Cont2 &c2) const {
  //  Assert the sorting algorithm works by comparing it with std::sort
  std::vector<int> sorted_args(args.begin(), args.end());
  std::sort(sorted_args.begin(), sorted_args.end());

  if (!std::equal(sorted_args.begin(), sorted_args.end(), c1.begin())) {
    assert(false);
  }
  if (!std::equal(sorted_args.begin(), sorted_args.end(), c2.begin())) {
    assert(false);
  }
}

#endif // PMERGE_ME_HPP_

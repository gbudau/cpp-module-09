#ifndef ALGORITHM_HPP_
#define ALGORITHM_HPP_

#include <algorithm>
#include <iterator>

const std::ptrdiff_t INSERTION_SORT_THRESHOLD = 10;

template <class RandIt> void insertion_sort(RandIt begin, RandIt end) {
  for (RandIt i = begin; i != end; ++i) {
    typename std::iterator_traits<RandIt>::value_type key = *i;
    RandIt j = i;

    while (j != begin && *(j - 1) > key) {
      *j = *(j - 1);
      --j;
    }
    *j = key;
  }
}

template <class RandIt> void merge_insert_sort(RandIt begin, RandIt end) {
  typename std::iterator_traits<RandIt>::difference_type length = end - begin;

  if (length < 2) {
    return;
  }

  if (length <= INSERTION_SORT_THRESHOLD) {
    insertion_sort(begin, end);
  } else {
    RandIt middle = begin + length / 2;

    merge_insert_sort(begin, middle);
    merge_insert_sort(middle, end);

    std::inplace_merge(begin, middle, end);
  }
}

#endif // ALGORITHM_HPP_

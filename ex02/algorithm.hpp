#ifndef ALGORITHM_HPP_
#define ALGORITHM_HPP_

#include <algorithm>
#include <iterator>

const std::ptrdiff_t INSERTION_SORT_THRESHOLD = 10;

template <class RanIt> void insertion_sort(RanIt begin, RanIt end) {
  for (RanIt i = begin; i != end; ++i) {
    typename std::iterator_traits<RanIt>::value_type key = *i;
    RanIt j = i;

    while (j != begin && *(j - 1) > key) {
      *j = *(j - 1);
      --j;
    }
    *j = key;
  }
}

template <class RanIt> void merge_insert_sort(RanIt begin, RanIt end) {
  typename std::iterator_traits<RanIt>::difference_type length = end - begin;

  if (length < 2) {
    return;
  }

  if (length <= INSERTION_SORT_THRESHOLD) {
    insertion_sort(begin, end);
  } else {
    RanIt middle = begin + length / 2;

    merge_insert_sort(begin, middle);
    merge_insert_sort(middle, end);

    std::inplace_merge(begin, middle, end);
  }
}

#endif // ALGORITHM_HPP_

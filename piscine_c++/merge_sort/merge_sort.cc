#include "merge_sort.hh"

#include <algorithm>

void merge_sort(iterator_type begin, iterator_type end)
{
    if (std::ranges::distance(begin, end) == 1)
        return;
    merge_sort(begin, begin + std::ranges::distance(begin, end) / 2);
    merge_sort(begin + (std::ranges::distance(begin, end) / 2), end);
    std::inplace_merge(begin, begin + (std::ranges::distance(begin, end) / 2),
                       end);
}

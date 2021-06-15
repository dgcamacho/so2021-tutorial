#pragma once

#include <tuple>
#include <vector>

// binary search through indices [start, stop] of an ordered std::vector<>
// return the index i such that vec[i] <= value < vec[i+1]
// REQUIRES vec to contain only unique entries of a LessThanComparable type and to be ordered
// RETURNS std::tuple<index where the element is/should be, element_found_flag>
template <typename size_type, typename value_type>

std::tuple<value_type, bool> binary_search(std::vector<value_type> vec, size_type start, size_type stop, value_type value) {
    // while the remaining block to search in is nonempty
    while (start <= stop)
    {
        // calculate pivot index
        int middle = start + ((stop - start) / 2);

        // check for direct match
        if (vec[middle] == value){
            return {middle, true};
        }
        else {
            // set searchblock to left or right half as neccessary
            if (value < vec[middle]){
                stop = middle - 1;
            }
            else {
                start = middle + 1;
            }
        }
    }
    // element not found
    return {start, false};
}
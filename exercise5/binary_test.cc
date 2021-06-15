#pragma once

#include <vector>
#include <cassert>

#include "BinarySearch.cc"

// test only
void binary_search_tests() {
    std::tuple<int, bool> bs_return;
    
    std::vector<int> v1{1, 3, 4, 6, 7, 8};
    bs_return = binary_search(v1, 0, 5, 5);
    assert(std::get<1>(bs_return) == false);
    assert(std::get<0>(bs_return) == 3);

    bs_return = binary_search(v1, 0, 5, 3);
    assert(std::get<1>(bs_return) == true);
    assert(std::get<0>(bs_return) == 1);

    bs_return = binary_search(v1, 2, 5, 3);
    assert(std::get<1>(bs_return) == false);
    assert(std::get<0>(bs_return) == 2);

    bs_return = binary_search(v1, 0, -1, 3);
    assert(std::get<1>(bs_return) == false);
    assert(std::get<0>(bs_return) == 0);

    bs_return = binary_search(v1, 1, 4, 8);
    assert(std::get<1>(bs_return) == false);
    assert(std::get<0>(bs_return) == 5);

    std::vector<int> v2{0, 0, 0, 0, 0};
    bs_return = binary_search(v2, 0, -1, 0);
    assert(std::get<1>(bs_return) == false);
}
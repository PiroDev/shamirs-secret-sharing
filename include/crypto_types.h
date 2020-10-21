#pragma once

#include <boost/multiprecision/cpp_int.hpp>
using boost::multiprecision::int256_t;
using boost::multiprecision::uint256_t;

#include <boost/multiprecision/cpp_bin_float.hpp>
using boost::multiprecision::pow;
using float328_t = boost::multiprecision::number<
    boost::multiprecision::backends::cpp_bin_float<264, boost::multiprecision::backends::digit_base_2, void,
                                                   long long int>,
    boost::multiprecision::et_off>;

#include <utility>
using std::pair;

typedef pair<int16_t, int256_t> share_t;

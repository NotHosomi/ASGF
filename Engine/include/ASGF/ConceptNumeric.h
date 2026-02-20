#pragma once
#include <type_traits>

template<typename Numeric_t>
concept NumericType = std::is_arithmetic_v<Numeric_t>;
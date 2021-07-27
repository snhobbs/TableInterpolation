/*
 * Copyright 2020 Electrooptical Innovations
 * main.cpp

 *
 *      Author: simon
 */

#include <gtest/gtest.h>
#include <cstdint>
#include <array>
#include <iostream>
#include <vector>
#include <tuple>
#include "TableInterpolation/LinearInterpolator.h"
#include "cnl/fixed_point.h"


static const constexpr std::array<std::tuple<double, double, double>, 7> table {{
  {3, 300, 100},
  {4, 400, 100},
  {5, 500, 100},
  {7, 700, 100},
  {8, 800, 100},
  {9, 900, 100},
  {10, 1000, 100},
}};

TEST(LinearInterpolator, Interpolate_InterpolatePoint) {
  const auto value = LinearInterpolator::Interpolate<double>(table.data(), table.size(), 6);
  EXPECT_NEAR(600, value, 1e-8);
}

TEST(LinearInterpolator, Interpolate_InterpolatePoint_ExtapolateLow) {
  const auto value = LinearInterpolator::Interpolate<double>(table.data(), table.size(), 1);
  EXPECT_NEAR(100, value, 1e-8);
}
TEST(LinearInterpolator, Interpolate_InterpolatePoint_ExtapolateHigh) {
  const auto value = LinearInterpolator::Interpolate<double>(table.data(), table.size(), 12);
  EXPECT_NEAR(1200, value, 1e-8);
}

//  FIXME add reverse interpolate tests

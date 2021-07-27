#pragma once
/*
 * Expect an array of tuples with the input key, value at that point, and slope
 * */
#include <cassert>
#include <tuple>
#include <numeric>
#include <cmath>
#include <utility>


namespace LinearInterpolator {
static constexpr size_t SourceValueTuplePos = 0;
static constexpr size_t OutputValueTuplePos = 1;
static constexpr size_t SlopeValueTuplePos = 2;

template<typename calc_t, size_t kIndex>
constexpr size_t find_closest_point(const std::tuple<calc_t, calc_t, calc_t>* table, const size_t table_size, const calc_t point) {
  calc_t min_error = std::numeric_limits<calc_t>::max();
  size_t min_error_index = 0;
  // Cycle through all the points, minimize the error
  for (size_t i=0; i<table_size; i++) {
    calc_t error = point - std::get<kIndex>(table[i]);
    error = error < 0 ? -error : error;
    if (error < min_error) {
      min_error = error;
      min_error_index = i;
    }
  }
  return min_error_index;
}

template<typename calc_t, size_t kIndex>
constexpr std::pair<size_t, size_t> find_boundry_points(const std::tuple<calc_t, calc_t, calc_t>* table, const size_t table_size, const calc_t point) {
  const auto min_error_index = find_closest_point<calc_t, kIndex>(table, table_size, point);
  if (min_error_index == 0) {
    return {0, 1};
  } else {
    const std::pair<size_t, size_t> limits = { min_error_index-1, min_error_index };
    return limits;
  }
}

/*
 * Takes a point of source type and outputs output scaling
 * */
template<typename calc_t>
constexpr calc_t Interpolate(const std::tuple<calc_t, calc_t, calc_t>* table, const size_t table_size, const calc_t reading) {
  //assert(reading <= kInputMax);
  const auto boundry_points = find_boundry_points<calc_t, SourceValueTuplePos>(table, table_size, reading);
  const auto& lastp = table[boundry_points.second];
  const auto& nextp = table[boundry_points.first];
  //  Condition of passing through all gain points

  //assert(reading_calc_t >= std::get<ADCValueTuplePos>(lastp));
  //assert(reading_calc_t <= std::get<ADCValueTuplePos>(nextp)); //  remove extrapolation

  calc_t value = 0;
#if 0
  //  Check if reading identically equal to either the points on the ends
  if (reading_calc_t == std::get<OutputValueTuplePos>(lastp)) {
    value = std::get<SourceValueTuplePos>(lastp);
  } else if (reading_calc_t == std::get<OutputValueTuplePos>(nextp)) {
    value = std::get<SourceValueTuplePos>(nextp);
  } else if (boundry_points.first == boundry_points.second) {
  }else {
#endif
    //  Linearly interpolate the value
    const calc_t deltax = (reading - std::get<SourceValueTuplePos>(lastp));
    const calc_t slope = std::get<SlopeValueTuplePos>(lastp);
    //assert(deltax < kAdcMax);//rollover error

    //  linear interpolation
    value = (std::get<OutputValueTuplePos>(lastp) + (slope*deltax));
  //}

  return value;
}

/*
 * Do the opposite of interpolate. Have a list of input, output, slope to output. Take output, return input.
 * */

template<typename calc_t>
constexpr calc_t reverse_interpolate(const std::tuple<calc_t, calc_t, calc_t>* table, const size_t table_size, const calc_t reading) {
  const auto boundry_points = find_boundry_points<calc_t, OutputValueTuplePos>(table, table_size, reading);
  const auto& lastp = table[boundry_points.second];
  const auto& nextp = table[boundry_points.first];
  //  Linearly interpolate the value
  const calc_t deltax = (reading - std::get<OutputValueTuplePos>(lastp));
  const calc_t slope = calc_t{1}/std::get<SlopeValueTuplePos>(lastp);
    //assert(deltax < kAdcMax);//rollover error

    //  linear interpolation
  const calc_t value = (std::get<SourceValueTuplePos>(lastp) + (slope*deltax));
  return value;
}
}

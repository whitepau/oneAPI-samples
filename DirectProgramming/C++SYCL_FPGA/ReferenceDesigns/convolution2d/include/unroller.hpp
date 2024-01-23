//  Copyright (c) 2021 Intel Corporation
//  SPDX-License-Identifier: MIT

// unroller.hpp

#ifndef __UNROLLER_HPP__
#define __UNROLLER_HPP__

#include <type_traits>
#include <utility>

namespace hldutils {

//
// The code below creates the constexprs make_integer_range 
// and make_index_range these are akin to std::make_integer_sequence
// and std::make_index_sequence, respectively.
// However they allow you to specificy a range and can either increment
// or decrement, rather than a strict increasing sequence
//
template<typename T, typename, T Begin, bool Increase>
struct integer_range_impl;

// incrementing case
template<typename T, T... N, T Begin>
struct integer_range_impl<T, std::integer_sequence<T, N...>, Begin, true> {
  using type = std::integer_sequence<T, N+Begin...>;
};

// decrementing case
template<typename T, T... N, T Begin>
struct integer_range_impl<T, std::integer_sequence<T, N...>, Begin, false> {
  using type = std::integer_sequence<T, Begin-N...>;
};

// integer_range
template<typename T, T Begin, T End>
using integer_range = typename integer_range_impl<
  T,
  std::make_integer_sequence<T, (Begin<End) ? End-Begin : Begin-End>,
  Begin,
  (Begin<End) >::type;

//
// make_integer_range
//
// USAGE:
//    make_integer_range<int,1,10>{} ==> 1,2,...,9
//    make_integer_range<int,10,1>{} ==> 10,9,...,2
//    
template<class T, T Begin, T End>
using make_integer_range = integer_range<T, Begin, End>;

//
// make_index_range
//
// USAGE:
//    make_index_range<1,10>{} ==> 1,2,...,9
//    make_index_range<10,1>{} ==> 10,9,...,2
//  
template<std::size_t Begin, std::size_t End>
using make_index_range = integer_range<std::size_t, Begin, End>;


//
// The code below creates the constexprs make_integer_pow2_sequence
// and make_index_pow2_sequence. These generate the sequence
// 2^0, 2^1, 2^2, ... , 2^(N-1) = 1,2,4,...,2^(N-1)
//
template<typename T, typename>
struct integer_pow2_sequence_impl;

template<typename T, T... Pows>
struct integer_pow2_sequence_impl<T,std::integer_sequence<T,Pows...>> {
  using type = std::integer_sequence<T, (T(1) << Pows)...>;
};

// integer_pow2_sequence
template<typename T, T N>
using integer_pow2_sequence = typename integer_pow2_sequence_impl<
  T,
  std::make_integer_sequence<T,N> >::type;

//
// make_integer_pow2_sequence
//
// USAGE:
//    make_integer_pow2_sequence<int,5>{} ==> 1,2,4,8,16
//
template<class T, T N>
using make_integer_pow2_sequence = integer_pow2_sequence<T, N>;

//
// make_index_pow2_sequence
//
// USAGE:
//    make_index_pow2_sequence<5>{} ==> 1,2,4,8,16
//
template<std::size_t N>
using make_index_pow2_sequence = integer_pow2_sequence<std::size_t, N>;


///////////////////////////////////////////////////////////////////////////////
//
// Example usage for UnrolledLoop constexpr:
//
// Base
//    UnrolledLoop(std::integer_sequence<int,5,2,7,8>{},
//                [&](auto i) { /*i = 5,2,7,8*/ });
//
// Case A
//    hldutils::UnrolledLoop<10>([&](auto i) { /*i = 0,1,...,9*/ });
//
// Case B
//    hldutils::UnrolledLoop<10>([&](auto i) { /*i = 0,1,...,9*/ });
//
// Case C
//    hldutils::UnrolledLoop<char, 1, 10>([&](auto i) { /* i = 1,2,...,9*/ });
//    hldutils::UnrolledLoop<char, 10, 1>([&](auto i) { /* i = 10,9,...,2*/ });
//
// Case D
//    hldutils::UnrolledLoop<1, 10>([&](auto i) { /* i = 1,2,...,9*/ });
//    hldutils::UnrolledLoop<10, 1>([&](auto i) { /* i = 10,9,...,2*/ });
//
///////////////////////////////////////////////////////////////////////////////

//
// Base implementation
// Templated on:
//    ItType    - the type of the iterator (size_t, int, char, ...)
//    ItType... - the indices to iterate on
//    F         - the function to run for each index (i.e. the lamda)
//
template<class ItType, ItType... inds, class F>
constexpr void UnrolledLoop(std::integer_sequence<ItType, inds...>, F&& f) {
  (f(std::integral_constant<ItType, inds>{}), ...);
}

//
// Convience implementation (A)
// performs UnrolledLoop in range [0,n) with iterator of type ItType
//
template<class ItType, ItType n, class F>
constexpr void UnrolledLoop(F&& f) {
  UnrolledLoop(std::make_integer_sequence<ItType, n>{}, std::forward<F>(f));
}

//
// Convenience implementation (B)
// performs UnrolledLoop in range [0,n) with an iterator of type std::size_t
//
template<std::size_t n, class F>
constexpr void UnrolledLoop(F&& f) {
  UnrolledLoop(std::make_index_sequence<n>{}, std::forward<F>(f));
}

//
// Convenience implementation (C)
// performs UnrolledLoop from start...end with an iterator of type ItType
// NOTE:  start is INCLUSIVE, end is EXCLUSIVE
// NOTE:  if start<=end, sequence is start,start+1,...,end-1
//        if end<=start, sequence is start,start-1,...,end+1
//
template<class ItType, ItType start, ItType end, class F>
constexpr void UnrolledLoop(F&& f) {
  UnrolledLoop(make_integer_range<ItType, start, end>{}, std::forward<F>(f));
}

//
// Convenience implementation (C)
// performs UnrolledLoop from start...end with an iterator of type size_t
// NOTE:  start is INCLUSIVE, end is EXCLUSIVE
// NOTE:  if start<=end, sequence is start,start+1,...,end-1
//        if end<=start, sequence is start,start-1,...,end+1
//
template<std::size_t start, std::size_t end, class F>
constexpr void UnrolledLoop(F&& f) {
  UnrolledLoop(make_index_range<start, end>{}, std::forward<F>(f));
}

}  // namespace hldutil

#endif /* __UNROLLER_HPP__ */
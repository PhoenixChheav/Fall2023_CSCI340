/**********************************************************************************************
 * NIU CSCI 340 Section 0003                                                                  *
 * Assignment 2b                                                                              *
 * Phoenix Chheav - Z1966108 - phoenixchh                                                     *
 *                                                                                            *
 *   I certify that everything I am submitting is either provided by the professor for use in *
 * the assignment, or work done by me personally. I understand that if I am caught submitting *
 * the work of others (including StackOverflow or ChatGPT) as my own is an act of Academic    *
 * Misconduct and will be punished as such.                                                   *
 *                                                                                            *
 **********************************************************************************************/
#ifndef NIUCSCI340ASSIGN2_ALGOS_H
#define NIUCSCI340ASSIGN2_ALGOS_H

#warning These programs will not work properly until you have implemented the template functions in assign2-algos.h. Once you have, remove this #warning line from the file. In the beginning, there will likely be more warnings and errors after this because of the missing implementations.

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <ostream>
#include "assign2-algos.decl.h"

using std::vector;
using std::string;
using std::setw;

// Implement your algorithms for assignment 2 in this file.

/**
 * @brief implement a function to sum all elements in the vector
 * 
 * @tparam ITERATOR 
 * @param begin start of range
 * @param end end of the range
 * @return integer: total sum of numbers in the range
 */
template <typename ITERATOR>
int range_sum(ITERATOR begin, ITERATOR end) {
  int sum = 0;
  //vector<int>::iterator i;
  for(auto i = begin; i != end; ++i){
    sum += *i;
  }
  return sum;
}

/**
 * @brief function to calculate the average value of the vector
 * 
 * @tparam ITERATOR 
 * @param begin start of the range
 * @param end end of the range
 * @return double: value of the average
 */
template <typename ITERATOR>
double range_avg(ITERATOR begin, ITERATOR end) {
  double total = range_sum(begin, end);
  double count = range_count(begin, end);

  return total/count;
}

/**
 * @brief function to find the maximum value in range
 * 
 * @tparam ITERATOR 
 * @param begin the beginning of range
 * @param end the end of the range
 * @return auto maximum value
 */
template <typename ITERATOR>
auto range_maxval(ITERATOR begin, ITERATOR end) {
  int max = 0;
  //vector<int>::iterator i;
  for(auto i = begin; i != end; ++i){
    if(*i > max){
      max = *i;
    }
  }
  return max;
}

/**
 * @brief function to calculate the minimum value of the range
 * 
 * @tparam ITERATOR 
 * @param begin the beginning of the range
 * @param end the end of the range
 * @return auto minimum value
 */
template <typename ITERATOR>
auto range_minval(ITERATOR begin, ITERATOR end) {
  int min = 1000000;
  //vector<int>::iterator i;
  for(auto i = begin; i != end; ++i){
    if(*i < min){
      min = *i;
    }
  }
  return min;
}

/**
 * @brief function to count amount of number in range
 * 
 * @tparam ITERATOR 
 * @param begin the beginning of the range
 * @param end the end of the range
 * @return int amount of number in the range
 */
template <typename ITERATOR>
int range_count(ITERATOR begin, ITERATOR end) {
  int r_count = 0;
  //vector<int>::iterator i;
  for(auto i = begin; i != end; ++i){
    r_count++;
  }
  return r_count;
}

/**
 * @brief function to print all elements in range
 * 
 * @tparam ITERATOR 
 * @param ost output stream
 * @param begin beginning of range
 * @param end end of range
 * @param pre string that get printed one time before anything else
 * @param sep (separator) is a string that gets printed between each element (but not before the first or after the last)
 * @param post is a string that gets printed after all of the elements have been printed
 * @param width is the width, in characters, of the column in which the elements' values are printed, or 0 (zero) if you do not want to use a fixed size. Set `std::setw` for details.
 */
template <typename ITERATOR>
void print_range(std::ostream & ost, ITERATOR begin, ITERATOR end, const std::string &pre, const std::string &sep, const std::string &post, int width) {
  ost << pre;
  for(auto i = begin; i != end; ++i){
    if(i != begin){
      ost << sep;
    }
    if (width > 0) {
      ost << setw(width) << *i; // Print with a fixed width if specified
    } else {
      ost << *i; // Print without a fixed width
    }
  }
  ost << post;

  // another way
  //   setw(width);
  // int n = 0;
  // int e = range_count(begin, end);
  // ost<< pre;
  // for(auto i = begin; i != end; ++i){
  //   ost<<*i;
  //   if(n != e - 1){
  //   ost << sep;
  //   }
     
  //   n++;
  // }
  // ost<<post;
}

/**
 * @brief histogram: iterate over every element in the range from "begin" to "end", find out 
 *                   which bin that element belongs in, and increment the count for the appropriate bin.
 *                   Make sure the counts are already at zero before you begin.
 * 
 * @tparam ITERATOR 
 * @tparam RANDOM_ACCESS 
 * @param begin iterator at the beginning of the sequence we're computing a histogram for
 * @param end iterator one past the last element of the sequence we're computing a histogram for
 * @param nums an object supports the subscript `[]` operator to access integers containing the bin counts.
 *             The type is templated, so this could easily be an array or a `vector`, but
 *             it could also be any object that can be used in the appropriate way.
 *             This function will assume that it is already set up so you can read from and write to integers with indices from `nums[0]` to `nums[N-1]` without a problem.
 * @param N the total number of bins, and an upper bound on the indices used with `nums`
 * @param divisor divide the number by this and use the quotient to decide which bin this fits in.
 *                If the quotient is less than zero or greater than `N-1`, then do not increment any of the bins.
 */
template<typename ITERATOR, typename RANDOM_ACCESS>
void histogram(ITERATOR begin, ITERATOR end, RANDOM_ACCESS & nums, int N, int divisor) {

//vector<int>::iterator i;
int quotient = 0;

nums.resize(N,0);

  for(auto i = begin; i != end; ++i){
    quotient = *i / divisor;
    if(quotient >= 0 && quotient < N){
      nums[quotient]++;
    }
  }
}

/**
 * @brief Get the next token strict object
 * 
 * @tparam ITERATOR 
 * @tparam T 
 * @param begin where to begin the search for delimeter
 * @param end the end of the range to search
 * @param delim delimeter, used to indicate that one token has ended
 * @return iter_token_info
 */
template <typename ITERATOR, typename T>
iter_token_info<ITERATOR> get_next_token_strict(ITERATOR begin, ITERATOR end, T delim) {
  iter_token_info<ITERATOR> token_info;
  token_info.b = begin;

  while(begin != end && *begin != delim){
    ++begin;
  }

  token_info.e = begin;

  if(begin != end){
    ++begin;
  }

  token_info.n = begin;

  return token_info;
}

/**
 * @brief Get the next token greedy object
 * 
 * @tparam ITERATOR 
 * @tparam T 
 * @param begin where to begin search for delimeter
 * @param end the end of range search
 * @param delim delimeter value when it is found in range, it is used to indicate that one token has ended
 * @return iter_token_info<ITERATOR> 
 */
template <typename ITERATOR, typename T>
iter_token_info<ITERATOR> get_next_token_greedy(ITERATOR begin, ITERATOR end, T delim) {
  iter_token_info<ITERATOR> token_info;
  //start at the beginning of range
  token_info.b = begin;

  //check if it is true we move to next element in range
  while(begin != end && *begin != delim){
    ++begin;
  }

  //then assign e to the current value of begin
  token_info.e = begin;

  //if the condition is while is true, delim is being skipped
  while(begin != end && *begin == delim){
    ++begin;
  }

  //assign n to the current value of begin
  //record the beginning of next token if no more token, it means this is the end
  token_info.n = begin;

  return token_info;
}

#endif /*NIUCSCI340ASSIGN2_ALGOS_H*/

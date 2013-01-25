/*
 * Class Fibonacci, implementation.
 */

#include "improvedfibonacci.h"
#include <stdexcept>

ImprovedFibonacci::ImprovedFibonacci(size_t maxSize) {
    this->maxSize = maxSize;
    this->result = new int[maxSize];
    this->result[0] = 1;
    this->result[1] = 1;
    this->maxComputed = 1;
}


int ImprovedFibonacci::fibonacci(int n) {
if( n <= 0 ) { throw std::out_of_range("n must be > 0"); }
if( static_cast<unsigned int>(n) >= maxSize ) { throw std::out_of_range("n must be lower than maxSize"); }
  if (n <= maxComputed)
    return result[n];
  for (int i = maxComputed + 1; i <= n; ++i)
    result[i] = result[i-1] + result[i-2];
  maxComputed = n;
  return result[n];
}

/*
 * Class Fibonacci, implementation.
 */

#include "fibonacci.h"

Fibonacci::Fibonacci() {
  result[0] = 1;   // pre-compute first two numbers
  result[1] = 1;
  maxComputed = 1;
}

int Fibonacci::fibonacci(int n) const {
  if (n <= maxComputed)
    return result[n];
  for (int i = maxComputed + 1; i <= n; ++i)
    result[i] = result[i-1] + result[i-2];
  maxComputed = n;
  return result[n];
}

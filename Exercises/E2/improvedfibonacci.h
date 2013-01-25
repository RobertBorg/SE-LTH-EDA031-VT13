/*
 * Class Fibonacci: computes Fibonacci numbers efficiently.
 * Contains no error handling.
 */

#ifndef FIBONACCI_H
#define FIBONACCI_H

#include <cstddef>

class ImprovedFibonacci {
public:
    ImprovedFibonacci(size_t maxSize);
    ImprovedFibonacci() : ImprovedFibonacci(20) {}
    int fibonacci(int n); // fibonacci number n, n >= 0
private:
    size_t maxSize;
    int* result;     // cache for computed results
    int maxComputed;    // max index in result
};

#endif

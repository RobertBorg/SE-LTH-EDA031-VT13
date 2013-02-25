/*
 * Class Fibonacci: computes Fibonacci numbers efficiently.
 * Contains no error handling.
 */

#ifndef FIBONACCI_H
#define FIBONACCI_H

class Fibonacci {
public:
    Fibonacci();
    int fibonacci(int n) const; // fibonacci number n, n >= 0
private:
    mutable int result[40];     // cache for computed results
    mutable int maxComputed;    // max index in result
};

#endif

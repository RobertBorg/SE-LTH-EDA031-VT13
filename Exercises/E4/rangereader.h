/*
 * class RangeReader: read numbers in the range [min, max]. Give an
 * error message if a number outside the range is entered, or if 
 * something that's not a number is entered.
 */
#ifndef RANGE_READER_H
#define RANGE_READER_H

#include <string>

class RangeReader {
public:
    RangeReader(const std::string& prompt, // the prompt text
                const std::string& err,    // the error message
                int min, int max);         // the interval
    int askAndGet() const;                 // prompt and read
private:
    std::string promptMsg; // the prompt text
    std::string errMsg;    // the error message text
    int minValue;          // the minimum value accepted
    int maxValue;          // the maximum value accepted
};

#endif

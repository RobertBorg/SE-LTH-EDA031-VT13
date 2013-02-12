#include "rangereader.h"
#include <iostream>
#include <string>

using namespace std;

RangeReader::RangeReader(const string& prompt, 
                         const string& err,
                         int min, int max) :
promptMsg(prompt), errMsg(err), minValue(min), maxValue(max) {}

int RangeReader::askAndGet() const {
    bool error;
    int answer;
    do {
        error = false;
        cout << promptMsg;
        cin >> answer;
        if (!cin) {
            /*
             * The input wasn't a number. Clear the error state and
             * ignore the rest of the line.
             */
            error = true;
            cin.clear();
            cin.ignore(256, '\n');
        }
        else if (answer < minValue || answer > maxValue)
            error = true;
        if (error) 
            cout << errMsg << endl;
    } while (error);
    return answer;
}

#ifndef READER_H__
#define READER_H__
#include <string>
template<typename T>
class Reader {
public:
    RangeReader(const string& prompt, // the prompt text
                const string& err,    // the error message
                T min, T max) : promptMsg(prompt), errMsg(err), rangeMin(min), rangeMax(max) {}
    auto askAndGet() const -> T {
	    bool error;
	    T answer;
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
    }                 // prompt and read
private:
    std::string promptMsg; // the prompt text
    std::string errMsg;    // the error message text
    IterType rangeMin;
    IterType rangeMax;
};

#endif /* end of include guard: READER_H__ */

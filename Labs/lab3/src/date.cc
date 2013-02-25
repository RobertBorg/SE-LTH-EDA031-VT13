/*
 * Class Date, implementation.
 * 
 */

#include <ctime>    // for C-routines: time and localtime
#include "date.h"
#include <iomanip>
using std::setfill;
using std::setw;

namespace cpp_lab3 {
    using std::dec;

    ostream& operator<<(ostream& os, Date& date) {
        os << setfill('0');
        os  << setw(4) << date.getYear() << '-'
            << setw(2) << date.getMonth() << '-'
            << setw(2) << date.getDay();

        return os;
    }

    istream& operator>>(istream& is, Date& date) {
        char tmp;
        is >> dec >> date.year;
        is.get(tmp);
        is >> dec >> date.month;
        is.get(tmp);
        is >> dec >> date.day;
        return is;
    }
    int Date::daysPerMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    Date::Date() {
        time_t timer = time(0);           // time in seconds since 1970-01-01
        tm* locTime = localtime(&timer);  // broken-down time
        year = 1900 + locTime->tm_year;
        month = 1 + locTime->tm_mon;
        day = locTime->tm_mday;
    }
    
    Date::Date(int y, int m, int d) : year(y), month(m), day(d) {}
    
    int Date::getYear() const {
        return year;
    }
    
    int Date::getMonth() const {
        return month;
    }
    
    int Date::getDay() const {
        return day;
    }
    
    void Date::next() {
        if(++day > daysPerMonth[month-1]) {
            if( ++month > 12) {
                ++year;
                month = 1;
            }
            day = 1;
        }
    }
}

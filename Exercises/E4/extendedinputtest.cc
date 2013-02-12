#include "rangereader.h"
//#include "enumvaluesreader.h"  /* uncomment when you have written the file */
#include <iostream>

using namespace std;

int main() {
    RangeReader rr1("Type a number between 1 and 20: ", 
                    "Illegal number!", 1, 20);
    int nbr1 = rr1.askAndGet();
    cout << "Accepted the number " << nbr1 << endl;
    cout << endl;
    
    RangeReader rr2("Type a number between -5 and +5: ", 
                    "Illegal number!", -5, +5);
    int nbr2 = rr2.askAndGet();
    cout << "Accepted the number " << nbr2 << endl;
    
    /*
     * Check EnumValuesReader. Uncomment the following when you have
     * written the class.
     */
    /*
    int x[] = {10, 20, 30, 40, 50};
    const int X_SIZE = sizeof(x) / sizeof(int);
    EnumValuesReader evr("Type a number (10, 20, 30, 40, 50): ",
                         "Illegal number!", x, X_SIZE);
    int nbr3 = evr.askAndGet();
    cout << "Accepted the number " << nbr3 << endl;
     */
}

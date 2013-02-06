/*
 * A program containing many common programming errors, to test
 * valgrind.
 *
 */
#include <iostream>
#include <vector>

using namespace std;

/*
 * Use uninitalized variable.
 */
void test1() {
    int x;
    int y = x;
    cout << y << endl;
}

/*
 * Dereference null pointer.
 */
void test2() {
    int *x = 0;
    cout << *x << endl;
}

/*
 * IMPLEMENT more methods!
 */

int main() {
    cout << "Test # ";
    int nbr;
    cin >> nbr;
    switch (nbr) {
        case 1: test1(); break;
        case 2: test2(); break;
        default: cout << "No such test" << endl;
    }
}

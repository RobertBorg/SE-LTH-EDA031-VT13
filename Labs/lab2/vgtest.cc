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
* ArrayOutOfBoundsException
*/
void test3() {
    int array [3] = {1, 3, 2};
    cout << array[1337] << endl;
}

/*
* Call to deleted object
*/
void test4() {
    int* x = new int;
    *x = 1337;
    delete x;
    cout << x << endl;
    //*x = 31337;
    //cout << x << endl;
}

int main() {
    cout << "Test # ";
    int nbr;
    cin >> nbr;
    switch (nbr) {
        case 1: test1(); break;
        case 2: test2(); break;
        case 3: test3(); break;
        case 4: test4(); break;
        default: cout << "No such test" << endl;
    }
}
#include <iostream>

using namespace std;

int main() {

	string palindrome;
	int toReturn = 0;
	while(1) {
		cout << "Enter a potential palindrome: ";
		cout.flush();
		cin >> palindrome;
		int size = palindrome.size() - 1;
		for(int i = 0; i <= size; ++i) {
			if(palindrome[i] != palindrome[size - i]) {
				toReturn = 1;
				break;
			}
		}
		cout << toReturn << endl;
		toReturn = 0;
	}
	return toReturn;
}
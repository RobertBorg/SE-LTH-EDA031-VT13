#include <iostream>
#include <string>

bool isPalindrome(std::string word){
    int front = 0;
    int end = word.length() - 1;
    while( end != 0){
        if(word[front] != word[end]){
            return false;
        }
        front++;
        end--;
    }
    return true;
}

int main () {
    std::string word;
    while(std::cin >> word){
        std::cout << (isPalindrome(word) ? "is" : "is NOT") << " palindrome." << std::endl;
    }
}

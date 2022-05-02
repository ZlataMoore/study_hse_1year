#include "palindrome.h"

bool IsPalindrome(const std::string& str) {

    int64_t length = str.length();
    int64_t left = 0;

    for (int right = (length - 1); right >= left;) {
        if (str[right] == ' ') {
            right -= 1;
        } else if (str[left] == ' ') {
            left += 1;
        } else if (str[left] != str[right]) {
            return false;
        } else {
            left += 1;
            right -= 1;
        }
    }

    return true;
}

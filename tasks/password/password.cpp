#include "password.h"
#include <cctype>
bool ValidatePassword(const std::string& password) {

    int64_t length = password.length();
    bool lower_letters = false;
    bool upper_letters = false;
    bool numbers = false;
    bool other = false;
    int64_t min_size = 8;
    int64_t max_size = 14;
    int64_t start_ascii = 33;
    int64_t end_ascii = 127;

    if (length < min_size or length > max_size) {
        return false;
    }
    for (auto letter : password) {
        if (int(letter) < start_ascii or int(letter) > end_ascii) {
            return false;
        }
        if (std::islower(letter)) {
            lower_letters = true;
        } else if (std::isupper(letter)) {
            upper_letters = true;
        } else if (std::isdigit(letter)) {
            numbers = true;
        } else {
            other = true;
        }
    }

    return lower_letters + upper_letters + numbers + other >= 3;
}

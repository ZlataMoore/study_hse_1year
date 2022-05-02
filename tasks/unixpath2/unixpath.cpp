#include "unixpath.h"
#include <cmath>

UnixPath::UnixPath(std::string_view initial_dir) {
    first_initial_dir_ = initial_dir;
    initial_dir_ = initial_dir;
}

void UnixPath::ChangeDirectory(std::string_view path) {
    path_ = path;
    initial_dir_current_ = initial_dir_;
    initial_dir_ = UnixPath::GetAbsolutePath();
}

std::string UnixPath::GetAbsolutePath() const {
    std::string path_absolute;
    if (path_[0] == '/') {
        for (const auto &letter : path_) {
            path_absolute += letter;
        }
    } else {
        for (const auto &letter : initial_dir_current_) {
            path_absolute += letter;
        }

        path_absolute += '/';

        for (const auto &letter : path_) {
            path_absolute += letter;
        }
    }

    std::vector<std::string> help_vector;
    int length = path_absolute.length();
    std::string result;
    for (int index = 0; index < length; index++) {

        std::string current_dir;
        while (index < length && path_absolute[index] != '/') {
            current_dir += path_absolute[index];
            index++;
        }

        if (current_dir == "..") {
            if (!help_vector.empty()) {
                help_vector.pop_back();
            }
        } else if (current_dir != "." && !current_dir.empty()) {
            help_vector.push_back(current_dir);
        }
    }

    for (auto i : help_vector) {
        result += "/" + i;
    }

    if (result.empty()) {
        return "/";
    }

    return result;
}

std::string UnixPath::GetRelativePath() const {

    std::vector<std::string> dir;
    std::vector<std::string> dir_previous;
    std::string word;

    for (const auto &letter : initial_dir_) {
        if (letter == '/') {
            if (!word.empty()) {
                dir.push_back(word);
            }
            word = "";
        } else {
            word += letter;
        }
    }
    dir.push_back(word);
    word = "";

    for (const auto &letter : first_initial_dir_) {
        if (letter == '/') {
            if (!word.empty()) {
                dir_previous.push_back(word);
            }
            word = "";
        } else {
            word += letter;
        }
    }
    dir_previous.push_back(word);

    std::string answer;

    int64_t length_dir = dir.size();
    int64_t length_dir_previous = dir_previous.size();
    int64_t index = 0;

    for (; index != fmin(length_dir, length_dir_previous); ++index) {
        if (dir[index] != dir_previous[index]) {
            break;
        }
    }

    int64_t minus = length_dir_previous - index;

    if (minus == 0) {
        answer += ".";
        int64_t i = index;
        while (i != length_dir) {
            answer += "/";
            answer += dir[i];
            i += 1;
        }
    } else {
        int64_t i = index;
        while (i != length_dir_previous - 1) {
            answer += "../";
            i += 1;
        }
        answer += "..";
        i = index;
        while (i != length_dir) {
            answer += "/";
            answer += dir[i];
            i += 1;
        }
    }

    return answer;
}

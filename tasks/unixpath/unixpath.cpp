#include "unixpath.h"

std::string NormalizePath(std::string_view current_working_dir, std::string_view path) {

    std::string path_absolute;
    if (path[0] == '/') {
        for (const auto &letter : path) {
            path_absolute += letter;
        }
    } else {
        for (const auto &letter : current_working_dir) {
            path_absolute += letter;
        }

        path_absolute += '/';

        for (const auto &letter : path) {
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

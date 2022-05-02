#pragma once

#include <string>
#include <string_view>
#include <vector>

class UnixPath {
public:
    UnixPath(std::string_view initial_dir);

    void ChangeDirectory(std::string_view path);

    std::string GetAbsolutePath() const;
    std::string GetRelativePath() const;

private:
    std::string first_initial_dir_;
    std::string initial_dir_current_;
    std::string initial_dir_;
    std::string path_;
};

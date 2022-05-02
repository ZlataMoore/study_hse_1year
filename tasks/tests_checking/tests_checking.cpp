#include "tests_checking.h"
#include <deque>

std::vector<std::string> StudentsOrder(const std::vector<StudentAction>& student_actions,
                                       const std::vector<size_t>& queries) {

    std::deque<std::string> deque_with_works;
    std::vector<std::string> answer;

    for (const auto& student_action : student_actions) {
        if (student_action.side == Side::Top) {
            deque_with_works.push_front(student_action.name);
        } else {
            deque_with_works.push_back(student_action.name);
        }
    }

    for (const auto& index : queries) {
        answer.push_back(deque_with_works[index - 1]);
    }

    return {answer};
}

#include "scorer.h"

bool CompareFunc(const Event* event1, const Event* event2) {
    return std::tie(event1->time) <= std::tie(event2->time);
}

ScoreTable GetScoredStudents(const Events& events, time_t score_time) {

    std::vector<const Event*> events_ptrs;
    std::map<StudentName, std::set<TaskName>> score_table;
    std::map<std::pair<StudentName, TaskName>, EventType> last_checking;
    std::map<std::pair<StudentName, TaskName>, EventType> last_merge;

    for (const auto& event : events) {
        events_ptrs.push_back(&event);
    }

    std::sort(events_ptrs.begin(), events_ptrs.end(), CompareFunc);

    for (const auto& event : events_ptrs) {
        if (event->time > score_time) {
            break;
        }
        auto student_task_pair = std::make_pair(event->student_name, event->task_name);

        if (event->event_type == EventType::MergeRequestOpen or event->event_type == EventType::MergeRequestClosed) {
            last_merge[student_task_pair] = event->event_type;
        } else {
            last_checking[student_task_pair] = event->event_type;
        }

        if (last_merge[student_task_pair] == EventType::MergeRequestOpen or
            last_checking[student_task_pair] == EventType::CheckFailed) {
            score_table[event->student_name].erase(event->task_name);
            if (score_table[event->student_name].empty()) {
                score_table.erase(event->student_name);
            }
        } else {
            score_table[event->student_name].insert(event->task_name);
        }
    }

    return score_table;  // test
}

#pragma once

#include <map>
#include <set>
#include <string>
#include <vector>

enum class EventType {
    CheckFailed,
    CheckSuccess,
    MergeRequestOpen,
    MergeRequestClosed,
};

using StudentName = std::string;
using TaskName = std::string;

using ScoreTable = std::map<StudentName, std::set<TaskName>>;

class Scorer {
public:
    void OnCheckFailed(const StudentName& student_name, const TaskName& task_name);
    void OnCheckSuccess(const StudentName& student_name, const TaskName& task_name);
    void OnMergeRequestOpen(const StudentName& student_name, const TaskName& task_name);
    void OnMergeRequestClosed(const StudentName& student_name, const TaskName& task_name);
    void Reset();
    void AddToScoreTable(const StudentName& student_name, const TaskName& task_name);

    ScoreTable GetScoreTable() const;

private:
    std::map<StudentName, std::set<TaskName>> score_table_;
    std::map<std::pair<StudentName, TaskName>, EventType> last_checking_;
    std::map<std::pair<StudentName, TaskName>, EventType> last_merge_;
};

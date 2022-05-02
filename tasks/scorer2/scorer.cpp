#include "scorer.h"

void Scorer::AddToScoreTable(const StudentName& student_name, const TaskName& task_name) {

    auto student_task_pair = std::make_pair(student_name, task_name);

    if (this->last_merge_[student_task_pair] == EventType::MergeRequestOpen or
        this->last_checking_[student_task_pair] == EventType::CheckFailed) {
        this->score_table_[student_name].erase(task_name);
        if (this->score_table_[student_name].empty()) {
            this->score_table_.erase(student_name);
        }
    } else {
        this->score_table_[student_name].insert(task_name);
    }
}

void Scorer::OnCheckFailed(const StudentName& student_name, const TaskName& task_name) {
    auto student_task_pair = std::make_pair(student_name, task_name);
    this->last_checking_[student_task_pair] = EventType::CheckFailed;

    AddToScoreTable(student_name, task_name);
}

void Scorer::OnCheckSuccess(const StudentName& student_name, const TaskName& task_name) {
    auto student_task_pair = std::make_pair(student_name, task_name);
    this->last_checking_[student_task_pair] = EventType::CheckSuccess;

    AddToScoreTable(student_name, task_name);
}

void Scorer::OnMergeRequestOpen(const StudentName& student_name, const TaskName& task_name) {
    auto student_task_pair = std::make_pair(student_name, task_name);
    this->last_merge_[student_task_pair] = EventType::MergeRequestOpen;

    AddToScoreTable(student_name, task_name);
}

void Scorer::OnMergeRequestClosed(const StudentName& student_name, const TaskName& task_name) {
    auto student_task_pair = std::make_pair(student_name, task_name);
    this->last_merge_[student_task_pair] = EventType::MergeRequestClosed;

    AddToScoreTable(student_name, task_name);
}

void Scorer::Reset() {

    this->score_table_.clear();
}

ScoreTable Scorer::GetScoreTable() const {
    return this->score_table_;
}

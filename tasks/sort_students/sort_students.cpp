#include "sort_students.h"
#include <catch.hpp>

bool CompareByNames(const Student& student1, const Student& student2) {
    return std::tie(student1.last_name, student1.name, student1.birth_date.year,
                    student1.birth_date.month, student1.birth_date.day) <
           std::tie(student2.last_name, student2.name, student2.birth_date.year,
                    student2.birth_date.month, student2.birth_date.day);
}

bool CompareByDates(const Student& student1, const Student& student2) {
    return std::tie(student1.birth_date.year, student1.birth_date.month, student1.birth_date.day,
                    student1.last_name, student1.name) <
           std::tie(student2.birth_date.year, student2.birth_date.month, student2.birth_date.day,
                    student2.last_name, student2.name);
}

void SortStudents(std::vector<Student>& students, SortKind sort_kind) {
    if (sort_kind == SortKind::Date) {
        std::sort(students.begin(), students.end(), CompareByDates);
    } else {
        std::sort(students.begin(), students.end(), CompareByNames);
    }

}

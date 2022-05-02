#include "admission.h"

bool CompareFunc(const Applicant* applicant1, const Applicant* applicant2) {
    return std::tie(applicant1->points, applicant2->student.birth_date.year, applicant2->student.birth_date.month,
                    applicant2->student.birth_date.day, applicant1->student.name) >
           std::tie(applicant2->points, applicant1->student.birth_date.year, applicant1->student.birth_date.month,
                    applicant1->student.birth_date.day, applicant2->student.name);
}

AdmissionTable FillUniversities(const std::vector<University>& universities, const std::vector<Applicant>& applicants) {

    std::unordered_map<std::string, int> max_students;
    std::vector<const Applicant*> applicants_ptrs;
    std::unordered_map<std::string, std::vector<const Student*>> admission_table;

    for (const auto& university : universities) {
        max_students[university.name] = university.max_students;
    }

    for (const auto& applicant : applicants) {
        applicants_ptrs.push_back(&applicant);
    }

    std::sort(applicants_ptrs.begin(), applicants_ptrs.end(), CompareFunc);

    for (auto& applicant : applicants_ptrs) {

        for (auto& university : applicant->wish_list) {
            if (static_cast<int64_t>(admission_table[university].size()) < max_students[university]) {
                admission_table[university].push_back(&applicant->student);
                break;
            }
        }
    }

    return admission_table;
}

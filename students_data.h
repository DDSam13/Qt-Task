#pragma once
#include <string>
#include <set>
#include <map>
#include <vector>

struct Student {
    std::string surname;
};

using StudentSubjectsMap = std::map<std::string, std::set<std::string>>;

using SubjectStudentsMap = std::map<std::string, std::set<std::string>>;

void loadStudentsFromFile(const std::string& filename, StudentSubjectsMap& studentSubjects, SubjectStudentsMap& subjectStudents);

std::vector<std::string> findStudentsBySubjects(const StudentSubjectsMap& studentSubjects,
    const std::set<std::string>& requiredSubjects,
    const std::set<std::string>& excludedSubjects); 

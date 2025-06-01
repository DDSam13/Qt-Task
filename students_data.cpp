#include "students_data.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>

void loadStudentsFromFile(const std::string& filename, StudentSubjectsMap& studentSubjects, SubjectStudentsMap& subjectStudents) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл: " + filename);
    }

    std::string line;
    int lineNumber = 0;
    while (std::getline(file, line)) {
        ++lineNumber;
        if (line.empty()) continue;
        std::istringstream iss(line);
        std::string surname, subject;
        if (!(iss >> surname >> subject)) {
            throw std::runtime_error("Некорректный формат в строке " + std::to_string(lineNumber));
        }
        studentSubjects[surname].insert(subject);
        subjectStudents[subject].insert(surname);
    }
}

std::vector<std::string> findStudentsBySubjects(const StudentSubjectsMap& studentSubjects,
    const std::set<std::string>& requiredSubjects,
    const std::set<std::string>& excludedSubjects)
{
    std::vector<std::string> result;
    for (const auto& [surname, subjects] : studentSubjects) {
        // Проверяем наличие всех обязательных предметов
        bool hasAllRequired = std::all_of(
            requiredSubjects.begin(), requiredSubjects.end(),
            [&subjects](const std::string& subj) {
                return subjects.count(subj) > 0;
            }
        );
        if (!hasAllRequired) continue;
        // Проверяем отсутствие исключённых предметов
        bool hasExcluded = std::any_of(
            excludedSubjects.begin(), excludedSubjects.end(),
            [&subjects](const std::string& subj) {
                return subjects.count(subj) > 0;
            }
        );
        if (hasExcluded) continue;
        result.push_back(surname);
    }
    return result;
} 
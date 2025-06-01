#pragma once
#include <string>
#include <set>
#include <map>
#include <vector>

// Структура для хранения информации о студенте
struct Student {
    std::string surname;
    // Можно добавить другие поля при необходимости
};

// Контейнер: фамилия -> множество предметов
using StudentSubjectsMap = std::map<std::string, std::set<std::string>>;

// Контейнер: предмет -> множество фамилий студентов
using SubjectStudentsMap = std::map<std::string, std::set<std::string>>;

// Прототип функции для загрузки данных из файла
void loadStudentsFromFile(const std::string& filename, StudentSubjectsMap& studentSubjects, SubjectStudentsMap& subjectStudents);

// Прототип функции для поиска студентов по условиям
std::vector<std::string> findStudentsBySubjects(const StudentSubjectsMap& studentSubjects,
    const std::set<std::string>& requiredSubjects,
    const std::set<std::string>& excludedSubjects); 
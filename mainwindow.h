#pragma once
#include <QMainWindow>
#include <QListWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QString>
#include <set>
#include "students_data.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr, const QString& filename = QString());
    ~MainWindow();

private slots:
    void onSearchClicked();
    void onClearClicked();
    void onChooseFileClicked();

private:
    void loadData(const QString& filename);
    void updateSubjectsList();
    std::set<std::string> getSelectedSubjects(QListWidget* listWidget) const;

    StudentSubjectsMap studentSubjects;
    SubjectStudentsMap subjectStudents;
    std::set<std::string> allSubjects;

    QListWidget* requiredSubjectsList;
    QListWidget* excludedSubjectsList;
    QPushButton* searchButton;
    QPushButton* clearButton;
    QPushButton* chooseFileButton;
    QTextEdit* resultEdit;

    QString initialFilename;
};

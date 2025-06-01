#pragma once
#include <QWidget>
#include <QString>
#include <QListWidget>
#include <QPushButton>
#include <QTextEdit>
#include <set>
#include "students_data.h"

class StudentWidget : public QWidget {
    Q_OBJECT
public:
    explicit StudentWidget(const QString& filename, QWidget* parent = nullptr);
signals:
    void requestOpenAnother();
private slots:
    void onSearchClicked();
    void onClearClicked();
    void onOpenAnotherClicked();
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
    QPushButton* openAnotherButton;
    QTextEdit* resultEdit;
}; 
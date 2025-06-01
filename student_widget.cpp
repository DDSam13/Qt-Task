#include "student_widget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>

StudentWidget::StudentWidget(const QString& filename, QWidget* parent) : QWidget(parent) {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QHBoxLayout* listsLayout = new QHBoxLayout();
    requiredSubjectsList = new QListWidget(this);
    requiredSubjectsList->setSelectionMode(QAbstractItemView::MultiSelection);
    excludedSubjectsList = new QListWidget(this);
    excludedSubjectsList->setSelectionMode(QAbstractItemView::MultiSelection);
    listsLayout->addWidget(new QLabel("Обязательные предметы:"));
    listsLayout->addWidget(requiredSubjectsList);
    listsLayout->addWidget(new QLabel("Исключаемые предметы:"));
    listsLayout->addWidget(excludedSubjectsList);
    mainLayout->addLayout(listsLayout);

    searchButton = new QPushButton("Поиск", this);
    mainLayout->addWidget(searchButton);

    clearButton = new QPushButton("Очистить", this);
    clearButton->setEnabled(false);
    mainLayout->addWidget(clearButton);

    openAnotherButton = new QPushButton("Открыть ещё одно окно", this);
    mainLayout->addWidget(openAnotherButton);

    resultEdit = new QTextEdit(this);
    resultEdit->setReadOnly(true);
    mainLayout->addWidget(resultEdit);

    connect(searchButton, &QPushButton::clicked, this, &StudentWidget::onSearchClicked);
    connect(clearButton, &QPushButton::clicked, this, &StudentWidget::onClearClicked);
    connect(openAnotherButton, &QPushButton::clicked, this, &StudentWidget::onOpenAnotherClicked);

    loadData(filename);
    updateSubjectsList();
}

void StudentWidget::loadData(const QString& filename) {
    try {
        loadStudentsFromFile(filename.toStdString(), studentSubjects, subjectStudents);
        allSubjects.clear();
        for (const auto& [subject, _] : subjectStudents) {
            allSubjects.insert(subject);
        }
    } catch (const std::exception& ex) {
        QMessageBox::critical(this, "Ошибка", ex.what());
    }
}

void StudentWidget::updateSubjectsList() {
    requiredSubjectsList->clear();
    excludedSubjectsList->clear();
    for (const auto& subject : allSubjects) {
        requiredSubjectsList->addItem(QString::fromStdString(subject));
        excludedSubjectsList->addItem(QString::fromStdString(subject));
    }
}

std::set<std::string> StudentWidget::getSelectedSubjects(QListWidget* listWidget) const {
    std::set<std::string> result;
    for (QListWidgetItem* item : listWidget->selectedItems()) {
        result.insert(item->text().toStdString());
    }
    return result;
}

void StudentWidget::onSearchClicked() {
    auto required = getSelectedSubjects(requiredSubjectsList);
    auto excluded = getSelectedSubjects(excludedSubjectsList);
    auto found = findStudentsBySubjects(studentSubjects, required, excluded);
    resultEdit->clear();
    if (found.empty()) {
        resultEdit->setText("Нет подходящих студентов.");
    } else {
        for (const auto& surname : found) {
            resultEdit->append(QString::fromStdString(surname));
        }
    }
    clearButton->setEnabled(true);
}

void StudentWidget::onClearClicked() {
    requiredSubjectsList->clearSelection();
    excludedSubjectsList->clearSelection();
    resultEdit->clear();
    clearButton->setEnabled(false);
}

void StudentWidget::onOpenAnotherClicked() {
    emit requestOpenAnother();
} 

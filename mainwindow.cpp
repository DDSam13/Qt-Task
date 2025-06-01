#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QLabel>
#include <QFileDialog>
#include "logger.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    QWidget* central = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(central);

    // Списки предметов
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

    // Кнопка поиска
    searchButton = new QPushButton("Поиск", this);
    mainLayout->addWidget(searchButton);

    // Поле для вывода результатов
    resultEdit = new QTextEdit(this);
    resultEdit->setReadOnly(true);
    mainLayout->addWidget(resultEdit);

    setCentralWidget(central);
    resize(600, 400);

    connect(searchButton, &QPushButton::clicked, this, &MainWindow::onSearchClicked);

    // Удалено приветственное окно
    loadData();
    updateSubjectsList();
    Logger::instance().info("Приложение запущено. Открытие главного окна.");
}

MainWindow::~MainWindow() {}

void MainWindow::loadData() {
    QString filename = QFileDialog::getOpenFileName(this, "Выберите файл со студентами");
    if (filename.isEmpty()) {
        Logger::instance().warning("Пользователь не выбрал файл для загрузки студентов.");
        return;
    }
    try {
        loadStudentsFromFile(filename.toStdString(), studentSubjects, subjectStudents);
        Logger::instance().info("Данные успешно загружены из файла: " + filename.toStdString());
        // Собираем все предметы
        allSubjects.clear();
        for (const auto& [subject, _] : subjectStudents) {
            allSubjects.insert(subject);
        }
    } catch (const std::exception& ex) {
        Logger::instance().error(std::string("Ошибка при загрузке файла: ") + ex.what());
        QMessageBox::critical(this, "Ошибка", ex.what());
    }
}

void MainWindow::updateSubjectsList() {
    requiredSubjectsList->clear();
    excludedSubjectsList->clear();
    for (const auto& subject : allSubjects) {
        requiredSubjectsList->addItem(QString::fromStdString(subject));
        excludedSubjectsList->addItem(QString::fromStdString(subject));
    }
}

std::set<std::string> MainWindow::getSelectedSubjects(QListWidget* listWidget) const {
    std::set<std::string> result;
    for (QListWidgetItem* item : listWidget->selectedItems()) {
        result.insert(item->text().toStdString());
    }
    return result;
}

void MainWindow::onSearchClicked() {
    auto required = getSelectedSubjects(requiredSubjectsList);
    auto excluded = getSelectedSubjects(excludedSubjectsList);
    Logger::instance().info("Запрос поиска студентов. Обязательные: " + std::to_string(required.size()) + ", исключаемые: " + std::to_string(excluded.size()));
    auto found = findStudentsBySubjects(studentSubjects, required, excluded);
    Logger::instance().info("Результат поиска: найдено студентов: " + std::to_string(found.size()));
    resultEdit->clear();
    if (found.empty()) {
        resultEdit->setText("Нет подходящих студентов.");
    } else {
        for (const auto& surname : found) {
            resultEdit->append(QString::fromStdString(surname));
        }
    }
}

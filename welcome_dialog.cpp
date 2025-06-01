#include "welcome_dialog.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QFileDialog>

WelcomeDialog::WelcomeDialog(QWidget* parent) : QDialog(parent) {
    setWindowTitle("Добро пожаловать");
    QVBoxLayout* layout = new QVBoxLayout(this);
    infoLabel = new QLabel("Для начала работы выберите файл со списком студентов и предметов.", this);
    layout->addWidget(infoLabel);
    chooseFileButton = new QPushButton("Выбрать файл", this);
    layout->addWidget(chooseFileButton);
    connect(chooseFileButton, &QPushButton::clicked, this, &WelcomeDialog::onChooseFileClicked);
}

void WelcomeDialog::onChooseFileClicked() {
    QString file = QFileDialog::getOpenFileName(this, "Выберите файл со студентами");
    if (!file.isEmpty()) {
        selectedFile = file;
        accept();
    }
}

QString WelcomeDialog::getSelectedFile() const {
    return selectedFile;
} 
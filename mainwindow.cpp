#include "mainwindow.h"
#include "student_widget.h"
#include "welcome_dialog.h"
#include <QMenuBar>
#include <QFileDialog>
#include <QApplication>

MainWindow::MainWindow(const QString& firstFile, QWidget* parent) : QMainWindow(parent) {
    tabWidget = new QTabWidget(this);
    tabWidget->setTabsClosable(true);
    setCentralWidget(tabWidget);
    connect(tabWidget, &QTabWidget::tabCloseRequested, this, &MainWindow::onTabCloseRequested);

    fileMenu = menuBar()->addMenu("Файл");
    openFileAction = new QAction("Открыть ещё одно окно", this);
    fileMenu->addAction(openFileAction);
    connect(openFileAction, &QAction::triggered, this, &MainWindow::onOpenFile);

    openStudentTab(firstFile);
}

MainWindow::~MainWindow() {}

void MainWindow::onOpenFile() {
    QString filename = QFileDialog::getOpenFileName(this, "Выберите файл со студентами");
    if (!filename.isEmpty()) {
        openStudentTab(filename);
    }
}

void MainWindow::openStudentTab(const QString& filename) {
    StudentWidget* widget = new StudentWidget(filename);
    connect(widget, &StudentWidget::requestOpenAnother, this, &MainWindow::onOpenFile);
    int idx = tabWidget->addTab(widget, filename.section('/', -1));
    tabWidget->setCurrentIndex(idx);
}

void MainWindow::onTabCloseRequested(int index) {
    QWidget* widget = tabWidget->widget(index);
    tabWidget->removeTab(index);
    delete widget;
    if (tabWidget->count() == 0) {
        this->close();
    }
}

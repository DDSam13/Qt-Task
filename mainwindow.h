#pragma once
#include <QMainWindow>
#include <QTabWidget>
#include <QMenu>
#include <QAction>
#include <QString>

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(const QString& firstFile, QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void onOpenFile();
    void openStudentTab(const QString& filename);
    void onTabCloseRequested(int index);

private:
    QTabWidget* tabWidget;
    QMenu* fileMenu;
    QAction* openFileAction;
};

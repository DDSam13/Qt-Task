#include <QApplication>
#include "mainwindow.h"
#include "logger.h"

int main(int argc, char *argv[])
{
    Logger::instance().info("Запуск приложения Task4");
    QApplication app(argc, argv);
    MainWindow w;
    w.show();
    int result = app.exec();
    Logger::instance().info("Завершение приложения Task4");
    return result;
}

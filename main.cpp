#include <QIcon>
#include <QApplication>
#include "mainwindow.h"
#include "welcome_dialog.h"
#include "logger.h"

int main(int argc, char *argv[])
{
    ;Logger::instance();
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/new/prefix1/images/icon.png"));
    while (true) {
        WelcomeDialog welcome;
        if (welcome.exec() == QDialog::Accepted) {
            QString filename = welcome.getSelectedFile();
            if (!filename.isEmpty()) {
                MainWindow w(filename);
                w.show();
                app.exec();
                continue;
            }
        }
        break;
    }
    return 0;
}

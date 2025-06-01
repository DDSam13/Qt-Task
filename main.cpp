#include <QApplication>
#include "mainwindow.h"
#include "welcome_dialog.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    WelcomeDialog welcome;
    if (welcome.exec() == QDialog::Accepted) {
        QString filename = welcome.getSelectedFile();
        if (!filename.isEmpty()) {
            MainWindow w(nullptr, filename);
            w.show();
            return app.exec();
        }
    }
    return 0;
}

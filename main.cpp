#include <QApplication>
#include "mainwindow.h"
#include "welcome_dialog.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
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

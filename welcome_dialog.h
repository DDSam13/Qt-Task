#pragma once
#include <QDialog>
#include <QString>

class QPushButton;
class QLabel;

class WelcomeDialog : public QDialog {
    Q_OBJECT
public:
    explicit WelcomeDialog(QWidget* parent = nullptr);
    QString getSelectedFile() const;
private slots:
    void onChooseFileClicked();
private:
    QLabel* infoLabel;
    QPushButton* chooseFileButton;
    QString selectedFile;
}; 
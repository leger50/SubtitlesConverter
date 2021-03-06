#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardPaths>

#include "charsetconverter.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_importFile_clicked();
    void on_btn_startConvert_clicked();

    void displayMessage(QString message);
    void displayConversionProgress(quint8 percentage);
    void displayError(QString error);

private:
    void importFile();
    void startConverter();

    QString chooseFileFromUserSpace(QStandardPaths::StandardLocation userDirectory);
    bool filePathIsValid(QString pathToFile);

    QString getFilenameOuput();

    void displayFilenameInput(QString filename);
    void displayFilenameOuput(QString filename);

private:
    Ui::MainWindow *ui;
    CharsetConverter *m_converter;

    QString m_pathToDirectory;
    QString m_filenameInput;
    QString m_filenameOutput;

    const static QString DEFAULT_TEXT_FILE_INPUT;
};
#endif // MAINWINDOW_H

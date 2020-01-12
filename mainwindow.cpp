#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_importFile_clicked(){
    importFile();
}

void MainWindow::on_btn_startConvert_clicked(){
    startConverter();
}

void MainWindow::importFile(){
    QString pathToFilename = chooseFileFromUserSpace(QStandardPaths::DocumentsLocation);

    if(!pathToFilename.isNull() && !pathToFilename.isEmpty()){
        m_converter.configure(pathToFilename);
        displayFilenameInput(QFileInfo(pathToFilename).fileName());
    }
}

void MainWindow::startConverter(){
    if(m_converter.isConfigure()){
        m_converter.launchConversionToUtf8();
        m_converter.saveConversion();
    }
}

QString MainWindow::chooseFileFromUserSpace(QStandardPaths::StandardLocation userDirectory){
    return QFileDialog::getOpenFileName(this, tr("Open subtitle file"), QStandardPaths::writableLocation(userDirectory), tr("Subtitles Files (*.srt *.sub *.sbv)"));
}

void MainWindow::displayFilenameInput(QString filename){
    ui->label_valueFileImport->setText(filename);
}

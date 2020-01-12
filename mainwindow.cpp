#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

const QString MainWindow::DEFAULT_TEXT_FILE_INPUT = tr("No selected file");

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_converter = new CharsetConverter();

    connect(m_converter, SIGNAL(throw_error(QString)), this, SLOT(displayError(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_converter;
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
        m_converter->configure(pathToFilename);
        displayFilenameInput(QFileInfo(pathToFilename).fileName());
    }else{
        displayFilenameInput(DEFAULT_TEXT_FILE_INPUT);
    }
}

void MainWindow::startConverter(){
    m_converter->launchConversionToUtf8();
    m_converter->saveConversion();
}

QString MainWindow::chooseFileFromUserSpace(QStandardPaths::StandardLocation userDirectory){
    return QFileDialog::getOpenFileName(this, tr("Open subtitle file"), QStandardPaths::writableLocation(userDirectory), tr("Subtitles Files (*.srt *.sub *.sbv)"));
}

void MainWindow::displayError(QString error){
    QMessageBox::critical(this, tr("Error"), error);
}

void MainWindow::displayFilenameInput(QString filename){
    ui->label_valueFileImport->setText(filename);
}

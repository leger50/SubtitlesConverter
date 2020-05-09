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

    connect(m_converter, SIGNAL(sMessage(QString)), this, SLOT(displayMessage(QString)));
    connect(m_converter, SIGNAL(sProgressConversion(quint8)), this, SLOT(displayConversionProgress(quint8)));
    connect(m_converter, SIGNAL(sThrowError(QString)), this, SLOT(displayError(QString)));
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

    if(filePathIsValid(pathToFilename)){
        QFileInfo fileInfo(pathToFilename);
        m_pathToDirectory = fileInfo.path().append("/");
        m_filenameInput = fileInfo.fileName();
        m_filenameOutput = fileInfo.baseName() + "_new." + fileInfo.suffix();

        displayFilenameInput(m_filenameInput);
        displayFilenameOuput(m_filenameOutput);
    }else{
        displayFilenameInput(DEFAULT_TEXT_FILE_INPUT);
    }
}

void MainWindow::startConverter(){
    m_filenameOutput = getFilenameOuput();

    QString pathToInputFile = m_pathToDirectory + m_filenameInput;
    QString pathToOutputFile = m_pathToDirectory + m_filenameOutput;

    if(filePathIsValid(pathToInputFile) && filePathIsValid(pathToOutputFile)){
        m_converter->configure(pathToInputFile, pathToOutputFile);
    }

    m_converter->launchConversionToUtf8();
    m_converter->saveConversion();
}

QString MainWindow::chooseFileFromUserSpace(QStandardPaths::StandardLocation userDirectory){
    return QFileDialog::getOpenFileName(this, tr("Open subtitle file"), QStandardPaths::writableLocation(userDirectory), tr("Subtitles Files (*.srt *.sub *.sbv)"));
}

QString MainWindow::getFilenameOuput(){
    return ui->edit_nameFileOutput->text();
}

bool MainWindow::filePathIsValid(QString pathToFile){
    return !pathToFile.isNull() && !pathToFile.isEmpty();
}

void MainWindow::displayMessage(QString message){
    ui->text_messageConversion->appendPlainText(message);
    ui->text_messageConversion->ensureCursorVisible();
}

void MainWindow::displayConversionProgress(quint8 percentage){
    ui->bar_statusConversion->setValue(percentage);
}

void MainWindow::displayError(QString error){
    QMessageBox::critical(this, tr("Error"), error);
}

void MainWindow::displayFilenameInput(QString filename){
    ui->label_valueFileImport->setText(filename);
}

void MainWindow::displayFilenameOuput(QString filename){
    ui->edit_nameFileOutput->setText(filename);
}

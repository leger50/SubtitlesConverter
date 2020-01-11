#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "charsetconverter.h"

#include <QStandardPaths>
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
    const QString documentFolder = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open subtitle file"), documentFolder, tr("Subtitles Files (*.srt *.sub *.sbv)"));

    startConverter(fileName);
}

void MainWindow::startConverter(QString pathToFilename){
    CharsetConverter converter;

    converter.configure(pathToFilename);
    converter.launchConversionToUtf8();
    converter.saveConversion();
}

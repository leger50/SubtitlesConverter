#include "charsetconverter.h"

#include <QTextCodec>
#include <QTextStream>
#include <QFile>

const QString CharsetConverter::ERROR_CONFIGURATION = tr("Charset converter is not properly configured");
const QString CharsetConverter::ERROR_SAVE = tr("Could not save results");

CharsetConverter::CharsetConverter(){

}

CharsetConverter::~CharsetConverter(){

}

void CharsetConverter::configure(QString pathToFile){
   loadDataFile(pathToFile);
   m_pathToNewFilename = pathToFile.append(".new");
}

void CharsetConverter::launchConversionToUtf8(){
    if(isConfigure()){
        QTextDecoder *decoder = QTextCodec::codecForName("Windows-1252")->makeDecoder();
        QString result = decoder->toUnicode(m_dataFile,m_dataFile.length());

        m_dataFile = result.toUtf8();
        delete decoder;

    }else{
        emit throw_error(ERROR_CONFIGURATION);
    }
}

void CharsetConverter::saveConversion(){
    QFile file(m_pathToNewFilename);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        emit throw_error(ERROR_SAVE);
        return;
    }

    QTextStream stream(&file); stream.setCodec("UTF-8");
    stream << m_dataFile;
    file.close();
}

bool CharsetConverter::loadDataFile(QString pathToFilename){
    QFile file(pathToFilename);

    if(file.open(QFile::ReadOnly)){
        m_dataFile = file.readAll();
        return true;
    }

    return false;
}

bool CharsetConverter::isConfigure(){
    return !m_dataFile.isNull();
}

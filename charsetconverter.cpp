#include "charsetconverter.h"

#include <QTextCodec>
#include <QTextStream>
#include <QFile>

const QString CharsetConverter::MESSAGE_SAVE = tr("File save to : %1");
const QString CharsetConverter::MESSAGE_CONVERSION = tr("Conversion from %1 to UTF-8 succeeded");

const QString CharsetConverter::ERROR_CONFIGURATION = tr("Charset converter is not properly configured");
const QString CharsetConverter::ERROR_SAVE = tr("Could not save results");

CharsetConverter::CharsetConverter(){

}

CharsetConverter::~CharsetConverter(){

}

void CharsetConverter::configure(QString pathToFileInput, QString pathToFileOutput){
   loadDataFile(pathToFileInput);
   m_pathToFileOutput = pathToFileOutput;
}

void CharsetConverter::launchConversionToUtf8(){
    emit sProgressConversion(0);

    if(isConfigure()){
        QTextDecoder *decoder = QTextCodec::codecForName("Windows-1252")->makeDecoder();
        QString result = decoder->toUnicode(m_dataFile, m_dataFile.length());

        m_dataFile = result.toUtf8();

        emit sProgressConversion(100);
        emit sMessage(MESSAGE_CONVERSION.arg("Windows-1252"));
        delete decoder;

    }else{
        emit sThrowError(ERROR_CONFIGURATION);
    }
}

void CharsetConverter::saveConversion(){
    QFile file(m_pathToFileOutput);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        emit sThrowError(ERROR_SAVE);
        return;
    }

    QTextStream stream(&file); stream.setCodec("UTF-8");
    stream << m_dataFile;
    file.close();

    emit sMessage(MESSAGE_SAVE.arg(file.fileName()));
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

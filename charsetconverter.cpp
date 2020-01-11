#include "charsetconverter.h"

#include <QTextCodec>
#include <QTextStream>
#include <QFile>

CharsetConverter::CharsetConverter()
{

}

void CharsetConverter::configure(QString pathToFile){
   loadDataFile(pathToFile);
   m_pathToNewFilename = pathToFile.append(".new");
}

void CharsetConverter::launchConversionToUtf8(){
    QTextDecoder* decoder = QTextCodec::codecForName("Windows-1252")->makeDecoder();
    QString result = decoder->toUnicode(m_dataFile,m_dataFile.length());

    m_dataFile = result.toUtf8();
}

void CharsetConverter::saveConversion(){
    QFile file(m_pathToNewFilename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

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

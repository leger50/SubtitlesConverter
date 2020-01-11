#ifndef CHARSETCONVERTER_H
#define CHARSETCONVERTER_H

#include <QByteArray>
#include <QString>

class CharsetConverter
{

public:
    CharsetConverter();

    void configure(QString pathToFile);
    void launchConversionToUtf8();
    void saveConversion();

private:
    bool loadDataFile(QString pathToFilename);

    QByteArray m_dataFile;
    QString m_pathToNewFilename;

};

#endif // CHARSETCONVERTER_H

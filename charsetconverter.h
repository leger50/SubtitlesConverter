#ifndef CHARSETCONVERTER_H
#define CHARSETCONVERTER_H

#include <QObject>
#include <QByteArray>
#include <QString>

class CharsetConverter : public QObject
{
    Q_OBJECT

public:
    CharsetConverter();
    ~CharsetConverter();

    void configure(QString pathToFile);
    void launchConversionToUtf8();
    void saveConversion();

signals:
    void throw_error(QString message);

private:
    bool loadDataFile(QString pathToFilename);
    bool isConfigure();

    QByteArray m_dataFile;
    QString m_pathToNewFilename;

    const static QString ERROR_CONFIGURATION;
    const static QString ERROR_SAVE;

};

#endif // CHARSETCONVERTER_H

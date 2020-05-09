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
    void sMessage(QString message);
    void sProgressConversion(quint8 percentage);
    void sThrowError(QString message);

private:
    bool loadDataFile(QString pathToFilename);
    bool isConfigure();

private:
    QByteArray m_dataFile;
    QString m_pathToNewFilename;

    const static QString MESSAGE_CONVERSION;
    const static QString MESSAGE_SAVE;

    const static QString ERROR_CONFIGURATION;
    const static QString ERROR_SAVE;

};

#endif // CHARSETCONVERTER_H

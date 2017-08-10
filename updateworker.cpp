#include "updateworker.h"
#include <QDir>
#include <QtNetwork>
#include <QCryptographicHash>
#include <QUrl>
#include <QJsonDocument>

UpdateWorker::UpdateWorker(QObject *parent) : QObject(parent)
{

}

// TODO remove QEventLoop, moving over to slots
// TODO update progress on which files are being downloaded

void UpdateWorker::process()
{
    QEventLoop loop;

    // First ensure directories required exist
    if (!QDir("config").exists()) QDir().mkdir("config");
    if (!QDir("resources").exists()) QDir().mkdir("resources");
    if (!QDir("resources/default").exists()) QDir("resources").mkdir("default");

    // Download manifest
    QNetworkAccessManager nam;
    QNetworkRequest manifestRequest(QUrl(MANIFEST));
    QNetworkReply* manifestReply = nam.get(manifestRequest);

    connect(manifestReply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    if (manifestReply->error() == QNetworkReply::NoError)
    {
        QByteArray replyArray = manifestReply->readAll();
        QString replyText = QString::fromUtf8(replyArray);
        QStringList entries = replyText.split("#");

        foreach (QString entryJson, entries)
        {
            // Blank entry at end of manifest
            if (entryJson == "") continue;

            // Decode JSON into something we can use
            QJsonDocument entry = QJsonDocument::fromJson(entryJson.toUtf8());
            QJsonObject entryObject = entry.object();
            QString filename = "./" + getDirectory(entryObject["filename"].toString());
            bool toUpdate = true;

            emit progress("Checking " + entryObject["filename"].toString());

            // If file exists, check hash
            if (QFile(filename).exists())
            {
                QFile file(filename);
                file.open(QIODevice::ReadOnly);
                QByteArray hash = QCryptographicHash::hash(file.readAll(), QCryptographicHash::Sha256);
                file.close();
                toUpdate = hash.toHex() != entryObject["sha256"].toString();
            }

            // Download new file if it doesn't exist of it hash doesn't match
            if (toUpdate)
            {
                emit progress("Updating " + entryObject["filename"].toString());
                QNetworkRequest request(QUrl(entryObject["url"].toString()));
                QNetworkReply* reply = nam.get(request);
                QFile file(filename);
                file.open(QIODevice::WriteOnly);

                connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
                loop.exec();

                file.write(reply->readAll());
                file.close();

                delete reply;
            }
        }

        emit progress("Updated! Ready to play");

    }
    else
    {
        // Presume game is up to date incase we can't get manifest
        emit progress("Couldn't download manifest, presuming game is up to date.");
    }
    delete manifestReply;

    // TODO update game
    emit finished();
}

QString UpdateWorker::getDirectory(QString file)
{
    if (file == "toon.dc")
    {
        return "config/" + file;
    }
    else if (file.startsWith("phase") && file.endsWith(".mf"))
    {
        return "resources/default/" + file;
    }
    return file;
}

UpdateWorker::~UpdateWorker()
{

}

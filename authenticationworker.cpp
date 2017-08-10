#include "authenticationworker.h"
#include <QUrl>
#include <QJsonDocument>

AuthenticationWorker::AuthenticationWorker(QString username, QString password, QObject *parent) : QObject(parent)
{
    this->username = username;
    this->password = password;
}

void AuthenticationWorker::process()
{
    QNetworkRequest request(QUrl(AUTHAPI));
    QJsonObject parameters;

    nam = new QNetworkAccessManager();

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    parameters.insert("u", this->username);
    parameters.insert("p", this->password);

    QJsonDocument parametersDocument(parameters);

    reply = nam->post(request, parametersDocument.toJson());
    connect(reply, SIGNAL(finished()), this, SLOT(serverReplied()));
}

void AuthenticationWorker::serverReplied()
{
    if (reply->error() == QNetworkReply::NoError)
    {
        QJsonDocument responseDocument = QJsonDocument::fromJson(reply->readAll());
        QJsonObject response = responseDocument.object();
        emit result(response["status"].toBool(), response["reason"].toString(), response["additional"].toString());
    }
    else
    {
        emit result(false, "Failed to connect to auth server.", "Oopsy daisy!");
    }
    delete reply;
    delete nam;
    emit finished();
}

AuthenticationWorker::~AuthenticationWorker()
{

}

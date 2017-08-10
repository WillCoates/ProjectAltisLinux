#ifndef AUTHENTICATIONWORKER_H
#define AUTHENTICATIONWORKER_H

#include <QObject>
#include <QtNetwork>

#define AUTHAPI "https://projectaltis.com/api/login"

class AuthenticationWorker : public QObject
{
    Q_OBJECT
public:
    explicit AuthenticationWorker(QString username, QString password, QObject *parent = nullptr);
    ~AuthenticationWorker();
public slots:
    void process();
private:
    QString username, password;
    QNetworkAccessManager* nam;
    QNetworkReply* reply;
private slots:
    void serverReplied();
signals:
    void result(bool success, QString reason, QString additonal);
    void finished();
};

#endif // AUTHENTICATIONWORKER_H

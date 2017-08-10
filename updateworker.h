#ifndef UPDATEWORKER_H
#define UPDATEWORKER_H

#include <QObject>

#define MANIFEST "https://projectaltis.com/api/manifest"

class UpdateWorker : public QObject
{
    Q_OBJECT
public:
    explicit UpdateWorker(QObject *parent = nullptr);
    ~UpdateWorker();
public slots:
    void process();
private:
    QString getDirectory(QString file);
signals:
    void finished();
    void progress(QString message);
};

#endif // UPDATEWORKER_H

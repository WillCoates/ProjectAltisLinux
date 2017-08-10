#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void onLoginClick();
    void updateFinished();
    void updateProgress(QString message);
    void authResponse(bool status, QString reason, QString additonal);
private:
    Ui::MainWindow *ui;
    void showEvent(QShowEvent *event);

    void startAltis();
    void updateAltis();
    void authenticate();
};

#endif // MAINWINDOW_H

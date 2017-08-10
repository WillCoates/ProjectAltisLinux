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
private:
    Ui::MainWindow *ui;
    void showEvent(QShowEvent *event);

    void startAltis();
    void updateAltis();
};

#endif // MAINWINDOW_H

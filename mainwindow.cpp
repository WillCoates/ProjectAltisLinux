#include <qprocess.h>
#include <qthread.h>
#include <qdir.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "updateworker.h"
#include "systemtype.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon("altis.ico"));
}

void MainWindow::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    ui->loginButton->setEnabled(false);
    updateAltis();
}

void MainWindow::onLoginClick()
{
    disconnect(ui->loginButton, SIGNAL(released()), this, SLOT(onLoginClick()));
    startAltis();
}

void MainWindow::startAltis()
{
    QProcess *altisProcess = new QProcess(this);
    QStringList arguments;
    QString program;

#if defined(SYSTEM_WINDOWS)
    // We can start the game straight off
    program = currentDir + "\\ProjectAltis.exe";
#elif defined(SYSTEM_LINUX) || defined(SYSTEM_MACOSX)
    // We need to start with wine for now
    program = "./wine/bin/wine";
    qputenv("WINEPREFIX", (QDir::currentPath() + "/wineprefix").toUtf8());
    arguments << "ProjectAltis.exe";
#endif
    // This is the way the official altis launcher starts, was kinda expecting an auth API to get a key but I guess environment variables works.
    qputenv("TT_GAMESERVER", "gs1.projectaltis.com");
    qputenv("TT_USERNAME", ui->usernameEdit->text().toUtf8());
    qputenv("TT_PASSWORD", ui->passwordEdit->text().toUtf8());

    ui->passwordEdit->setText(""); // Clear password box
    ui->statusLabel->setText("Launched Altis. Please note this environment is not supported.");
    altisProcess->start(program, arguments);
    setVisible(false);
    altisProcess->waitForFinished(-1);
    setVisible(true);
}

void MainWindow::updateAltis()
{
    QThread* updateThread = new QThread(this);
    UpdateWorker* updateWorker = new UpdateWorker();
    updateWorker->moveToThread(updateThread);

    ui->statusLabel->setText("Checking for updates");

    // FIXME Thread doesn't terminate when updates finished, causing core dump
    connect(updateThread, SIGNAL (started()), updateWorker, SLOT (process()));
    connect(updateThread, SIGNAL (finished()), updateThread, SLOT (quit()));
    connect(updateThread, SIGNAL (finished()), updateThread, SLOT (deleteLater()));
    connect(updateWorker, SIGNAL (finished()), updateWorker, SLOT (deleteLater()));
    connect(updateWorker, SIGNAL (finished()), this, SLOT (updateFinished()));
    connect(updateWorker, SIGNAL (progress(QString)), this, SLOT (updateProgress(QString)));

    updateThread->start();
}

void MainWindow::updateProgress(QString message)
{
    ui->statusLabel->setText(message);
}

void MainWindow::updateFinished()
{
    ui->loginButton->setEnabled(true);
    connect(ui->loginButton, SIGNAL(released()), this, SLOT(onLoginClick()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

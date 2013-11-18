#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSocketNotifier>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    con = nullptr;
//    term = nullptr;
    par.port = 22;
    par.userName = "dsby";
    par.password = "123789";
    par.timeout = 500;
    par.authenticationType = QSsh::SshConnectionParameters::AuthenticationByPassword;
    this->ui->lineip->setText("192.168.56.102");
}

MainWindow::~MainWindow()
{
    delete ui;
    if (nullptr != con)
    {
        con->deleteLater();
    }

}

void MainWindow::on_pushcon_clicked()
{
    par.host = this->ui->lineip->text();
    con = new QSsh::SshConnection(par);
    connect(con,&QSsh::SshConnection::connected,this,&MainWindow::sshcon);
    connect(con,&QSsh::SshConnection::dataAvailable,[this](const QString & mse){this->ui->textEdit->append(mse);});
    connect(con,&QSsh::SshConnection::disconnected,[this](){this->ui->textEdit->append("SSH disconnect");});
    con->connectToHost();
}

void MainWindow::on_pushsend_clicked()
{
    if (nullptr != con)
    {
        if (con->state() == QSsh::SshConnection::Connected)
        {
            QString str(this->ui->lineEdit->text());
            str += "\r\n";
           m_shell.data()->write(str.toStdString().c_str());
        }
    }
}

void MainWindow::sshcon()
{
    m_shell = con->createRemoteShell();
    connect(m_shell.data(),&QSsh::SshRemoteProcess::started,[this](){this->ui->textEdit->append("SshRemoteProcess start succsess");});
    connect(m_shell.data(),&QSsh::SshRemoteProcess::readyReadStandardOutput,[this](){this->ui->textEdit->append(QString(this->m_shell.data()->readAllStandardOutput()));
    });
    connect(m_shell.data(),&QSsh::SshRemoteProcess::readyRead,[this](){this->ui->textEdit->append(QString(this->m_shell.data()->readAllStandardOutput()));});
    connect(m_shell.data(),&QSsh::SshRemoteProcess::readyReadStandardError,[this](){this->ui->textEdit->append(QString(this->m_shell.data()->readAll()));});
    connect(m_shell.data(),&QSsh::SshRemoteProcess::closed,[this](){this->ui->textEdit->append("SshRemoteProcess stop");});
    m_shell.data()->start();
}


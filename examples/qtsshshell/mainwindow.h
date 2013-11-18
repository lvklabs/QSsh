#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSsh>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void on_pushcon_clicked();
    void on_pushsend_clicked();
    void sshcon();

private:
    Ui::MainWindow *ui;
    QSsh::SshConnectionParameters par;
    QSsh::SshConnection * con;
    QSharedPointer<QSsh::SshRemoteProcess> m_shell;

};

#endif // MAINWINDOW_H

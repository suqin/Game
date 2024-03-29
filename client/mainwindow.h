#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QStringList>
#include <QtNetwork>
#include <QDataStream>
#include <QMap>
#include <QProcess>
#include "tcp.h"
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
    void on_login_clicked();
    void on_reg_clicked();
    void newUser(struct User *);
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);
    void DelUser(QString user);
    void startGameAsClient(QStringList *);
    void GameExited(int);

private:
    Ui::MainWindow *ui;
    Tcp *ServerSocket;
    QMap<QString, struct User *> map;
    QProcess *Game;
    QString MyName;
};

#endif // MAINWINDOW_H

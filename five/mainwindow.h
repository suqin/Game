#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QTextCodec>
#include <QMainWindow>
#include <QMessageBox>
#include <QPainter>
#include <QMouseEvent>
#include <QLabel>
#include <QVector>
#include "../Public.h"
#include "core.h"
#include "net.h"
#include "player.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0,
                        QString name = "debug",
                        QString add= "127.0.0.1",
                        QString port = "8910",
                        QString type = "5");
    ~MainWindow();
    void mousePressEvent(QMouseEvent *);
public slots:
    void d();
    void on_reset_clicked();
    void on_pushButton_clicked();
    void rec_data(QString *);
    void error(QString );
    void _startGame();
signals:
    void click();
private:
    Ui::MainWindow *ui;
    int x,y,_type;
    int color;
    QVector<QLabel *> labels;
    Core *core;
    Net *net;
    Player *player;
};

#endif // MAINWINDOW_H

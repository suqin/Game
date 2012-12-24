#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent,
                       QString name,
                       QString add,
                       QString port,
                       QString type) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    ui->setupUi(this);
    //if(type.toInt() == TYPE_SERVER)
    color = COLOR_BLACK;
    //else
    //    color = COLOR_WHITE;

    core= new Core();

    net = new Net(name,add,port,type.toInt());
    _type=type.toInt();
    player = new Player();
    connect(this,SIGNAL(click()),this,SLOT(d()));
    connect(net,SIGNAL(has_data(QString*)),
            this,SLOT(rec_data(QString*)));
    connect(net,SIGNAL(has_err(QString)),
            this,SLOT(error(QString)));
    connect(net,SIGNAL(startGame()),this,SLOT(_startGame()));
    if(_type == TYPE_SERVER)
        player->setcolor(COLOR_BLACK);
    else
        player->setcolor(COLOR_WHITE);
}
void MainWindow::mousePressEvent(QMouseEvent *e)
{
    //ui->label_4->setText(QString("%1--%2").arg(color).arg(player->getColor()));
    if(player->IsMyTurn(color)) {   //轮到当前玩家
        x=e->x();
        y=e->y();
        x=(x-200)/35;
        y=(y-102)/35;
        emit click();
    }
}
void MainWindow::d()
{
    QString buff;
    QLabel *l = new QLabel("you");
    labels.push_back(l);
    int resault;
    l->setParent(this);
    QPixmap black(":/img/black.jpg");
    QPixmap white(":/img/white.jpg");

    qDebug()<<x<<y;
    //坐标合法性检查
    if(x<SIZE && x>=0 && y <SIZE && y>=0) {
        resault=core->play(x,y,color);
        //打包要发送的数据
        if(x<10)
            buff+=QString("0%1").arg(x);
        else
            buff+=QString("%1").arg(x);
        if(y<10)
            buff+=QString("0%1").arg(y);
        else
            buff+=QString("%1").arg(y);

        if(resault) {//下棋成功 发送数据 绘制图标
            net->senddata(buff);
            if(color==COLOR_WHITE) {
                l->setPixmap(white);
                l->setGeometry(x*35+200,y*35+103,31,31);
                l->show();
                color=COLOR_BLACK;
            }
            else {
               l->setPixmap(black);
               l->setGeometry(x*35+200,y*35+103,31,31);
               l->show();
               color=COLOR_WHITE;
           }
        }
        if(resault == 2)
        {
            if(color==COLOR_BLACK) {
                QMessageBox box;
                box.setText(QString("白胜"));
                box.exec();
            }
            else {
                QMessageBox box;
                box.setText(QString("黑胜"));
                box.exec();
            }
            on_reset_clicked();
        }
    }
    update();
}
void MainWindow::on_reset_clicked() //重置
{
    color=COLOR_BLACK;
    for(int i=0;i<labels.size();i++)
        delete labels[i];
    labels.clear();
    core->reset();

}
void MainWindow::rec_data(QString *data) //接受到新数据
{
    qDebug()<<"main"<<*data;
    x=data->mid(0,2).toInt();
    y=data->mid(2,2).toInt();
    qDebug()<<"rec"<<x<<y;
    data->clear();
    emit click();
}
void MainWindow::error(QString err)
{
    on_reset_clicked();
    net->listen();
}
void MainWindow::_startGame()
{
    if(_type == TYPE_SERVER)
        player->setcolor(COLOR_BLACK);
    else
        player->setcolor(COLOR_WHITE);
    if(player->getColor()==-1)
        player->setcolor(COLOR_BLACK);
}
MainWindow::~MainWindow()
{
    delete core;
    delete net;
    delete player;
    delete ui;
}

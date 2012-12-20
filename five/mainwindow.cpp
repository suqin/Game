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
    //QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    ui->setupUi(this);
    color = COLOR_BLACK;
    connect(this,SIGNAL(click()),this,SLOT(d()));

    core= new Core();
    //qDebug()<<type;
    net = new Net(name,add,port,type);
    //qDebug()<<"ok1";
    player = new Player();
    connect(net,SIGNAL(has_data(QString*)),
            this,SLOT(rec_data(QString*)));
    connect(net,SIGNAL(has_err(QString)),
            this,SLOT(error(QString)));
    connect(net,SIGNAL(startGame()),
            this,SLOT(startGame()));
   /* if(net->IsListening())
        ui->label_4->setText("等待链接中...");*/
}
void MainWindow::mousePressEvent(QMouseEvent *e)
{
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
    if(ui->label_4->text()!="GameStart...") {
         ui->lineEdit->show();
         ui->pushButton->show();
         ui->reset->show();
    }
}
void MainWindow::rec_data(QString *data) //接受到新数据
{
    qDebug()<<"main"<<*data;
    x=data->mid(0,2).toInt();
    y=data->mid(2,2).toInt();
    qDebug()<<"rec"<<x<<y;
    emit click();
}
void MainWindow::error(QString err)
{

    ui->label_4->setText(err);
    on_reset_clicked();

    net->listen();
}
void MainWindow::startGame()
{
    player->setcolor(color);
    ui->label_4->setText("GameStart...");
    ui->lineEdit->hide();
    ui->pushButton->hide();
    ui->reset->hide();
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
void MainWindow::on_pushButton_clicked()
{
    if(net->connectto(ui->lineEdit->text()))
        player->setcolor(COLOR_WHITE);
}

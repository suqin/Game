#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QTextCodec::codecForName("UTF-8");
    ui->setupUi(this);
    ui->listWidget->hide();
    ServerSocket=NULL;
    Game=NULL;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_login_clicked()   //处理登录按钮
{
    ui->login->hide();
    if(ServerSocket==NULL)
    {
        qDebug()<<__FUNCTION__<<"create server socket";
        ServerSocket = new Tcp(this);
        QHostAddress add(GAMESERVERIP);
        ServerSocket->ConnectTo(&add,GAMESERVERPORT);
        connect(ServerSocket,SIGNAL(startGame(QStringList*)),this,SLOT(startGameAsClient(QStringList*)));
        //将启动游戏信号与启动函数连接起来
        connect(ServerSocket,SIGNAL(newUser(User*)),this,SLOT(newUser(User*)));
        //将上线信号发给用户窗口
    }
    if(ServerSocket->isOpen())
    {
        MyName = ui->name->text();
        if(!ServerSocket->login(ui->name->text(),ui->passwd->text()))
        {
            ui->info->setText("登录失败");
            ServerSocket->deleteLater();
            ServerSocket=NULL;
            ui->login->show();
            return ;
        }
        ui->widget->hide();
        ui->listWidget->show();//显示用户列表窗口
    }
    connect(ServerSocket,SIGNAL(delU(QString)),this,SLOT(DelUser(QString)));

    //connect()

}
//向界面里添加新的用户用户信息由TCP填写
void MainWindow::newUser(struct User *user)
{
    if(user->name!=MyName)
    {
        qDebug()<<user->name<<MyName;
        map.insert(user->name,user);
        ui->listWidget->addItem(user->name);
    }
}
void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)  //双击用户启动游戏
{
    if(Game!=NULL)
        return;
    struct User *temp;

    temp = map[item->text()];
    QString _port=QString("%1").arg(temp->port);
    QString _type= QString("%1").arg(TYPE_SERVER);
    QStringList arguments;
    arguments.append(temp->name);
    arguments.append(temp->add.toString());
    arguments.append(_port);
    arguments.append(_type);
    qDebug()<<__FUNCTION__<<arguments;
    Game = new QProcess(this);
    Game->start(PATHTOGAME,arguments);
    connect(Game,SIGNAL(finished(int)),this,SLOT(GameExited(int)));
    //游戏的结束信号和处理函数连接

}
void MainWindow::startGameAsClient(QStringList *list)//list 在Tcp中定义
{
    if(Game!=NULL)
        return;
    else
    {
        qDebug()<<__FUNCTION__<<*list;
        Game = new QProcess(this);
        Game->start(PATHTOGAME,*list);
        connect(Game,SIGNAL(finished(int)),this,SLOT(GameExited(int)));
        delete list;
    }
}
void MainWindow::GameExited(int code)
{
    Game->deleteLater();
    Game = NULL;
    qDebug()<<__FUNCTION__<<"exited"<<code;
}


void MainWindow::DelUser(QString user)
{

    (ui->listWidget->findItems(user,Qt::MatchExactly).first())->setHidden(1);
    ui->listWidget->update();
    this->update();//刷新
}
void MainWindow::on_reg_clicked()
{
    ui->reg->hide();
    if(ServerSocket==NULL) //如果与服务器相连的套接字没有建立
    {
        ServerSocket = new Tcp(this);
        QHostAddress add(GAMESERVERIP);
        ServerSocket->ConnectTo(&add,GAMESERVERPORT);
        connect(ServerSocket,SIGNAL(newUser(User*)),this,SLOT(newUser(User*)));
    }
    if(ServerSocket->isOpen())
    {
        MyName = ui->name->text();
        if(!ServerSocket->reg(ui->name->text(),ui->passwd->text()))
        {
            ui->info->setText("error");
            delete ServerSocket;
            ServerSocket=NULL;
            ui->reg->show();
            return ;
        }
        ui->info->setText("注册成功");

    }
}

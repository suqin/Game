#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->listWidget->hide();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_login_clicked()   //处理登录按钮
{
    ui->login->hide();
    ServerSocket = new Tcp(this);
    QHostAddress add(GAMESERVERIP);
    ServerSocket->ConnectTo(&add,GAMESERVERPORT);
    connect(ServerSocket,SIGNAL(newUser(User*)),this,SLOT(newUser(User*)));
    if(ServerSocket->isOpen())
    {
        if(!ServerSocket->login(ui->name->text(),ui->passwd->text()))
        {
            ui->info->setText("error");
            delete ServerSocket;
            ui->login->show();
            return ;
        }
        ui->widget->hide();
        ui->listWidget->show();
    }

}

void MainWindow::newUser(struct User *user)  //向界面里添加新的用户
{
    map.insert(user->name,user);
    ui->listWidget->addItem(user->name);
}
void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)  //双击用户启动游戏
{
    /*QStringList argvs;
    argvs<<item->text()
         <<map[item->text()]->add.toString()
         <<QString("%1").arg(map[item->text()]->port)
         <<QString("%1").arg(TYPE_SERVER);
    Game = new  QProcess(this);
    Game->start(PATHTOFIVE,argvs);*/
    //ServerSocket->Send_Game_Req(item->text());
}

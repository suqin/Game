#include <QDebug>

#define PATHTOGAME "dasd.exe"

#define GAMESERVERIP "127.0.0.1"
#define DBSERVERIP "127.0.0.1"
#define GAMESERVERPORT 8910
#define DBSERVERPORT 8911
#define GAMEPORT 8912
#define WAITTIME 5000

#define MAXCONNECTION 10  //最大连接数
#define MAXBUFFSIZE 1024  //最长消息长度
#define MAX_STR_LEN 20

#define SUCCEED 0
#define FAULT 1

#define CMD_LOGIN 2
#define CMD_REG 10
#define CMD_GET_LIST 3
#define CMD_GAME_REQ 4
#define CMD_DEL_USER 5
#define CMD_ADD_USER 9


#define VAL_USER 6


#define TYPE_CLIENT 7
#define TYPE_SERVER 8

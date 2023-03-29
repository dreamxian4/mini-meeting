#pragma once


#define _DEF_BUFFER  ( 4096 )
#define _DEF_CONTENT_SIZE	(1024)
#define _MAX_SIZE	(40)

//自定义协议   先写协议头 再写协议结构
//登录 注册 获取好友信息 添加好友 聊天 发文件 下线请求
#define _DEF_PROTOCOL_BASE	(10000)
#define _DEF_PROTOCOL_COUNT (100)

//注册
#define _DEF_PACK_REGISTER_RQ	(_DEF_PROTOCOL_BASE + 0 )
#define _DEF_PACK_REGISTER_RS	(_DEF_PROTOCOL_BASE + 1 )
//登录
#define _DEF_PACK_LOGIN_RQ	(_DEF_PROTOCOL_BASE + 2 )
#define _DEF_PACK_LOGIN_RS	(_DEF_PROTOCOL_BASE + 3 )
//好友信息
#define _DEF_PACK_FRIEND_INFO	(_DEF_PROTOCOL_BASE + 4 )
//添加好友
#define _DEF_PACK_ADDFRIEND_RQ	(_DEF_PROTOCOL_BASE + 5 )
#define _DEF_PACK_ADDFRIEND_RS	(_DEF_PROTOCOL_BASE + 6 )
//聊天
#define _DEF_PACK_CHAT_RQ	(_DEF_PROTOCOL_BASE + 7 )
#define _DEF_PACK_CHAT_RS	(_DEF_PROTOCOL_BASE + 8 )
//离线
#define _DEF_PACK_OFFLINE_RQ	(_DEF_PROTOCOL_BASE + 9 )

//返回的结果
//注册请求的结果
#define user_is_exist		(0)
#define register_success	(1)
//登录请求的结果
#define user_not_exist		(0)
#define password_error		(1)
#define login_success		(2)
//添加好友的结果
#define no_this_user		(0)
#define user_refuse			(1)
#define user_offline		(2)
#define add_success			(3)

typedef int PackType;

//协议结构
//注册
typedef struct STRU_REGISTER_RQ
{
	STRU_REGISTER_RQ():type(_DEF_PACK_REGISTER_RQ)
	{
		memset( tel  , 0, sizeof(tel));
		memset( name  , 0, sizeof(name));
		memset( password , 0, sizeof(password) );
	}
	//需要手机号码 , 密码, 昵称
	PackType type;
	char tel[_MAX_SIZE];
	char name[_MAX_SIZE];
	char password[_MAX_SIZE];

}STRU_REGISTER_RQ;

typedef struct STRU_REGISTER_RS
{
	//回复结果
	STRU_REGISTER_RS(): type(_DEF_PACK_REGISTER_RS) , result(register_success)
	{
	}
	PackType type;
	int result;

}STRU_REGISTER_RS;

//登录
typedef struct STRU_LOGIN_RQ
{
	//登录需要: 手机号 密码 
	STRU_LOGIN_RQ():type(_DEF_PACK_LOGIN_RQ)
	{
		memset( tel , 0, sizeof(tel) );
		memset( password , 0, sizeof(password) );
	}
	PackType type;
	char tel[_MAX_SIZE];
	char password[_MAX_SIZE];

}STRU_LOGIN_RQ;

typedef struct STRU_LOGIN_RS
{
	// 需要 结果 , 用户的id
	STRU_LOGIN_RS(): type(_DEF_PACK_LOGIN_RS) , result(login_success),userid(0)
	{
	}
	PackType type;
	int result;
	int userid;

}STRU_LOGIN_RS;

//好友信息
typedef struct STRU_FRIEND_INFO
{
	STRU_FRIEND_INFO():type(_DEF_PACK_FRIEND_INFO) , userid(0) , iconid(0) , state(0) 
	{
		memset( name ,  0 , sizeof(name) );
		memset( feeling , 0 , sizeof(feeling));
	}
	//需要 用户id 头像id 昵称 签名 状态--是否在线
	PackType type;
	int userid;
	int iconid;
	int state;
	char name[_MAX_SIZE];
	char feeling[_MAX_SIZE];

}STRU_FRIEND_INFO;

//添加好友
typedef struct STRU_ADD_FRIEND_RQ
{
	// 如果用户1 添加用户2 为好友 需要 用户1 id 用户1 名字 ,用户2的名字
	STRU_ADD_FRIEND_RQ():type(_DEF_PACK_ADDFRIEND_RQ) , userid(0)
	{
		memset( userName  , 0 , sizeof(userName));
		memset( friendName , 0 , sizeof(friendName));
	}
	PackType type;
	int userid;
	char userName[_MAX_SIZE];
	char friendName[_MAX_SIZE];

}STRU_ADD_FRIEND_RQ;

typedef struct STRU_ADD_FRIEND_RS
{
	STRU_ADD_FRIEND_RS():type(_DEF_PACK_ADDFRIEND_RS) , userid(0), friendid(0),result(add_success)
	{
		memset( friendName  , 0 , sizeof(friendName));
	}
	//如果用户1 添加用户2 需要 用户1id  用户2 id 用户2的名字 结果
	PackType type;
	int userid; // 用户1
	int friendid; // 用户2
	int result;
	char friendName[_MAX_SIZE];
	
}STRU_ADD_FRIEND_RS;

//聊天
typedef struct STRU_CHAT_RQ
{
	STRU_CHAT_RQ():type(_DEF_PACK_CHAT_RQ) , userid(0) , friendid(0)
	{
		memset( content , 0 , _DEF_CONTENT_SIZE );
	}
	// 谁发给谁 服务器转发  用户1 id 用户2 id 发的内容
	PackType type;
	int userid;
	int friendid;
	char content[_DEF_CONTENT_SIZE];

}STRU_CHAT_RQ;

typedef struct STRU_CHAT_RS
{
	STRU_CHAT_RS():type(_DEF_PACK_CHAT_RS) , userid(0) , friendid(0),result(0)
	{
	}
	PackType type;
	int userid;
	int friendid; //方便找是哪个人不在线
	int result;

}STRU_CHAT_RS;

//发给服务器说明离线
typedef struct STRU_OFFLINE
{
    STRU_OFFLINE():type(_DEF_PACK_OFFLINE_RQ) , userid(0)
    {
    }
    PackType type;
    int userid;

}STRU_OFFLINE;

// 数据库
/*
	表1 用户表 id->唯一标识 tel  password  name  iconid   feeling 也可以写成两张表 登录和用户信息
	列:  id  tel password  name  iconid  feeling

	表2 好友  idA  idB
	列 idA  idB  
	操作: 好友关系是双向关系  关注是单向关系  , 添加好友时 , 需要写入两行 即 A->B B->A 方便查询
	(添加好友 查找一般比插入多)

//	表3 离线消息
	
	用户数据表t_user
	create table t_user ( id bigint unsigned  AUTO_INCREMENT primary key, tel varchar (260) , 
	password varchar(260)  , name varchar (260) , icon int , feeling varchar(260));

	可以添加测试数据 
	insert into t_user ( tel,password , name , icon , feeling  ) 
	values ('12345','test', '12345' ,1,'比较懒,什么也没写')

	好友表 t_friend
	create table t_friend ( idA bigint unsigned  , idB bigint unsigned);

*/









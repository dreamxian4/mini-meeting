#include "clogic.h"


void CLogic::setNetPackMap()
{
    NetPackMap(DEF_PACK_REGISTER_RQ)    = &CLogic::RegisterRq;
    NetPackMap(DEF_PACK_LOGIN_RQ)       = &CLogic::LoginRq;
    NetPackMap(DEF_PACK_CREATEROOM_RQ)  = &CLogic::CreateRoomRq;
    NetPackMap(DEF_PACK_JOINROOM_RQ)    = &CLogic::JoinRoomRq;
}

//注册
void CLogic::RegisterRq(sock_fd clientfd,char* szbuf,int nlen)
{
    printf("clientfd:%d RegisterRq\n", clientfd);
    //拆包
    STRU_REGISTER_RQ *rq=(STRU_REGISTER_RQ*)szbuf;

    //查数据库，有没有号码，
    list<string>lstRes;
    char strsql[1024];
    sprintf(strsql,"select tel from t_user where tel='%s'",rq->m_tel);
    m_sql->SelectMysql(strsql,1,lstRes);

    STRU_REGISTER_RS rs;
    //如果有，已存在，如果没有，注册成功
    if(lstRes.size()>0){
        rs.m_lResult=tel_is_exist;
    }else{
        rs.m_lResult=register_success;
        sprintf(strsql,"insert into t_user(tel,password,name,icon,feeling)values('%s','%s','%s',5,'happy')",rq->m_tel,rq->m_password,rq->m_tel);
        if(!m_sql->UpdataMysql(strsql)){
            printf("update fail:%s\n",strsql);
        }
    }
    SendData(clientfd,(char*)&rs,sizeof(rs));
}

//登录
void CLogic::LoginRq(sock_fd clientfd ,char* szbuf,int nlen)
{
    printf("clientfd:%d LoginRq\n", clientfd);

    //拆包
    STRU_LOGIN_RQ *rq=(STRU_LOGIN_RQ*)szbuf;

    //查数据库，有没有号码，
    list<string>lstRes;
    char strsql[1024];
    sprintf(strsql,"select id,password from t_user where tel='%s'",rq->m_tel);
    bool res=m_sql->SelectMysql(strsql,2,lstRes);
    if(!res)printf("select error:%s\n",strsql);

    STRU_LOGIN_RS rs;
    if(lstRes.size()>0){
        //如果有，判断密码是否正确
        int id=atoi(lstRes.front().c_str());
        lstRes.pop_front();
        string strPass=lstRes.front();
        lstRes.pop_front();
        if(strcmp(strPass.c_str(),rq->m_password)==0){
            //正确，登录成功
            rs.m_lResult=login_success;
            rs.m_userid=id;
            //id->socket 为了方便以后转发通信
            UserInfo* user=NULL;
            if(m_mapIdToUserInfo.find(id,user)){
                //查到了
                //要不要强制上一个人下线
                //写一个协议包
                //find会完成赋值
                delete user;
            }
            //没查到
            user=new UserInfo;

            user->m_id=id;
            user->m_sockfd=clientfd;
            m_mapIdToUserInfo.insert(id,user);

            SendData( clientfd , (char*)&rs , sizeof rs );
            //同步这个人的状态信息，让登录者知道自己的info
            //聊天软件-》好友列表，离线信息	多媒体-》媒体列表	微博-》推送信息
            return;
        }else{
            //错误，密码不正确
            rs.m_lResult=password_error;
        }
    }else{
        //没有，用户不存在
        rs.m_lResult=user_not_exist;
    }

    SendData( clientfd , (char*)&rs , sizeof rs );
}

//创建房间
void CLogic::CreateRoomRq(sock_fd clientfd, char *szbuf, int nlen)
{
    printf("clientfd:%d CreateRoomRq\n", clientfd);
    STRU_CREATEROOM_RQ* rq=(STRU_CREATEROOM_RQ*)szbuf;
    int roomid=0;
    do{
        roomid=random()%899999+100000;
    }while(m_mapRoomIDToUserList.IsExist(roomid));
    printf("roomid:%d\n",roomid);
    list<int>lst;
    lst.push_back(rq->m_UserID);
    m_mapRoomIDToUserList.insert(roomid,lst);

    //回复
    STRU_CREATEROOM_RS rs;
    rs.m_RoomId=roomid;
    rs.m_lResult=1;
    SendData(clientfd,(char*)&rs,sizeof(rs));
}

//加入房间
void CLogic::JoinRoomRq(sock_fd clientfd, char *szbuf, int nlen)
{

}

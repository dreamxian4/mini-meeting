#include "clogic.h"


void CLogic::setNetPackMap()
{
    NetPackMap(DEF_PACK_REGISTER_RQ)    = &CLogic::RegisterRq;
    NetPackMap(DEF_PACK_LOGIN_RQ)       = &CLogic::LoginRq;
    NetPackMap(DEF_PACK_CREATEROOM_RQ)  = &CLogic::CreateRoomRq;
    NetPackMap(DEF_PACK_JOINROOM_RQ)    = &CLogic::JoinRoomRq;
    NetPackMap(DEF_PACK_USER_INFO)      = &CLogic::UserInfoRq;
    NetPackMap(DEF_PACK_LEAVEROOM_RQ)   = &CLogic::LeaveRoomRq;
    NetPackMap(DEF_PACK_AUDIO_FRAME)   = &CLogic::AudioFrame;
    NetPackMap(DEF_PACK_VIDEO_FRAME)   = &CLogic::VideoFrame;
}

void CLogic::GetUserInfoAndSend(int id){
    //获取信息
    char sqlstr[1024]="";
    sprintf(sqlstr,"select name,icon,feeling from t_user where id=%d",id);
    list<string>lst;
    m_sql->SelectMysql(sqlstr,3,lst);
    if(lst.size()!=3)return;
    string name=lst.front();
    lst.pop_front();
    string iconid=lst.front();
    lst.pop_front();
    string feeling=lst.front();
    lst.pop_front();
    //设置信息
    UserInfo* user=nullptr;
    if(!m_mapIdToUserInfo.find(id,user))return;
    strcpy(user->m_userName,name.c_str());
    //发送给客户端
    STRU_USER_INFO_RQ rq;
    rq.m_UserID=id;
    rq.m_iconid=atoi(iconid.c_str());
    strcpy(rq.m_szUser,name.c_str());
    strcpy(rq.m_userFeeling,feeling.c_str());
    SendData(user->m_sockfd,(char*)&rq,sizeof(rq));
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
            GetUserInfoAndSend(id);
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
    printf("clientfd:%d JoinRoomRq\n", clientfd);
    //拆包
    STRU_JOINROOM_RQ* rq=(STRU_JOINROOM_RQ*)szbuf;
    STRU_JOINROOM_RS rs;
    //判断房间是否存在
    list<int>lst;
    rs.m_RoomID=rq->m_RoomID;
    if(!m_mapRoomIDToUserList.find(rq->m_RoomID,lst)){
        //不存在，返回结果
        rs.m_lResult=room_no_exist;
    }else{
        //存在，返回结果
        rs.m_lResult=join_success;
    }
    SendData(clientfd,(char*)&rs,sizeof(rs));
    UserInfo* joinInfo=nullptr;
    if(!m_mapIdToUserInfo.find(rq->m_UserID,joinInfo))return;

    //加入人信息
    STRU_ROOM_MEMBER_RQ joinrq;
    joinrq.m_UserID=rq->m_UserID;
    strcpy(joinrq.m_szUser,joinInfo->m_userName);
    //获取房间列表 lst
    //遍历房间成员列表拿到每个人信息
    for(auto ite=lst.begin();ite!=lst.end();ite++){
        int memid=*ite;
        UserInfo* memInfo=nullptr;
        if(!m_mapIdToUserInfo.find(memid,memInfo)){
            continue;
        }
        //成员信息
        STRU_ROOM_MEMBER_RQ memrq;
        memrq.m_UserID=memid;
        strcpy(memrq.m_szUser,memInfo->m_userName);
        //加入者信息，发给房间每个人
        SendData(memInfo->m_sockfd,(char*)&joinrq,sizeof(joinrq));
        //房间成员信息发送给加入者
        SendData(clientfd,(char*)&memrq,sizeof(memrq));
    }
    //加入者添加到房间成员列表
    lst.push_back(joinrq.m_UserID);
    //更新map节点
    m_mapRoomIDToUserList.insert(rq->m_RoomID,lst);
}

//设置个人信息
void CLogic::UserInfoRq(sock_fd clientfd, char *szbuf, int nlen)
{
    printf("clientfd:%d UserInfoRq\n", clientfd);
    //拆包
    STRU_USER_INFO_RQ* rq=(STRU_USER_INFO_RQ*)szbuf;
    //mysql修改信息
    char strsql[1024];
    sprintf(strsql,"update t_user set icon=%d,name='%s',feeling='%s' where id=%d",
            rq->m_iconid,rq->m_szUser,rq->m_userFeeling,rq->m_UserID);
    m_sql->UpdataMysql(strsql);
    GetUserInfoAndSend(rq->m_UserID);
}

//退出房间
void CLogic::LeaveRoomRq(sock_fd clientfd, char *szbuf, int nlen)
{
    printf("clientfd:%d LeaveRoomRq\n", clientfd);
    //拆包
    STRU_LEAVEROOM_RQ* rq=(STRU_LEAVEROOM_RQ*)szbuf;
    list<int>lst;
    if(!m_mapRoomIDToUserList.find(rq->m_RoomId,lst))return;
    //根据房间id 获取列表 发给房间里每个人
    for(auto ite=lst.begin();ite!=lst.end();){
        int id=*ite;
        if(id==rq->m_nUserId)ite=lst.erase(ite);//该人从列表移出
        else{
            //转发
            UserInfo *user=nullptr;
            if(!m_mapIdToUserInfo.find(id,user))continue;
            SendData(user->m_sockfd,szbuf,nlen);
            ite++;
        }
    }
    //列表为空，map中移出
    if(lst.size()==0){
        m_mapRoomIDToUserList.erase(rq->m_RoomId);
    }else{
        m_mapRoomIDToUserList.insert(rq->m_RoomId,lst);
    }
}

//音频
void CLogic::AudioFrame(sock_fd clientfd, char *szbuf, int nlen)
{
    printf("clientfd:%d AudioFrame\n", clientfd);
    //拆包
    char* tmp=szbuf;
    //反序列化
    tmp+=sizeof(int);
    int userid=*(int*)tmp;//按照四个字节读
    tmp+=sizeof(int);
    int roomid=*(int*)tmp;
    //roomid->列表
    list<int>lst;
    if(!m_mapRoomIDToUserList.find(roomid,lst))return;
    for(auto ite=lst.begin();ite!=lst.end();ite++){
        int id=*ite;
        if(id!=userid){
            //转发
            UserInfo* user=nullptr;
            if(!m_mapIdToUserInfo.find(userid,user))continue;
            SendData(user->m_sockfd,szbuf,nlen);
        }
    }
}

//视频
void CLogic::VideoFrame(sock_fd clientfd, char *szbuf, int nlen)
{
    //拆包
    char* tmp=szbuf;
    //反序列化
    tmp+=sizeof(int);
    int userid=*(int*)tmp;//按照四个字节读
    tmp+=sizeof(int);
    int roomid=*(int*)tmp;
    //roomid->列表
    list<int>lst;
    if(!m_mapRoomIDToUserList.find(roomid,lst))return;
    for(auto ite=lst.begin();ite!=lst.end();ite++){
        int id=*ite;
        if(id!=userid){
            //转发
            UserInfo* user=nullptr;
            if(!m_mapIdToUserInfo.find(id,user))continue;
            printf("fasong\n");
            SendData(user->m_sockfd,szbuf,nlen);
        }
    }
}

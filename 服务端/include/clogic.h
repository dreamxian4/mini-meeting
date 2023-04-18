#ifndef CLOGIC_H
#define CLOGIC_H

#include"TCPKernel.h"

class CLogic
{
public:
    CLogic( TcpKernel* pkernel )
    {
        m_pKernel = pkernel;
        m_sql = pkernel->m_sql;
        m_tcp = pkernel->m_tcp;
    }
public:
    //设置协议映射
    void setNetPackMap();
    /************** 发送数据*********************/
    void SendData( sock_fd clientfd, char*szbuf, int nlen )
    {
        m_pKernel->SendData( clientfd ,szbuf , nlen );
    }
    void GetUserInfoAndSend(int id);
    /************** 网络处理 *********************/
    //注册
    void RegisterRq(sock_fd clientfd, char*szbuf, int nlen);
    //登录
    void LoginRq(sock_fd clientfd, char*szbuf, int nlen);
    //创建房间
    void CreateRoomRq(sock_fd clientfd, char*szbuf, int nlen);
    //加入房间
    void JoinRoomRq(sock_fd clientfd, char*szbuf, int nlen);
    //设置个人信息
    void UserInfoRq(sock_fd clientfd, char*szbuf, int nlen);
    //退出房间
    void LeaveRoomRq(sock_fd clientfd, char*szbuf, int nlen);
    //音频
    void AudioFrame(sock_fd clientfd, char*szbuf, int nlen);
    //视频
    void VideoFrame(sock_fd clientfd, char*szbuf, int nlen);

    /*******************************************/

private:
    TcpKernel* m_pKernel;
    CMysql * m_sql;
    Block_Epoll_Net * m_tcp;

    //加映射关系 id-userinfo
    MyMap<int,UserInfo*>m_mapIdToUserInfo;
    //room-member
    MyMap<int,list<int>>m_mapRoomIDToUserList;
};

#endif // CLOGIC_H

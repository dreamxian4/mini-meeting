#include "clogic.h"

void CLogic::setNetPackMap()
{
    NetPackMap(DEF_PACK_REGISTER_RQ)    = &CLogic::RegisterRq;
    NetPackMap(DEF_PACK_LOGIN_RQ)       = &CLogic::LoginRq;
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

//    STRU_LOGIN_RS rs;
//    rs.m_lResult = password_error;
//    SendData( clientfd , (char*)&rs , sizeof rs );
}

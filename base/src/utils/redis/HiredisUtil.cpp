#include "HiredisUtil.h"

CRedisConn::CRedisConn(const char *server_ip, int server_port, const char *szPasswd, int db_num)
{
    m_server_ip = server_ip;
    m_server_port = server_port;
    m_db_num = db_num;
    m_pContext = NULL;
    m_last_connect_time = 0;
    if (szPasswd != NULL)
    {
        m_password = szPasswd;
    }
}

CRedisConn::~CRedisConn()
{
    if (m_pContext)
    {
        redisFree(m_pContext);
        m_pContext = NULL;
    }
}

/*
 * redis初始化连接和重连操作，类似mysql_ping()
 */
int CRedisConn::Init()
{
    if (m_pContext)
    {
        return 0;
    }
    // 4s 尝试重连一次
    time_t cur_time = (time_t)time(NULL);
    if (cur_time < m_last_connect_time + 4)
    {
        return 1;
    }
    m_last_connect_time = cur_time;
    // 200ms超时
    struct timeval timeout = {0, 200000};
    m_pContext = redisConnectWithTimeout(m_server_ip.c_str(), m_server_port, timeout);
    if (!m_pContext || m_pContext->err)
    {
        if (m_pContext)
        {
            //REPORT_EVENT(LOG_CRITICAL, "redis init", "redisConnect failed %s, In Line %d of File %s", m_pContext->errstr, __LINE__, __FILE__);
            redisFree(m_pContext);
            m_pContext = NULL;
        }
        else
        {
            //REPORT_EVENT(LOG_CRITICAL, "redis init", "redisConnect failed");
        }
        return 1;
    }
    if (m_password.length() > 0)
    {
        redisReply *reply = (redisReply *)redisCommand(m_pContext, "AUTH %s", m_password.c_str());
        if (reply->type == REDIS_REPLY_ERROR)
        {
            //REPORT_EVENT(LOG_CRITICAL, "redis init", "redis auth failed");
            redisFree(m_pContext);
            m_pContext = NULL;
            return 1;
        }
        freeReplyObject(reply);
    }

    redisReply *reply = (redisReply *)redisCommand(m_pContext, "SELECT %d", m_db_num);
    if (reply && (reply->type == REDIS_REPLY_STATUS) && (strncmp(reply->str, "OK", 2) == 0))
    {
        freeReplyObject(reply);
        return 0;
    }
    else
    {
        //REPORT_EVENT(LOG_CRITICAL, "redis init", "select cache db failed");
        return 2;
    }
    return 0;
}

char *get_int(int s)
{
    static char s_buff_int[64];
    sprintf(s_buff_int, "%d", s);
    return s_buff_int;
}

char *get_int64(long long v)
{
    static char s_buff_int64[64];
    sprintf(s_buff_int64, "%I64d", v);
    return s_buff_int64;
}

char *get_float(double v)
{
    static char s_buff_float[64];
    sprintf(s_buff_float, "%f", v);
    return s_buff_float;
}

string &CRedisConn::get(const char *key, string &value, string *pCmd)
{
    if (pCmd != NULL)
    {
        *pCmd = "GET ";
        *pCmd += key;
        return value;
    }
    if (Init())
    {
        return value;
    }
    redisReply *reply = (redisReply *)redisCommand(m_pContext, "GET %s", key);
    if (!reply)
    {
        //REPORT_EVENT(LOG_CRITICAL, "redis get", "redisCommand failed:%s", m_pContext->errstr);
        redisFree(m_pContext);
        m_pContext = NULL;
        return value;
    }

    if (reply->type == REDIS_REPLY_STRING)
    {
        value.append(reply->str, reply->len);
    }

    freeReplyObject(reply);
    return value;
}

string &CRedisConn::setex(const char *key, const char *value, int timeout, string &ret_value, string *pCmd)
{
    if (pCmd != NULL)
    {
        *pCmd = "SETEX ";
        *pCmd += key;
        *pCmd += " ";
        *pCmd += get_int(timeout);
        *pCmd += " ";
        *pCmd += value;
        return ret_value;
    }

    if (Init())
    {
        return ret_value;
    }

    redisReply *reply = (redisReply *)redisCommand(m_pContext, "SETEX %s %d %s", key, timeout, value);
    if (!reply)
    {
        //REPORT_EVENT(LOG_CRITICAL, "redis setex", "redisCommand failed:%s", m_pContext->errstr);
        redisFree(m_pContext);
        m_pContext = NULL;
        return ret_value;
    }

    ret_value.append(reply->str, reply->len);
    freeReplyObject(reply);
    return ret_value;
}

string &CRedisConn::set(const char *key, const char *value, string &ret_value, string *pCmd)
{
    if (pCmd != NULL)
    {
        *pCmd = "SET ";
        *pCmd += key;
        *pCmd += " ";
        *pCmd += value;
        return ret_value;
    }

    if (Init())
    {
        return ret_value;
    }

    redisReply *reply = (redisReply *)redisCommand(m_pContext, "SET %s %s", key, value);
    if (!reply)
    {
        //REPORT_EVENT(LOG_CRITICAL, "redis set", "redisCommand failed:%s", m_pContext->errstr);
        redisFree(m_pContext);
        m_pContext = NULL;
        return ret_value;
    }

    ret_value.append(reply->str, reply->len);
    freeReplyObject(reply);
    return ret_value;
}

bool CRedisConn::exists(const char *key, string *pCmd)
{
    if (pCmd != NULL)
    {
        *pCmd = "EXISTS ";
        *pCmd += key;
        return true;
    }

    if (Init())
    {
        return false;
    }

    redisReply *reply = (redisReply *)redisCommand(m_pContext, "EXISTS %s", key);
    if (!reply)
    {
        //REPORT_EVENT(LOG_CRITICAL, "redis exists", "redisCommand failed:%s", m_pContext->errstr);
        redisFree(m_pContext);
        m_pContext = NULL;
        return false;
    }

    long ret_value = reply->integer;
    freeReplyObject(reply);
    if (0 == ret_value)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool CRedisConn::mget(const vector<string> &keys, vector<string> &values, string *pCmd)
{
    if (keys.empty())
    {
        return false;
    }

    string strKey;
    bool bFirst = true;
    for (vector<string>::const_iterator it = keys.begin(); it != keys.end(); ++it)
    {
        if (bFirst)
        {
            bFirst = false;
            strKey = *it;
        }
        else
        {
            strKey += " " + *it;
        }
    }

    if (strKey.empty())
    {
        return false;
    }
    strKey = "MGET " + strKey;

    if (pCmd != NULL)
    {
        *pCmd = strKey;
        return true;
    }

    if (Init())
    {
        return false;
    }

    redisReply *reply = (redisReply *)redisCommand(m_pContext, strKey.c_str());
    if (!reply)
    {
        //REPORT_EVENT(LOG_CRITICAL, "redis mget", "redisCommand failed:%s", m_pContext->errstr);
        redisFree(m_pContext);
        m_pContext = NULL;
        return false;
    }
    if (reply->type == REDIS_REPLY_ARRAY)
    {
        for (size_t i = 0; i < reply->elements; ++i)
        {
            redisReply *child_reply = reply->element[i];
            if (child_reply->type == REDIS_REPLY_STRING)
            {
                values.push_back(child_reply->str);
            }
        }
    }
    freeReplyObject(reply);
    return true;
}

long CRedisConn::hdel(const char *key, const char *field, string *pCmd)
{
    if (pCmd != NULL)
    {
        *pCmd = "HDEL ";
        *pCmd += key;
        *pCmd += " ";
        *pCmd += field;
        return 0;
    }

    if (Init())
    {
        return 0;
    }

    redisReply *reply = (redisReply *)redisCommand(m_pContext, "HDEL %s %s", key, field);
    if (!reply)
    {
        //REPORT_EVENT(LOG_CRITICAL, "redis hdel", "redisCommand failed:%s", m_pContext->errstr);
        redisFree(m_pContext);
        m_pContext = NULL;
        return 0;
    }

    long ret_value = reply->integer;
    freeReplyObject(reply);
    return ret_value;
}

string &CRedisConn::hget(const char *key, const char *field, string &ret_value, string *pCmd)
{
    if (pCmd != NULL)
    {
        *pCmd = "HGET ";
        *pCmd += key;
        *pCmd += " ";
        *pCmd += field;
        return ret_value;
    }

    if (Init())
    {
        return ret_value;
    }

    redisReply *reply = (redisReply *)redisCommand(m_pContext, "HGET %s %s", key, field);
    if (!reply)
    {
        //REPORT_EVENT(LOG_CRITICAL, "redis hget", "redisCommand failed:%s", m_pContext->errstr);
        redisFree(m_pContext);
        m_pContext = NULL;
        return ret_value;
    }

    if (reply->type == REDIS_REPLY_STRING)
    {
        ret_value.append(reply->str, reply->len);
    }

    freeReplyObject(reply);
    return ret_value;
}

bool CRedisConn::hgetAll(const char *key, map<string, string> &ret_value, string *pCmd)
{
    if (pCmd != NULL)
    {
        *pCmd = "HGETALL ";
        *pCmd += key;
        return true;
    }

    if (Init())
    {
        return false;
    }

    redisReply *reply = (redisReply *)redisCommand(m_pContext, "HGETALL %s", key);
    if (!reply)
    {
        //REPORT_EVENT(LOG_CRITICAL, "redis hgetall", "redisCommand failed:%s", m_pContext->errstr);
        redisFree(m_pContext);
        m_pContext = NULL;
        return false;
    }

    if ((reply->type == REDIS_REPLY_ARRAY) && (reply->elements % 2 == 0))
    {
        for (size_t i = 0; i < reply->elements; i += 2)
        {
            redisReply *field_reply = reply->element[i];
            redisReply *value_reply = reply->element[i + 1];
            string field(field_reply->str, field_reply->len);
            string value(value_reply->str, value_reply->len);
            ret_value.insert(make_pair(field, value));
        }
    }

    freeReplyObject(reply);
    return true;
}

long CRedisConn::hset(const char *key, const char *field, const char *value, string *pCmd)
{
    if (pCmd != NULL)
    {
        *pCmd = "HSET ";
        *pCmd += key;
        *pCmd += " ";
        *pCmd += field;
        *pCmd += " ";
        *pCmd += value;
        return true;
    }

    if (Init())
    {
        return -1;
    }

    redisReply *reply = (redisReply *)redisCommand(m_pContext, "HSET %s %s %s", key, field, value);
    if (!reply)
    {
        //REPORT_EVENT(LOG_CRITICAL, "redis hset", "redisCommand failed:%s", m_pContext->errstr);
        redisFree(m_pContext);
        m_pContext = NULL;
        return -1;
    }

    long ret_value = reply->integer;
    freeReplyObject(reply);
    return ret_value;
}

long CRedisConn::hincrBy(const char *key, const char *field, long value)
{
    if (Init())
    {
        return -1;
    }

    redisReply *reply = (redisReply *)redisCommand(m_pContext, "HINCRBY %s %s %ld", key, field, value);
    if (!reply)
    {
        //REPORT_EVENT(LOG_CRITICAL, "redis hincrby", "redisCommand failed:%s", m_pContext->errstr);
        redisFree(m_pContext);
        m_pContext = NULL;
        return -1;
    }

    long ret_value = reply->integer;
    freeReplyObject(reply);
    return ret_value;
}

long CRedisConn::incrBy(const char *key, long value)
{
    if (Init())
    {
        return -1;
    }

    redisReply *reply = (redisReply *)redisCommand(m_pContext, "INCRBY %s %ld", key, value);
    if (!reply)
    {
        //REPORT_EVENT(LOG_CRITICAL, "redis incrby", "redisCommand failed:%s", m_pContext->errstr);
        redisFree(m_pContext);
        m_pContext = NULL;
        return -1;
    }
    long ret_value = reply->integer;
    freeReplyObject(reply);
    return ret_value;
}

string &CRedisConn::hmset(const char *key, map<string, string> &hash, string &ret_value)
{
    if (Init())
    {
        return ret_value;
    }

    int argc = hash.size() * 2 + 2;
    const char **argv = new const char *[argc];
    if (!argv)
    {
        return ret_value;
    }

    argv[0] = "HMSET";
    argv[1] = key;
    int i = 2;
    for (map<string, string>::iterator it = hash.begin(); it != hash.end(); it++)
    {
        argv[i++] = it->first.c_str();
        argv[i++] = it->second.c_str();
    }

    redisReply *reply = (redisReply *)redisCommandArgv(m_pContext, argc, argv, NULL);
    if (!reply)
    {
        //REPORT_EVENT(LOG_CRITICAL, "redis hmset", "redisCommand failed:%s", m_pContext->errstr);
        delete[] argv;
        redisFree(m_pContext);
        m_pContext = NULL;
        return ret_value;
    }
    ret_value.append(reply->str, reply->len);

    delete[] argv;
    freeReplyObject(reply);
    return ret_value;
}

bool CRedisConn::hmget(const char *key, list<string> &fields, list<string> &ret_value)
{
    if (Init())
    {
        return false;
    }

    int argc = fields.size() + 2;
    const char **argv = new const char *[argc];
    if (!argv)
    {
        return false;
    }

    argv[0] = "HMGET";
    argv[1] = key;
    int i = 2;
    for (list<string>::iterator it = fields.begin(); it != fields.end(); it++)
    {
        argv[i++] = it->c_str();
    }

    redisReply *reply = (redisReply *)redisCommandArgv(m_pContext, argc, (const char **)argv, NULL);
    if (!reply)
    {
        //REPORT_EVENT(LOG_CRITICAL, "redis hmget", "redisCommand failed:%s", m_pContext->errstr);
        delete[] argv;
        redisFree(m_pContext);
        m_pContext = NULL;
        return false;
    }

    if (reply->type == REDIS_REPLY_ARRAY)
    {
        for (size_t i = 0; i < reply->elements; i++)
        {
            redisReply *value_reply = reply->element[i];
            string value(value_reply->str, value_reply->len);
            ret_value.push_back(value);
        }
    }

    delete[] argv;
    freeReplyObject(reply);
    return true;
}

long CRedisConn::incr(const char *key)
{
    if (Init())
    {
        return -1;
    }

    redisReply *reply = (redisReply *)redisCommand(m_pContext, "INCR %s", key);
    if (!reply)
    {
        //REPORT_EVENT(LOG_CRITICAL, "redis incr", "redisCommand failed:%s", m_pContext->errstr);
        redisFree(m_pContext);
        m_pContext = NULL;
        return -1;
    }
    long ret_value = reply->integer;
    freeReplyObject(reply);
    return ret_value;
}

long CRedisConn::decr(const char *key)
{
    if (Init())
    {
        return -1;
    }

    redisReply *reply = (redisReply *)redisCommand(m_pContext, "DECR %s", key);
    if (!reply)
    {
        //REPORT_EVENT(LOG_CRITICAL, "redis decr", "redisCommand failed:%s", m_pContext->errstr);
        redisFree(m_pContext);
        m_pContext = NULL;
        return -1;
    }
    long ret_value = reply->integer;
    freeReplyObject(reply);
    return ret_value;
}

long CRedisConn::lpush(const char *key, const char *value)
{
    if (Init())
    {
        return -1;
    }

    redisReply *reply = (redisReply *)redisCommand(m_pContext, "LPUSH %s %s", key, value);
    if (!reply)
    {
        //REPORT_EVENT(LOG_CRITICAL, "redis lpush", "redisCommand failed:%s", m_pContext->errstr);
        redisFree(m_pContext);
        m_pContext = NULL;
        return -1;
    }

    long ret_value = reply->integer;
    freeReplyObject(reply);
    return ret_value;
}

long CRedisConn::rpush(const char *key, const char *value)
{
    if (Init())
    {
        return -1;
    }

    redisReply *reply = (redisReply *)redisCommand(m_pContext, "RPUSH %s %s", key, value);
    if (!reply)
    {
        //REPORT_EVENT(LOG_CRITICAL, "redis rpush", "redisCommand failed:%s", m_pContext->errstr);
        redisFree(m_pContext);
        m_pContext = NULL;
        return -1;
    }

    long ret_value = reply->integer;
    freeReplyObject(reply);
    return ret_value;
}

long CRedisConn::llen(const char *key)
{
    if (Init())
    {
        return -1;
    }

    redisReply *reply = (redisReply *)redisCommand(m_pContext, "LLEN %s", key);
    if (!reply)
    {
        //REPORT_EVENT(LOG_CRITICAL, "redis llen", "redisCommand failed:%s", m_pContext->errstr);
        redisFree(m_pContext);
        m_pContext = NULL;
        return -1;
    }

    long ret_value = reply->integer;
    freeReplyObject(reply);
    return ret_value;
}

bool CRedisConn::lrange(const char *key, long start, long end, list<string> &ret_value)
{
    if (Init())
    {
        return false;
    }

    redisReply *reply = (redisReply *)redisCommand(m_pContext, "LRANGE %s %d %d", key, start, end);
    if (!reply)
    {
        //REPORT_EVENT(LOG_CRITICAL, "redis lrange", "redisCommand failed:%s", m_pContext->errstr);
        redisFree(m_pContext);
        m_pContext = NULL;
        return false;
    }

    if (reply->type == REDIS_REPLY_ARRAY)
    {
        for (size_t i = 0; i < reply->elements; i++)
        {
            redisReply *value_reply = reply->element[i];
            string value(value_reply->str, value_reply->len);
            ret_value.push_back(value);
        }
    }

    freeReplyObject(reply);
    return true;
}

long CRedisConn::zadd(const char *key, long long score, const char *value, string *pCmd)
{
    if (pCmd != NULL)
    {
        *pCmd = "ZADD ";
        *pCmd += key;
        *pCmd += " ";
        *pCmd += get_int64(score);
        *pCmd += " ";
        *pCmd += value;
        return 0;
    }

    if (Init())
    {
        return -1;
    }

    redisReply *reply = (redisReply *)redisCommand(m_pContext, "ZADD %s %I64d %s", key, score, value);
    if (!reply)
    {
        //REPORT_EVENT(LOG_CRITICAL, "redis zadd", "redisCommand failed:%s", m_pContext->errstr);
        redisFree(m_pContext);
        m_pContext = NULL;
        return false;
    }

    long ret_value = reply->integer;
    freeReplyObject(reply);

    return 0;
}

long CRedisConn::zadd(const char *key, double score, const char *value, string *pCmd)
{
    if (pCmd != NULL)
    {
        *pCmd = "ZADD ";
        *pCmd += key;
        *pCmd += " ";
        *pCmd += get_float(score);
        *pCmd += " ";
        *pCmd += value;
        return 0;
    }

    if (Init())
    {
        return -1;
    }

    redisReply *reply = (redisReply *)redisCommand(m_pContext, "ZADD %s %f %s", key, score, value);
    if (!reply)
    {
        //REPORT_EVENT(LOG_CRITICAL, "redis zadd", "redisCommand failed:%s", m_pContext->errstr);
        redisFree(m_pContext);
        m_pContext = NULL;
        return false;
    }

    long ret_value = reply->integer;
    freeReplyObject(reply);
    return 0;
}

long CRedisConn::zrem(const char *key, const char *value, string *pCmd)
{
    if (pCmd != NULL)
    {
        *pCmd = "ZREM ";
        *pCmd += key;
        *pCmd += " ";
        *pCmd += value;
        return 0;
    }

    if (Init())
    {
        return -1;
    }

    redisReply *reply = (redisReply *)redisCommand(m_pContext, "ZREM %s %s", key, value);
    if (!reply)
    {
        //REPORT_EVENT(LOG_CRITICAL, "redis zrem", "redisCommand failed:%s", m_pContext->errstr);
        redisFree(m_pContext);
        m_pContext = NULL;
        return false;
    }

    long ret_value = reply->integer;
    freeReplyObject(reply);
    return 0;
}

bool CRedisConn::pipeline_process(struct timeval access_timeout, const vector<string> &cmds, vector<string> &resps, vector<bool> &resp_status)
{
    if (Init())
    {
        return false;
    }
    printf("pipeline_process:");
    redisSetTimeout(m_pContext, access_timeout);

    for (size_t i = 0; i < cmds.size(); i++)
    {
        redisAppendCommand(m_pContext, cmds[i].c_str());
    }

    bool status = false;
    std::string resp_str = "";
    redisReply *reply = 0;
    resps.clear();
    resp_status.clear();
    for (size_t i = 0; i < cmds.size(); i++)
    {
        resp_str = "";
        if (redisGetReply(m_pContext, (void **)&reply) == REDIS_OK)
        {
            status = true;
            if (reply != NULL && reply->type == REDIS_REPLY_STRING)
            {
                resp_str = reply->str;
            }
        }
        else
        {
            status = false;
            resp_str = m_pContext->errstr;
            if (reply != NULL && reply->str != NULL)
            {
                resp_str += reply->str;
            }
        }
        //free
        freeReplyObject(reply);
        if (!status)
        {
            printf("reply is false!\n");
        }
        resp_status.push_back(status);
        resps.push_back(resp_str);
    }
    return true;
}

void CRedisConn::flushdb()
{
    if (Init())
    {
        return;
    }

    redisReply *reply = (redisReply *)redisCommand(m_pContext, "FLUSHDB");

    freeReplyObject(reply);
}
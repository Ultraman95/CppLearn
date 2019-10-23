#pragma once

//Window环境下无法使用

#include <vector>
#include "hiredis.h"
#include <cstring>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <time.h>

using std::list;
using std::map;
using std::string;
using std::vector;

class CRedisConn
{
public:
	CRedisConn(const char *server_ip, int server_port, const char *szPasswd, int db_num);
	virtual ~CRedisConn();

	int Init();

	void flushdb();

	string &get(const char *key, string &value, string *pCmd);
	string &setex(const char *key, const char *value, int timeout, string &ret_value, string *pCmd);
	string &set(const char *key, const char *value, string &ret_value, string *pCmd);

	//批量获取
	bool mget(const vector<string> &keys, vector<string> &values, string *pCmd);
	
	// 判断一个key是否存在
	bool exists(const char *key, string *pCmd);

	// Redis hash structure
	long hdel(const char *key, const char *field, string *pCmd);
	string &hget(const char *key, const char *field, string &ret_value, string *pCmd);
	bool hgetAll(const char *key, map<string, string> &ret_value, string *pCmd);
	long hset(const char *key, const char *field, const char *value, string *pCmd);

	long hincrBy(const char *key, const char *field, long value);
	long incrBy(const char *key, long value);
	string &hmset(const char *key, map<string, string> &hash, string &ret_value);
	bool hmget(const char *key, list<string> &fields, list<string> &ret_value);

	//原子加减1
	long incr(const char *key);
	long decr(const char *key);

	// Redis list structure
	long lpush(const char *key, const char *value);
	long rpush(const char *key, const char *value);
	long llen(const char *key);
	bool lrange(const char *key, long start, long end, list<string> &ret_value);

	// Redis sorted set
	long zadd(const char *key, long long score, const char *value, string *pCmd);
	long zadd(const char *key, double score, const char *value, string *pCmd);
	long zrem(const char *key, const char *value, string *pCmd);

	//pipeline
	bool pipeline_process(struct timeval access_timeout, const vector<string> &cmds, vector<string> &resps, vector<bool> &resp_status);

private:
	string m_server_ip;
	int m_server_port;
	int m_db_num;
	string m_password;
	redisContext *m_pContext;
	uint64_t m_last_connect_time;
};

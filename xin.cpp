#include<iostream>
#include<hiredis/hiredis.h>
using namespace std;

//#define REDIS_HOST "127.0.0.1"
//#define REDIS_PORT 6379
const char* REDIS_HOST = "127.0.0.1";


const int REDIS_PORT = 6379;

int main()
{
	redisContext *c = NULL;
	redisReply *r = NULL;
	c = redisConnect(REDIS_HOST, REDIS_PORT);
	if(c == NULL)
	{
		cout<< "connect failure" <<endl;
		return -1;
	}
	cout<< "connect success" <<endl;
	const char *cmd1 = "set test hello";
	r = (redisReply*)redisCommand(c, cmd1);
	if(!r)
	{
<<<<<<< HEAD
		cout<< "redis command error1" <<endl;
=======
		cout<< "redis command error" <<endl;
>>>>>>> 276d6074a985fb9d6f55c04da21dceceed3df1e8
		redisFree(c);
		return -1;
	}
	if(r->type == REDIS_REPLY_ERROR)
	{
<<<<<<< HEAD
		cout<< "redis command error2" <<endl;
=======
		cout<< "redis command error" <<endl;
>>>>>>> 276d6074a985fb9d6f55c04da21dceceed3df1e8
		freeReplyObject(r);
		redisFree(c);
		return -1;
	}
	const char *cmd2 = "get test";
	r = (redisReply*)redisCommand(c, cmd2);
	if(!r)
	{
<<<<<<< HEAD
		cout<< "redis command error3" <<endl;
=======
		cout<< "redis command error" <<endl;
>>>>>>> 276d6074a985fb9d6f55c04da21dceceed3df1e8
		redisFree(c);
		return -1;
	}
	if(r->type == REDIS_REPLY_ERROR)
	{
<<<<<<< HEAD
		cout<< "redis command error4" <<endl;
=======
		cout<< "redis command error" <<endl;
>>>>>>> 276d6074a985fb9d6f55c04da21dceceed3df1e8
		freeReplyObject(r);
		redisFree(c);
		return -1;
	}
	cout<< "get test value is:" << r->str <<endl;
	freeReplyObject(r);
	redisFree(c);
	return 0; 
}

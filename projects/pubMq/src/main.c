/**#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "MQTTClient.h"

#define ADDRESS     "tcp://localhost:1883"
#define CLIENTID    "ExampleClientPub"
#define TOPIC       "HT"
#define PAYLOAD     "Hello World!"
#define QOS         1
#define TIMEOUT     10000L

int main(int argc, char* argv[])
{
    MQTTClient client;
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    MQTTClient_deliveryToken token;
    int rc;

    MQTTClient_create(&client, ADDRESS, CLIENTID,
        MQTTCLIENT_PERSISTENCE_NONE, NULL);
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;

    printf("Start Connect !\n");
    if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to connect, return code %d\n", rc);
        exit(-1);
    }
    printf("Start Connect Success !\n");
    pubmsg.payload = PAYLOAD;
    pubmsg.payloadlen = strlen(PAYLOAD);
    pubmsg.qos = QOS;
    pubmsg.retained = 0;
    MQTTClient_publishMessage(client, TOPIC, &pubmsg, &token);
    printf("Waiting for up to %d seconds for publication of %s\n"
            "on topic %s for client with ClientID: %s\n",
            (int)(TIMEOUT/1000), PAYLOAD, TOPIC, CLIENTID);
    rc = MQTTClient_waitForCompletion(client, token, TIMEOUT);
    printf("Message with delivery token %d delivered\n", token);
    MQTTClient_disconnect(client, 10000);
    MQTTClient_destroy(&client);
    return rc;
}**/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "paho-mqtt/MQTTClient.h"
#include <pthread.h>
#if defined(WIN32) || defined(WIN64)
#include <windows.h>
#else
#include <unistd.h>
#endif

#define NUM_THREADS     2
#define ADDRESS         "tcp://localhost:1883"          //MQ——Broker的地址
#define PUB_CLIENTID    "pubTest"                       //发布客户端ID
#define SUB_CLIENTID    "subTest"                       //订阅客户端ID
#define TOPIC           "topicTest"                     //发布，订阅的主题
#define PAYLOAD         "{\"productId\":\"BTC\",\"instrumentType\":1,\"instrumentId\":\"BTC1209\",\"direction\":1,\"offset\":0,\"price\":\"0.000000147\",\"volume\":\"1.23444\"}"  	//消息体

#define QOS             1
#define TIMEOUT         10000L
#define USERNAME        "test_user"
#define PASSWORD        "jim777"
#define DISCONNECT      "out"

int CONNECT = 1;
volatile MQTTClient_deliveryToken deliveredtoken;

void delivered(void *context, MQTTClient_deliveryToken dt)
{
    printf("Message with token value %d delivery confirmed\n", dt);
    deliveredtoken = dt;
}

int msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message)
{
    int i;
    char* payloadptr;

    printf("Message arrived\n");
    printf("   topic: %s\n", topicName);
    printf("   message: ");

    payloadptr = message->payload;
    if(strcmp(payloadptr, DISCONNECT) == 0){
        printf(" \n out!!");
        CONNECT = 0;
    }
    
    for(i=0; i<message->payloadlen; i++)
    {
        putchar(*payloadptr++);
    }
    printf("\n");
    
    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);
    return 1;
}

void connlost(void *context, char *cause)
{
    printf("\nConnection lost\n");
    printf("     cause: %s\n", cause);
}

void *subClient(void *threadid){
   long tid;
   tid = (long)threadid;
   printf("Hello World! It's me, thread #%ld!\n", tid);
   
    MQTTClient client;
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    int rc;
    int ch;

    MQTTClient_create(&client, ADDRESS, SUB_CLIENTID,
        MQTTCLIENT_PERSISTENCE_NONE, NULL);
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;
    conn_opts.username = USERNAME;
    conn_opts.password = PASSWORD;
    
    MQTTClient_setCallbacks(client, NULL, connlost, msgarrvd, delivered);

    if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to connect, return code %d\n", rc);
        exit(EXIT_FAILURE);
    }
    printf("Subscribing to topic [%s] , for client %s using QoS-%d\n\n"
           "Press Q<Enter> to quit\n\n", TOPIC, PUB_CLIENTID, QOS);
    MQTTClient_subscribe(client, TOPIC, QOS);

    do 
    {
        ch = getchar();
        printf("%c",ch);
    } while(ch!='Q' && ch != 'q');

    MQTTClient_unsubscribe(client, TOPIC);
    MQTTClient_disconnect(client, 10000);
    MQTTClient_destroy(&client);
   
   pthread_exit(NULL);
}

void *pubClient(void *threadid){
    long tid;
    tid = (long)threadid;
    int count = 0;
    printf("Hello World! It's me, thread #%ld!\n", tid);
    //声明一个MQTTClient
    MQTTClient client;
    //初始化MQTT Client选项
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    //#define MQTTClient_message_initializer { {'M', 'Q', 'T', 'M'}, 0, 0, NULL, 0, 0, 0, 0 }
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    //声明消息token
    MQTTClient_deliveryToken token;
    int rc;
    //使用参数创建一个client，并将其赋值给之前声明的client
    MQTTClient_create(&client, ADDRESS, PUB_CLIENTID,
        MQTTCLIENT_PERSISTENCE_NONE, NULL);
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;
    conn_opts.username = USERNAME;
    conn_opts.password = PASSWORD;
     //使用MQTTClient_connect将client连接到服务器，使用指定的连接选项。成功则返回MQTTCLIENT_SUCCESS
    if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to connect, return code %d\n", rc);
        exit(EXIT_FAILURE);
    }
    pubmsg.payload = PAYLOAD;
    pubmsg.payloadlen = strlen(PAYLOAD);
    pubmsg.qos = QOS;
    pubmsg.retained = 0;
    deliveredtoken = 0;
    time_t start , end;
    long tCount = 1L;
    time(&start);
    while(CONNECT){
        MQTTClient_publishMessage(client, TOPIC, &pubmsg, &token);
        tCount++;
        
        if (tCount % 10000 == 0) {
            //time(&end);
            //double deltime = difftime(end, start);
            //printf("1000 publish cost time %f \n", deltime);
            Sleep(100L);
        }
        

        /*(printf("Waiting for up to %d seconds for publication of [%s] , "
                "on topic [%s] for client with ClientID: %s\n",
                (int)(TIMEOUT/1000), PAYLOAD, TOPIC, PUB_CLIENTID);*/
        //rc = MQTTClient_waitForCompletion(client, token, TIMEOUT);
        //printf("Message with delivery token %d delivered\n", token);
        //Sleep(10000L);
    }
    
    while(deliveredtoken != token);
    MQTTClient_disconnect(client, 10000);
    MQTTClient_destroy(&client);
}

int main(int argc, char* argv[])
{
    pthread_t threads[NUM_THREADS];
    long t;
    //pthread_create(&threads[0], NULL, subClient, (void *)0);
    pthread_create(&threads[1], NULL, pubClient, (void *)1);
    pthread_exit(NULL);
}
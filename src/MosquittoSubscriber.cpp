#include <iostream>
#include <string.h>
#include "MosquittoSubscriber.h"

MosquittoSubscriber::MosquittoSubscriber():
  PORT(1883), KEEPALIVE(60)
{
  mosqpp::lib_init();
  std::cout << "constructor was called." << std::endl;
}

MosquittoSubscriber::~MosquittoSubscriber()
{
  mosqpp::lib_cleanup();
  free(mHOST);
  free(mTopic);
  free(mClientId);
  std::cout << "destructor was called." << std::endl;
}

void MosquittoSubscriber::on_connect(int rc){
  if(rc == 0){
    std::cout << "connected to broker." << std::endl;
    subscribe(NULL, mTopic, mQos);
    //subscribe(NULL, mTopic);
    /* if QoS > 1 */
    //subscribe(NULL, mTopic, 1);
  }
  else{
    std::cerr << "failed to connect to broker with code" << rc << " ." << std::endl;
    mosqpp::lib_cleanup();
  }
}

void MosquittoSubscriber::on_disconnect(int rc){
  std::cout << "disconnected from broker with code " << rc << " ." << std::endl;
}

void MosquittoSubscriber::on_subscribe(int mid, int qos_count, const int *granted_qos){
  std::cout << "Subscription started." << std::endl;
}

void MosquittoSubscriber::on_message(const struct mosquitto_message* message){
  if(message->payloadlen){
    std::cout << "topic: " << message->topic << std::endl;
    char* part = NULL;
    part = (char*)malloc(message->payloadlen + 1);
    strcpy(part, (char*)(message->payload));
    std::cout << "Received: " << part << std::endl;
    free(part);
  }
  else{
    std::cout << message->topic << ": (null)" << std::endl;
  }
}

void MosquittoSubscriber::mosq_connect(const char* host, const char* topic, const int qos, const char* clientId){
  /* host name */
  mHOST = (char *)malloc(strlen(host) + 1);
  strcpy(mHOST, host);
  /* topic name */
  mTopic = (char *)malloc(strlen(topic) + 1);
  strcpy(mTopic, topic);
  /* QoS number */
  mQos = qos;
  /* Client ID */
  mClientId = (char *)malloc(strlen(clientId) + 1);
  strcpy(mClientId, clientId);
  reinitialise(mClientId, true);

  connect(mHOST, PORT, KEEPALIVE);
  //connect_async(HOST, PORT, KEEPALIVE, NULL);
  //loop_forever();
  loop_start();
}

void MosquittoSubscriber::mosq_disconnect(){
  loop_stop(true);
  disconnect();
}


/* main for test */
/*
int
main ( int argc, char *argv[] )
{
  const char* host = "localhost";
  const char *topic_p = "test";
  const int qos = 0;
  const char* cid = "subtest1";

  MosquittoSubscriber* ms = new MosquittoSubscriber();

  ms->mosq_connect(host, topic_p, qos, cid);
  //ms->loop_forever(0, 1);
  ms->mosq_disconnect();

  delete ms;

  return 0;
}
*/

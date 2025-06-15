#include <iostream>
#include <string.h>
#include <unistd.h>
#include "MosquittoPublisher.h"

MosquittoPublisher::MosquittoPublisher():
  PORT(1883), KEEPALIVE(60)
{
  mosqpp::lib_init();
  std::cout << "constructor was called." << std::endl;
}

MosquittoPublisher::~MosquittoPublisher()
{
  mosqpp::lib_cleanup();
  free(mHOST);
  free(mTopic);
  free(mClientId);
  std::cout << "destructor was called." << std::endl;
}

void MosquittoPublisher::on_connect(int rc){
  if(rc == 0){
    std::cout << "connected to broker." << std::endl;
  }
  else{
    std::cerr << "failed to connect to broker with code" << rc << " ." << std::endl;
    mosqpp::lib_cleanup();
  }
}

void MosquittoPublisher::on_disconnect(int rc){
  std::cout << "disconnected from broker with code " << rc << " ." << std::endl;
}

void MosquittoPublisher::mosq_connect(const char* host, const char* topic, const int qos, const char* clientId){
  /* host name */
  mHOST = (char *)malloc(strlen(host) + 1);
  strcpy(mHOST, host);
  /* topic name */
  mTopic = (char *)malloc(strlen(topic) + 1);
  strcpy(mTopic, topic);
  /* QoS number */
  mQos = qos;
  /* Clinet ID */
  mClientId = (char *)malloc(strlen(clientId) + 1);
  strcpy(mClientId, clientId);
  reinitialise(mClientId, true);

  connect(mHOST, PORT, KEEPALIVE);
  //connect_async(mHOST, PORT, KEEPALIVE, NULL);
  loop_start();
}

void MosquittoPublisher::mosq_disconnect(){
  loop_stop(true);
  disconnect();
}

void MosquittoPublisher::mosq_pub(const void* data, const int datalen){
  publish(NULL, mTopic, datalen, data, mQos);
  //publish(NULL, mTopic, datalen, data);
  /* if QoS > 0 or retain == true */
  // publish(NULL, mTopic, datalen, data, 1, true);
  //publish(NULL, mTopic, datalen, data, 1);
  /*
  if(loop(0,1)){
    reconnect();
  }
  */
}

/* main for test */
/*
int
main ( int argc, char *argv[] )
{
  const char *topic_p = "test";
  const char *text_p = "Hello world! Mosquitto MQTT!";

  MosquittoPublisher* mp = new MosquittoPublisher();

  mp->mosq_connect(topic_p);
  mp->mosq_pub(text_p, strlen(text_p));
  sleep(2);
  mp->mosq_pub(text_p, strlen(text_p));
  sleep(3);
  mp->mosq_pub(text_p, strlen(text_p));
  mp->mosq_disconnect();

  delete mp;

  return 0;
}
*/

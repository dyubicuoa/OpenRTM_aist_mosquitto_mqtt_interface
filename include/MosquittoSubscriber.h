#ifndef MOSQUITTOSUBSCRIBER_H
#define MOSQUITTOSUBSCRIBER_H

#include <mosquittopp.h>

class MosquittoSubscriber : public mosqpp::mosquittopp{
private:
  //const char* ID;
  char* mHOST;
  const int PORT;
  const int KEEPALIVE;
  char* mTopic;
  int mQos;
  char* mClientId;

public:
  MosquittoSubscriber();
  virtual ~MosquittoSubscriber();

  void on_connect(int rc);
  void on_disconnect(int rc);
  void on_subscribe(int mid, int qos_count, const int *granted_qos);
  //void on_message(const struct mosquitto_message* message);
  void on_message(const struct mosquitto_message* message) override;

  void mosq_connect(const char* host, const char* topic, const int qos, const char* clientId);
  void mosq_disconnect();
};

#endif


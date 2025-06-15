#ifndef MOSQUITTOPUBLISHER_H
#define MOSQUITTOPUBLISHER_H

#include <mosquittopp.h>

class MosquittoPublisher : public mosqpp::mosquittopp{
private:
  //const char* ID;
  char* mHOST;
  const int PORT;
  const int KEEPALIVE;
  char* mTopic;
  int mQos;
  char* mClientId;

public:
  MosquittoPublisher();
  virtual ~MosquittoPublisher();

  void on_connect(int rc);
  void on_disconnect(int rc);

  void mosq_connect(const char* host, const char* topic, const int qos, const char* clientId);
  void mosq_disconnect();
  void mosq_pub(const void* data, const int datalen);
};

#endif


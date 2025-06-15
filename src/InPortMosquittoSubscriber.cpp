// -*- C++ -*-
/*!
 * @file  InPortMosquittoSubscriber.cpp
 * @brief InPortMosquittoSubscriber class
 * @date  $Date: 2019-07-12 14:44:03 $
 * @author Daishi Yoshino <daishi-y@u-aizu.ac.jp>
 */

#include <InPortMosquittoSubscriber.h>

namespace RTC
{
/*****************************************************************************
 * messageReceiveCallback
 *****************************************************************************/
void InPortMosquittoSubscriber::on_message(const struct mosquitto_message* message)
{
  unsigned long len = message->payloadlen;
  void* payload = (void *)malloc(len);
  memcpy(payload, (void *)(message->payload), len);
  //void* part;
  //part = (void *)malloc(message->payloadlen);
  //memcpy(part, (void *)(message->payload), message->payloadlen);

  //::OpenRTM::CdrData tmp((CORBA::ULong)(message->payloadlen), 
  //                       (CORBA::ULong)(message->payloadlen), 
  //                       static_cast<CORBA::Octet*>(part), 0);

  //if (m_buffer == 0)
  if (m_connector == nullptr)
  {
    //cdrMemoryStream cdr;
    //cdr.put_octet_array(&(tmp[0]), tmp.length());
    ByteData data_obj;
    data_obj.writeData(static_cast<unsigned char*>(payload), len);

    onReceiverError(data_obj);
  }

  //RTC_PARANOID(("received data size: %d", tmp.length()))
  RTC_PARANOID(("received data size: %d", len));
  //cdrMemoryStream cdr;
  ByteData data_obj;
  // set endian type
  bool endian_type = m_connector->isLittleEndian();
  RTC_TRACE(("connector endian: %s", endian_type ? "little":"big"));
  //cdr.setByteSwapFlag(endian_type);
  //cdr.put_octet_array(&(tmp[0]), tmp.length());


  data_obj.writeData(static_cast<unsigned char*>(payload), len);
  //RTC_PARANOID(("converted CDR data size: %d", cdr.bufSize()));
  RTC_PARANOID(("converted serialized data size: %d", data_obj.getDataLength()));
  onReceived(data_obj);
  //BufferStatus::Enum ret = m_buffer->write(cdr);
  BufferStatus ret = m_connector->write(data_obj);

  convertReturn(ret, data_obj);

  //free(part);
  free(payload);
}

  /*!
   * @if jp
   * @brief コンストラクタ
   * @else
   * @brief Constructor
   * @endif
   */
  InPortMosquittoSubscriber::InPortMosquittoSubscriber()
   //: m_buffer(nullptr), m_connector(nullptr)
   //: m_connector(nullptr)
  {
    // PortProfile setting
    setInterfaceType("mosq_mqtt");
  }
  
  /*!
   * @if jp
   * @brief デストラクタ
   * @else
   * @brief Destructor
   * @endif
   */
  InPortMosquittoSubscriber::~InPortMosquittoSubscriber()
  {
    // disconnect from Mosquitto broker
    std::cout << "[disconnecting from Mosquitto broker start]" << std::endl;
    mosq_disconnect();
    std::cout << "[disconnecting from Mosquitto broker end]" << std::endl;
  }

  void InPortMosquittoSubscriber::init(coil::Properties& /*prop*/)
  {
  }

  /*!
   * @if jp
   * @brief バッファをセットする
   * @else
   * @brief Setting outside buffer's pointer
   * @endif
   */
  void InPortMosquittoSubscriber::
  setBuffer(BufferBase<ByteData>* buffer)
  {
    m_buffer = buffer;
  }

  /*!
   * @if jp
   * @brief リスナを設定する
   * @else
   * @brief Set the listener
   * @endif
   */
  void InPortMosquittoSubscriber::setListener(ConnectorInfo& info,
                                              ConnectorListenersBase* listeners)
  {
    m_profile = info;
    m_listeners = listeners;
  }

  /*!
   * @if jp
   * @brief Connectorを設定する。
   * @else
   * @brief set Connector
   * @endif
   */
  void InPortMosquittoSubscriber::setConnector(InPortConnector* connector)
  {
    m_connector = connector;
  }

  /*!
   * @if jp
   * @brief リターンコード変換
   * @else
   * @brief Return codes conversion
   * @endif
   */
  ::OpenRTM::PortStatus
  InPortMosquittoSubscriber::convertReturn(BufferStatus status,
                                           ByteData& data)
  {
    switch(status)
      {
      case BufferStatus::OK:
        onBufferWrite(data);
        return ::OpenRTM::PORT_OK;

      case BufferStatus::BUFFER_ERROR:
        onReceiverError(data);
        return ::OpenRTM::PORT_ERROR;

      case BufferStatus::FULL:
        onBufferFull(data);
        onReceiverFull(data);
        return ::OpenRTM::BUFFER_FULL;

      case BufferStatus::EMPTY:
        // never come here
        return ::OpenRTM::BUFFER_EMPTY;

      case BufferStatus::PRECONDITION_NOT_MET:
        onReceiverError(data);
        return ::OpenRTM::PORT_ERROR;

      case BufferStatus::TIMEOUT:
        onBufferWriteTimeout(data);
        onReceiverTimeout(data);
        return ::OpenRTM::BUFFER_TIMEOUT;

      case BufferStatus::NOT_SUPPORTED: /* FALLTHROUGH */
      default:
        return ::OpenRTM::UNKNOWN_ERROR;
      }

    //onReceiverError(data);
    //return ::OpenRTM::UNKNOWN_ERROR;
  }

  /*!
   * @if jp
   * @brief InterfaceProfile情報を公開する
   * @else
   * @brief Publish InterfaceProfile information
   * @endif
   */
  void InPortMosquittoSubscriber::publishInterfaceProfile(SDOPackage::NVList& properties){
    std::cout << "setting pub/sub information" << std::endl;
    return;
  }

  /*!
   * @if jp
   * @brief Interface情報を公開する
   * @else
   * @brief Publish Interface information
   * @endif
   */
  bool InPortMosquittoSubscriber::publishInterface(SDOPackage::NVList& properties)
  {
    RTC_TRACE(("publishInterface()"));
    RTC_DEBUG_STR((NVUtil::toString(properties)));
    std::cout << "reading InPort infomation" << std::endl;

   // getting Topic information
   if(subscribeMosquittoSubscriber(properties)){
     return true;
   }

   return false;
  }

  /*!
   * @brief Setting to connect to broker
   */
  bool InPortMosquittoSubscriber::subscribeMosquittoSubscriber(const SDOPackage::NVList& properties)
  {
    RTC_TRACE(("subscribeMosquittoSubscriber()"));

    const char* pn_host = "host";
    const char* pn_topic = "topic";
    const char* pn_qos = "qos";
    const char* pn_id = "sid";

    CORBA::Long index0, index1, index2, index3;
    index0 = NVUtil::find_index(properties, pn_host);
    index1 = NVUtil::find_index(properties, pn_topic);
    index2 = NVUtil::find_index(properties, pn_qos);
    index3 = NVUtil::find_index(properties, pn_id);

    const char* tmp_host = "localhost";
    const char* tmp_topic = "test";
    const char* str_qos = "0";
    int tmp_qos = 0;

    struct timespec sub_num;
    clock_gettime(CLOCK_REALTIME, &sub_num);
    //const char* tmp_id = "mqtt/sub0";
    std::string sub_id = "sub";
    sub_id += std::to_string((long)(sub_num.tv_sec * 1.0E9 + sub_num.tv_nsec));
    const char* tmp_id = sub_id.c_str();

    if(index0 < 0)
    {
      //RTC_ERROR(("Mosquitto Host not found"));
      std::cout << "Mosquitto Host not found. Default Host(localhost) is used." << std::endl;
      //return false;
    }
    else{
      if(!(NVUtil::isString(properties, pn_host)))
      {
        //RTC_ERROR(("Host Name is not string"));
        std::cout << "Host Name is not string. Default Host(localhost) is used." << std::endl;
        //return false;
      }
      else{
        properties[index0].value >>= tmp_host;
      }
    }

    std::cout << "Host: " << tmp_host << std::endl;

    if(index1 < 0)
    {
      //RTC_ERROR(("Mosquitto Topic not found"));
      std::cout << "Mosquitto Topic not found. Default Topic is used." << std::endl;
      //return false;
    }
    else{
      if(!(NVUtil::isString(properties, pn_topic)))
      {
        //RTC_ERROR(("Topic Name is not string"));
        std::cout << "Topic Name is not string. Default Topic is used." << std::endl;
        //return false;
      }
      else{
        properties[index1].value >>= tmp_topic;
      }
    }

    std::cout << "Topic: " << tmp_topic << std::endl;

    if(index2 < 0)
    {
      //RTC_ERROR(("Mosquitto QoS not found"));
      std::cout << "Mosquitto QoS not found. Default QoS(0) is used." << std::endl;
      //return false;
    }
    else{
      if(!(NVUtil::isString(properties, pn_qos)))
      {
        //RTC_ERROR(("QoS number is not string"));
        std::cout << "QoS number is not string. Default QoS(0) is used." << std::endl;
        //return false;
      }
      else{
        properties[index2].value >>= str_qos;
        tmp_qos = atoi(str_qos);
        if(tmp_qos < 0 || tmp_qos > 2){
          std::cout << "Selected Mosquitto QoS number is out of range. Default QoS(0) is used." << std::endl;
          tmp_qos = 0;
        }
      }
    }

    std::cout << "QoS: " << tmp_qos << std::endl;

    if(index3 < 0)
    {
      //RTC_ERROR(("MQTT Client ID not found"));
      std::cout << "MQTT Client ID not found. Default ID(mqtt/sub0) is used." << std::endl;
      //return false;
    }
    else{
      if(!(NVUtil::isString(properties, pn_id)))
      {
        //RTC_ERROR(("MQTT Client ID is not string"));
        std::cout << "MQTT Client ID is not string. Default ID(mqtt/sub0) is used." << std::endl;
        //return false;
      }
      else{
        properties[index3].value >>= tmp_id;
      }
    }

    std::cout << "Client ID: " << tmp_id << std::endl;

    std::cout << "[connecting to Mosquitto broker start]" << std::endl;
    mosq_connect(tmp_host, tmp_topic, tmp_qos, tmp_id);
    std::cout << "[connecting to Mosquitto broker end]" << std::endl;

    return true;
  }
};     // namespace RTC


extern "C"
{
  /*!
   * @if jp
   * @brief モジュール初期化関数
   * @else
   * @brief Module initialization
   * @endif
   */
  void InPortMosquittoSubscriberInit(void)
  {
    RTC::InPortProviderFactory& factory(RTC::InPortProviderFactory::instance());
    factory.addFactory("mosq_mqtt",
                       ::coil::Creator< ::RTC::InPortProvider,
                                        ::RTC::InPortMosquittoSubscriber>,
                       ::coil::Destructor< ::RTC::InPortProvider,
                                           ::RTC::InPortMosquittoSubscriber>);
  }
};

/*
void registerModule(void)
{
  std::cout << "[Mosquitto Subscriber initialization start]" << std::endl;
  InPortMosquittoSubscriberInit();
  std::cout << "[Mosquitto Subscriber initialization end]" << std::endl;
};
*/

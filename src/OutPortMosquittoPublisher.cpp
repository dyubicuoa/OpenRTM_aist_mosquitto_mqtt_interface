// -*- C++ -*-
/*!
 * @file  OutPortMosquittoPublisher.cpp
 * @brief OutPortMosquittoPublisher class
 * @date  $Date: 2019-07-29 10:27:54 $
 * @author Daishi Yoshino <daishi-y@u-aizu.ac.jp>
 */

#include <rtm/NVUtil.h>
#include <OutPortMosquittoPublisher.h>

namespace RTC
{
  /*!
   * @if jp
   * @brief コンストラクタ
   * @else
   * @brief Constructor
   * @param buffer The buffer object that is attached to this Consumer
   * @endif
   */
  OutPortMosquittoPublisher::OutPortMosquittoPublisher()
    : rtclog("OutPortMosquittoPublisher")
  {
  }
  
  /*!
   * @if jp
   * @brief デストラクタ
   * @else
   * @brief Destructor
   * @endif
   */
  OutPortMosquittoPublisher::~OutPortMosquittoPublisher()
  {
    RTC_PARANOID(("~OutPortMosquittoPublisher()"));

    // disconnect from Mosquitto broker
    std::cout << "[disconnecting from Mosquitto broker start]" << std::endl;
    mosq_disconnect();
    std::cout << "[disconnecting from Mosquitto broker end]" << std::endl;
  }

  /*!
   * @if jp
   * @brief 設定初期化
   * @else
   * @brief Initializing configuration
   * @endif
   */
  void OutPortMosquittoPublisher::init(coil::Properties& prop)
  {
    m_properties = prop;
  }

  /*!
   * @if jp
   * @brief メッセージの発行
   * @else
   * @brief Publish the message to server (broker)
   * @endif
   */
  DataPortStatus OutPortMosquittoPublisher::
  put(ByteData& data)
  {
    RTC_PARANOID(("put()"));

    //const int bufleng = static_cast<int>(data.bufSize());
    //const void* data_p = data.bufPtr();
    unsigned long data_len = data.getDataLength();
    void* data_ptr = (void *)malloc(data_len);
    data.readData(static_cast<unsigned char*>(data_ptr), data_len);
    try
      {
        mosq_pub(data_ptr, data_len);
	free(data_ptr);

        return DataPortStatus::PORT_OK;
      }
    catch (...)
      {
	free(data_ptr);

        return DataPortStatus::CONNECTION_LOST;
      }
    free(data_ptr);
    return DataPortStatus::UNKNOWN_ERROR;
  }
  
  /*!
   * @if jp
   * @brief InterfaceProfile情報を公開する
   * @else
   * @brief Publish InterfaceProfile information
   * @endif
   */
  void OutPortMosquittoPublisher::
  publishInterfaceProfile(SDOPackage::NVList& /*properties*/)
  {
    std::cout << "setting pub/sub information" << std::endl;
    return;
  }

  /*!
   * @if jp
   * @brief データ送信通知への登録
   * @else
   * @brief Subscribe to the data sending notification
   * @endif
   */
  bool OutPortMosquittoPublisher::
  subscribeInterface(const SDOPackage::NVList& properties)
  {
    RTC_TRACE(("subscribeInterface()"));
    RTC_DEBUG_STR((NVUtil::toString(properties)));
    std::cout << "reading OutPort information" << std::endl;
    
    // getting Topic information
    if(subscribeMosquittoPublisher(properties)){
      return true;
    }

    return false;
  }
  
  /*!
   * @if jp
   * @brief データ送信通知からの登録解除
   * @else
   * @brief Unsubscribe the data send notification
   * @endif
   */
  void OutPortMosquittoPublisher::
  unsubscribeInterface(const SDOPackage::NVList& properties)
  {
    RTC_TRACE(("unsubscribeInterface()"));
    RTC_DEBUG_STR((NVUtil::toString(properties)));
    std::cout << "unsbscribing OutPort" << std::endl;

    return;
  }
  
  //----------------------------------------------------------------------
  // private functions

  /*!
   * @brief Setting to connect to broker
   */
  bool OutPortMosquittoPublisher::
  subscribeMosquittoPublisher(const SDOPackage::NVList& properties)
  {
    RTC_TRACE(("subscribeMosquittoPublisher()"));

    const char* pn_host = "host";
    const char* pn_topic = "topic";
    const char* pn_qos = "qos";
    const char* pn_id = "pid";

    CORBA::Long index0, index1, index2, index3;
    index0 = NVUtil::find_index(properties, pn_host);
    index1 = NVUtil::find_index(properties, pn_topic);
    index2 = NVUtil::find_index(properties, pn_qos);
    index3 = NVUtil::find_index(properties, pn_id);

    const char* tmp_host = "localhost";
    const char* tmp_topic = "test";
    const char* str_qos = "0";
    int tmp_qos = 0;

    struct timespec pub_num;
    clock_gettime(CLOCK_REALTIME, &pub_num);
    //const char* tmp_id = "mqtt/pub0";
    std::string pub_id = "pub";
    pub_id += std::to_string((long)(pub_num.tv_sec * 1.0E9 + pub_num.tv_nsec));
    const char* tmp_id = pub_id.c_str();

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
      std::cout << "MQTT Client ID not found. Timestamp ID is used." << std::endl;
      //return false;
    }
    else{
      if(!(NVUtil::isString(properties, pn_id)))
      {
        //RTC_ERROR(("MQTT Client ID is not string"));
        std::cout << "MQTT Client ID is not string. Timestamp ID is used." << std::endl;
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

  /*!
   * @if jp
   * @brief リターンコード変換
   * @else
   * @brief Return codes conversion
   * @endif
   */
  DataPortStatus
  OutPortMosquittoPublisher::convertReturnCode(OpenRTM::PortStatus ret)
  {
    switch (ret)
      {
      case OpenRTM::PORT_OK:
        return DataPortStatus::PORT_OK;
        break;
      case OpenRTM::PORT_ERROR:
        return DataPortStatus::PORT_ERROR;
        break;
      case OpenRTM::BUFFER_FULL:
        return DataPortStatus::SEND_FULL;
        break;
      case OpenRTM::BUFFER_TIMEOUT:
        return DataPortStatus::SEND_TIMEOUT;
        break;
      case OpenRTM::UNKNOWN_ERROR: /* FALLTHROUGH */
      case OpenRTM::BUFFER_EMPTY:  /* FALLTHROUGH */
      default:
        return DataPortStatus::UNKNOWN_ERROR;
        break;
      }
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
  void OutPortMosquittoPublisherInit(void)
  //DLL_EXPORT void OutPortMosquittoPublisherInit(RTC::Manager* manager)
  {
    RTC::InPortConsumerFactory& factory(RTC::InPortConsumerFactory::instance());
    factory.addFactory("mosq_mqtt",
                       ::coil::Creator< ::RTC::InPortConsumer,
                                        ::RTC::OutPortMosquittoPublisher>,
                       ::coil::Destructor< ::RTC::InPortConsumer,
                                           ::RTC::OutPortMosquittoPublisher>);
  }
};

/*
void registerModule(void)
{
  std::cout << "[Mosquitto Publisher initialization start]" << std::endl;
  OutPortMosquittoPublisherInit();
  std::cout << "[Mosquitto Publisher initialization end]" << std::endl;
};
*/

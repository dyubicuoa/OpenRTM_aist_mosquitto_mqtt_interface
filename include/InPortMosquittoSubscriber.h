// -*- C++ -*-
/*!
 * @file  InPortMosquittoSubscriber.h
 * @brief InPortMosquittoSubscriber class
 * @date  $Date: 2019-07-29 10:11:04 $
 * @author Daishi Yoshino <daishi-y@u-aizu.ac.jp>
 */

#ifndef RTC_INPORTMOSQUITTOSUBSCRIBER_H
#define RTC_INPORTMOSQUITTOSUBSCRIBER_H

//#include <rtm/idl/DataPortSkel.h>
//#include <rtm/SystemLogger.h>
#include <rtm/idl/DataPort_OpenRTMSkel.h>
#include <rtm/BufferBase.h>
#include <rtm/InPortProvider.h>
#include <rtm/CORBA_SeqUtil.h>
#include <rtm/Manager.h>
#include <rtm/ConnectorListener.h>
#include <rtm/ConnectorBase.h>
//#include <sys/time.h>

#include "MosquittoSubscriber.h"

namespace RTC
{
  /*!
   * @if jp
   * @class InPortMosquittoSubscriber
   * @brief InPortMosquittoSubscriber クラス
   *
   * データ転送に MQTT の Mosquitto 通信インターフェースを利用し
   * pub/sub型のデータフローを実現する InPort Subscriber クラス。
   *
   * @else
   * @class InPortMosquittoSubscriber
   * @brief InPortMosquittoSubscriber class
   * @endif
   */
  class InPortMosquittoSubscriber
    : public InPortProvider, public MosquittoSubscriber
  {
  public:
    /*!
     * @if jp
     * @brief コンストラクタ
     * @else
     * @brief Constructor
     * @endif
     */
    InPortMosquittoSubscriber();
    
    /*!
     * @if jp
     * @brief デストラクタ
     * @else
     * @brief Destructor
     * @endif
     */
    ~InPortMosquittoSubscriber() override;

    /*!
     * @if jp
     * @brief 設定初期化
     * @else
     * @brief Initializing configuration
     * @endif
     */
    void init(coil::Properties& prop) override;

    /*!
     * @if jp
     * @brief バッファをセットする
     * @else
     * @brief Setting outside buffer's pointer
     * @endif
     */
    void setBuffer(BufferBase<ByteData>* buffer) override;

    /*!
     * @if jp
     * @brief リスナを設定する。
     * @else
     * @brief Set the listener. 
     * @endif
     */
    void setListener(ConnectorInfo& info,
                     ConnectorListenersBase* listeners) override;

    /*!
     * @if jp
     * @brief Connectorを設定する。
     * @else
     * @brief set Connector
     * @endif
     */
    void setConnector(InPortConnector* connector) override;

    /*!
     * @brief Publish InterfaceProfle information
     */
    void publishInterfaceProfile(SDOPackage::NVList& properties) override;

    /*!
     * @brief Publish interface information
     */
    bool publishInterface(SDOPackage::NVList& properties) override;
    
    /*************************************************************************
     * messageReceiveCallback
     *
     * The message callback is invoked for each Direct message received by
     * the Session. In this sample, the message is printed to the screen.
     *************************************************************************/
    void on_message(const struct mosquitto_message* message) override;

  private:
    /*!
     * @if jp
     * @brief リターンコード変換
     * @else
     * @brief Return codes conversion
     * @endif
     */
    ::OpenRTM::PortStatus
    convertReturn(BufferStatus status,
                  ByteData& data);

    
    /*!
     * @if jp
     * @brief ON_BUFFER_WRITE のリスナへ通知する。 
     * @else
     * @brief Notify an ON_BUFFER_WRITE event to listeners
     * @endif
     */
    inline void onBufferWrite(ByteData& data)
    {
      //m_listeners->
      //  connectorData_[ON_BUFFER_WRITE].notifyIn(m_profile, data);
      m_listeners->notifyIn(ConnectorDataListenerType::ON_BUFFER_WRITE, m_profile, data);
    }

    /*!
     * @if jp
     * @brief ON_BUFFER_FULL のリスナへ通知する。 
     * @else
     * @brief Notify an ON_BUFFER_FULL event to listeners
     * @endif
     */
    inline void onBufferFull(ByteData& data)
    {
      //m_listeners->
      //  connectorData_[ON_BUFFER_FULL].notifyIn(m_profile, data);
      m_listeners->notifyIn(ConnectorDataListenerType::ON_BUFFER_FULL, m_profile, data);
    }

    /*!
     * @if jp
     * @brief ON_BUFFER_WRITE_TIMEOUT のリスナへ通知する。 
     * @else
     * @brief Notify an ON_BUFFER_WRITE_TIMEOUT event to listeners
     * @endif
     */
    inline void onBufferWriteTimeout(ByteData& data)
    {
      //m_listeners->
      //  connectorData_[ON_BUFFER_WRITE_TIMEOUT].notifyIn(m_profile, data);
      m_listeners->notifyIn(ConnectorDataListenerType::ON_BUFFER_WRITE_TIMEOUT, m_profile, data);
    }

    /*!
     * @if jp
     * @brief ON_BUFFER_WRITE_OVERWRITE のリスナへ通知する。 
     * @else
     * @brief Notify an ON_BUFFER_WRITE_OVERWRITE event to listeners
     * @endif
     */
    inline void onBufferWriteOverwrite(ByteData& data)
    {
      //m_listeners->
      //  connectorData_[ON_BUFFER_OVERWRITE].notifyIn(m_profile, data);
      m_listeners->notifyIn(ConnectorDataListenerType::ON_BUFFER_OVERWRITE, m_profile, data);
    }

    /*!
     * @if jp
     * @brief ON_RECEIVED のリスナへ通知する。 
     * @else
     * @brief Notify an ON_RECEIVED event to listeners
     * @endif
     */
    inline void onReceived(ByteData& data)
    {
      //m_listeners->
      //  connectorData_[ON_RECEIVED].notifyIn(m_profile, data);
      m_listeners->notifyIn(ConnectorDataListenerType::ON_RECEIVED, m_profile, data);
    }

    /*!
     * @if jp
     * @brief ON_RECEIVER_FULL のリスナへ通知する。 
     * @else
     * @brief Notify an ON_RECEIVER_FULL event to listeners
     * @endif
     */
    inline void onReceiverFull(ByteData& data)
    {
      //m_listeners->
      //  connectorData_[ON_RECEIVER_FULL].notifyIn(m_profile, data);
      m_listeners->notifyIn(ConnectorDataListenerType::ON_RECEIVER_FULL, m_profile, data);
    }

    /*!
     * @if jp
     * @brief ON_RECEIVER_TIMEOUT のリスナへ通知する。 
     * @else
     * @brief Notify an ON_RECEIVER_TIMEOUT event to listeners
     * @endif
     */
    inline void onReceiverTimeout(ByteData& data)
    {
      //m_listeners->
      //  connectorData_[ON_RECEIVER_TIMEOUT].notifyIn(m_profile, data);
      m_listeners->notifyIn(ConnectorDataListenerType::ON_RECEIVER_TIMEOUT, m_profile, data);
    }

    /*!
     * @if jp
     * @brief ON_RECEIVER_ERRORのリスナへ通知する。 
     * @else
     * @Brief Notify an ON_RECEIVER_ERROR event to listeners
     * @endif
     */
    inline void onReceiverError(ByteData& data)
    {
      //m_listeners->
      //  connectorData_[ON_RECEIVER_ERROR].notifyIn(m_profile, data);
      m_listeners->notifyIn(ConnectorDataListenerType::ON_RECEIVER_ERROR, m_profile, data);
    }

    /*!
     * @brief Subscriber_Information
     */
    bool subscribeMosquittoSubscriber(const SDOPackage::NVList& properties);

  private:
    CdrBufferBase* m_buffer{nullptr};
    //::OpenRTM::InPortCdr_var m_objref;
    ConnectorListenersBase* m_listeners;
    ConnectorInfo m_profile;
    InPortConnector* m_connector{nullptr};
    //ByteData m_cdr;

  };  // class InPortMosquittoSubscriber
};    // namespace RTC

extern "C"
{
  /*!
   * @if jp
   * @brief モジュール初期化関数
   * @else
   * @brief Module initialization
   * @endif
   */
  void InPortMosquittoSubscriberInit(void);
};

#endif // RTC_INPORTMOSQUITTOSUBSCRIBER_H

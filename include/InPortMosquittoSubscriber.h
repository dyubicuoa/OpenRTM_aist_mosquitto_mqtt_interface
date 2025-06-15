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
   * @brief InPortMosquittoSubscriber ���饹
   *
   * �ǡ���ž���� MQTT �� Mosquitto �̿����󥿡��ե����������Ѥ�
   * pub/sub���Υǡ����ե���¸����� InPort Subscriber ���饹��
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
     * @brief ���󥹥ȥ饯��
     * @else
     * @brief Constructor
     * @endif
     */
    InPortMosquittoSubscriber();
    
    /*!
     * @if jp
     * @brief �ǥ��ȥ饯��
     * @else
     * @brief Destructor
     * @endif
     */
    ~InPortMosquittoSubscriber() override;

    /*!
     * @if jp
     * @brief ��������
     * @else
     * @brief Initializing configuration
     * @endif
     */
    void init(coil::Properties& prop) override;

    /*!
     * @if jp
     * @brief �Хåե��򥻥åȤ���
     * @else
     * @brief Setting outside buffer's pointer
     * @endif
     */
    void setBuffer(BufferBase<ByteData>* buffer) override;

    /*!
     * @if jp
     * @brief �ꥹ�ʤ����ꤹ�롣
     * @else
     * @brief Set the listener. 
     * @endif
     */
    void setListener(ConnectorInfo& info,
                     ConnectorListenersBase* listeners) override;

    /*!
     * @if jp
     * @brief Connector�����ꤹ�롣
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
     * @brief �꥿���󥳡����Ѵ�
     * @else
     * @brief Return codes conversion
     * @endif
     */
    ::OpenRTM::PortStatus
    convertReturn(BufferStatus status,
                  ByteData& data);

    
    /*!
     * @if jp
     * @brief ON_BUFFER_WRITE �Υꥹ�ʤ����Τ��롣 
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
     * @brief ON_BUFFER_FULL �Υꥹ�ʤ����Τ��롣 
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
     * @brief ON_BUFFER_WRITE_TIMEOUT �Υꥹ�ʤ����Τ��롣 
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
     * @brief ON_BUFFER_WRITE_OVERWRITE �Υꥹ�ʤ����Τ��롣 
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
     * @brief ON_RECEIVED �Υꥹ�ʤ����Τ��롣 
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
     * @brief ON_RECEIVER_FULL �Υꥹ�ʤ����Τ��롣 
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
     * @brief ON_RECEIVER_TIMEOUT �Υꥹ�ʤ����Τ��롣 
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
     * @brief ON_RECEIVER_ERROR�Υꥹ�ʤ����Τ��롣 
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
   * @brief �⥸�塼�������ؿ�
   * @else
   * @brief Module initialization
   * @endif
   */
  void InPortMosquittoSubscriberInit(void);
};

#endif // RTC_INPORTMOSQUITTOSUBSCRIBER_H

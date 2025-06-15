// -*- C++ -*-
/*!
 * @file  OutPortMosquittoPublisher.h
 * @brief OutPortMosquittoPublisher class
 * @date  $Date: 2019-07-29 10:11:04 $
 * @author Daishi Yoshino <daishi-y@u-aizu.ac.jp>
 */

#ifndef RTC_OUTPORTMOSQUITTOPUBLISHER_H
#define RTC_OUTPORTMOSQUITTOPUBLISHER_H


//#include <rtm/idl/DataPortSkel.h>
#include <rtm/SystemLogger.h>
#include <rtm/idl/DataPort_OpenRTMSkel.h>
#include <rtm/InPortConsumer.h>
#include <rtm/Manager.h>
//#include <sys/time.h>

#include "MosquittoPublisher.h"

namespace RTC
{
  /*!
   * @if jp
   * @class OutPortMosquittoPublisher
   * @brief OutPortMosquittoPublisher ���饹
   *
   * �ǡ���ž���� MQTT �� Mosquitto �̿����󥿡��ե����������Ѥ�
   * Pub/Sub���Υǡ����ե���¸����� OutPort Publisher ���饹��
   *
   * @else
   * @class OutPortMosquittoPublisher
   * @brief OutPortMosquittoPublisher class
   * @endif
   */
  class OutPortMosquittoPublisher
    : public InPortConsumer, public MosquittoPublisher
  {
  public:
    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     * @else
     * @brief Constructor
     * @endif
     */
    OutPortMosquittoPublisher();
    
    /*!
     * @if jp
     * @brief �ǥ��ȥ饯��
     * @else
     * @brief Destructor
     * @endif
     */
    ~OutPortMosquittoPublisher() override;

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
     * @brief ��³��ؤΥǡ�������
     * @else
     * @brief Send data to the destination port
     * @endif
     */
    DataPortStatus put(ByteData& data) override;

    /*!
     * @if jp
     * @brief InterfaceProfile������������
     * @else
     * @brief Publish InterfaceProfile information
     * @endif
     */
    void publishInterfaceProfile(SDOPackage::NVList& properties) override;

    /*!
     * @if jp
     * @brief �ǡ����������Τؤ���Ͽ
     * @else
     * @brief Subscribe to the data sending notification
     * @endif
     */
    bool subscribeInterface(const SDOPackage::NVList& properties) override;
    
    /*!
     * @if jp
     * @brief �ǡ����������Τ������Ͽ���
     * @else
     * @brief Unsubscribe the data send notification
     * @endif
     */
    void unsubscribeInterface(const SDOPackage::NVList& properties) override;

  private:
    bool subscribeMosquittoPublisher(const SDOPackage::NVList& properties);

  private:
    /*!
     * @if jp
     * @brief �꥿���󥳡����Ѵ�
     * @else
     * @brief Return codes conversion
     * @endif
     */
    static DataPortStatus convertReturnCode(OpenRTM::PortStatus ret);

    mutable Logger rtclog;
    coil::Properties m_properties;
  };
};     // namespace RTC

extern "C"
{
  /*!
   * @if jp
   * @brief �⥸�塼�������ؿ�
   * @else
   * @brief Module initialization
   * @endif
   */
  void OutPortMosquittoPublisherInit(void);
  //DLL_EXPORT void OutPortMosquittoPublisherInit(RTC::Manager* manager);
};

#endif // RTC_OUTPORTMOSQUITTOPUBLISHER_H


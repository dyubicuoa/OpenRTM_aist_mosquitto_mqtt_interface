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
   * @brief OutPortMosquittoPublisher クラス
   *
   * データ転送に MQTT の Mosquitto 通信インターフェースを利用し
   * Pub/Sub型のデータフローを実現する OutPort Publisher クラス。
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
     * @brief コンストラクタ
     * @else
     * @brief Constructor
     * @endif
     */
    OutPortMosquittoPublisher();
    
    /*!
     * @if jp
     * @brief デストラクタ
     * @else
     * @brief Destructor
     * @endif
     */
    ~OutPortMosquittoPublisher() override;

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
     * @brief 接続先へのデータ送信
     * @else
     * @brief Send data to the destination port
     * @endif
     */
    DataPortStatus put(ByteData& data) override;

    /*!
     * @if jp
     * @brief InterfaceProfile情報を公開する
     * @else
     * @brief Publish InterfaceProfile information
     * @endif
     */
    void publishInterfaceProfile(SDOPackage::NVList& properties) override;

    /*!
     * @if jp
     * @brief データ送信通知への登録
     * @else
     * @brief Subscribe to the data sending notification
     * @endif
     */
    bool subscribeInterface(const SDOPackage::NVList& properties) override;
    
    /*!
     * @if jp
     * @brief データ送信通知からの登録解除
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
     * @brief リターンコード変換
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
   * @brief モジュール初期化関数
   * @else
   * @brief Module initialization
   * @endif
   */
  void OutPortMosquittoPublisherInit(void);
  //DLL_EXPORT void OutPortMosquittoPublisherInit(RTC::Manager* manager);
};

#endif // RTC_OUTPORTMOSQUITTOPUBLISHER_H


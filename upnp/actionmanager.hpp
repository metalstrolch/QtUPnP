#ifndef ACTION_MANAGER_HPP
#define ACTION_MANAGER_HPP 1

#include "using_upnp_namespace.hpp"
#include "upnp_global.hpp"
#include <QtNetwork/QNetworkReply>
#include <QEventLoop>

START_DEFINE_UPNP_NAMESPACE

class CActionInfo;

/*! \brief Provides the mechanism to sent action to the device.
 *
 * The action message is sent using a QNetworkManager.
 */
class UPNP_API CActionManager : public QEventLoop
{
  Q_OBJECT

public :
  enum ETime { Timeout = 5000 }; //!< HTTP request timeout in ms (5s).

  /*! Default constructor. */
  CActionManager (QObject* parent = nullptr);

  /*! Destructor. */
  ~CActionManager ();

  /*! Post an upnp action on the network.
   * \param device: The device uuid.
   * \param url: The destination url.
   * \param info: The class CActionInfo that contains the formatted message to sent end the response.
   * \param timeout: Maximum time for the responds.
   */
  bool post (QString const & device, QUrl const & url, CActionInfo& info,
             int timeout = CActionManager::Timeout);

  /*! The time to execute the last action. */
  static int lastElapsedTime () { return m_elapsedTime; }

  /*! The error generated by the last action.
   * A better way is to use the signal/slot mecanism to handle the error. See CControlPoint.
   */
  static QString lastError () { return m_lastError; }

protected:
  /*! This function is called in case of timeout. */
  virtual void timerEvent (QTimerEvent*);

private slots:
  /*! Slot call when the responds is finished. */
  void finished ();

  /*! Slot for network error.
   * \param err: The QNetworkReply::NetworkError code.
   */
  void error (QNetworkReply::NetworkError err);

signals :
  /*! Signal for network error. */
  void networkError (QString const &, QNetworkReply::NetworkError, QString const &);

private :
  int     m_milliSeconds = Timeout; //!< Timeout in ms.
  QString m_device; //!< Device uuid.

  static int m_elapsedTime; //!< The time to execute the last action.
  static QString m_lastError; //!< The error generated by the last action.
}; // CActionManager

} // Namespace

#endif

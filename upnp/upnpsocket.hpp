#ifndef UPNP_SOCKET_HPP
#define UPNP_SOCKET_HPP 1

#include "using_upnp_namespace.hpp"
#include "upnp_global.hpp"
#include <QUdpSocket>
#include <QUrl>

START_DEFINE_UPNP_NAMESPACE

/*! \brief The base class of CUnicastSocket and CMulticastSocket. */
class UPNP_API CUpnpSocket : public QUdpSocket
{
public :
  /*! \brief The structure holds information about the device that extracted from datagram using UDP sockets.*/
  struct SNDevice
  {
    /*! The device message type. */
    enum EType { Unknown, //!< Unknown
                 Notify, //!< NOTIFY * HTTP/1.1
                 Search, //!< M-SEARCH * HTTP/1.1
                 Response, //!< HTTP/1.1
                 Byebye //!< The NTS: header is ssdp:byebye
               };

    /*! Default constructor. */
    SNDevice (EType type = Unknown);

    /*! Constructor.
     *
     * \param type: The type.
     * \param url: The url of the device.
     * \param uuid: The uuid of the device.
     */
    SNDevice (EType type, QUrl const & url, QString const & uuid);

    /*! Copy constructor. */
    SNDevice (SNDevice const & other);

    /*! Equal operator. */
    SNDevice& operator =  (SNDevice const & other);

    /*! Equality operator. */
    bool operator == (SNDevice const & other) const;

    EType m_type; //!< The type.
    QUrl m_url; //!< The url.
    QString m_uuid; //!< The uuid.
  };

  /*! Default constructor. */
  CUpnpSocket (QObject* parent = nullptr);

  /*! Destructor. */
  virtual ~CUpnpSocket ();

  /*! Returns the device host address. */
  QHostAddress senderAddress () const { return m_senderAddr; }

  /*! Returns the port used by the device. */
  quint16 senderPort () const { return m_senderPort; }

  /*! Returns the current datagram. */
  QByteArray const & datagram () const { return m_datagram; }

  /*! Returns the datagram. */
  QByteArray const & readDatagrams ();

  /*! Decodes the datagram. */
  void decodeDatagram ();

  /*! Launchs the M-SEARCH udp datagram. */
  bool discover (QHostAddress hostAddress, quint16 port, quint16 mx = 1, char const * uuid = nullptr);

  /*! Clear the device list. */
  void resetDevices () { m_devices.clear (); }

  /*! Returns the device list. */
  QList<SNDevice> const & devices () const { return m_devices; }

  /*! Returns the local host address from router.
   * This function is used in case of multiple network interfaces.
   */
  static QHostAddress localHostAddressFromRouter ();

  /*! Returns the local host address.
   * This function returns the local host address of the first interface and different of 127.0.0.1.
   */
  static QHostAddress localHostAddress (bool ipv6 = false);

  void resetWait () { m_wait = StartingWait; }

private :
  /*! See CUpnpSocket::readDatagrams comment. */
  enum EWait { StartingWait = 30 };

  /*! Adds a device in the device list. */
  void addDevice (SNDevice const & device);

  /*! Creates a device from a datagram. */
  SNDevice createDevice (QByteArray datagram);

private :
  static QHostAddress m_localHostAddress; //!< The local host address.

private :
  QHostAddress m_senderAddr; //!< Host address of the device.
  quint16  m_senderPort; //!< The port used by the device.
  QByteArray m_datagram; //!< The current datagram.
  QList<SNDevice> m_devices; //!< The list of devices.
  int m_wait = StartingWait; //!< Current wait for linux system (2s). Reduce by 400ms at each call.
};

} // End namespace

#endif

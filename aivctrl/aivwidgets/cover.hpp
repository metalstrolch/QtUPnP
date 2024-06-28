#ifndef COVER_HPP
#define COVER_HPP

#include <QVideoWidget>
#include <QMediaPlayer>
#include <QLabel>

/*! \brief The CCover class is a simple image manager.
 * The main functionalities are to show the cover and scale the image at the size of the container.
 * In this case a Qlabel. The cover can be provided by the server or the cache.
 */
class CCover : public QVideoWidget
{
public:
  /*! Default constructor. */
  CCover (QWidget* parent = nullptr);

  /*! Sets an image from an uri. */
  void setImage (QString const & uri);

  /*! Returns the actual pixmap. */
  QPixmap image () const { return m_pixmap; }

  /*! Sets the default image. */
  void setDefaultPixmapName (QString const & name);

  /*! Returns the default image. */
  QString const & defaultPixmapName () const { return m_defaultPixmap; }

  /*! Returns Player*/
  QMediaPlayer * getPlayer(void) { return &m_player; }

  /*! Try to play URI */
  void playUri (const QString & uri);

protected :
  void resizeEvent(QResizeEvent *event) override;
protected :
  QMediaPlayer m_player;
  int m_imageTimeout = 10000; //!< Timeout to obtain the image from the server.
  QPixmap m_pixmap; //!< The actual pixmap.
  QString m_defaultPixmap; //!< The default image
  QLabel m_label;
};


#endif // COVER_HPP

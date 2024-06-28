#include "cover.hpp"
#include "widgethelper.hpp"
#include "../upnp/datacaller.hpp"
#include <QPainter>
#include <QUrl>
#include <QResizeEvent>

#include <stdio.h>

USING_UPNP_NAMESPACE

CCover::CCover (QWidget* parent) : QVideoWidget (parent), m_label{this}
{
  m_player.setVideoOutput(this);

  connect(&m_player, &QMediaPlayer::stateChanged, this, [this](QMediaPlayer::State state) {
    if(state == QMediaPlayer::PlayingState) {
       m_label.hide();
       m_label.lower();
    } else {
       m_label.show();
       m_label.raise();
    }
  });
  m_label.hide();
}

void CCover::resizeEvent(QResizeEvent *event)
{
  m_label.setAlignment (Qt::AlignCenter);
  m_label.resize(event->size());
  m_label.setPixmap(m_pixmap.scaled(event->size(),Qt::KeepAspectRatio));
  QVideoWidget::resizeEvent(event);
}

void CCover::setImage (QString const & uri)
{
  bool defName = true;
  if (!uri.isEmpty ())
  {
    QByteArray pxmBytes = CDataCaller ().callData (uri, m_imageTimeout);
    if (!pxmBytes.isEmpty ())
    {
      m_pixmap.loadFromData (pxmBytes);
      if (!m_pixmap.isNull ())
      {
        defName = false;
      }
    }
  }

  if (defName)
  {
    m_pixmap = QPixmap (::resIconFullPath (m_defaultPixmap));
  }
  m_label.setAlignment (Qt::AlignCenter);
  m_label.setPixmap(m_pixmap.scaled(m_label.size(),Qt::KeepAspectRatio));

  m_label.update ();
}

void CCover::playUri (const QString & uri)
{
  fprintf(stderr, "playUri == %s\n", uri.toStdString().c_str());
  m_player.stop();
  m_player.setMedia(nullptr);
  m_label.hide();
  m_player.setMedia(QUrl(uri));
  setMinimumWidth(10);
  setMinimumHeight(10);
  m_player.play();
  show();
}

void CCover::setDefaultPixmapName (QString const & pixmap)
{
    m_defaultPixmap = pixmap;
}

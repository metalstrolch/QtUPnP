#include "cover.hpp"
#include "widgethelper.hpp"
#include "../upnp/datacaller.hpp"
#include <QPainter>
#include <QUrl>
#include <QResizeEvent>

#include <stdio.h>

USING_UPNP_NAMESPACE

CCover::CCover (QWidget* parent) : QStackedWidget (parent)
{
  m_video = new QVideoWidget();
  m_player = new QMediaPlayer();
  m_label = new QLabel();

  addWidget(m_label);
  addWidget(m_video);

  m_video->setMinimumWidth(10);
  m_video->setMinimumHeight(10);
  m_player->setVideoOutput(m_video);

  connect(m_player, &QMediaPlayer::stateChanged, this, [this](QMediaPlayer::State state) {
    if(state == QMediaPlayer::PlayingState) {
      setCurrentIndex(1);
    } else {
      setCurrentIndex(0);
    }
  });
  setCurrentIndex(0);
}

CCover::~CCover()
{
  m_player->stop();
  m_player->setMedia(nullptr);
  delete(m_player);
  m_player=nullptr;
}

//void CCover::resizeEvent(QResizeEvent *event)
//{
//  m_label.setAlignment (Qt::AlignCenter);
//  m_label.resize(event->size());
//  m_label.setPixmap(m_pixmap.scaled(event->size(),Qt::KeepAspectRatio));
//  QVideoWidget::resizeEvent(event);
//}

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
  m_label->setAlignment (Qt::AlignCenter);
  m_label->setPixmap(m_pixmap.scaled(m_label->size(),Qt::KeepAspectRatio));

  m_label->update ();
}

void CCover::playUri (const QString & uri)
{
  fprintf(stderr, "playUri == %s\n", uri.toStdString().c_str());
  m_player->setMedia(QUrl(uri));
  m_video->setMinimumWidth(10);
  m_video->setMinimumHeight(10);
  m_video->show();
  m_player->play();
}

void CCover::setDefaultPixmapName (QString const & pixmap)
{
    m_defaultPixmap = pixmap;
}

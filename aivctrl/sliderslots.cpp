#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "../upnp/renderingcontrol.hpp"
#include "../upnp/avtransport.hpp"
#include "fakerenderer.hpp"

USING_UPNP_NAMESPACE

void CMainWindow::on_m_volume_valueChanged (int volume)
{
  if (!ui->m_volume->signalsBlocked ())
  {
    searchAction (false);
    if(isFakeRenderer(m_renderer))
      ui->m_cover->getPlayer()->setVolume(volume);
    else
      CRenderingControl (m_cp).setVolume (m_renderer, volume);
  }
}

void CMainWindow::on_m_volume2_valueChanged (int volume)
{
  if (!ui->m_volume->signalsBlocked ())
  {
    searchAction (false);
    if(isFakeRenderer(m_renderer))
      ui->m_cover->getPlayer()->setVolume(volume);
    else
      CRenderingControl (m_cp).setVolume (m_renderer, volume);
  }
}

void CMainWindow::on_m_position_valueChanged (int position)
{
  if (!ui->m_position->signalsBlocked ())
  {
    searchAction (false);
    QTime   time         = QTime (0, 0).addSecs (position);
    QString timePosition = time.toString ("hh:mm:ss");

    bool restart = false;
    if (m_positionTimer.isActive ())
    {
      restart = true;
      m_positionTimer.stop ();
    }
    if (isFakeRenderer(m_renderer)) {
      auto* player = ui->m_cover->getPlayer();
      if(player->isSeekable())
        player->setPosition(position * 1000);
    } else {
      CAVTransport (m_cp).seek (m_renderer, timePosition);
    }
    if (restart)
    {
      startPositionTimer ();
    }
  }
}

void CMainWindow::on_m_volume_actionTriggered (int action)
{
  searchAction (false);
  static_cast<CSlider*>(sender ())->jumpToMousePosition (action);
}

void CMainWindow::on_m_volume2_actionTriggered (int action)
{
  searchAction (false);
  static_cast<CSlider*>(sender ())->jumpToMousePosition (action);
}

void CMainWindow::on_m_position_actionTriggered (int action)
{
  CSlider* slider = static_cast<CSlider*>(sender ());
  searchAction (false);
  slider->jumpToMousePosition (action);
}

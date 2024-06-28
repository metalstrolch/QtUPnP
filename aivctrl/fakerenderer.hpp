#ifndef FAKERENDERER_HPP
#define FAKERENDERER_HPP

#include <QString>

#define LOCAL_PLAYBACK_GUID "local_playback_guid"

inline bool isFakeRenderer(QString player) {
    if(player == QStringLiteral(LOCAL_PLAYBACK_GUID))
       return true;
    return false;
}

#endif

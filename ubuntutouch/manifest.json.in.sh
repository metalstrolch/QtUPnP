#! /bin/sh
cat << EOF
{
    "name": "qtupnp.aivctrl",
    "description": "aivctrl a new control point based on Qt5 to manage UPnP (DLNA) media severs and renderers",
    "architecture": "${DEB_TARGET_ARCH}",
    "title": "AIVCtrl",
    "hooks": {
        "aivctrl": {
            "apparmor": "aivctrl.apparmor",
            "desktop":  "aivctrl.desktop"
        }
    },
    "version": "1.1.4",
    "maintainer": "Stefan Wildemann <spamfaenger@metalstrolche.de>",
    "framework" : "${SDK_FRAMEWORK}"
}
EOF

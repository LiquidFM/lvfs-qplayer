/**
 * This file is part of lvfs-qplayer.
 *
 * Copyright (C) 2011-2015 Dmitriy Vilkov, <dav.daemon@gmail.com>
 *
 * lvfs-qplayer is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * lvfs-qplayer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with lvfs-qplayer. If not, see <http://www.gnu.org/licenses/>.
 */

#include "lvfs_qplayer_Package.h"
#include "lvfs_qplayer_Plugin.h"


namespace LVFS {
namespace QPlayer {

Package::Package()
{}

Package::~Package()
{}

const char *Package::name() const
{
    return "QPlayer";
}

const Package::Plugin **Package::contentPlugins() const
{
    static const QPlayer::Plugin plugin;
    static const Plugin types[] =
    {
            { "video/dv",                      plugin },
            { "video/mpeg",                    plugin },
            { "video/x-mpeg",                  plugin },
            { "video/msvideo",                 plugin },
            { "video/quicktime",               plugin },
            { "video/x-anim",                  plugin },
            { "video/x-avi",                   plugin },
            { "video/x-ms-asf",                plugin },
            { "video/x-ms-wmv",                plugin },
            { "video/x-msvideo",               plugin },
            { "video/x-nsv",                   plugin },
            { "video/x-flc",                   plugin },
            { "video/x-fli",                   plugin },
            { "video/x-flv",                   plugin },
            { "video/vnd.rn-realvideo",        plugin },
            { "video/mp4",                     plugin },
            { "video/mp4v-es",                 plugin },
            { "video/mp2t",                    plugin },
            { "application/ogg",               plugin },
            { "application/x-ogg",             plugin },
            { "video/x-ogm+ogg",               plugin },
            { "audio/x-vorbis+ogg",            plugin },
            { "application/x-matroska",        plugin },
            { "audio/x-matroska",              plugin },
            { "video/x-matroska",              plugin },
            { "video/webm",                    plugin },
            { "audio/webm",                    plugin },
            { "audio/x-mp3",                   plugin },
            { "audio/x-mpeg",                  plugin },
            { "audio/mpeg",                    plugin },
            { "audio/x-wav",                   plugin },
            { "audio/x-mpegurl",               plugin },
            { "audio/x-scpls",                 plugin },
            { "audio/x-m4a",                   plugin },
            { "audio/x-ms-asf",                plugin },
            { "audio/x-ms-asx",                plugin },
            { "audio/x-ms-wax",                plugin },
            { "application/vnd.rn-realmedia",  plugin },
            { "audio/x-real-audio",            plugin },
            { "audio/x-pn-realaudio",          plugin },
            { "application/x-flac",            plugin },
            { "audio/x-flac",                  plugin },
            { "application/x-shockwave-flash", plugin },
            { "misc/ultravox",                 plugin },
            { "audio/vnd.rn-realaudio",        plugin },
            { "audio/x-pn-aiff",               plugin },
            { "audio/x-pn-au",                 plugin },
            { "audio/x-pn-wav",                plugin },
            { "audio/x-pn-windows-acm",        plugin },
            { "image/vnd.rn-realpix",          plugin },
            { "audio/x-pn-realaudio-plugin",   plugin },
            { "application/x-extension-mp4",   plugin },
            { "audio/mp4",                     plugin },
            { "audio/amr",                     plugin },
            { "audio/amr-wb",                  plugin },
            { "x-content/video-vcd",           plugin },
            { "x-content/video-svcd",          plugin },
            { "x-content/video-dvd",           plugin },
            { "x-content/audio-cdda",          plugin },
            { "x-content/audio-player",        plugin },
            { "application/xspf+xml",          plugin },
            { "x-scheme-handler/mms",          plugin },
            { "x-scheme-handler/rtmp",         plugin },
            { "x-scheme-handler/rtsp",         plugin }
    };
    enum { Count = sizeof(types) / sizeof(Plugin) };

    static const Plugin *res[Count + 1] = {};

    for (unsigned i = 0; i < Count; ++i)
        res[i] = &types[i];

    return res;
}

const Package::Plugin **Package::protocolPlugins() const
{
    return NULL;
}

}}


DECLARE_PLUGIN(::LVFS::QPlayer::Package)

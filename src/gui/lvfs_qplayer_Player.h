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

#ifndef LVFS_QPLAYER_PLAYER_H_
#define LVFS_QPLAYER_PLAYER_H_

#include <lvfs/IStream>
#include <QtGui/QDialog>
#include <platform/utils.h>
#include <phonon/videoplayer.h>


using namespace LVFS;


class PLATFORM_MAKE_PRIVATE Player : public QDialog
{
    Q_OBJECT

public:
    Player(const Interface::Adaptor<IStream> &file, QWidget *parent = 0);
    virtual ~Player();

private:
    Phonon::VideoPlayer m_player;
};

#endif /* LVFS_QPLAYER_PLAYER_H_ */

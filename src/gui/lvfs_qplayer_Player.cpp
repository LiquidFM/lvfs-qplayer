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

#include "lvfs_qplayer_Player.h"

#include <efc/Thread>

#include <phonon/abstractmediastream.h>


namespace {
    class Stream : public Phonon::AbstractMediaStream, public EFC::Thread
    {
    public:
        enum
        {
            BufferSize = 1 * 1024 * 1024
        };

    public:
        Stream(const Interface::Adaptor<IStream> &file, QObject *parent) :
            AbstractMediaStream(parent),
            m_size(0),
            m_abort(false),
            m_offset(-1),
            m_eof(false),
            m_needData(false),
            m_setOffset(false),
            m_file(file)
        {
            EFC::Mutex::Locker lock(m_handler.mutex());

            if (LIKELY(start() == NoError))
                m_handler.waitForStart();
            else
                m_file.reset();
        }

        virtual ~Stream()
        {
            EFC::Mutex::Locker lock(m_handler.mutex());

            if (m_handler.isRunning())
            {
                m_abort = true;
                m_needData = false;
                m_condition.wakeAll();
                m_handler.waitForStop();
            }
        }

    protected:
        /**
         * Reimplement this function to reset the stream. Subsequent calls to writeData should start
         * from the first position of the data unless a seek is requested.
         *
         * The function is necessary for the case where a non-seekable MediaStream is
         * played more than once. For a seekable stream the implementation can simply call
         * \code
         * seekStream(0);
         * \endcode.
         */
        virtual void reset()
        {
            seekStream(0);
        }

        /**
         * Reimplement this function to be notified when the backend needs data.
         *
         * When this function is called you should try to call writeData or endOfData before
         * returning.
         */
        virtual void needData()
        {
            EFC::Mutex::Locker lock(m_handler.mutex());

            if (m_handler.isRunning())
            {
                m_needData = true;
                m_condition.wakeAll();
            }
        }

        /**
         * Reimplement this function to be notified when the backend has enough data and your stream
         * object may take a break. This method is important for pushing data to the backend in
         * order to not fill the backend buffer unnecessarily.
         */
        virtual void enoughData()
        {
            EFC::Mutex::Locker lock(m_handler.mutex());

            if (m_handler.isRunning())
                m_needData = false;
        }

        /**
         * Reimplement this function if your stream is seekable.
         *
         * When this function is called the next call to writeData has to be at the requested \p
         * offset.
         *
         * \warning Do not call the parent implementation.
         */
        virtual void seekStream(qint64 offset)
        {
            EFC::Mutex::Locker lock(m_handler.mutex());

            if (m_handler.isRunning())
            {
                m_offset = offset;
                m_setOffset = true;
                m_condition.wakeAll();
            }
        }

    protected:
        virtual void run()
        {
            EFC::Mutex::Locker lock(m_handler.mutex());
            m_handler.signalStarted();

            for (;!m_abort;)
                if (m_setOffset)
                {
                    m_eof = !m_file->seek(m_offset, IStream::FromBeginning);
                    m_setOffset = false;
                }
                else if (!m_needData || m_eof)
                    m_condition.wait(m_handler.mutex());
                else
                {
                    EFC::Mutex::Unlocker unlock(lock);
                    size_t read;

                    do
                        if (read = m_file->read(m_buffer, BufferSize))
                            writeData(QByteArray::fromRawData(m_buffer, read));
                        else
                            m_eof = true;
                    while (m_needData && !m_eof && !m_setOffset);
                }

            m_handler.signalStopped();
        }

    private:
        int m_size;
        bool m_abort;
        qint64 m_offset;
        volatile bool m_eof;
        volatile bool m_needData;
        volatile bool m_setOffset;
        char m_buffer[BufferSize];
        StartStopHandler m_handler;
        EFC::WaitCondition m_condition;
        Interface::Adaptor<IStream> m_file;
    };
}


Player::Player(const Interface::Adaptor<IStream> &file, QWidget *parent) :
    QDialog(parent),
    m_player(this)
{
    m_player.load(new Stream(file, this));
    m_player.play();
}

Player::~Player()
{}

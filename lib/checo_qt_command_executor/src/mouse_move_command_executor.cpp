/*
 * MIT License
 *
 * Copyright (c) 2024 Sergei Cherevichko
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "checo/qt/mouse_move_command_executor.h"

#include <QApplication>
#include <QDataStream>
#include <QIODevice>
#include <QScreen>

#ifdef WIN32
#include <Windows.h>
// WARNING: Windows.h MUST be included first
#include <WinUser.h>
#endif // WIN32

namespace checo::qt
{

MouseMoveCommandExecutor::MouseMoveCommandExecutor() = default;

MouseMoveCommandExecutor::MouseMoveCommandExecutor(const Direction direction)
    : CommandExecutor{},
      m_Direction{direction}
{
}

MouseMoveCommandExecutor::~MouseMoveCommandExecutor() = default;

MouseMoveCommandExecutor::Direction MouseMoveCommandExecutor::direction() const
{
    return m_Direction;
}

void MouseMoveCommandExecutor::execute()
{
    const QRect screenGeometry = qApp->screens().front()->geometry();
    const int horzMovement = max(static_cast<int>(screenGeometry.width() * 0.004f), 3);
    const int vertMovement = max(static_cast<int>(screenGeometry.height() * 0.004f), 3);

#ifdef WIN32
    switch (m_Direction)
    {
    case Left:
        mouse_event(MOUSEEVENTF_MOVE, -horzMovement, 0, 0, 0);
        break;
    case Right:
        mouse_event(MOUSEEVENTF_MOVE, horzMovement, 0, 0, 0);
        break;
    case Up:
        mouse_event(MOUSEEVENTF_MOVE, 0, -vertMovement, 0, 0);
        break;
    case Down:
        mouse_event(MOUSEEVENTF_MOVE, 0, vertMovement, 0, 0);
        break;
    }
#endif // WIN32
}

QByteArray MouseMoveCommandExecutor::toByteArray() const
{
    QByteArray result;

    QDataStream resultStream(&result, QIODevice::WriteOnly);
    resultStream << m_Direction;

    return result;
}

void MouseMoveCommandExecutor::fromByteArray(const QByteArray &data)
{
    QDataStream dataStream(data);
    dataStream >> m_Direction;
}

QString MouseMoveCommandExecutor::toString()
{
    switch (m_Direction)
    {
    case Left:
        return QObject::tr("Mouse Pointer Left");
    case Right:
        return QObject::tr("Mouse Pointer Right");
    case Up:
        return QObject::tr("Mouse Pointer Up");
    case Down:
        return QObject::tr("Mouse Pointer Down");
    default:
        return QObject::tr("Mouse Move");
    }
}

} // namespace checo::qt

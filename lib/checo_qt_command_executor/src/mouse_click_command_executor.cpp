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

#include "checo/qt/mouse_click_command_executor.h"

#include <QDataStream>
#include <QIODevice>

#include <map>

#ifdef WIN32
#include <Windows.h>
// WARNING: Windows.h MUST be included first
#include "WinUser.h"
#endif // WIN32

namespace checo::qt
{

MouseClickCommandExecutor::MouseClickCommandExecutor() = default;

MouseClickCommandExecutor::MouseClickCommandExecutor(const Qt::MouseButton button)
    : CommandExecutor{},
      m_Button{button}
{
}

MouseClickCommandExecutor::~MouseClickCommandExecutor() = default;

Qt::MouseButton MouseClickCommandExecutor::button() const
{
    return m_Button;
}

void MouseClickCommandExecutor::execute()
{
#ifdef WIN32
    // Association of press/release events for all mouse buttons
    const std::map<Qt::MouseButton, std::pair<quint32, quint32>> actionMap = {
        {Qt::LeftButton, {MOUSEEVENTF_LEFTDOWN, MOUSEEVENTF_LEFTUP}},
        {Qt::RightButton, {MOUSEEVENTF_RIGHTDOWN, MOUSEEVENTF_RIGHTUP}},
        {Qt::MiddleButton, {MOUSEEVENTF_MIDDLEDOWN, MOUSEEVENTF_MIDDLEUP}},
        {Qt::XButton1, {MOUSEEVENTF_XDOWN, MOUSEEVENTF_XUP}}};

    DWORD dwData = 0;
    if (m_Button == Qt::XButton1)
        dwData = XBUTTON1;
    if (m_Button == Qt::XButton2)
        dwData = XBUTTON2;

    // Execute mouse click
    mouse_event(actionMap.at(m_Button).first, 0, 0, dwData, 0);
    mouse_event(actionMap.at(m_Button).second, 0, 0, dwData, 0);
#endif // WIN32
}

QByteArray MouseClickCommandExecutor::toByteArray() const
{
    QByteArray result;

    QDataStream resultStream(&result, QIODevice::WriteOnly);
    resultStream << m_Button;

    return result;
}

void MouseClickCommandExecutor::fromByteArray(const QByteArray &data)
{
    QDataStream dataStream(data);
    dataStream >> m_Button;
}

QString MouseClickCommandExecutor::toString()
{
    switch (m_Button)
    {
    case Qt::LeftButton:
        return QObject::tr("Mouse Left Click");
    case Qt::RightButton:
        return QObject::tr("Mouse Right Click");
    default:
        return QObject::tr("Mouse Click");
    }
}

} // namespace checo::qt

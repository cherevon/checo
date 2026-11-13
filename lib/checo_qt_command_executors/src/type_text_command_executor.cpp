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

#include "checo/qt/type_text_command_executor.h"

#include <QObject>

#ifdef WIN32
#include <Windows.h>
// WARNING: Windows.h MUST be included first
#include <WinUser.h>
#endif // WIN32

namespace checo::qt
{

TypeTextCommandExecutor::TypeTextCommandExecutor() = default;

TypeTextCommandExecutor::TypeTextCommandExecutor(const QString &text)
    : CommandExecutor(),
      m_Text(text)
{
}

TypeTextCommandExecutor::~TypeTextCommandExecutor() = default;

void TypeTextCommandExecutor::execute()
{
#ifdef WIN32
    std::u16string unicodeString = m_Text.toStdU16String();
    for (std::u16string::size_type i = 0; i < unicodeString.size(); ++i)
    {
        INPUT curKey;
        curKey.type = INPUT_KEYBOARD;
        curKey.ki.wVk = 0;
        curKey.ki.wScan = static_cast<WORD>(unicodeString[i]);
        curKey.ki.time = 0;
        curKey.ki.dwFlags = KEYEVENTF_UNICODE;
        SendInput(1, &curKey, sizeof(INPUT));

        curKey.ki.dwFlags = KEYEVENTF_KEYUP | KEYEVENTF_UNICODE;
        SendInput(1, &curKey, sizeof(INPUT));
    }
#endif // WIN32
}

QByteArray TypeTextCommandExecutor::toByteArray() const
{
    return m_Text.toUtf8();
}

void TypeTextCommandExecutor::fromByteArray(const QByteArray &data)
{
    m_Text = QString::fromUtf8(data);
}

QString TypeTextCommandExecutor::toString()
{
    int newLineIndex = m_Text.indexOf('\n');
    return QObject::tr("Paste: ") + ((newLineIndex >= 0) ? m_Text.sliced(0, newLineIndex) : m_Text);
}

} // namespace checo::qt

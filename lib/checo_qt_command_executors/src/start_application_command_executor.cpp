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

#include "checo/qt/start_application_command_executor.h"

#include <QDesktopServices>
#include <QUrl>

namespace checo::qt
{

StartApplicationCommandExecutor::StartApplicationCommandExecutor() = default;

StartApplicationCommandExecutor::StartApplicationCommandExecutor(const QString &displayName,
    const QFileInfo &executable)
    : CommandExecutor(),
      m_DisplayName(displayName),
      m_Executable(executable)
{
}

StartApplicationCommandExecutor::~StartApplicationCommandExecutor() = default;

const QString &StartApplicationCommandExecutor::displayName() const
{
    return m_DisplayName;
}

const QFileInfo &StartApplicationCommandExecutor::executable() const
{
    return m_Executable;
}

void StartApplicationCommandExecutor::execute()
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(m_Executable.absoluteFilePath()));
}

QByteArray StartApplicationCommandExecutor::toByteArray() const
{
    return m_DisplayName.toUtf8() + "|" + m_Executable.absoluteFilePath().toUtf8();
}

void StartApplicationCommandExecutor::fromByteArray(const QByteArray &data)
{
    const QList<QByteArray> parts = data.split('|');
    if (parts.size() == 2)
    {
        m_DisplayName = QString::fromUtf8(parts[0]);
        m_Executable = QFileInfo(QString::fromUtf8(parts[1]));
    }
}

QString StartApplicationCommandExecutor::toString()
{
    return QObject::tr("Launch \"%1\"").arg(m_DisplayName);
}

} // namespace checo::qt

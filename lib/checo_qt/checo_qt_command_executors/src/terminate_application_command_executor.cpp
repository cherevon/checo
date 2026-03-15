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

#include "checo/qt/terminate_application_command_executor.h"

#include <QDesktopServices>
#include <QDir>
#include <QUrl>

#ifdef WIN32
#include <windows.h>
// WARNING!!! Psapi.h MUST be included after Windows.h. Otherwise you will get a lot of compilation errors
#include <psapi.h>
#endif // WIN32

namespace checo::qt
{

#ifdef WIN32
BOOL CALLBACK EnumWindowsClosePath(HWND hwnd, LPARAM ptr)
{
    DWORD dwProcId = 0;
    GetWindowThreadProcessId(hwnd, &dwProcId);

    HANDLE procHandle = NULL;
    procHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, dwProcId);
    if (NULL == procHandle)
    {
        return TRUE;
    }

    WCHAR buffer[MAX_PATH] = {0};
    DWORD pathSize = GetModuleFileNameEx(procHandle, NULL, buffer, MAX_PATH);
    CloseHandle(procHandle);
    if (!pathSize)
    {
        return TRUE;
    }

    QString filePath = QString::fromWCharArray(buffer, pathSize);
    QString appPath = QDir::cleanPath(filePath).toLower();

    LPCWSTR pathPtr = reinterpret_cast<LPCWSTR>(ptr);
    QString killAppPath = QString::fromWCharArray(pathPtr);

    if (appPath.compare(killAppPath, Qt::CaseInsensitive) == 0)
    {
        DWORD processID;
        GetWindowThreadProcessId(hwnd, &processID);
        HANDLE processHandle = OpenProcess(PROCESS_TERMINATE, false, processID);
        TerminateProcess(processHandle, 0);
        CloseHandle(processHandle);
    }
    return TRUE;
}
#endif // WIN32

TerminateApplicationCommandExecutor::TerminateApplicationCommandExecutor() = default;

TerminateApplicationCommandExecutor::TerminateApplicationCommandExecutor(const QString &displayName,
    const QFileInfo &executable)
    : CommandExecutor(),
      m_DisplayName(displayName),
      m_Executable(executable)
{
}

TerminateApplicationCommandExecutor::~TerminateApplicationCommandExecutor() = default;

const QString &TerminateApplicationCommandExecutor::displayName() const
{
    return m_DisplayName;
}

const QFileInfo &TerminateApplicationCommandExecutor::executable() const
{
    return m_Executable;
}

void TerminateApplicationCommandExecutor::execute()
{
#ifdef WIN32
    EnumWindows(EnumWindowsClosePath, reinterpret_cast<LPARAM>(m_Executable.absoluteFilePath().toStdWString().c_str()));
#endif // WIN32
}

QByteArray TerminateApplicationCommandExecutor::toByteArray() const
{
    return m_DisplayName.toUtf8() + "|" + m_Executable.absoluteFilePath().toUtf8();
}

void TerminateApplicationCommandExecutor::fromByteArray(const QByteArray &data)
{
    const QList<QByteArray> parts = data.split('|');
    if (parts.size() == 2)
    {
        m_DisplayName = QString::fromUtf8(parts[0]);
        m_Executable = QFileInfo(QString::fromUtf8(parts[1]));
    }
}

QString TerminateApplicationCommandExecutor::toString()
{
    return QObject::tr("Close \"%1\"").arg(m_DisplayName);
}

} // namespace checo::qt

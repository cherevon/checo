#include "checo/command_executor/terminate_application.h"

#include <QDesktopServices>
#include <QDir>
#include <QUrl>

#ifdef WIN32
#include <windows.h>
// WARNING!!! Psapi.h MUST be included after Windows.h. Otherwise you will get a lot of compilation errors
#include <psapi.h>
#endif // WIN32

namespace checo::command_executor
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

TerminateAppCommandExecutor::TerminateAppCommandExecutor(const os::ApplicationInfo &appInfo)
    : CommandExecutor(), mAppInfo(appInfo)
{
}

const os::ApplicationInfo &TerminateAppCommandExecutor::applicationInfo() const
{
    return mAppInfo;
}

void TerminateAppCommandExecutor::execute()
{
#ifdef WIN32
    EnumWindows(EnumWindowsClosePath,
        reinterpret_cast<LPARAM>(mAppInfo.executable().absoluteFilePath().toStdWString().c_str()));
#endif // WIN32
}

QByteArray TerminateAppCommandExecutor::toByteArray() const
{
    return mAppInfo.toByteArray();
}

void TerminateAppCommandExecutor::fromByteArray(const QByteArray &data)
{
    mAppInfo.fromByteArray(data);
}

QString TerminateAppCommandExecutor::toString()
{
    return QObject::tr("Close \"%1\"").arg(mAppInfo.displayName());
}

} // namespace checo::command_executor

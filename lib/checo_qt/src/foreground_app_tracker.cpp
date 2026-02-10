#include "checo/qt/foreground_app_tracker.h"

#include <QDir>

#ifdef WIN32
#include <Windows.h>
// WARNING!!! Psapi.h MUST be included after Windows.h. Otherwise you will get a lot of compilation errors
#include <Psapi.h>
#include <WinUser.h>
#endif // WIN32

namespace checo::qt
{

#ifdef WIN32

/// Registered hooks. They are used to unhook
static std::map<HWINEVENTHOOK, ForegroundAppTracker *> winHooks;

QString hwndPath(HWND hwnd)
{
    DWORD pid = 0;
    GetWindowThreadProcessId(hwnd, &pid);
    HANDLE process_hwnd = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
    wchar_t fname[MAX_PATH];
    ZeroMemory(fname, sizeof(fname));
    DWORD size = GetModuleFileNameEx(process_hwnd, NULL, fname, MAX_PATH);

    QString filepath = QString::fromWCharArray(fname, size);
    CloseHandle(process_hwnd);

    return QDir::cleanPath(filepath).toLower();
}

VOID CALLBACK winEventProcCallback(HWINEVENTHOOK hWinEventHook, DWORD dwEvent, HWND, LONG, LONG, DWORD, DWORD)
{
    if (dwEvent == EVENT_SYSTEM_FOREGROUND || dwEvent == EVENT_OBJECT_FOCUS)
    {
        ForegroundAppTracker *tracker = winHooks[hWinEventHook];
        emit tracker->foregroundApplicationChanged();
    }
}

#endif // WIN32

ForegroundAppTracker::ForegroundAppTracker(QObject *parent)
    : QObject(parent)
{
#ifdef WIN32
    HWINEVENTHOOK newHook = SetWinEventHook(EVENT_SYSTEM_FOREGROUND, EVENT_OBJECT_FOCUS, NULL, winEventProcCallback, 0,
        0, WINEVENT_OUTOFCONTEXT);
    winHooks.emplace(newHook, this);
#endif // WIN32
}

ForegroundAppTracker::~ForegroundAppTracker()
{
#ifdef WIN32
    // Remove Windows event hook
    const auto delHook = std::find_if(winHooks.begin(), winHooks.end(),
        [this](const std::pair<HWINEVENTHOOK, ForegroundAppTracker *> checkHook) { return checkHook.second == this; });
    if (delHook != winHooks.end())
    {
        UnhookWinEvent(delHook->first);
        winHooks.erase(delHook);
    }
#endif // WIN32
}

QString ForegroundAppTracker::foregroundApplication() const
{
#ifdef WIN32
    return hwndPath(GetForegroundWindow());
#endif // WIN32
}

} // namespace checo::qt

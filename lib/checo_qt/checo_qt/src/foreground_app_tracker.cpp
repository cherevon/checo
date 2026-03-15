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

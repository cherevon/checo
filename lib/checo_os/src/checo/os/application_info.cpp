#include "checo/os/application_info.h"

#include <QDesktopServices>
#include <QFileIconProvider>
#include <QUrl>

#ifdef WIN32
#include <QDirIterator>

#include <Windows.h>
// WARNING!!! Psapi.h MUST be included after Windows.h. Otherwise you will get a lot of compilation errors
#include <Psapi.h>
#include <ShlObj.h>
#include <initguid.h>
// WARNING!!! initguid.h MUST be included before commoncontrols.h
#include <commctrl.h>
#include <commoncontrols.h>
#include <shellapi.h>
#endif // WIN32

namespace checo::os
{

#ifdef WIN32
/// Get path to the special directory in Windows specified by its \p id
QString getWindowsSpecialDirectoryPath(int id)
{
    TCHAR szDir[MAX_PATH];
    SHGetFolderPath(nullptr, id, nullptr, 0, szDir);
    return QString::fromStdWString(std::wstring(szDir));
}

bool isValidExecutable(const QString &displayName, const QFileInfo &executable)
{
    if (!executable.exists() || !executable.isExecutable())
        return false;

    for (const QString &excl : {"unin", "\\Windows\\Installer", "rundll", "update"})
    {
        if (displayName.contains(excl, Qt::CaseInsensitive))
            return false;
        if (executable.absoluteFilePath().contains(excl, Qt::CaseInsensitive))
            return false;
    }

    return true;
}

int CALLBACK testWin(HWND hwnd, LPARAM listPtr)
{
    const DWORD TITLE_SIZE = 1024;
    TCHAR fileName[TITLE_SIZE];
    DWORD procId;
    GetWindowThreadProcessId(hwnd, &procId);
    auto procHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, false, procId);

    GetModuleFileNameEx(procHandle, nullptr, fileName, TITLE_SIZE);

    std::list<QFileInfo> *procNames = reinterpret_cast<std::list<QFileInfo> *>(listPtr);
    procNames->push_back(QFileInfo(QString::fromUtf16(reinterpret_cast<const char16_t *>(fileName))));
    CloseHandle(procHandle);
    return true;
}

bool isMainWindow(HWND hwnd)
{
    HWND hwndTry, hwndWalk = NULL;
    hwndTry = GetAncestor(hwnd, GA_ROOTOWNER);
    while (hwndTry != hwndWalk)
    {
        hwndWalk = hwndTry;
        hwndTry = GetLastActivePopup(hwndWalk);
        if (IsWindowVisible(hwndTry))
            break;
    }
    if (hwndWalk != hwnd)
    {
        return false;
    }

    // the following removes some task tray programs and "Program Manager"
    TITLEBARINFO ti;
    ti.cbSize = sizeof(ti);
    GetTitleBarInfo(hwnd, &ti);
    if (ti.rgstate[0] & STATE_SYSTEM_INVISIBLE)
    {
        return false;
    }

    // Tool windows should not be displayed either, these do not appear in the
    // task bar.
    if (GetWindowLong(hwnd, GWL_EXSTYLE) & WS_EX_TOOLWINDOW)
    {
        return false;
    }

    return true;
}

int CALLBACK bringWindowToFrontCallback(HWND hwnd, LPARAM exeFileInfo)
{
    const DWORD TITLE_SIZE = 1024;
    TCHAR fileName[TITLE_SIZE];
    DWORD procId;
    GetWindowThreadProcessId(hwnd, &procId);
    auto procHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, false, procId);

    GetModuleFileNameEx(procHandle, nullptr, fileName, TITLE_SIZE);

    const QFileInfo *exePath = reinterpret_cast<QFileInfo *>(exeFileInfo);
    const QFileInfo processPath = QFileInfo(QString::fromUtf16(reinterpret_cast<const char16_t *>(fileName)));
    bool windowFound = (*exePath == processPath) && isMainWindow(hwnd);
    if (windowFound)
    {
        if (IsIconic(hwnd))
        {
            ShowWindow(hwnd, SW_RESTORE);
        }
        else
        {
            ShowWindow(hwnd, SW_SHOW);
            SetForegroundWindow(hwnd);
        }
    }
    CloseHandle(procHandle);

    return !windowFound;
}

#endif // WIN32

std::vector<ApplicationInfo> ApplicationInfo::installedApplications()
{
    std::vector<ApplicationInfo> result;

#ifdef WIN32
    for (const int dirID : {CSIDL_COMMON_PROGRAMS, CSIDL_PROGRAMS})
    {
        const QString directoryPath = getWindowsSpecialDirectoryPath(dirID);
        QDirIterator it(directoryPath, {"*"}, QDir::Files, QDirIterator::Subdirectories);
        while (it.hasNext())
        {
            const QFileInfo entry = it.fileInfo();
            if (entry.isSymLink())
            {
                const QFileInfo linkTarget = QFileInfo(entry.symLinkTarget());
                if (isValidExecutable(entry.completeBaseName(), linkTarget))
                    result.emplace_back(entry.completeBaseName(), linkTarget);
            }
            else if (isValidExecutable(entry.completeBaseName(), entry))
                result.emplace_back(entry.completeBaseName(), entry);

            it.next();
        }
    }
#endif // WIN32

    return result;
}

QIcon ApplicationInfo::getAssociatedIcon(const QFileInfo &file, const QSize &iconSize)
{
#ifdef WIN32
    SHFILEINFO shfi;
    const DWORD fileAttr = file.isDir() ? FILE_ATTRIBUTE_DIRECTORY : 0;
    SHGetFileInfo(file.absoluteFilePath().toStdWString().c_str(), fileAttr, &shfi, sizeof(shfi),
        SHGFI_ICON | SHGFI_USEFILEATTRIBUTES);

    HIMAGELIST imgList;
    HRESULT hRes = SHGetImageList((iconSize.width() > 64) ? SHIL_LAST : SHIL_LARGE, IID_IImageList, (void **)&imgList);
    if (hRes == S_OK)
    {
        HICON hIcon = ImageList_GetIcon(imgList, shfi.iIcon, ILD_TRANSPARENT);
        if (hIcon != NULL)
        {
            QIcon result(QPixmap::fromImage(QImage::fromHICON(hIcon)));
            DestroyIcon(hIcon);
            return result;
        }
        else
        {
            return QIcon();
        }
    }
    else
    {
        return QIcon();
    }
#endif // WIN32
}

std::list<QFileInfo> ApplicationInfo::getRunningWindows()
{
    std::list<QFileInfo> result;
#ifdef WIN32
    EnumWindows(testWin, (LPARAM)&result);
#endif // WIN32

    return result;
}

bool ApplicationInfo::isApplicationRunning(const QFileInfo &executablePath)
{
    const auto runningApps = getRunningWindows();
    return std::find(runningApps.begin(), runningApps.end(), executablePath) != runningApps.end();
}

void ApplicationInfo::openFile(const QFileInfo &file)
{
    if (ApplicationInfo::isApplicationRunning(file))
    {
#ifdef WIN32
        EnumWindows(bringWindowToFrontCallback, (LPARAM)&file);
#endif // WIN32
    }
    else
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile(file.absoluteFilePath()));
    }
}

ApplicationInfo::ApplicationInfo(const QString &name, const QFileInfo &exe) : mDisplayName(name), mExecutable(exe)
{
    mNormalIcon = getAssociatedIcon(mExecutable, QSize(48, 48));
    mLargeIcon = getAssociatedIcon(mExecutable, QSize(256, 256));
}

const QString &ApplicationInfo::displayName() const
{
    return mDisplayName;
}

void ApplicationInfo::setDisplayName(const QString &newDisplayName)
{
    mDisplayName = newDisplayName;
}

const QFileInfo &ApplicationInfo::executable() const
{
    return mExecutable;
}

void ApplicationInfo::setExecutable(const QFileInfo &newExecutable)
{
    mExecutable = newExecutable;
}

const QIcon &ApplicationInfo::normalIcon() const
{
    return mNormalIcon;
}

const QIcon &ApplicationInfo::largeIcon() const
{
    return mLargeIcon;
}

QByteArray ApplicationInfo::toByteArray() const
{
    QByteArray result;
    QDataStream data(&result, QIODevice::WriteOnly);

    // Write display name
    QByteArray displayNameBytes = mDisplayName.toUtf8();
    data << static_cast<int>(displayNameBytes.size());
    data.writeRawData(displayNameBytes.data(), displayNameBytes.size());

    // Write executable
    QByteArray executableBytes = mExecutable.absoluteFilePath().toUtf8();
    data << static_cast<int>(executableBytes.size());
    data.writeRawData(executableBytes.data(), executableBytes.size());

    return result;
}

void ApplicationInfo::fromByteArray(const QByteArray &data)
{
    QDataStream reader(data);

    // Read display name
    int stringSize{0};
    reader >> stringSize;
    QByteArray displayNameBytes;
    displayNameBytes.resize(static_cast<qsizetype>(stringSize));
    reader.readRawData(displayNameBytes.data(), stringSize);
    mDisplayName = QString::fromUtf8(displayNameBytes);

    // Read executable
    reader >> stringSize;
    QByteArray executableBytes;
    executableBytes.resize(static_cast<qsizetype>(stringSize));
    reader.readRawData(executableBytes.data(), stringSize);
    mExecutable = QFileInfo(QString::fromUtf8(executableBytes));
}

} // namespace checo::os

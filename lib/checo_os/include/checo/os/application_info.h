#pragma once

#include "checo_os_export.h"

#include <QFileInfo>
#include <QIcon>

#include <list>
#include <vector>

namespace checo::os
{

/// Information about a single application installed on the PC
class CHECO_OS_EXPORT ApplicationInfo
{
  public:
    static std::vector<ApplicationInfo> installedApplications();
    static QIcon getAssociatedIcon(const QFileInfo &file, const QSize &iconSize);
    static std::list<QFileInfo> getRunningWindows();
    static bool isApplicationRunning(const QFileInfo &executablePath);
    static void openFile(const QFileInfo &file);

  public:
    ApplicationInfo() = default;
    ApplicationInfo(const QString &name, const QFileInfo &exe);
    virtual ~ApplicationInfo() = default;

  public:
    const QString &displayName() const;
    void setDisplayName(const QString &newDisplayName);

    const QFileInfo &executable() const;
    void setExecutable(const QFileInfo &newExecutable);

    const QIcon &normalIcon() const;
    const QIcon &largeIcon() const;

  public:
    QByteArray toByteArray() const;
    void fromByteArray(const QByteArray &data);

  private:
    QString mDisplayName;
    QFileInfo mExecutable;
    QIcon mNormalIcon;
    QIcon mLargeIcon;
};

} // namespace checo::os

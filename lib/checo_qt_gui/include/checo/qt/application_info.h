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

#pragma once

#include "checo_qt_gui_export.h"

#include <QFileInfo>
#include <QIcon>

#include <list>
#include <vector>

namespace checo::qt
{

/// Information about a single application installed on the PC
class CHECO_QT_GUI_EXPORT ApplicationInfo
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

} // namespace checo::qt

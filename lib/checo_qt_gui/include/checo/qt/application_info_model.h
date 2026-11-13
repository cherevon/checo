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

#include "checo/qt/application_info.h"
#include "checo_qt_gui_export.h"

#include <QAbstractListModel>

#include <vector>

namespace checo::qt
{

/// Model that provides a list of applications
class CHECO_QT_GUI_EXPORT ApplicationInfoModel : public QAbstractListModel
{
    Q_OBJECT

  public:
    explicit ApplicationInfoModel(const std::vector<ApplicationInfo> &apps, QObject *parent = nullptr);
    virtual ~ApplicationInfoModel() = default;

  public:
    /// Get the application by its \p index
    inline const ApplicationInfo &application(const QModelIndex &index)
    {
        return mApps[index.row()];
    }

  public:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

  private:
    /// The list of all applications
    std::vector<ApplicationInfo> mApps;
};

} // namespace checo::qt

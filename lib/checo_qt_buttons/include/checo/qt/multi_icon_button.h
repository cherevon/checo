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

#include "checo_qt_buttons_export.h"

#include <QIcon>
#include <QPushButton>
#include <QStyle>

#include <map>

namespace checo::qt
{

/// Button that allows to set different icons for its different states
class CHECO_QT_BUTTONS_EXPORT MultiIconButton : public QPushButton
{
    Q_OBJECT

  public:
    /// Visualization of the button
    enum ButtonStyle
    {
        IconOnly,       ///< Display only icon
        TextUnderIcon,  ///< Display text under icon
        TextBesideIcon, ///< Display text beside icon
    };

  public:
    explicit MultiIconButton(QWidget *parent = nullptr);

  public:
    inline ButtonStyle buttonStyle() const
    {
        return mStyle;
    }

    void setButtonStyle(const ButtonStyle newStyle);

    void clearStateIcons();
    void setStateIcon(const QStyle::StateFlag state, const QIcon &icon);

    inline QMargins contentsPadding() const
    {
        return mContentsPadding;
    }

    void setContentsPadding(const int padding);
    void setContentsPadding(const QMargins &value);

  public:
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

  protected:
    void paintEvent(QPaintEvent *event) override;

  private:
    std::map<QStyle::StateFlag, QIcon> mStateIcons;
    ButtonStyle mStyle = TextBesideIcon;
    QMargins mContentsPadding = QMargins(7, 7, 7, 7);
};

} // namespace checo::qt

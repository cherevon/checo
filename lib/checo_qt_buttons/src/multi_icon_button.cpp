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

#include "checo/qt/multi_icon_button.h"

#include <QPaintEvent>
#include <QStyleOptionButton>
#include <QStylePainter>

namespace checo::qt
{

MultiIconButton::MultiIconButton(QWidget *parent)
    : QPushButton(parent)
{
}

void MultiIconButton::setButtonStyle(const ButtonStyle newStyle)
{
    mStyle = newStyle;
    update();
}

void MultiIconButton::clearStateIcons()
{
    mStateIcons.clear();
    update();
}

void MultiIconButton::setStateIcon(const QStyle::StateFlag state, const QIcon &icon)
{
    mStateIcons[state] = icon;
}

void MultiIconButton::setContentsPadding(const int padding)
{
    setContentsPadding(QMargins(padding, padding, padding, padding));
}

void MultiIconButton::setContentsPadding(const QMargins &value)
{
    mContentsPadding = value;
    update();
}

QSize MultiIconButton::sizeHint() const
{
    return minimumSizeHint();
}

QSize MultiIconButton::minimumSizeHint() const
{
    const int spacing = (icon().isNull() || text().isEmpty()) ? 0 : fontMetrics().averageCharWidth();
    const int textWidth = fontMetrics().horizontalAdvance(text());
    const int textHeight = fontMetrics().height();
    const QSize realIconSize = iconSize();
    QSize bestContentSize;
    switch (mStyle)
    {
    case IconOnly:
        bestContentSize = realIconSize;
        break;
    case TextBesideIcon:
        bestContentSize =
            QSize(realIconSize.width() + spacing + textWidth, std::max(realIconSize.height(), textHeight));
        break;
    case TextUnderIcon:
        bestContentSize =
            QSize(std::max(realIconSize.width(), textWidth), realIconSize.height() + textHeight + spacing);
        break;
    }
    return bestContentSize.grownBy(mContentsPadding);
}

void MultiIconButton::paintEvent(QPaintEvent *)
{
    QStylePainter painter(this);

    // Prepare style options to render this control as a typical QPushButton
    QStyleOptionButton option;
    initStyleOption(&option);

    // Change icon to be rendered to the correct one
    for (const auto &[state, icon] : mStateIcons)
    {
        if (option.state.testFlag(state))
        {
            // Don't render mouseover icons for disabled buttons
            if (!isEnabled() && state == QStyle::State_MouseOver)
            {
                continue;
            }
            option.icon = icon;
        }
    }

    // When the mouse is over this button we highlight text color
    if (option.state.testFlag(QStyle::State_MouseOver))
        option.palette.setColor(QPalette::ButtonText, option.palette.color(QPalette::Highlight));

    // Render the button box
    if (!isFlat())
    {
        QStyleOptionButton drawOption;
        initStyleOption(&drawOption);
        drawOption.icon = QIcon();
        drawOption.text = "";
        painter.drawControl(QStyle::CE_PushButton, drawOption);
    }

    // Determine rectangles for button contents (icon and text)
    QRect iconRect;
    QRect textRect;
    const int spacing = (option.icon.isNull() || option.text.isEmpty()) ? 0 : option.fontMetrics.averageCharWidth();
    switch (mStyle)
    {
    case IconOnly:
    {
        const int widthDiff = option.rect.width() - option.iconSize.width();
        const int heightDiff = option.rect.height() - option.iconSize.height();
        iconRect = option.rect.adjusted(widthDiff / 2, heightDiff / 2, -widthDiff / 2, -heightDiff / 2);
    }
    break;
    case TextBesideIcon:
    {
        const int textWidth = option.fontMetrics.horizontalAdvance(option.text);
        const int textHeight = option.fontMetrics.height();
        const int contentWidth = option.iconSize.width() + spacing + textWidth;
        const int contentLeft = (option.rect.width() - contentWidth) / 2;
        iconRect = QRect(contentLeft, (option.rect.height() - option.iconSize.height()) / 2, option.iconSize.width(),
            option.iconSize.height());
        textRect = QRect(iconRect.right() + spacing, (option.rect.height() - textHeight) / 2, textWidth, textHeight);
    }
    break;
    case TextUnderIcon:
    {
        const int textWidth = option.fontMetrics.horizontalAdvance(option.text);
        const int textHeight = option.fontMetrics.height();
        const int contentHeight = option.iconSize.height() + spacing + textHeight;
        const int contentTop = (option.rect.height() - contentHeight) / 2;
        iconRect = QRect((option.rect.width() - option.iconSize.width()) / 2, contentTop, option.iconSize.width(),
            option.iconSize.height());
        textRect = QRect((option.rect.width() - textWidth) / 2, iconRect.bottom() + spacing, textWidth, textHeight);
    }
    break;
    }

    // Render icon
    iconRect.setSize(option.iconSize);
    option.icon.paint(&painter, iconRect);

    // Render text
    if (mStyle != IconOnly)
    {
        painter.setPen(option.palette.color(QPalette::ButtonText));
        painter.drawText(textRect, Qt::AlignCenter, option.text);
    }
}

} // namespace checo::qt

#pragma once

#include "checo_buttons_export.h"

#include <QIcon>
#include <QPushButton>
#include <QStyle>

#include <map>

namespace checo::ui
{

/// Button that allows to set different icons for its different states
class CHECO_BUTTONS_EXPORT MultiIconButton : public QPushButton
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

} // namespace checo::ui

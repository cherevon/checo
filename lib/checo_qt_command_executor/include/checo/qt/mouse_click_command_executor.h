#pragma once

#include "checo/qt/command_executor.h"
#include "checo_qt_command_executor_export.h"

namespace checo::qt
{

/// Command which executes mouse click event
class CHECO_QT_COMMAND_EXECUTOR_EXPORT MouseClickCommandExecutor : public CommandExecutor
{
  public:
    MouseClickCommandExecutor();
    explicit MouseClickCommandExecutor(const Qt::MouseButton button);

    ~MouseClickCommandExecutor() override;

  public:
    Qt::MouseButton button() const;

  public:
    void execute() override;

    QByteArray toByteArray() const override;
    void fromByteArray(const QByteArray &data) override;

    QString toString() override;

  private:
    Qt::MouseButton m_Button{Qt::LeftButton};
};

} // namespace checo::qt

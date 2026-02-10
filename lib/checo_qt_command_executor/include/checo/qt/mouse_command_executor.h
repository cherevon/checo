#pragma once

#include "checo/qt/command_executor.h"
#include "checo_qt_command_executor_export.h"

#include <QMouseEvent>

#include <memory>

namespace checo::qt
{

/// Command which executes mouse event
class CHECO_QT_COMMAND_EXECUTOR_EXPORT MouseCommandExecutor : public CommandExecutor
{
  public:
    MouseCommandExecutor();
    explicit MouseCommandExecutor(const std::shared_ptr<QMouseEvent> &event);

    ~MouseCommandExecutor() override;

  public:
    std::shared_ptr<QMouseEvent> event() const;

  public:
    void execute() override;

    QByteArray toByteArray() const override;
    void fromByteArray(const QByteArray &data) override;

    QString toString() override;

  private:
    /// Event which should be executed
    std::shared_ptr<QMouseEvent> m_Event{nullptr};
};

} // namespace checo::qt

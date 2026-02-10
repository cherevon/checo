#pragma once

#include "checo/qt/command_executor.h"
#include "checo_qt_command_executor_export.h"

namespace checo::qt
{

/// Toggle window (Alt+Tab) to the next or previous one
class CHECO_QT_COMMAND_EXECUTOR_EXPORT ToggleWindowCommandExecutor : public CommandExecutor
{
  public:
    enum Direction
    {
        Next,
        Previous,
    };

  public:
    explicit ToggleWindowCommandExecutor(const Direction direction = Next);
    ~ToggleWindowCommandExecutor() override;

  public:
    Direction direction() const;

  public:
    void execute() override;
    void finishExecution() override;

    QByteArray toByteArray() const override;
    void fromByteArray(const QByteArray &data) override;

    QString toString() override;

  private:
    bool m_IsInitialized{false};
    Direction m_Direction{Next};
};

} // namespace checo::qt

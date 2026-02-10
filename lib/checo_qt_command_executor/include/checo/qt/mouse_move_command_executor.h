#pragma once

#include "checo/qt/command_executor.h"
#include "checo_qt_command_executor_export.h"

#include <QByteArray>
#include <QString>

namespace checo::qt
{

/// Command which executes mouse move event
class CHECO_QT_COMMAND_EXECUTOR_EXPORT MouseMoveCommandExecutor : public CommandExecutor
{
  public:
    enum Direction
    {
        Left,
        Right,
        Up,
        Down
    };

  public:
    MouseMoveCommandExecutor();
    explicit MouseMoveCommandExecutor(const Direction direction);

    ~MouseMoveCommandExecutor() override;

  public:
    Direction direction() const;

  public:
    void execute() override;

    QByteArray toByteArray() const override;
    void fromByteArray(const QByteArray &data) override;

    QString toString() override;

  private:
    Direction m_Direction{Left};
};

} // namespace checo::qt

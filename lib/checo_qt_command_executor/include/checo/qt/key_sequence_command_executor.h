#pragma once

#include "checo/qt/command_executor.h"

#include <QKeySequence>

#include <vector>

namespace checo::qt
{

/// Command which executes QKeySequence
class CHECO_QT_COMMAND_EXECUTOR_EXPORT KeySequenceCommandExecutor : public CommandExecutor
{
  public:
    KeySequenceCommandExecutor();
    explicit KeySequenceCommandExecutor(const std::vector<Qt::Key> &keys);

    ~KeySequenceCommandExecutor() override;

  public:
    void execute() override;

    QByteArray toByteArray() const override;
    void fromByteArray(const QByteArray &data) override;

    QString toString() override;

  public:
    const std::vector<Qt::Key> &keySequence() const;

  private:
    std::vector<Qt::Key> m_KeySequence{};
};

} // namespace checo::qt

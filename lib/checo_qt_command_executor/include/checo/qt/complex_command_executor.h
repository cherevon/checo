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

#include "checo/qt/command_executor.h"
#include "checo_qt_command_executor_export.h"

namespace checo::qt
{

/// Command which executes a sequence of subcommands when execute() is called
class CHECO_QT_COMMAND_EXECUTOR_EXPORT ComplexCommandExecutor : public CommandExecutor
{
  public:
    ComplexCommandExecutor();
    ~ComplexCommandExecutor() override;

  public:
    void execute() override;

  public:
    QByteArray toByteArray() const override;
    void fromByteArray(const QByteArray &) override;

    QString toString() override;

  public:
    const std::list<std::pair<uint32_t, std::shared_ptr<CommandExecutor>>> &commands() const;
    /** Add command in the end of execution sequence
     * @param cmd Command to be added
     * @param delayTime Time to wait before command execution (in milliseconds)
     */
    void addCommand(const std::shared_ptr<CommandExecutor> &cmd, const uint32_t delayTime = 0);

  public:
    /// Commands which are executed sequentially with delay time between them (in milliseconds)
    std::list<std::pair<uint32_t, std::shared_ptr<CommandExecutor>>> m_Commands{};
};

} // namespace checo::qt

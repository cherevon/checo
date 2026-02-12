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

#include "checo_qt_command_executor_export.h"

#include <QByteArray>
#include <QString>

namespace checo::qt
{

/// Command which performs some operation when execute() is called
class CHECO_QT_COMMAND_EXECUTOR_EXPORT CommandExecutor
{
  public:
    CommandExecutor();
    virtual ~CommandExecutor();

  public:
    /// Execute the command
    virtual void execute() = 0;

    /** Finalize all side effects from command execution (if the command saves state between execute() calls
     * @remark For example, Alt+Tab command press Alt button in execute() but doesn't release it because Tab can be
     * pressed more than once
     */
    virtual void finishExecution();

    /// Save settings of the command to the binary data
    virtual QByteArray toByteArray() const = 0;
    /// Load settings of the command from the binary data
    virtual void fromByteArray(const QByteArray &data) = 0;

    virtual QString toString() = 0;
};

} // namespace checo::qt

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

#include "checo/qt/complex_command_executor.h"

#include <QTimer>

namespace checo::qt
{

ComplexCommandExecutor::ComplexCommandExecutor() = default;

ComplexCommandExecutor::~ComplexCommandExecutor() = default;

void ComplexCommandExecutor::execute()
{
    uint32_t totalDelayTime = 1;
    for (auto &[delayTime, cmd] : m_Commands)
    {
        if (cmd == nullptr)
        {
            continue;
        }

        totalDelayTime += delayTime;
        QTimer::singleShot(totalDelayTime, [cmd] { cmd->execute(); });
    }
}

QByteArray ComplexCommandExecutor::toByteArray() const
{
    return QByteArray();
}

void ComplexCommandExecutor::fromByteArray(const QByteArray &)
{
    throw std::runtime_error("NOT SUPPORTED");
}

QString ComplexCommandExecutor::toString()
{
    return QObject::tr("Complex command");
}

const std::list<std::pair<uint32_t, std::shared_ptr<CommandExecutor>>> &ComplexCommandExecutor::commands() const
{
    return m_Commands;
}

void ComplexCommandExecutor::addCommand(const std::shared_ptr<CommandExecutor> &cmd, const uint32_t delayTime)
{
    m_Commands.push_back(std::make_pair(delayTime, cmd));
}

} // namespace checo::qt

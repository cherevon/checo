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

#include "checo/qt/shutdown_command_executor.h"

#include <QProcess>

namespace checo::qt
{

ShutdownCommandExecutor::ShutdownCommandExecutor() = default;

ShutdownCommandExecutor::~ShutdownCommandExecutor() = default;

void ShutdownCommandExecutor::execute()
{
    QProcess::startDetached("shutdown", {"/s", "/f", "/t", "0"});
}

QByteArray ShutdownCommandExecutor::toByteArray() const
{
    return QByteArray();
}

void ShutdownCommandExecutor::fromByteArray(const QByteArray &)
{
    // This command executor has no additional information that can be stored in QByteArray
}

QString ShutdownCommandExecutor::toString()
{
    return QObject::tr("Shutdown PC");
}

} // namespace checo::qt

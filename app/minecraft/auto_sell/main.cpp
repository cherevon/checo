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

#include "checo/logging/log_stdout.h"

#include <chrono>
#include <format>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include <windows.h>

static constexpr std::chrono::milliseconds KEY_PROCESS_TIME{500};

INPUT createKeyboardInput(const WORD &vkCode, const DWORD &flags)
{
    INPUT result{};
    result.type = INPUT_KEYBOARD;
    result.ki.wScan = 0;
    result.ki.time = 0;
    result.ki.dwExtraInfo = 0;
    result.ki.wVk = vkCode;
    result.ki.dwFlags = flags;
    return result;
}

void keyPress(const WORD &vkCode, const std::chrono::milliseconds &handleTime)
{
    // Send key press events
    std::vector<INPUT> inputs{
        createKeyboardInput(vkCode, 0),
        createKeyboardInput(vkCode, KEYEVENTF_KEYUP),
    };
    SendInput(inputs.size(), inputs.data(), sizeof(INPUT));

    // Let the operating system handle the input
    std::this_thread::sleep_for(handleTime);
}

void typeText(const std::string &text, const std::chrono::milliseconds &typeTime)
{
    const std::chrono::milliseconds symbTime = typeTime / text.size();

    // Send commands to type the text
    std::vector<INPUT> inputs{};
    for (const auto symb : text)
    {
        keyPress(VkKeyScan(symb), symbTime);
    }
}

void sellItems()
{
    using namespace std::chrono_literals;

    // Open chat
    keyPress(VkKeyScan('t'), 100ms);

    // Type command to sell items
    typeText("/sell", 250ms);

    // Execute the command by pressing Enter
    keyPress(VK_RETURN, 100ms);
}

int main()
{
    using namespace std::chrono_literals;

    // Create logger
    checo::logging::LogStdOut logger{};

    // Let the user some time to switch to the working window
    std::this_thread::sleep_for(5s);

    // Constantly sell items
    int sellCount{0};
    while (true)
    {
        sellItems();

        // Log the number of sell operations executed
        ++sellCount;
        logger.info(std::format("Items sold {} times", sellCount));

        // Sleep for some time to prevent kicks from the server because of too often sell requests
        std::this_thread::sleep_for(750ms);
    }

    // Success
    return 0;
}

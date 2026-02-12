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

#include <format>
#include <iostream>
#include <string>
#include <thread>

#include <windows.h>

static constexpr std::chrono::milliseconds KEY_PROCESS_TIME{500};

inline void KeyDown(const HWND winID, const int vkCode)
{
    // Press the key
    SendMessage(winID, WM_KEYDOWN, vkCode, 0);

    // Let the target window handle it
    std::this_thread::sleep_for(KEY_PROCESS_TIME);
}

inline void KeyUp(const HWND winID, const int vkCode)
{
    // Release the key
    SendMessage(winID, WM_KEYUP, vkCode, 0);

    // Let the target window handle it
    std::this_thread::sleep_for(KEY_PROCESS_TIME);
}

inline void KeyPress(const HWND winID, const int vkCode)
{
    // Press and release the key
    SendMessage(winID, WM_KEYDOWN, vkCode, 0);
    SendMessage(winID, WM_KEYUP, vkCode, 0);

    // Let the target window handle it
    std::this_thread::sleep_for(KEY_PROCESS_TIME);
}

inline void MouseLeftClick(const HWND winID)
{
    SendMessage(winID, WM_LBUTTONDOWN, 0, 1);
    SendMessage(winID, WM_LBUTTONUP, 0, 1);
}

inline void MouseRightClick(const HWND winID)
{
    SendMessage(winID, WM_RBUTTONDOWN, 0, 1);
    SendMessage(winID, WM_RBUTTONUP, 0, 1);
}

void MousePressThread(std::stop_token stopToken, const HWND winID)
{
    while (!stopToken.stop_requested())
    {
        MouseLeftClick(winID);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

void KillGaia(const HWND winID)
{
    static constexpr int GAIA_INGOT_SLOT{4};
    static constexpr int GAIA_SWORD_SLOT{5};

    static constexpr std::chrono::seconds DAMAGE_DURATION{15};

    static constexpr int VK_0 = 0x30;

    // Select Gaia ingot
    KeyPress(winID, VK_0 + GAIA_INGOT_SLOT);

    // Use Gaia ingot on the beacon
    KeyDown(winID, VK_LSHIFT);
    MouseRightClick(winID);
    KeyUp(winID, VK_LSHIFT);

    // Select Gaia sword
    KeyPress(winID, VK_0 + GAIA_SWORD_SLOT);

    // Constantly hit with the sword
    std::jthread clickerThread(MousePressThread, winID);
    std::this_thread::sleep_for(DAMAGE_DURATION);
    clickerThread.request_stop();
    if (clickerThread.joinable())
    {
        clickerThread.join();
    }
}

int main()
{
    // Create logger
    checo::logging::LogStdOut logger{};

    // Find minecraft window
    logger.info("Trying to find McSkill OneBlock window...");
    const auto minecraftWinID = FindWindow(NULL, "McSkill | OneBlock | cherevon");
    if (!minecraftWinID)
    {
        logger.error("Failed to find McSkill OneBlock window");
        return 1;
    }
    logger.info("McSkill OneBlock window found.");

    // Constantly kill Gaia
    int killCount{0};
    while (true)
    {
        KillGaia(minecraftWinID);
        ++killCount;
        logger.info(std::format("Gaia killed {} times", killCount));
    }

    // Success
    return 0;
}

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

#include <chrono>
#include <format>
#include <iostream>
#include <string>
#include <thread>

#include <windows.h>

static constexpr std::chrono::milliseconds CLICK_INTERVAL{20};

int main()
{
    // Ask the user to enter nickname
    std::string nickname;
    std::cout << "Enter your nickname: ";
    std::getline(std::cin, nickname);

    // Find minecraft window
    std::cout << "Trying to find McSkill OneBlock window..." << std::endl;
    const auto minecraftWinID = FindWindow(NULL, std::format("McSkill | OneBlock | {}", nickname).c_str());
    if (!minecraftWinID) {
        std::cout << "Failed to find McSkill OneBlock window" << std::endl;
        return 1;
    }
    std::cout << "McSkill OneBlock window found." << std::endl;

    // Ask user to select mouse button to click
    std::cout << "Select mouse button to click (L for left, R for right): ";
    char buttonChoice{'L'};
    std::cin >> buttonChoice;

    // Click the selected mouse button in a loop
    std::cout << "Starting auto clicker. Press Ctrl+C to stop." << std::endl;
    while (true) {
        if (buttonChoice == 'L' || buttonChoice == 'l') {
            SendMessage(minecraftWinID, WM_LBUTTONDOWN, 0, 1);
        } else if (buttonChoice == 'R' || buttonChoice == 'r') {
            SendMessage(minecraftWinID, WM_RBUTTONDOWN, 0, 1);
        } else {
            std::cout << "Invalid button choice. Please select L or R." << std::endl;
            return 1;
        }

        std::this_thread::sleep_for(CLICK_INTERVAL);
    }

    // Success
    return 0;
}

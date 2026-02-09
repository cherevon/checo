// Standard C++ includes
#include <chrono>
#include <format>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

// Operating system specific includes
#include <windows.h>

static constexpr std::chrono::milliseconds KEY_PROCESS_TIME{500};

inline void logInfo(const std::string& message)
{
	std::cout << message << std::endl;
}

inline void logError(const std::string& message)
{
	std::cout << std::format("ERROR: {}", message) << std::endl;
}

INPUT createKeyboardInput(const WORD& vkCode, const DWORD& flags)
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

void keyPress(const WORD& vkCode, const std::chrono::milliseconds& handleTime)
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

void typeText(const std::string& text, const std::chrono::milliseconds& typeTime)
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

	// Let the user some time to switch to the working window
	std::this_thread::sleep_for(5s);

	// Constantly sell items
	int sellCount{0};
	while (true)
	{
		sellItems();

		// Log the number of sell operations executed
		++sellCount;
		logInfo(std::format("Items sold {} times", sellCount));

		// Sleep for some time to prevent kicks from the server for too often sell requests
		std::this_thread::sleep_for(750ms);
	}

	// Success
	return 0;
}

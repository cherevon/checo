#include <format>
#include <iostream>
#include <string>
#include <thread>
#include <windows.h>

static constexpr std::chrono::milliseconds KEY_PROCESS_TIME{500};

inline void LogInfo(const std::string& message)
{
	std::cout << message << std::endl;
}

inline void LogError(const std::string& message)
{
	std::cout << std::format("ERROR: {}", message) << std::endl;
}

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
	// Find minecraft window
	LogInfo("Trying to find McSkill OneBlock window...");
	const auto minecraftWinID = FindWindow(NULL, "McSkill | OneBlock | cherevon");
	if (!minecraftWinID)
	{
		LogError("Failed to find McSkill OneBlock window");
		return 1;
	}
	LogInfo("McSkill OneBlock window found.");

	// Constantly kill Gaia
	int killCount{0};
	while (true)
	{
		KillGaia(minecraftWinID);
		++killCount;
		LogInfo(std::format("Gaia killed {} times", killCount));
	}

	// Success
	return 0;
}

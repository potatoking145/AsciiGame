#ifndef GREENFINGERS_WINDOW_H_
#define GREENFINGERS_WINDOW_H_

namespace window
{
	inline void HideConsole() { ::ShowWindow(::GetConsoleWindow(), SW_HIDE); };
	inline void ShowConsole() { ::ShowWindow(::GetConsoleWindow(), SW_SHOW); };
	inline bool IsConsoleVisible() { return ::IsWindowVisible(::GetConsoleWindow()) != FALSE; };
}

#endif
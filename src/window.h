#ifndef GREENFINGERS_WINDOW_H_
#define GREENFINGERS_WINDOW_H_

namespace window
{
	inline void HideConsole() { ::ShowWindow(::GetConsoleWindow(), SW_HIDE); };
	inline void ShowConsole() { ::ShowWindow(::GetConsoleWindow(), SW_SHOW); };
	inline bool IsConsoleVisible() { return ::IsWindowVisible(::GetConsoleWindow()) != FALSE; };

	class ApplicationInterface
	{
	public:
		ApplicationInterface();
		ApplicationInterface(const char*, bool, int, int);
		~ApplicationInterface();

		inline void DisplayConsole(TCOD_Console& console) { context->present(console); };
		inline void CaptureEvent(SDL_Event* event)
		{
			captured_event = (event->window.windowID == id) ? event : nullptr;
		};
		inline bool IsClosed(SDL_Event* event) { return (event->window.windowID == id && event->window.event == SDL_WINDOWEVENT_CLOSE); }; //Checks if the exit button has been pressed
		inline bool IfClosedClose(SDL_Event* event) //Closes the window if the close button has been pressed
		{
			if (IsClosed(event)) {
				context.reset();
				return true;
			}
			else {
				return false;
			}
		};
		inline uint8_t GetId() { return id; };
		inline SDL_Event* GetCapturedEvent() { return captured_event; };
	private:
		uint8_t id; //tracks this window's id ;; used for checking which window an event happened in

		TCOD_ContextParams context_params;
		void InitContextParams();
		void InitContextParams(const char*, bool, int, int);

		tcod::ContextPtr context;

		SDL_Event* captured_event{nullptr}; //nullptr indicates no captured event
	};
}

#endif
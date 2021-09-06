#ifndef GREENFINGERS_WINDOW_H_
#define GREENFINGERS_WINDOW_H_

namespace window
{
	extern uint8_t current_window; //tracks how many window's have been created ;; used to give each window a unique id

	//Default Params
	extern const char* DEF_WINDOW_TITLE;
	extern bool DEF_VSYNC;
	extern int DEF_SDL_WINDOW_FLAGS;

	inline void HideConsole() { ::ShowWindow(::GetConsoleWindow(), SW_HIDE); };
	inline void ShowConsole() { ::ShowWindow(::GetConsoleWindow(), SW_SHOW); };
	inline bool IsConsoleVisible() { return ::IsWindowVisible(::GetConsoleWindow()) != FALSE; };

	class ApplicationInterface
	{
	public:
		ApplicationInterface();
		ApplicationInterface(const char*, bool, int);
		~ApplicationInterface();

		inline void DisplayConsole(TCOD_Console& console) { context->present(console); };
		inline void CaptureEvent(SDL_Event* event)
		{
			if (event->window.windowID == id) {
				captured_event = event;
			}
			else {
				captured_event = nullptr;
			}
		};
		inline bool IsClosed(SDL_Event* event) { return (event->window.windowID == id && event->window.event == SDL_WINDOWEVENT_CLOSE); }; //Checks if the exit button has been pressed
		inline bool IfClosedClose(SDL_Event* event) //Closed the window if the close button has been pressed
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
		void InitContextParams(const char*, bool, int);

		tcod::ContextPtr context;

		SDL_Event* captured_event{nullptr};
	};
}

#endif
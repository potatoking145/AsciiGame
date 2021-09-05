#ifndef GREENFINGERS_WINDOW_H_
#define GREENFINGERS_WINDOW_H_

namespace window
{
	void HideConsole();
	void ShowConsole();
	bool IsConsoleVisible();

	class ApplicationInterface
	{
	public:
		ApplicationInterface();
	private:
		//Default Params
		const char* DEF_WINDOW_TITLE = "Greenfingers";
		int DEF_TCOD_VERSION = TCOD_COMPILEDVERSION; // Denotes the use of the pre-compiled version as opposed to the source code
		bool DEF_VSYNC = true;
		int DEF_SDL_WINDOW_FLAGS = SDL_WINDOW_RESIZABLE;
		int DEF_RENDERER = TCOD_RENDERER_SDL2;

		TCOD_ContextParams generic_context_params;

		inline void InitGenericContextParams();


		tcod::ContextPtr generic_context;
		tcod::ContextPtr* active_context;
	};
}

#endif
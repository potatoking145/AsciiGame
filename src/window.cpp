#include "window.h"

uint8_t current_window = 1; //tracks how many window's have been created ;; used to give each window a unique id

window::ApplicationInterface::ApplicationInterface()
{
	InitContextParams();
	context = tcod::new_context(context_params);

	id = current_window++;
}

window::ApplicationInterface::ApplicationInterface(const char* title, bool vsync, int flags, int renderer)
{
	InitContextParams(title, vsync, flags, renderer);
	context = tcod::new_context(context_params);

	id = current_window++;
}

window::ApplicationInterface::~ApplicationInterface()
{
	delete captured_event;
}

inline void window::ApplicationInterface::InitContextParams(const char* title, bool vsync, int flags, int renderer)
{
	context_params.tcod_version = TCOD_COMPILEDVERSION; // Denotes the use of the pre-compiled version as opposed to the source code
	context_params.window_title = title;
	context_params.vsync = vsync;
	context_params.sdl_window_flags = flags;
	context_params.renderer_type = renderer;
}

inline void window::ApplicationInterface::InitContextParams()
{
	//Default values
	context_params.tcod_version = TCOD_COMPILEDVERSION; // Denotes the use of the pre-compiled version as opposed to the source code
	context_params.window_title = "Greenfingers";
	context_params.vsync = true;
	context_params.sdl_window_flags = SDL_WINDOW_RESIZABLE;
	context_params.renderer_type = TCOD_RENDERER_SDL2;
}
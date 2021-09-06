#include "window.h"

uint8_t window::current_window = 1;

//Default Params
const char* window::DEF_WINDOW_TITLE = "Greenfingers";
bool window::DEF_VSYNC = true;
int window::DEF_SDL_WINDOW_FLAGS = SDL_WINDOW_RESIZABLE;

window::ApplicationInterface::ApplicationInterface()
{
	InitContextParams();
	context = tcod::new_context(context_params);

	id = current_window++;
}

window::ApplicationInterface::ApplicationInterface(const char* title, bool vsync, int flags)
{
	InitContextParams(title, vsync, flags);
	context = tcod::new_context(context_params);

	id = current_window++;
}

window::ApplicationInterface::~ApplicationInterface()
{
	delete captured_event;
}

inline void window::ApplicationInterface::InitContextParams(const char* title, bool vsync, int flags)
{
	context_params.tcod_version = TCOD_COMPILEDVERSION; // Denotes the use of the pre-compiled version as opposed to the source code
	context_params.window_title = title;
	context_params.vsync = vsync;
	context_params.sdl_window_flags = flags;
	context_params.renderer_type = TCOD_RENDERER_SDL2;
}

inline void window::ApplicationInterface::InitContextParams()
{
	context_params.tcod_version = TCOD_COMPILEDVERSION; // Denotes the use of the pre-compiled version as opposed to the source code
	context_params.window_title = DEF_WINDOW_TITLE;
	context_params.vsync = DEF_VSYNC;
	context_params.sdl_window_flags = DEF_SDL_WINDOW_FLAGS;
	context_params.renderer_type = TCOD_RENDERER_SDL2;
}
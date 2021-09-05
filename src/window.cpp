#include "window.h"

void window::HideConsole()
{
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);
}

void window::ShowConsole()
{
	::ShowWindow(::GetConsoleWindow(), SW_SHOW);
}

bool window::IsConsoleVisible()
{
	return ::IsWindowVisible(::GetConsoleWindow()) != FALSE;
}

window::ApplicationInterface::ApplicationInterface()
{
	InitGenericContextParams();

	generic_context = tcod::new_context(generic_context_params);
	active_context = &generic_context;
}

inline void window::ApplicationInterface::InitGenericContextParams()
{
	generic_context_params.tcod_version = DEF_RENDERER;
	generic_context_params.window_title = DEF_WINDOW_TITLE;
	generic_context_params.vsync = DEF_VSYNC;
	generic_context_params.sdl_window_flags = DEF_SDL_WINDOW_FLAGS;
	generic_context_params.renderer_type = DEF_RENDERER;
}
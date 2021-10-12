#include "application.h"

uint8_t current_window = 1; //tracks how many window's have been created ;; used to give each window a unique id

application::ApplicationInterface::ApplicationInterface()
{
	_id = current_window++;
}

application::ApplicationInterface::~ApplicationInterface()
{
	current_window--;
}

//add input events here
std::vector<uint16_t> application::ApplicationManager::InputEvents()
{
	std::vector<uint16_t> results;

	if (_global_ctx.sdl_event->type == SDL_KEYDOWN) {
		switch (_global_ctx.sdl_event->key.keysym.sym) {
		case SDLK_w:
			results.push_back(inputs::UP);
			break;
		case SDLK_s:
			results.push_back(inputs::DOWN);
			break;
		case SDLK_a:
			results.push_back(inputs::LEFT);
			break;
		case SDLK_d:
			results.push_back(inputs::RIGHT);
			break;
		}
	}

	return results;
}
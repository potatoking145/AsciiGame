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
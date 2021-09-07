#ifndef GREENFINGERS_STDAFX_H_
#define GREENFINGERS_STDAFX_H_

//C system headers
#include <stdint.h>

//C++ standard library headers
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <filesystem>
#include <chrono>
#include <type_traits>
#include <fstream>

//Local libraries
#include <libtcod/libtcod.h>
#include <sdl/SDL.h>
#include <cereal/types/memory.hpp>
#include <cereal/archives/binary.hpp>
#include <flecs.h>

//for some reason has to be added after #include <libtcod/libtcod.h> or will cause chaos
#define NOMINMAX
#include <windows.h>

#endif
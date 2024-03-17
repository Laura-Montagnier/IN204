#pragma once
#include "defs.hpp"

extern SDL_Renderer *renderer;
extern SDL_Window *window;

bool init_graphics();
void cleanup_graphics();

void updateRender();
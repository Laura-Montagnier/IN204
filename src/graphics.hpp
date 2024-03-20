#pragma once
#include "defs.hpp"

extern SDL_Renderer *renderer;

bool init_graphics();
void cleanup_graphics();
void saveScreen();

void updateRender();
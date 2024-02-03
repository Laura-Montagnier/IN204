#include "graphics.hpp"

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *display;
TTF_Font *font;

bool init_graphics() {

    bool success = true;

    window = SDL_CreateWindow("Ray Tracing",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              WINDOW_WIDTH, WINDOW_HEIGHT,
                              SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window, -1,
                                SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (window == NULL || renderer == NULL) {
        success = false;
        fprintf(stderr,
                "\nUnable to open the window: %s\n",
                SDL_GetError());
    }

    return success;
}

void updateRender() {
    SDL_SetRenderTarget(renderer, display);
    SDL_RenderPresent(renderer);
}


void cleanup_graphics() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    TTF_Quit();
}
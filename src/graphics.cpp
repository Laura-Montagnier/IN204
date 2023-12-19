#include "graphics.hpp"

SDL_Window *window;
SDL_Renderer *render;
SDL_Texture *display;
TTF_Font *font;

bool init_graphics() {

    bool success = true;

    window = SDL_CreateWindow("Ray Tracing",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              WINDOW_WIDTH, WINDOW_HEIGHT,
                              SDL_WINDOW_SHOWN);

    render = SDL_CreateRenderer(window, -1,
                                SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (window == NULL || render == NULL) {
        success = false;
        fprintf(stderr,
                "\nUnable to open the window: %s\n",
                SDL_GetError());
    }

    return success;
}

void updateRender() {
    SDL_SetRenderTarget(render, display);
    SDL_RenderPresent(render);
}


void cleanup_graphics() {
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    TTF_Quit();
}
#include "graphics.hpp"

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *display;

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

void saveScreen(){
    // Capture the current screen into a surface
    SDL_Surface *screenshot = SDL_CreateRGBSurface(0, WINDOW_WIDTH, WINDOW_HEIGHT, 32, 0, 0, 0, 0);
    SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888, screenshot->pixels, screenshot->pitch);

    IMG_SavePNG(screenshot, "out.png");
    SDL_FreeSurface(screenshot);
}

void cleanup_graphics() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}
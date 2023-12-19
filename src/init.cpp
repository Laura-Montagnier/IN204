#include "init.hpp"

void init() {
    // Only called once

    srand(time(NULL));

    bool fail = false;
    // Start up SDL, and make sure it went ok
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr,
                "\nUnable to initialize SDL:  %s\n",
                SDL_GetError());
        fail = true;
    }

    if (TTF_Init() == -1) {
        fprintf(stderr,
                "\nTTF_Init Error:  %s\n",
                SDL_GetError());
        fail = true;
    }

    if (!init_graphics()) {
        fprintf(stderr, "Couldn't initialize graphics.\n");
        fail = true;
    }

    if (fail){
        exit(EXIT_FAILURE);
    }

    printf("\n");

}

void cleanup() {
    // Shuts down everything
    cleanup_graphics();
    SDL_Quit();

    printf("Bye bye !\n\n");


}

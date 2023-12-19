#include "main.hpp"

int main(int argc, const char *argv[]) {

    init();
    atexit(cleanup);

    updateRender();

    // Set to ~60 fps.
    // 1000 ms/ 60 fps = 1/16 s^2/frame
        SDL_Delay(16);

    SDL_Event event;
    updateRender();


    //Cette boucle sert à fermer la fenêtre en cliquant sur la petite croix.
    while (SDL_PollEvent(&event)) { // Empties event poll
    }

    while (true) {
        SDL_Delay(200);
        while (SDL_PollEvent(&event)) {
            switch (event.type) {

            case SDL_QUIT:
            case SDL_KEYDOWN:
                exit(0);
                break;
            }
        }
    }
    return 0;
}

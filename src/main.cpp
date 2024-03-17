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

    Camera camera;
    camera.image();

    // Rayon rayon(0, 0, 0, 0, 0, 1);
    // Intersection i;
    // calcul_intersection(rayon, plan, i);
    // std::cout<< i.existe << i << "\n";

    // SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    // SDL_Rect rect;
    // rect.x = rect.y = rect.h = rect.w = 20;
    // SDL_RenderDrawRect(renderer, &rect);

    updateRender();

    // Cette boucle sert à fermer la fenêtre en cliquant sur la petite croix.
    while (SDL_PollEvent(&event)) { // Empties event poll
    }

    while (true) {
        SDL_Delay(200);
        while (SDL_PollEvent(&event)) {
            switch (event.type) {

            case SDL_QUIT:
                exit(0);
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                case SDLK_q:
                    exit(0);
                    break;
                }
            }
        }
    }
    return 0;
}

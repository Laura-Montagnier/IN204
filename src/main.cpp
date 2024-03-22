#include "main.hpp"

int main(int argc, const char *argv[]) {

    init();
    atexit(cleanup);
    updateRender();

    std::cout << "Génération de l'image\n";

    Camera camera;
    camera.image();

    updateRender();

    saveScreen();

    std ::cout << "Fini     \n\n";
    std ::cout << "L'image a été sauvegardée dans le fichier 'out.png'\n";
    std ::cout << "Appuyer sur ESC, Q ou la croix pour quitter la fenêtre\n";

    SDL_Event event;

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

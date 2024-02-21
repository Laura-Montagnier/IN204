#include "camera.hpp"

Vecteur point(0, 0, 0);
Vecteur normale(.1, 0, 1);
Plan plan(point, normale);

Camera::Camera() : position_camera(0, 0, 1),
                   direction_camera(0, 1, 0),
                   ecran_x(1, 0, 0),
                   ecran_y(0, 0, -1),
                   largeur_ecran(WINDOW_WIDTH),
                   hauteur_ecran(WINDOW_HEIGHT),
                   taille_pixel(.01),
                   angle_vue(70 * M_PI / 180),
                   distance_ecran(largeur_ecran / std::tan(angle_vue / 2)),
                   centre_ecran(position_camera + distance_ecran * direction_camera){};

void Camera::image() {
    std::cout << "camera.image()\n";

    for (int i = 0; i < hauteur_ecran; i += 1) {
        for (int j = 0; j < largeur_ecran; j += 1) {
            Vecteur point_ecran =
                centre_ecran +
                (j - (double)largeur_ecran / 2) * taille_pixel * ecran_x +
                (i - (double)hauteur_ecran / 2) * taille_pixel * ecran_y;

            Rayon rayon(position_camera, point_ecran - position_camera);

            // TODO: faire interagir le rayon avec la scène 3d

            Intersection intersection;
            calcul_intersection(rayon, plan, intersection);

            if (intersection.existe) {
                SDL_SetRenderDrawColor(renderer, 120, 100, 80, 255);
            } else {
                SDL_SetRenderDrawColor(renderer, 0, 180, 255, 255);
            }
            SDL_RenderDrawPoint(renderer, j, i);
        }
    }
}
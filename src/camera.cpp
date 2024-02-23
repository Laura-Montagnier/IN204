#include "camera.hpp"

Vecteur point{0, 0, 0};
Vecteur normale{.1, 0, 1};
Plan plan{point, normale};

Union monde{&plan}; // objet contenant toute la scène 3d

Vecteur direction_lumiere{0, .4, 1}; // vecteur pointant vers le soleil (source ponctuelle à l'infini ?)

Vecteur couleur_ciel{0, 180, 255}; // à adapter avec un type couleur ?
Vecteur couleur_sol{120, 100, 80};

void colore_pixel(Vecteur couleur, int i, int j) {
    SDL_SetRenderDrawColor(renderer, couleur.x, couleur.y, couleur.z, 255);
    SDL_RenderDrawPoint(renderer, j, i);
}

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
    direction_lumiere *= 1 / (direction_lumiere * direction_lumiere);

    std::cout << "camera.image()\n";

    std::cout << "normale*lumiere: " << plan.normale * direction_lumiere << "\n";

    for (int i = 0; i < hauteur_ecran; i += 1) {
        for (int j = 0; j < largeur_ecran; j += 1) {
            Vecteur point_ecran =
                centre_ecran +
                (j - (double)largeur_ecran / 2) * taille_pixel * ecran_x +
                (i - (double)hauteur_ecran / 2) * taille_pixel * ecran_y;

            Rayon rayon(position_camera, point_ecran - position_camera);

            Intersection intersection;
            monde.calcule_intersection(rayon, intersection);

            Vecteur couleur;
            if (intersection.existe) {
                // couleur = rayon.couleur ...

                couleur = couleur_sol;
                // l'intensité varie avec cos(angle(normale,lumiere))
                couleur *= std::max(0., intersection.normale * direction_lumiere);
            } else {
                // couleur = get_ambiant_light ...
                couleur = couleur_ciel;
            }
            // Vecteur couleur = intersection.existe * couleur_sol + !intersection.existe * couleur_ciel;

            colore_pixel(couleur, i, j);
        }
    }
}
#include "camera.hpp"

Vecteur point{0, 0, 0};
Vecteur normale{.1, 0, 1};
Plan plan{point, normale};

Sphere sphere(0, 8, 1, 1);
Sphere s2(-.4, 4, 1, .2);

// objet contenant toute la scène 3d, (utiliser shared pointers ?)
Union monde{&sphere, &plan, &s2};

Vecteur direction_lumiere{1, -1, 1}; // vecteur pointant vers le soleil (source ponctuelle à l'infini ?)
// Vecteur direction_lumiere{0, -1, 0};

Vecteur couleur_sol{0, 255, 0};

void colore_pixel(Vecteur couleur, int i, int j) {
    // correction gamma
    couleur.x = sqrt(couleur.x / 255) * 255;
    couleur.y = sqrt(couleur.y / 255) * 255;
    couleur.z = sqrt(couleur.z / 255) * 255;


    SDL_SetRenderDrawColor(renderer, couleur.x, couleur.y, couleur.z, 255);
    SDL_RenderDrawPoint(renderer, j, i);
}

Vecteur couleur_ciel(int i, int max_i) {
    // double k = (rayon.direction.y / rayon.direction.norme() + 1) / 2;
    double k = (double)i / max_i;
    return Vecteur(200, 220, 255) * k + Vecteur(0, 100, 255) * (1 - k);
    // return Vecteur(0, 0, 0) * k + Vecteur(0, 60, 80) * (1 - k);
}

Camera::Camera() : position_camera(0, 0, 1),
                   direction_camera(0, 1, 0),
                   ecran_x(1, 0, 0),
                   ecran_y(0, 0, -1),
                   largeur_ecran(WINDOW_WIDTH),
                   hauteur_ecran(WINDOW_HEIGHT),
                   taille_pixel(.01),
                   angle_vue(70 * M_PI / 180),
                   distance_ecran(largeur_ecran * taille_pixel / std::tan(angle_vue / 2)),
                   centre_ecran(position_camera + distance_ecran * direction_camera){};

void Camera::image() {
    direction_lumiere *= 1 / direction_lumiere.norme();

    std::cout << "camera.image()\n";

    std::cout << "normale_plan*lumiere: " << plan.normale * direction_lumiere << "\n";

    for (int i = 0; i < hauteur_ecran; i += 1) {
        for (int j = 0; j < largeur_ecran; j += 1) {
            Vecteur point_ecran =
                centre_ecran +
                (j - (double)largeur_ecran / 2) * taille_pixel * ecran_x +
                (i - (double)hauteur_ecran / 2) * taille_pixel * ecran_y;

            Vecteur vitesse = point_ecran - position_camera;
            Rayon rayon(position_camera, vitesse);

            Intersection intersection;
            monde.calcul_intersection(rayon, intersection);

            Vecteur couleur;
            if (intersection.existe) {
                // couleur = rayon.couleur ...

                couleur = couleur_sol;
                // l'intensité varie avec cos(angle(normale,lumiere))
                couleur *= std::max(0., intersection.normale * direction_lumiere);

                // couleur = (intersection.normale + Vecteur(1, 1, 1)) *  .5 * 255; // Visualise normales

            } else {
                // couleur = get_ambiant_light ...
                couleur = couleur_ciel(i, hauteur_ecran);
            }
            // Vecteur couleur = intersection.existe * couleur_sol + !intersection.existe * couleur_ciel;

            colore_pixel(couleur, i, j);
        }
    }
}

// void Camera::image() {

//     Vecteur vitesse = centre_ecran - position_camera;
//     vitesse *= 1 / sqrt(vitesse * vitesse);
//     Rayon rayon(position_camera, vitesse);

//     std::cout << "ray " << rayon << "\n";
//     std::cout << "sph " << sphere << "\n";

//     Intersection intersection;
//     monde.calcul_intersection(rayon, intersection);

//     Vecteur couleur = couleur_sol;
//     // l'intensité varie avec cos(angle(normale,lumiere))
//     couleur *= std::max(0., intersection.normale * direction_lumiere);
//     std::cout << intersection.normale << couleur << "\n";
// }

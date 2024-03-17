#include "camera.hpp"

const bool affiche_normales = false;
const bool correction_gamma = true;

int nb_rayons = 10;
int max_rebonds = 5;

Materiau vert{0, .9, 0};
Materiau vert_fonce{10. / 255, 65. / 255, 0};

Vecteur point{0, 0, 0};
Vecteur normale{.1, 0, 1};

// Vecteur point{0, 5, 0};
// Vecteur normale{0, -1, .1};

Plan plan{point, normale, vert_fonce};

Sphere sphere(0, 8, 1, 1, vert);
Sphere s2(-.4, 4, 1, .2);

// objet contenant toute la scène 3d, (utiliser shared pointers ?)
Union monde{&sphere, &plan, &s2};
// Union monde{&sphere, &s2};
// Union monde{&plan};

Vecteur direction_lumiere{1, -1, 1}; // vecteur pointant vers le soleil (source ponctuelle à l'infini ?)
// Vecteur direction_lumiere{0, -1, 0};


std::random_device rd_;
std::mt19937 generator_(rd_()); // Mersenne Twister 19937 engine
std::uniform_real_distribution<double> rand_double(0, 1);


void colore_pixel(Vecteur couleur, int i, int j) {
    // correction gamma
    if (correction_gamma) {
        couleur.x = sqrt(couleur.x) * 255;
        couleur.y = sqrt(couleur.y) * 255;
        couleur.z = sqrt(couleur.z) * 255;
    }

    SDL_SetRenderDrawColor(renderer, (int)couleur.x, (int)couleur.y, (int)couleur.z, 255);
    SDL_RenderDrawPoint(renderer, j, i);
}

Vecteur couleur_ciel(int i, int max_i) {
    // double k = (rayon.direction.y / rayon.direction.norme() + 1) / 2;
    double k = (double)i / max_i;
    return Vecteur(200. / 255, 220. / 255, 255. / 255) * k + Vecteur(0. / 255, 100. / 255, 255. / 255) * (1 - k);
    // return Vecteur(0./255, 0./255, 0./255) * k + Vecteur(0./255, 60./255, 80./255) * (1 - k);
}

Vecteur lance_rayon(Rayon &rayon) {
    Vecteur couleur{1, 1, 1};
    for (int i = 0; i < max_rebonds; i++) {
        Intersection intersection;
        monde.calcul_intersection(rayon, intersection);
        if (intersection.existe) {
            // std::cout << intersection << "\n";
            couleur.x *= intersection.materiau.couleur.x;
            couleur.y *= intersection.materiau.couleur.y;
            couleur.z *= intersection.materiau.couleur.z;
            rayon.origine = intersection.point;

            if (rand_double(generator_) <= intersection.materiau.p_reflexion) {
                // reflexion
                rayon.direction = rayon.direction + 2 * (rayon.direction * intersection.normale) * intersection.normale;
            } else {
                // diffusion
                rayon.direction = diffusion_lambert(intersection.normale);
            }
            couleur *= std::max(0., intersection.normale * direction_lumiere);

        } else {
            break;
        }
    }

    return couleur;
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
    // crée la scène, à mettre dans une fonction
    direction_lumiere *= 1 / direction_lumiere.norme();
    // plan.normale *= 1 / plan.normale.norme();

    std::cout << "camera.image()\n";

    std::cout << "normale_plan*lumiere: " << plan.normale * direction_lumiere << "\n";

    for (int i = 0; i < hauteur_ecran; i += 1) {
            std::cout << i << "\n";
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

            for (int k = 0; k < nb_rayons; k++) {
                Rayon rayon(position_camera, vitesse);
                // rayon.origine += k*1e-4* Vecteur(1, 0, 0); // TODO: remplacer par variation aléatoire
                couleur += lance_rayon(rayon);
            }
            couleur *= 1. / nb_rayons;

            // return
            // if (intersection.existe) {
            //     // couleur = rayon.couleur ...

            //     if (affiche_normales) {
            //         couleur = (intersection.normale + Vecteur(1, 1, 1)) * .5; // Visualise normales
            //     } else {
            //         couleur = intersection.materiau.couleur;
            //         // l'intensité varie avec cos(angle(normale,lumiere))
            //         // couleur *= std::max(0., intersection.normale * direction_lumiere);
            //     }

            // } else {
            //     // couleur = get_ambiant_light ...
            //     couleur = couleur_ciel(i, hauteur_ecran);
            // }
            // Vecteur couleur = intersection.existe * couleur_sol + !intersection.existe * couleur_ciel;

            colore_pixel(couleur, i, j);
        }
    }

    std ::cout << "fini \n";
}

// void Camera::image() {

//     Vecteur vitesse = centre_ecran - position_camera;
//     vitesse *= 1 / sqrt(vitesse * vitesse);
//     Rayon rayon(position_camera, vitesse);

//     std::cout << "ray " << rayon << "\n";
//     std::cout << "sph " << sphere << "\n";

//     Intersection intersection;
//     // monde.calcul_intersection(rayon, intersection);

//     Vecteur couleur = lance_rayon(rayon);

//     // Vecteur couleur = couleur_sol;
//     // l'intensité varie avec cos(angle(normale,lumiere))
//     // couleur *= std::max(0., intersection.normale * direction_lumiere);
//     std::cout << intersection.normale << couleur << "\n";
// }

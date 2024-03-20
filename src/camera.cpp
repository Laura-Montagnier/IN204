#include "camera.hpp"

const bool affiche_normales = false;
const bool correction_gamma = true;

<<<<<<< HEAD
int nb_rayons = 500;
int max_rebonds = 8;

Materiau vert{
    0,
    .9,
    0,
};
Materiau blanche{1,1,1};
Materiau vert_fonce{10. / 255, 65. / 255, 0.1, 0, false};
Materiau materiau_soleil{1, 1, .5, 0, true};
Materiau bleu_fonce{10. / 255, 10. / 255, 70. / 255, 0, false};
Materiau rouge_fonce{65. / 255, 10. / 255, 5. / 255, 0, false};
=======
int nb_rayons = 20;
int max_rebonds = 10;

Materiau vert{0, .9, 0};
Materiau vert_fonce{10. / 255, 65. / 255, 0};
Materiau materiau_soleil{1, 1, .5, 0, 0, true};
Materiau bleu_fonce{10. / 255, 10. / 255, 70. / 255};
Materiau rouge_fonce{65. / 255, 10. / 255, 5. / 255};
Materiau verre{1, 1, 1, .1, .9};
>>>>>>> refs/remotes/origin/main

Materiau miroir{1, 1, 1, 0.9};

Materiau mat{1, 1, 1, 0};

Vecteur point{0, 0, 0};
Vecteur point_2{-3.5, 0, 0};
Vecteur point_3{3.5, 0, 0};
Vecteur point_4{0, 15, 0};
Vecteur point_5{0, 0, 3.5};

Vecteur normale{0, 0, 1};
Vecteur normale_2{1, 0, 0};
Vecteur normale_3{-1, 0, 0};
Vecteur normale_4{0, -1, 0};
Vecteur normale_5{0, 0, 1};

// Vecteur point{0, 5, 0};
// Vecteur normale{0, -1, .1};

Plan plan{point, normale, rouge_fonce};
Plan plan_2{point_2, normale_2, vert_fonce};
Plan plan_3{point_3, normale_3, vert_fonce};
Plan plan_4{point_4, normale_4, bleu_fonce};
Plan plafond{point_5, normale_5, materiau_soleil};

<<<<<<< HEAD
Sphere sphere(0, 8, 1, 1, miroir);
Sphere s2(-.4, 6, 0.2, .2, vert_fonce);
Sphere s3(0.5, 5, 0.4, 0.4, bleu_fonce);
=======
Sphere sphere(0, 8, 1, 1, verre);
Sphere s2(-.4, 4, 1, .2);
>>>>>>> refs/remotes/origin/main
Sphere soleil(8, 20, 12, 10, materiau_soleil);

// objet contenant toute la scène 3d, (utiliser shared pointers ?)
Union monde{&sphere, &plan, &plan_2, &plan_3, &plan_4, &s2, &s3, &plafond};
// Union monde{&sphere, &s2};
// Union monde{&plan};

// Vecteur direction_lumiere{0.5, -0.5, 1}; // vecteur pointant vers le soleil (source ponctuelle à l'infini ?)
//  Vecteur direction_lumiere{0, -1, 0};
Vecteur direction_lumiere{0, 0, 1}; // vecteur vers le plafond

std::random_device rd_;
std::mt19937 generator_(rd_()); // Mersenne Twister 19937 engine
std::uniform_real_distribution<double> rand_double(0, 1);

inline void colore_pixel(Vecteur couleur, int i, int j) {
    // correction gamma
    if (correction_gamma) {
        couleur.x = sqrt(couleur.x) * 255;
        couleur.y = sqrt(couleur.y) * 255;
        couleur.z = sqrt(couleur.z) * 255;
    }

    SDL_SetRenderDrawColor(renderer, (int)couleur.x, (int)couleur.y, (int)couleur.z, 255);
    SDL_RenderDrawPoint(renderer, j, i);
}

void colore_ligne(Vecteur couleurs[], int i, int largeur_ecran) {
    for (int j = 0; j < largeur_ecran; j++) {
        colore_pixel(couleurs[j], i, j);
    }
}

Vecteur couleur_ciel(int i, int max_i) {
    // double k = (rayon.direction.y / rayon.direction.norme() + 1) / 2;
    double k = (double)i / max_i;
    k = std::max(k, 1.);
    return Vecteur(200. / 255, 220. / 255, 255. / 255) * k + Vecteur(0. / 255, 100. / 255, 255. / 255) * (1 - k);
    // return Vecteur(0./255, 0./255, 0./255) * k + Vecteur(0./255, 60./255, 80./255) * (1 - k);
}

Vecteur lance_rayon(Rayon &rayon) {
    Vecteur couleur{1, 1, 1};
    for (int i = 0; i < max_rebonds; i++) {
        Intersection intersection;
        monde.calcul_intersection(rayon, intersection);
        if (!intersection.existe) {
            // Vecteur ciel = couleur_ciel(std::min(std::max(rayon.direction.z, 500.), 0.), 500);
            // couleur.x *= ciel.x;
            // couleur.y *= ciel.y;
            // couleur.z *= ciel.z;

            // couleur.x *= .5;
            // couleur.y *= .7;
            // couleur.z *= .9;

            couleur = Vecteur(0, 0, 0);
            break;
        }

        if (affiche_normales) {
            couleur = (intersection.normale + Vecteur(1, 1, 1)) * .5; // Visualise normales
            break;
        }

        Materiau mat = intersection.materiau;
        if (mat.lumineux) {

            couleur.x *= mat.couleur.x;
            couleur.y *= mat.couleur.y;
            couleur.z *= mat.couleur.z;

            // couleur *= 10.;

            break;
        }

        // std::cout << intersection << "\n";
        couleur.x *= mat.couleur.x;
        couleur.y *= mat.couleur.y;
        couleur.z *= mat.couleur.z;

        double r = rand_double(generator_);
        if (r <= mat.p_reflexion) {
            // reflexion
            rayon.direction = direction_reflechie(rayon.direction, intersection.normale);
            rayon.origine = intersection.point;
        } else if (r <= mat.p_reflexion + mat.p_transmission) {
            // transmission ou réflexion totale
            rayon.direction = direction_refractee(rayon.direction, intersection.normale);
            //     Vecteur d = direction_refractee(rayon.direction, intersection.normale);
            //     if (rayon.direction * d > 0) {
            //     // le rayon a bien été réfracté
            //     // On sassure que le pt d'origine est bien de l'autre coté de la surface

            //     // rayon.origine += intersection.distance * 3*epsilon * rayon.direction;
            // rayon.origine += intersection.distance * (2*epsilon) * rayon.direction ;
            //     rayon.direction = d;
            //     }

            // rayon.origine = intersection.point + (intersection.distance * (20 * epsilon) * rayon.direction);
            rayon.origine = intersection.point + (intersection.distance * (5 * epsilon) * rayon.direction);

        } else {
            // diffusion
            rayon.direction = direction_difusee(intersection.normale);
            // couleur *= std::max(0., intersection.normale * rayon.direction);
            rayon.origine = intersection.point;
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

    // std::cout << "normale_plan*lumiere: " << plan.normale * direction_lumiere << "\n";

#pragma omp parallel for schedule(dynamic, 10)
    for (int i = 0; i < hauteur_ecran; i += 1) {
        int id = omp_get_thread_num();
        int num_threads = omp_get_num_threads();
        if (id == 0) {
            std::cout << "> " << (int)(100. * i / hauteur_ecran) << "%   \r";
            std::flush(std::cout);
        }
        Vecteur couleurs_ligne[largeur_ecran];
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
                double dx = (rand_double(generator_) - .5) * taille_pixel;
                double dy = (rand_double(generator_) - .5) * taille_pixel;
                rayon.origine += dx * ecran_x + dy * ecran_y;
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

            couleurs_ligne[j] = couleur;
        }
#pragma omp critical
        colore_ligne(couleurs_ligne, i, largeur_ecran);

        if (id == 0) {
            // même pas de différence de perf, et effet très classe
            updateRender();
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

#include "camera.hpp"

const bool affiche_normales = false;
const bool correction_gamma = true;

//On lance 20 rayons par pixels, qui disparaissent au bout de 10 rebonds sur les objets environnants.
int nb_rayons = 20;
int max_rebonds = 10;

//Nos matériaux sont définis avec 6 champs : les trois premiers sont RGB, puis leur pourcentage de réfraction, 
//de réflexion, puis s'ils sont lumineux (booléen).
Materiau vert{0, .9, 0};
Materiau vert_fonce{10. / 255, 65. / 255, 0};
Materiau materiau_soleil{1, 1, .5, 0, 0, true};
Materiau bleu_fonce{10. / 255, 10. / 255, 70. / 255};
Materiau rouge_fonce{65. / 255, 10. / 255, 5. / 255};
Materiau verre{1, 1, 1, .1, .9};

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

Plan plan{point, normale, rouge_fonce};
Plan plan_2{point_2, normale_2, vert_fonce};
Plan plan_3{point_3, normale_3, vert_fonce};
Plan plan_4{point_4, normale_4, bleu_fonce};
Plan plafond{point_5, normale_5, materiau_soleil};

Sphere sphere(0, 8, 1, 1, miroir);
Sphere s2(-.4, 6, 0.2, .2, vert_fonce);
Sphere s3(0.5, 5, 0.4, 0.4, bleu_fonce);
Sphere soleil(8, 20, 12, 10, materiau_soleil);

// L'objet union permet de définir la scène 3D : ici c'est la boîte de Cornell
Union monde{&sphere, &plan, &plan_2, &plan_3, &plan_4, &s2, &s3, &plafond};

// Vecteur direction_lumiere{0.5, -0.5, 1}; // vecteur pointant vers le soleil 
Vecteur direction_lumiere{0, 0, 1}; // vecteur vers le plafond


//Définition de l'aléatoire en dehors des fonctions qui l'utilisent.
std::random_device rd_;
std::mt19937 generator_(rd_()); // Mersenne Twister 19937 engine
std::uniform_real_distribution<double> rand_double(0, 1);

inline void colore_pixel(Vecteur couleur, int i, int j) {
    // correction gamma encouragée par le professeur
    if (correction_gamma) {
        couleur.x = sqrt(couleur.x) * 255;
        couleur.y = sqrt(couleur.y) * 255;
        couleur.z = sqrt(couleur.z) * 255;
    }

    //Utilisation de SDL pour dessiner notre scène
    SDL_SetRenderDrawColor(renderer, (int)couleur.x, (int)couleur.y, (int)couleur.z, 255);
    SDL_RenderDrawPoint(renderer, j, i);
}

//Chaque ligne est colorée à son tour, ce qui permet de parralléliser.
void colore_ligne(Vecteur couleurs[], int i, int largeur_ecran) {
    for (int j = 0; j < largeur_ecran; j++) {
        colore_pixel(couleurs[j], i, j);
    }
}

//Dans nos premières simulations, le ciel était d'un dégradé de bleu.
Vecteur couleur_ciel(int i, int max_i) {
    double k = (double)i / max_i;
    k = std::max(k, 1.);
    return Vecteur(200. / 255, 220. / 255, 255. / 255) * k + Vecteur(0. / 255, 100. / 255, 255. / 255) * (1 - k);
}

Vecteur lance_rayon(Rayon &rayon) {
    Vecteur couleur{1, 1, 1};
    for (int i = 0; i < max_rebonds; i++) {
        Intersection intersection;
        monde.calcul_intersection(rayon, intersection);
        if (!intersection.existe) {
            // Vecteur ciel = couleur_ciel(std::min(std::max(rayon.direction.z, 500.), 0.), 500);
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
            break;
        }

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
            // On s'assure que le rayon a bien traversé la surface
            rayon.origine = intersection.point + (intersection.distance * (2 * epsilon) * rayon.direction);

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

    std::cout << "camera.image()\n";

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



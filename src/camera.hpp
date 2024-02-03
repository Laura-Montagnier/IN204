#pragma once
#include "defs.hpp"
#include "graphics.hpp"
#include "volumes.hpp"

Vecteur point(0, 0, 0);
Vecteur normale(.1, 0, 1);
Plan plan(point, normale);

class Camera {

public:
    Vecteur position_camera;  // origine des rayons, position du capteur
    Vecteur direction_camera; // direction d'observation

    // ecran_x et ecran_y definissent le plan de l'ecran virtuel
    // Note : Le triplet (ecran_x, ecran_y, direction_camera) est une base orthogonale (normée ?) directe
    Vecteur ecran_x;
    Vecteur ecran_y;

    Camera() : position_camera(0, 0, 1), direction_camera(0, 1, 0), ecran_x(1, 0, 0), ecran_y(0, 0, -1){};

    // taille écran virtuel en px
    const int largeur_ecran = WINDOW_WIDTH;
    const int hauteur_ecran = WINDOW_HEIGHT;

    /*   Note :
        (WINDOW_WIDTH, WINDOW_HEIGHT) est la taille de la fenêtre sur l'écran physique de l'ordinateur;
        (largeur_ecran, hauteur_ecran), celle de l'image
        Conceptuellement, les deux n'ont pas à être égales, mais on ne va pas s'embêter avec ça
    */

    // résolution en coordonnées-monde ; la taille physique de 
    // l'écran virtuel est (hauteur_ecran*taille_pixel, largeur_ecran*taille_pixel)
    const double taille_pixel = .01;

    const double angle_vue = 90 * M_PI / 180; // FOV, angle horizontal en radians entre la caméra et les bords du cadre
    const double distance_ecran = largeur_ecran / std::tan(angle_vue / 2);

    Vecteur centre_ecran = position_camera + distance_ecran * direction_camera;

    void image() {
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
};

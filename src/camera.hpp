#pragma once
#include "defs.hpp"
#include "graphics.hpp"
#include "volumes.hpp"
#include "rebond.hpp"

class Camera {

public:
    // origine des rayons, position du capteur
    Vecteur position_camera;
    
    // direction d'observation
    Vecteur direction_camera;

    // ecran_x et ecran_y definissent le plan de l'ecran virtuel
    // Note : Le triplet (ecran_x, ecran_y, direction_camera) est une base orthogonale (normée ?) directe
    Vecteur ecran_x;
    Vecteur ecran_y;

    // taille écran virtuel en px
    const int largeur_ecran;
    const int hauteur_ecran;

    /*   Note :
        (WINDOW_WIDTH, WINDOW_HEIGHT) est la taille de la fenêtre sur l'écran physique de l'ordinateur;
        (largeur_ecran, hauteur_ecran) est celle de l'image.
        Conceptuellement les deux sont distinctes, mais on va les prendre égales pour faire simple
    */

    // résolution en coordonnées-monde ; la taille physique de 
    // l'écran virtuel est (hauteur_ecran*taille_pixel, largeur_ecran*taille_pixel)
    const double taille_pixel;

    // FOV, angle horizontal en radians entre la caméra et les bords du cadre, max 180°
    const double angle_vue; 
    const double distance_ecran;

    Vecteur centre_ecran;



    Camera();

    void image();
};
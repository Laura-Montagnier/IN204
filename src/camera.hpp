#include "defs.hpp"
#include "volumes.hpp"


class Camera{

public:

    Vecteur position_camera; // centre optique, position du capteur
    Vecteur direction_camera; // direction d'observation

    // v_x et v_y definissent le plan de l'ecran
    Vecteur v_x;
    Vecteur v_y;

    // Le triplet (v_x, v_y, direction_camera) est une base orthogonale (normee ?) directe

    Camera() : direction_camera(0, 0, 1), v_x(1, 0, 0), v_y(0, -1, 0) {};


    const int hauteur_ecran = 200; // taille verticale
    const int largeur_ecran = 300; // taille horizontale

    const double angle_vue = 90 * M_PI/180; // FOV, angle horizontal en radians entre la camera et les bords du cadre
    const double distance_ecran = largeur_ecran / std::tan(angle_vue/2);
    

    const int taille_pixel = 1;
    // La resolution est : (hauteur_ecran/taille_pixel) x (largeur_ecran/taille_pixel) 


    void image() {

        for (float y = -hauteur_ecran/2; y < hauteur_ecran/2; y += taille_pixel){
            for (float x = -largeur_ecran/2; x < largeur_ecran/2; x += taille_pixel){
                // Normaliser direction ?
                Vecteur direction = direction_camera * distance_ecran + y * taille_pixel * v_x + x * taille_pixel * v_y;
                // Vecteur point_ecran = position_camera + direction ;
                Rayon rayon(position_camera, direction);

                // TODO: faire un truc avec le rayon
                // std::cout << "(xy:" << x << y << ") " << rayon << '\n';
            }
        }
    }
};

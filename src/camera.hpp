#include "defs.hpp"
#include "volumes.hpp"


class Camera{

public:

    Camera(){};

    int hauteur_ecran = 100;
    int largeur_ecran = 200;

    double fov = 150;


    int pixel_size = 1;


    void image(){

        Vecteur position_camera;
        Vecteur direction_camera(0, 0, 1);
        Vecteur v_x(1, 0, 0);
        Vecteur v_y(0, 1, 0);

        for (int x = -hauteur_ecran/2; x < hauteur_ecran/2; x++){
            for (int y = largeur_ecran/2; y < largeur_ecran/2; y++){

                2 * v_x;
                v_x * 2;

                Vecteur point_ecran = position_camera + direction_camera * fov + x * v_x + y * v_y;

                Rayon rayon(position_camera, point_ecran - position_camera);
                // TODO: faire un truc avec le rayon 

            }
        }
    }
};

#include "rebond.hpp"
#include <random>



Vecteur diffusion_lambert(const Vecteur &point, const Vecteur &normale){
    double I = 0.8 ;
    double x = point.x ;
    double y = point.y ;
    double z = point.z ;
    bool rejet = false ;
    Vecteur reflechi ;
    double cos_theta ;

    std::random_device rd;
    std::mt19937 generator(rd()); // Mersenne Twister 19937 engine

    std::uniform_int_distribution<int> distribution_1(x-0.5, x+0.5);
    std::uniform_int_distribution<int> distribution_2(y-0.5, y+0.5);
    std::uniform_int_distribution<int> distribution_3(z-0.5, z+0.5);

    while (rejet==false){
        // Définir des distributions uniformes autour de x, y et z
        
        double x_1 = distribution_1(generator);
        double y_1 = distribution_2(generator);
        double z_1 = distribution_3(generator);

        if (x*x_1 + y*y_1 + z*z_1 < 1){
            reflechi = Vecteur(x - x_1, y - y_1, z - z_1) ;
            cos_theta = reflechi*normale ;
            rejet=true ;
        }
    }


    return I*cos_theta*reflechi ;
}

int main(){
    return 0;
}

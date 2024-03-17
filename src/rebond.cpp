#include "rebond.hpp"
#include <random>

std::random_device rd;
std::mt19937 generator(rd()); // Mersenne Twister 19937 engine : une méthode pour avoir de l'aléatoire

std::uniform_real_distribution<double> distribution(-1, 1);

Vecteur diffusion_lambert(const Vecteur &normale) {
    bool reject = false;
    // On va utiliser la méthode du rejet ; on cherche un vecteur dans le cube unité et on le conserve uniquement si il est dans la sphère unité.
    Vecteur retour = {0, 0, 0};



    while (reject == false) {
        retour.x = distribution(generator);
        retour.y = distribution(generator);
        retour.z = distribution(generator);

        if (retour.norme2() <= 1) {
            if (retour * normale < 0) {
                retour = retour * (-1);
            }
            reject = true;
        }
    }
    return (retour);
}

/*
int main() {
    Vecteur normale = {1,1,1};
    Vecteur retour = diffusion_lambert(normale);
    std::cout << retour << std::endl;
    double norme = retour.norme2();
    std::cout << norme << std::endl;
    return 0;
}*/

#include "rebond.hpp"

std::random_device rd;
std::mt19937 generator(rd()); // Mersenne Twister 19937 engine : une méthode pour avoir de l'aléatoire

std::uniform_real_distribution<double> distribution(-1, 1);

#define DEV

#ifndef DEV
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

#else

Vecteur direction_difusee(const Vecteur &normale) {
    // bool reject = false;
    // On va utiliser la méthode du rejet ; on cherche un vecteur dans le cube unité et on le conserve uniquement si il est dans la sphère unité.
    Vecteur retour = {0, 0, 0};

    while (true) {
        retour.x = distribution(generator);
        retour.y = distribution(generator);
        retour.z = distribution(generator);

        if (retour.norme2() <= 1) {
            retour *= 1 / retour.norme();
            retour += normale;
            return (retour);
        }
    }
}

#endif

Vecteur direction_reflechie(const Vecteur &incident, const Vecteur &normale) {
    return incident - 2 * (incident * normale) * normale;
}

Vecteur direction_refractee(const Vecteur &incident, const Vecteur &normale) {

    double n_1, n_2;
    int sgn = (incident * normale > 0) ? 1 : -1 ;
    if (sgn == 1){
        // rayon sortant de l'objet
        n_1 = 1.3;
        n_2 = 1.;
    } else {
        // rayon entrant dans l'objet
        n_1 = 1.;
        n_2 = 1.3;
    }

    Vecteur i_n = (incident * normale) * normale;
    Vecteur i_t = incident - i_n;

    if (n_1/n_2 * i_t.norme2() > 50 * i_n.norme2()) {
        return direction_reflechie(incident, normale);
    }
    Vecteur refracte = i_n + n_1/n_2 * i_t;
    return refracte;
}
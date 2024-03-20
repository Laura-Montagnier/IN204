#include "rebond.hpp"

std::random_device rd;
std::mt19937 generator(rd()); // Mersenne Twister 19937 engine : une méthode pour avoir de l'aléatoire

std::uniform_real_distribution<double> distribution(-1, 1);

#define DEV

#ifndef DEV
Vecteur direction_difusee(const Vecteur &normale) {
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

#else

Vecteur direction_difusee(const Vecteur &normale) {
    // On choisit un point de la sphere unitaire tangente à la surface
    // Methode par rejet

    Vecteur direction;

    while (true) {
        direction.x = distribution(generator);
        direction.y = distribution(generator);
        direction.z = distribution(generator);

        if (direction.norme2() <= 1) { 
            direction *= 1 / direction.norme();
            direction += normale;
            return direction;
        }
    }
}

#endif

Vecteur direction_reflechie(const Vecteur &incident, const Vecteur &normale) {
    return incident - 2 * (incident * normale) * normale;
}

Vecteur direction_refractee(const Vecteur &incident, const Vecteur &normale) {

    const int methode = 2;

    double n_1, n_2;
    int sgn = (incident * normale > 0) ? 1 : -1;
    if (sgn == 1) {
        // rayon sortant de l'objet
        n_1 = 1.3;
        n_2 = 1.;
    } else {
        // rayon entrant dans l'objet
        n_1 = 1.;
        n_2 = 1.3;
    }
    double q = n_1 / n_2;

    // TENTATIVE 2 
    if (methode == 2) {

        Vecteur i_n = (incident * normale) * normale;
        Vecteur i_t = incident - i_n;

        Vecteur r_t = q * i_t;

        double a = incident.norme2() - q * q * i_t.norme2();
        if (a <= 0) {
            return direction_reflechie(incident, normale);
            std::cout << "*-*-\n";
        }
        Vecteur r_n = +sgn * sqrt(a) * normale;

        return r_t + r_n;
    }

    // WIKIPEDIA
    if (methode == 3) {

        Vecteur i = incident * (1 / incident.norme());
        double cos_i = -normale * i;

        double a = 1 - q * q * (1 - cos_i * cos_i);

        if (a <= 0) {
            return direction_reflechie(incident, normale);
        }

        double cos_r = sqrt(a);

        if (cos_i > 0) {
            return q * i + (q * cos_i - cos_r) * normale;
        }
        return q * i + (q * cos_i + cos_r) * normale;
    }
}
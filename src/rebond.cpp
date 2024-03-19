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

    // {  TENTATIVE 1
    // Vecteur i_n = (incident * normale) * normale;
    // Vecteur i_t = incident - i_n;

    // if (n_1/n_2 * i_t.norme2() > 50 * i_n.norme2()) {
    //     // reflection totale
    //     return direction_reflechie(incident, normale);
    // }
    // // Vecteur refracte = i_t + n_1/n_2 * i_n; // pas correct mais joli
    // Vecteur refracte = i_n + n_1/n_2 * i_t;
    // // Vecteur refracte = i_n - n_1/n_2 * i_t;
    // return refracte;
    // }

    // TENTATIVE 2
    if (methode == 2) {

        Vecteur i_n = (incident * normale) * normale;
        Vecteur i_t = incident - i_n;

        // double a = incident*i_t;
        // return q*a / i_t.norme2() * i_t  + sqrt(incident.norme2() - a*a / i_t.norme2())  * normale * -sgn;

        // if (q*q * i_t.norme2() < 1);

        Vecteur r_t = q * i_t;

        double radicande = incident.norme2() - q * q * i_t.norme2();
        if (radicande <= 0) {
            return direction_reflechie(incident, normale);
            std::cout << "*-*-\n";
        }
        Vecteur r_n = +sgn * sqrt(radicande) * normale;

        return r_t + r_n;
    }

    // WIKIPEDIA
    if (methode == 3) {

        Vecteur i = incident * (1 / incident.norme());
        double cos_i = -normale * i;

        double radicande = 1 - q * q * (1 - cos_i * cos_i);

        if (radicande <= 0) {
            return direction_reflechie(incident, normale);
            std::cout << "*-*-\n";
        }
        double cos_r = sqrt(1 - q * q * (1 - cos_i * cos_i));

        if (cos_i > 0) {
            return q * i + (q * cos_i - cos_r) * normale;
        }
        return q * i + (q * cos_i + cos_r) * normale;
    }

    // T4 gpt idem à wikipedia
    //     Vecteur i = incident* (1 / incident.norme());
    //     double theta_i = acos (i*normale);
    //     double sinTheta1 = sin(theta_i);

    //     double sinTheta2 = q * sinTheta1;

    //     if (sinTheta2 > 1){
    //         std::cout << "aze\n";
    //     }
    //     Vecteur refractedVector = q * (i - (i*normale) * normale) - normale * sqrt(1 - sinTheta2*sinTheta2);
    //     return refractedVector;
}
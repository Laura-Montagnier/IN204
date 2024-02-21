#include "volumes.hpp"

// Opérations sur les vecteurs

Vecteur Vecteur::operator+(const Vecteur autre) const { // Vecteur + Vecteur
    return Vecteur(x + autre.x, y + autre.y, z + autre.z);
};

Vecteur Vecteur::operator+=(const Vecteur autre) { // Vecteur =+ Vecteur
    return *this = *this + autre;
};

Vecteur Vecteur::operator*(double lambda) const { // Vecteur * double
    return Vecteur(lambda * x, lambda * y, lambda * z);
};

Vecteur Vecteur::operator*=(double lambda) { // Vecteur *= double
    return *this = *this * lambda;
};

Vecteur Vecteur::operator-() const { // - Vecteur
    return (*this) * -1;
};

Vecteur Vecteur::operator-(const Vecteur autre) const { // Vecteur - Vecteur
    return (*this) + (-autre);
};

Vecteur Vecteur::operator-=(const Vecteur autre) { // Vecteur -= Vecteur
    return *this = *this - autre;
};

double Vecteur::operator*(const Vecteur autre) const { // Vecteur.Vecteur Produit scalaire
    return (x * autre.x) + (y * autre.y) + (z * autre.z);
};

Vecteur operator*(double lambda, const Vecteur vecteur) { // double * Vecteur
    return vecteur * lambda;
}


// Affichage avec stream pour les différents objets

inline std::ostream &operator<<(std::ostream &stream, const Vecteur &vecteur) {
    return stream << "Vecteur(" << vecteur.x << ", " << vecteur.y << ", " << vecteur.z << ")";
}

inline std::ostream &operator<<(std::ostream &stream, const Rayon &rayon) {
    return stream << "Rayon d'origine " << rayon.origine << " et de direction " << rayon.direction;
}

inline std::ostream &operator<<(std::ostream &stream, const Intersection &intersection) {
    return stream << "Point d'intersection" << intersection.point << "issu du rayon" << intersection.direction;
}

inline std::ostream &operator<<(std::ostream &stream, const Sphere &sphere) {
    return stream << "Sphère de centre " << sphere.centre << " et de rayon " << sphere.radius;
}

inline std::ostream &operator<<(std::ostream &stream, const Plan &plan) {
    return stream << "Plan passant par " << plan.point << " et de normale " << plan.normale;
}


// calcul d'intersection rayon-objet

bool calcul_intersection(const Rayon& rayon, const Plan& plan, Intersection &intersection){

    if (rayon.direction * plan.normale == 0){
        intersection.existe = false;
        return false;
    }

    double t = - (rayon.origine - plan.point) * plan.normale / (rayon.direction * plan.normale);
    
    if(t <= 0){
        intersection.existe = false;
        return false;
    }

    intersection.existe = true;
    intersection.point = rayon.origine + t * rayon.direction;
    intersection.direction = rayon.direction;
    return true;
}
#include "volumes.hpp"

template <typename T>
int sign(T x) {
    // -1, 0 ou 1
    return (x > 0) - (x < 0);
}

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

double Vecteur::norme2() const {
    return (*this) * (*this);
}

double Vecteur::norme() const {
    return sqrt(norme2());
}

// Opérations sur les unions

Union::Union(std::initializer_list<Objet *> liste) {
    ajoute(liste);
}

void Union::ajoute(std::initializer_list<Objet *> liste) {
    for (auto &objet : liste) {
        push_back(objet);
    }
}

// Affichage avec stream pour les différents objets

std::ostream &operator<<(std::ostream &stream, const Vecteur &vecteur) {
    return stream << "Vecteur(" << vecteur.x << ", " << vecteur.y << ", " << vecteur.z << ")";
}

std::ostream &operator<<(std::ostream &stream, const Rayon &rayon) {
    return stream << "Rayon d'origine " << rayon.origine << " et de direction " << rayon.direction;
}

std::ostream &operator<<(std::ostream &stream, const Intersection &intersection) {
    return stream << "Point d'intersection" << intersection.point << "issu du rayon" << intersection.direction;
}

std::ostream &operator<<(std::ostream &stream, const Sphere &sphere) {
    return stream << "Sphère de centre " << sphere.centre << " et de rayon " << sphere.radius;
}

std::ostream &operator<<(std::ostream &stream, const Plan &plan) {
    return stream << "Plan passant par " << plan.point << " et de normale " << plan.normale;
}

// calcul d'intersection rayon-objet

bool Objet::calcul_intersection(const Rayon &rayon, Intersection &intersection) const {
    std::cout << "Err should be called from subclass, not Objet\n";
    throw; // should be pure virtual ?
}

bool Union::calcul_intersection(const Rayon &rayon, Intersection &intersection) const {
    double min_distance = INFINITY;
    Intersection inter;
    bool resultat = false;
    for (auto &objet : (*this)) {
        resultat |= objet->calcul_intersection(rayon, inter); // overriding : Union doit contenir des pointeurs ou références
        if (inter.existe && inter.distance < min_distance) {
            min_distance = inter.distance;
            intersection = inter; // .copy() ?
        }
    }
    return resultat;
}

bool Sphere::calcul_intersection(const Rayon &rayon, Intersection &intersection) const {
    // std::cout << rayon << *this <<"\n";
    // std::cout << "produit scalaire" << rayon.direction * sphere....? <<"\n";

    Vecteur D = rayon.direction;
    Vecteur O = rayon.origine;
    Vecteur C = centre;
    double R = radius;

    double a = D * D;
    double b = 2 * D * (O - C);
    double c = (O - C) * (O - C) - R * R;
    double delta = b * b - 4 * a * c;
    double t;

    // std::cout << a << "\n";
    // std::cout << b << "\n";
    // std::cout << c << "\n";
    // std::cout << delta << "\n";

    if (delta < 0) {
        // std::cout << "a\n" ;
        intersection.existe = false;
        return false;
    } else if (delta == 0) {
        t = -b / (2 * a);
    } else { // delta < 0
        // Il faut gérer le cas négatif, là je n'ai fait que l'intersection la plus proche au pif, oups
        t = (-b - sqrt(delta)) / (2 * a);
    }

    intersection.existe = true;
    intersection.point = O + t * D;
    intersection.direction = rayon.direction;
    intersection.distance = t; //  D normalisé ?
    intersection.normale = (intersection.point - C) * (1 / R);
    intersection.materiau = materiau;
    return true;
}

bool Plan::calcul_intersection(const Rayon &rayon, Intersection &intersection) const {

    if (rayon.direction * normale == 0) {
        intersection.existe = false;
        return false;
    }

    double t = -(rayon.origine - point) * normale / (rayon.direction * normale);

    if (t <= 0) {
        intersection.existe = false;
        return false;
    }

    intersection.existe = true;
    intersection.point = rayon.origine + t * rayon.direction;
    intersection.direction = rayon.direction;
    intersection.normale = normale; // * -sign(normale * rayon.direction);
    intersection.distance = t; //  t / norme(vitesse) ?
    intersection.materiau = materiau;
    return true;
}
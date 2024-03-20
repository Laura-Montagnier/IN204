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
    return stream << "(" << vecteur.x << ", " << vecteur.y << ", " << vecteur.z << ")";
}

std::ostream &operator<<(std::ostream &stream, const Rayon &rayon) {
    return stream << "Rayon d'origine " << rayon.origine << " et de direction " << rayon.direction;
}

std::ostream &operator<<(std::ostream &stream, const Intersection &intersection) {
    return stream << "Intersection au point " << intersection.point << " issu de direction " << intersection.direction;
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

    Vecteur D = rayon.direction;
    Vecteur O = rayon.origine;
    Vecteur C = centre;
    double R = radius;

    double a = D * D;
    double b = 2 * D * (O - C);
    double c = (O - C) * (O - C) - R * R;
    double delta = b * b - 4 * a * c;
    double t;

    if (delta < 0) {
        intersection.existe = false;
        return false;
    } else if (delta == 0) {
        t = -b / (2 * a);
    } else {
        // delta < 0
        if ((-b - sqrt(delta)) / (2 * a) > 0) {
            t = (-b - sqrt(delta)) / (2 * a);
        } else {
            intersection.existe = false;
            return false;
        }
    }

    t *= 1 - epsilon;

    intersection.existe = true;
    intersection.point = O + t * D;
    intersection.direction = rayon.direction;
    intersection.distance = t;
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

    t *= 1 - epsilon;

    intersection.existe = true;
    intersection.point = rayon.origine + t * rayon.direction;
    intersection.direction = rayon.direction;
    intersection.normale = normale;
    intersection.distance = t;
    intersection.materiau = materiau;
    return true;
}

// Constructeurs Materiau
Materiau::Materiau() : couleur(1, 0, 1), p_reflexion(0.), p_transmission(0.), lumineux(false){}; // Magenta bien visible par défaut
Materiau::Materiau(const Vecteur couleur, double p_reflexion, double p_transmission, bool lumineux) : couleur(couleur),
                                                                                                      p_reflexion(p_reflexion),
                                                                                                      p_transmission(p_transmission),
                                                                                                      lumineux(lumineux){};
Materiau::Materiau(double r, double g, double b, double p_reflexion, double p_transmission, bool lumineux) : couleur(r, g, b),
                                                                                                             p_reflexion(p_reflexion),
                                                                                                             p_transmission(p_transmission),
                                                                                                             lumineux(lumineux){};

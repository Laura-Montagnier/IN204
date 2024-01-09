#include "defs.hpp"
#include <cmath>
#include <iostream>

class Vecteur {
private:
public:
    double x;
    double y;
    double z;

    // Constructeur
    Vecteur() : x(0), y(0), z(0){};
    Vecteur(double x, double y, double z) : x(x), y(y), z(z){};
    Vecteur(Vecteur &autre) : x(autre.x), y(autre.y), z(autre.z){};

    // Pour afficher les infos du vecteur
    void print() const {
    }

    Vecteur operator+(Vecteur autre) const {
        return Vecteur(x + autre.x, y + autre.y, z + autre.z);
    };

    Vecteur operator*(double lambda) const {
        return Vecteur(lambda * x, lambda * y, lambda * z);
    };

    Vecteur operator-() const {
        return (*this) * -1;
    };

    Vecteur operator-(Vecteur autre) const {
        return (*this) + (-autre);
    };
};

Vecteur operator*(double lambda, const Vecteur vecteur) {
    return vecteur * lambda;
}

std::ostream &operator<<(std::ostream &stream, const Vecteur &vecteur) {
    return stream << "Vecteur(" << vecteur.x << ", " << vecteur.y << ", " << vecteur.z << ")";
}

class Sphere {
private:
public:
    Vecteur centre;
    double radius;

    // Constructeur
    Sphere(Vecteur point, double r) : centre(point), radius(r) {}
    Sphere(double x, double y, double z, double r) : centre(x, y, z), radius(r) {}
    Sphere(Sphere &s) = default;
};

// Afficher les informations de la sphère
std::ostream &operator<<(std::ostream &stream, const Sphere &sphere) {
    return stream << "Sphère de centre " << sphere.centre << " et de rayon " << sphere.radius;
}

class Rayon {
private:
public:
    Vecteur origine;
    Vecteur direction;

    // Constructeur
    Rayon(Vecteur origine, Vecteur direction) : origine(origine), direction(direction) {}
    Rayon(double x, double y, double z, double v_x, double v_y, double v_z) : origine(x, y, z), direction(v_x, v_y, v_z) {}
};

// Afficher les informations du rayon
std::ostream &operator<<(std::ostream &stream, const Rayon &rayon) {
    return stream << "Rayon d'origine" << rayon.origine << " et de direction " << rayon.direction << std::endl;
}
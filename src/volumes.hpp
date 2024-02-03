#include "defs.hpp"

class Vecteur {
private:
public:
    double x;
    double y;
    double z;

    // Constructeurs
    Vecteur() = default;
    Vecteur(double x, double y, double z) : x(x), y(y), z(z){};
    Vecteur(const Vecteur &) = default;
    // Vecteur(const Vecteur &autre) : x(autre.x), y(autre.y), z(autre.z){};

    // Operations sur les vecteurs
    Vecteur operator+(const Vecteur autre) const { // Vecteur + Vecteur
        return Vecteur(x + autre.x, y + autre.y, z + autre.z);
    };

    Vecteur operator+=(const Vecteur autre) { // Vecteur =+ Vecteur
        return *this = *this + autre;
    };

    Vecteur operator*(double lambda) const { // Vecteur * double
        return Vecteur(lambda * x, lambda * y, lambda * z);
    };

    Vecteur operator*(double lambda) const { // Vecteur * double
        return Vecteur(lambda * x, lambda * y, lambda * z);
    };

    Vecteur operator*=(double lambda) { // Vecteur *= double
        return *this = *this * lambda;
    };

    Vecteur operator-() const { // - Vecteur
        return (*this) * -1;
    };

    Vecteur operator-(const Vecteur autre) const { // Vecteur - Vecteur
        return (*this) + (-autre);
    };

    Vecteur operator-=(const Vecteur autre) { // Vecteur -= Vecteur
        return *this = *this - autre;
    };
};

Vecteur operator*(double lambda, const Vecteur vecteur) { // double * Vecteur
    return vecteur * lambda;
}

// Pour afficher les infos du vecteur
std::ostream &operator<<(std::ostream &stream, const Vecteur &vecteur) {
    return stream << "Vecteur(" << vecteur.x << ", " << vecteur.y << ", " << vecteur.z << ")";
}

class Sphere {
private:
public:
    Vecteur centre;
    double radius;

    // Constructeurs
    Sphere() = default;
    Sphere(Vecteur point, double r) : centre(point), radius(r) {}
    Sphere(double x, double y, double z, double r) : centre(x, y, z), radius(r) {}
    Sphere(const Sphere &) = default;
};

// Affiche les informations de la sphère
std::ostream &operator<<(std::ostream &stream, const Sphere &sphere) {
    return stream << "Sphère de centre " << sphere.centre << " et de rayon " << sphere.radius;
}


class Plan {
private:
public:
    Vecteur point;
    Vecteur normale;

    // Constructeurs
    Plan(Vecteur p, Vecteur n) : point(p), normale(n) {}
    Plan(const Plan &) = default;
};

std::ostream &operator<<(std::ostream &stream, const Plan &plan) {
    return stream << "Plan passant par " << plan.point << " et de normale " << plan.normale;
}


Intersection calcul_intersection(const Rayon rayon, const Plan plan, Intersection intersection){
    if (rayon .direction * plan.normale == 0){
        intersection.existe = false;
    }

    else{
        double t = (rayon.origine - plan.point) * plan.normale / (rayon.direction * plan.normale);
    } 
    
    Intersection.existe = true;
    Intersection.point = point_intersection = rayon.origine + t * rayon.direction;
    Intersection.direction = rayon.direction;
    return Intersection(point_intersection, rayon.direction);

}




class Rayon {
private:
public:
    Vecteur origine;
    Vecteur direction;

    // Constructeurs
    Rayon() = default;
    Rayon(Vecteur origine, Vecteur direction) : origine(origine), direction(direction) {}
    Rayon(double x, double y, double z, double v_x, double v_y, double v_z) : origine(x, y, z), direction(v_x, v_y, v_z) {}
    Rayon(const Rayon&) = default;
};

// Afficher les informations du rayon
std::ostream &operator<<(std::ostream &stream, const Rayon &rayon) {
    return stream << "Rayon d'origine " << rayon.origine << " et de direction " << rayon.direction;
}
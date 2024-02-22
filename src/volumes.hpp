#pragma once
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

    // Operations sur les vecteurs
    Vecteur operator+(const Vecteur) const;
    Vecteur operator+=(const Vecteur);
    Vecteur operator*(double) const;
    Vecteur operator*=(double);
    Vecteur operator-() const;
    Vecteur operator-(const Vecteur) const;
    Vecteur operator-=(const Vecteur);
    double operator*(const Vecteur) const; // produit scalaire
};

Vecteur operator*(double, const Vecteur);


// Pour afficher les infos du vecteur
inline std::ostream &operator<<(std::ostream &, const Vecteur &);

class Rayon {
private:
public:
    Vecteur origine;
    Vecteur direction;

    // Constructeurs
    Rayon() = default;
    Rayon(const Vecteur origine, const Vecteur direction) : origine(origine), direction(direction) {}
    Rayon(double x, double y, double z, double v_x, double v_y, double v_z) : origine(x, y, z), direction(v_x, v_y, v_z) {}
    Rayon(const Rayon &) = default;
};

// Afficher les informations du rayon
inline std::ostream &operator<<(std::ostream &, const Rayon &);

class Intersection {
private:
public:
    bool existe;
    Vecteur point;
    Vecteur direction;

    // Constructeurs
    Intersection() = default;
    Intersection(const Vecteur point, const Vecteur direction) : point(point), direction(direction) {}
    Intersection(double x, double y, double z, double v_x, double v_y, double v_z) : point(x, y, z), direction(v_x, v_y, v_z) {}
    Intersection(const Intersection &) = default;
};

// Afficher les informations de l'intersection
inline std::ostream &operator<<(std::ostream &, const Intersection &);

class Sphere {
private:
public:
    Vecteur centre;
    double radius;

    // Constructeurs
    Sphere() = default;
    Sphere(const Vecteur point, double r) : centre(point), radius(r) {}
    Sphere(double x, double y, double z, double r) : centre(x, y, z), radius(r) {}
    Sphere(const Sphere &) = default;
};

// Affiche les informations de la sphère
inline std::ostream &operator<<(std::ostream &, const Sphere &);

class Plan {
private:
public:
    Vecteur point;
    Vecteur normale;

    // Constructeurs
    Plan(const Vecteur p, const Vecteur n) : point(p), normale(n) {}
    Plan(const Plan &) = default;
};

inline std::ostream &operator<<(std::ostream &, const Plan &);

bool calcul_intersection(const Rayon &, const Plan &, Intersection &);

class Materiau {
private:
public:
    Vecteur couleur;

    //Constructeurs

    Materiau() = default;
    Materiau(const Vecteur point) : couleur(point) {}
    Materiau(double r, double g, double b) : couleur(r, g, b){}
    
    //Remarque pour plus tard : est-ce qu'il faudrait pas renvoyer des erreurs si on est en dehors de 0 et 258 ?

    Materiau(const Materiau &) = default;
};

inline std::ostream &operator<<(std::ostream &, const Materiau &);


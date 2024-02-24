#pragma once
#include "defs.hpp"

template <typename T>
int sign(T x);

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

    double norme2() const;
    double norme() const;
};

Vecteur operator*(double, const Vecteur);

// Pour afficher les infos du vecteur
std::ostream &operator<<(std::ostream &, const Vecteur &);

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
std::ostream &operator<<(std::ostream &, const Rayon &);

class Materiau {
private:
public:
    Vecteur couleur;

    // Constructeurs

    Materiau() : couleur(255, 0, 255){};
    Materiau(const Vecteur point) : couleur(point) {}
    Materiau(double r, double g, double b) : couleur(r, g, b) {}

    // Remarque pour plus tard : est-ce qu'il faudrait pas renvoyer des erreurs si on est en dehors de 0 et 258 ?

    Materiau(const Materiau &) = default;
};

std::ostream &operator<<(std::ostream &, const Materiau &);

class Intersection {
private:
public:
    bool existe;
    Vecteur point;
    Vecteur direction;
    Vecteur normale;
    double distance;
    Materiau materiau;

    // Constructeurs
    Intersection() : existe(false){};
    // Intersection(const Vecteur point, const Vecteur direction) : point(point), direction(direction) {}
    // Intersection(double x, double y, double z, double v_x, double v_y, double v_z) : point(x, y, z), direction(v_x, v_y, v_z) {}
    Intersection(const Intersection &) = default;
};

// Afficher les informations de l'intersection
std::ostream &operator<<(std::ostream &, const Intersection &);

class Objet {
protected:
    Objet() = default;
    Objet(Materiau materiau) : materiau(materiau){};

public:
    Materiau materiau;
    virtual bool calcul_intersection(const Rayon &, Intersection &) const = 0;
};

class Union : public Objet, public std::vector<Objet *> {
    // Vecteur contenant des pointeurs sur des Objets
public:
    Union(std::initializer_list<Objet *>);
    void ajoute(std::initializer_list<Objet *>);

    virtual bool calcul_intersection(const Rayon &, Intersection &) const;
};

class Sphere : public Objet {
private:
public:
    Vecteur centre;
    double radius;

    // Constructeurs
    Sphere() = default;
    Sphere(const Vecteur point, double r, Materiau mat = Materiau()) : Objet(mat), centre(point), radius(r) {}
    Sphere(double x, double y, double z, double r, Materiau mat = Materiau()) : Objet(mat), centre(x, y, z), radius(r) {}
    Sphere(const Sphere &) = default;

    virtual bool calcul_intersection(const Rayon &, Intersection &) const;
};

// Affiche les informations de la sphère
std::ostream &operator<<(std::ostream &, const Sphere &);

class Plan : public Objet {
private:
public:
    Vecteur point;
    Vecteur normale;

    // Constructeurs
    Plan(const Vecteur p, const Vecteur n, Materiau mat = Materiau()) : Objet(mat), point(p), normale(n) {}
    Plan(const Plan &) = default;

    virtual bool calcul_intersection(const Rayon &, Intersection &) const;
};

std::ostream &operator<<(std::ostream &, const Plan &);

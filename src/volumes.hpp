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
    Vecteur normale;
    double distance;

    // Constructeurs
    Intersection() : existe(false){};
    // Intersection(const Vecteur point, const Vecteur direction) : point(point), direction(direction) {}
    // Intersection(double x, double y, double z, double v_x, double v_y, double v_z) : point(x, y, z), direction(v_x, v_y, v_z) {}
    Intersection(const Intersection &) = default;
};

// Afficher les informations de l'intersection
inline std::ostream &operator<<(std::ostream &, const Intersection &);

class Objet {
protected:
    Objet() = default;

public:
    virtual bool calcule_intersection(const Rayon &, Intersection &) const = 0;
};

class Union : public Objet, public std::vector<Objet *> {
    // Vecteur contenant des pointeurs sur des Objets
public:
    void ajoute(Objet &objet);

    template <typename... Args>
    void ajoute(Objet &objet, Args &...args);

    Union(Objet &objet);

    template <typename... Args>
    Union(Objet &objet, Args &...args);

    virtual bool calcule_intersection(const Rayon &, Intersection &) const;
};

class Sphere : public Objet {
private:
public:
    Vecteur centre;
    double radius;

    // Constructeurs
    Sphere() = default;
    Sphere(const Vecteur point, double r) : centre(point), radius(r) {}
    Sphere(double x, double y, double z, double r) : centre(x, y, z), radius(r) {}
    Sphere(const Sphere &) = default;

    virtual bool calcule_intersection(const Rayon &, Intersection &) const;
};

// Affiche les informations de la sphère
inline std::ostream &operator<<(std::ostream &, const Sphere &);

class Plan : public Objet {
private:
public:
    Vecteur point;
    Vecteur normale;

    // Constructeurs
    Plan(const Vecteur p, const Vecteur n) : point(p), normale(n) {}
    Plan(const Plan &) = default;

    virtual bool calcule_intersection(const Rayon &, Intersection &) const;
};

inline std::ostream &operator<<(std::ostream &, const Plan &);

bool calcul_intersection(const Rayon &, const Plan &, Intersection &);

bool calcul_intersection(const Rayon &, const Union &, Intersection &);

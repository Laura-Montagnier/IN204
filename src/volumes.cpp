#include <iostream>
#include <cmath>

// La classe vecteur servira aussi pour les points, puisqu'il s'agit de contenir le même type d'informations.

class Vecteur {
private:
    double coordX;
    double coordY;
    double coordZ;

public:
    //Constructeur
    Vecteur(double x, double y, double z) : coordX(x), coordY(y), coordZ(z) {}

    //Accesseurs
    double getCoordX() const {return coordX; }
    double getCoordY() const {return coordY; }
    double getCoordZ() const {return coordZ; }

    //Pour afficher les infos du vecteur
}


class Sphere {
private:
    double centerX;
    double centerY;
    double centerZ;
    double radius;

public:
    // Constructeur
    Sphere(double x, double y, double z, double r) : centerX(x), centerY(y), centerZ(z), radius(r) {}

    // Accesseurs
    double getCenterX() const { return centerX; }
    double getCenterY() const { return centerY; }
    double getCenterZ() const { return centerZ; }
    double getRadius() const { return radius; }

   

    // Afficher les informations de la sphère
    void infoSphere() const {
        std::cout << "Sphère de centre (" << centerX << ", " << centerY << ", " << centerZ << ") et de rayon " << radius << std::endl;
    }
};

int main() {
    // Exemple d'utilisation de la classe Sphere
    Sphere maSphere(1.0, 2.0, 3.0, 4.0);

    // Afficher les informations sur la sphère
    maSphere.infoSphere();

   
    return 0;
}
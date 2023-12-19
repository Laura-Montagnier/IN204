#include <iostream>
#include <cmath>

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

    // Méthode pour afficher les informations sur la sphère
    void displaySphereInfo() const {
        std::cout << "Sphère de centre (" << centerX << ", " << centerY << ", " << centerZ
                  << ") et de rayon " << radius << std::endl;
    }
};

int main() {
    // Exemple d'utilisation de la classe Sphere
    Sphere maSphere(1.0, 2.0, 3.0, 4.0);

    // Afficher les informations sur la sphère
    maSphere.displaySphereInfo();

    return 0;
}

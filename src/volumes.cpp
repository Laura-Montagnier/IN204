#include "volumes.hpp"

// La classe vecteur servira aussi pour les points, puisqu'il s'agit de contenir le même type d'informations.

class Vecteur {
private:
public:
    double x;
    double y;
    double z;

    //Constructeur
    Vecteur() : x(0), y(0), z(0) {};
    Vecteur(double x, double y, double z) : x(x), y(y), z(z) {};
    Vecteur(Vecteur& autre) : x(autre.x), y(autre.y), z(autre.z) {};


    //Pour afficher les infos du vecteur
     void print() const {
        std::cout << "3 coordonées (" << x << ", " << y << ", " << z << ")" << std::endl;
    }

    Vecteur operator+(Vecteur& autre){
        return Vecteur(x + autre.x, y + autre.y, z + autre.z);
    };

    Vecteur operator*(double lambda){
        return Vecteur(lambda*x, lambda*y, lambda*z);
    };
};


class Sphere {
private:
public:
    Vecteur centre;
    double radius;
    
    // Constructeur
    Sphere(Vecteur point, double r) : centre(point), radius(r) {}
    Sphere(double x, double y, double z, double r) : centre(x, y, z), radius(r) {}
    Sphere(Sphere& s) = default;

    // Afficher les informations de la sphère
    void print() const {
        std::cout << "Sphère de centre (" << centre.x << ", " << centre.y << ", " << centre.z << ") et de rayon " << radius << std::endl;
    }
};

class Rayon {
private :
public :
    Vecteur origine;
    Vecteur direction;

    //Constructeur
    Rayon(double x, double y, double z, double v_x, double v_y, double v_z) : origine(x, y, z), direction(v_x, v_y, v_z) {}

    //Afficher les informations du rayon
    void print() const {
        std::cout << "Rayon d'origine ("<< origine.x <<", " << origine.y << ", " << origine.z << ") et de direction (" << direction.x << ", " << direction.y << ", " << direction.z << ")" << std::endl;
     }


};


int main() {
    // Exemple d'utilisation de la classe Sphere
    Sphere maSphere(1.0, 2.0, 3.0, 4.0);

    // Afficher les informations sur la sphère
    maSphere.print();

    return 0;
}



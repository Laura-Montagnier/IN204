#include <iostream>
#include <cmath>

// La classe vecteur servira aussi pour les points, puisqu'il s'agit de contenir le même type d'informations.

class Vecteur {
private:
    double X;
    double Y;
    double Z;

public:
    //Constructeur
    Vecteur(double x, double y, double z) : X(x), Y(y), Z(z) {}

    //Accesseurs
    double getCoordX() const {return X; }
    double getCoordY() const {return Y; }
    double getCoordZ() const {return Z; }

    //Pour afficher les infos du vecteur
     void print() const {
        std::cout << "3 coordonées (" << coordX << ", " << coordY << ", " << coordZ << ")" << std::endl;
    }
};


class Sphere {
private:
    

public:
    Vecteur centre;
    double radius;
    
    // Constructeur
    Sphere(double x, double y, double z, double r) : centre(Vecteur(X, Y, Z)), radius(r) {}

    // Afficher les informations de la sphère
    void print() const {
        std::cout << "Sphère de centre (" << X << ", " << Y << ", " << Z << ") et de rayon " << radius << std::endl;
    }
};

class Rayon {
private :
public :
    Vecteur origine;
    Vecteur direction;

    //Constructeur
    Rayon(double x, double y, double z, double a, double b, double c) : origine(Vecteur(X, Y, Z)), direction(Vecteur(A, B, C)) {}

    //Afficher les informations du rayon
    void print() const {
        std::cout << "Rayon d'origine ("<< X <<", " << Y << ", " << Z << ") et de direction ("<< A <<", " << B << ", " << C << ") << std::endl;
     }


};



int main() {
    // Exemple d'utilisation de la classe Sphere
    Sphere maSphere(1.0, 2.0, 3.0, 4.0);

    // Afficher les informations sur la sphère
    maSphere.print();

   
    return 0;
}
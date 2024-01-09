#include "volumes.hpp"

// La classe vecteur servira aussi pour les points, puisqu'il s'agit de contenir le même type d'informations.

int main() {
    // Exemple d'utilisation de la classe Sphere
    Sphere maSphere(1.0, 2.0, 3.0, 4.0);

    // Afficher les informations sur la sphère
    std::cout << maSphere << "\n";

    return 0;
}

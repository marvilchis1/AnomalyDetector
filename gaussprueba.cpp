#include <iostream>
#include "gauss.h"
#include <vector>

int main() {
    int apothem = 2;
    std::vector<double> gaussianmask = GaussianMask(apothem);
    std::vector<double> gaussianvector = Gauss::GaussConstant(apothem);
    int kl = Gauss::MaskLength(apothem);
    //std::vector <double> gm(kl);

    double sigma = apothem /2.0;

    std::cout <<  "\n\nVector con valores gauss (internet):\n" << std::endl;
    for (int i = 0; i < kl; ++i)
        std::cout << GaussianFunction(i, apothem, sigma) << " ";
        std::cout << std::endl;

    std::cout <<  "\n\nVector con valores gauss (mio):\n" << std::endl;
    for (int i = 0; i < kl; ++i)
        std::cout << gaussianvector[i] << " ";


    std::cout <<  "\n\nEjemplo mio:\n" << std::endl;
    for (int y = 0; y < kl; ++y) {
        for(int x = 0; x < kl; ++x) {
            std::cout << gaussianmask[Gauss::Index(x, y, kl)] << " ";
        }
        std::cout << std::endl;
    }

/*
    for (int i = 0; i < kl; ++i)
        std::cout << gaussianmask[i] << " ";

    std::cout << std::endl;
*/
    return 0;
}
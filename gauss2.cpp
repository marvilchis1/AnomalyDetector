#include "gauss.h"


int Gauss::MaskLength(int mask_apothem) {
    return 2*mask_apothem+1;
}

int Gauss::Index(int x, int y, int length) {
    return length * y + x;
}


double GaussianFunction( double x, double b, double sigma ) {
    // e^n
    double n = (x - b) / sigma;
    // Valor de euler: -0.5 = -1/2 y a*a para evitar usar pow()
    return std::exp(-0.5 * n * n);
}

std::vector<double> GaussianMask(int mask_apothem) {
    double sigma = mask_apothem/2.0;
    // Tamano de mascara = m x m
    int k_length = Gauss::MaskLength(mask_apothem);
    std::vector<double> gkernel(k_length * k_length);

    double sum = 0.0, aux = 0.0;

    for (int y = 0; y < k_length; ++y){
        for (int x = 0; x < k_length; ++x){
            aux =  GaussianFunction(y, mask_apothem, sigma) *
                   GaussianFunction(x, mask_apothem, sigma);
            gkernel[Gauss::Index(x, y, k_length)] = aux;
            sum += aux;
        }
    }

    // Normalizacion
    for(int y = 0; y < k_length; ++y){
        for(int x = 0; x < k_length; ++x){
            gkernel[Gauss::Index(x, y, k_length)] /= sum;
        }
    }
    return gkernel;
}







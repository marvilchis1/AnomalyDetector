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

// Regresa un vector el cual contiene las contantes
std::vector<double> Gauss::GaussConstant(int mask_apothem) {
    int k_length = Gauss::MaskLength(mask_apothem);
    std::vector<double> cvector(k_length);
    // c = -2*log(v); donde v = 1/255
    const double c = -2.0 * std::log(1/255.0);
    const double s = c/(2 * mask_apothem + 1);
    int k = 0;
    for(int a = -mask_apothem; a <= mask_apothem; ++a){
        cvector[k] = std::exp( -(a * a * s * s) );
        k += 1;
    }
    return cvector;
}

std::vector<double> GaussianMask(int mask_apothem) {
    // Tamano de mascara = m x m
    int k_length = Gauss::MaskLength(mask_apothem);
    std::vector<double> gmask(k_length * k_length), cgvector;
    //double sigma = mask_apothem/2.0;
    cgvector = Gauss::GaussConstant(mask_apothem);
    
    double sum = 0.0, aux = 0.0;
    for (int r = 0; r < k_length; ++r){
        for (int c = 0; c < k_length; ++c){
            aux = cgvector[r] * cgvector[c];
            gmask[Gauss::Index(c, r, k_length)] = aux;
            sum += aux;
        }
    }
    // Normalizacion
    for(int i = 0; i < gmask.size(); ++i){
        gmask[i] /= sum;
    }

    return gmask;
}







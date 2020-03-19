#ifndef _XYZ_H_
#define _XYZ_H_


#include <iostream>

struct XYZ {
    double x, y, z;
    XYZ();
    XYZ(double Y);
    XYZ(double X, double Y, double Z);
    // Imprime el valor de cada componente
    void Print();
};

#endif
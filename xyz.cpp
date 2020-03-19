#include "xyz.h"

XYZ::XYZ() {
    x = 0;
    y = 0;
    z = 0;
}

XYZ::XYZ(double Y) {
    x = Y;
    y = Y;
    z = Y;
}

XYZ::XYZ(double X, double Y, double Z) {
    x = X;
    y = Y;
    z = Z;
}



void XYZ::Print(){
    std::cout << "XYZ";
    std::cout << "(" << x << ", " << y << ", " << z;
    std::cout << ")" << std::endl;

}


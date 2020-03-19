#ifndef _GAUSSKERNEL_H_
#define _GAUSSKERNEL_H_

#include <cmath>
#include <vector>
#include <iomanip>

namespace Gauss {
    int MaskLength(int mask_apothem);
    int Index(int x, int y, int length);
    std::vector<double> GaussConstant(int mask_apothem);
}

double GaussianFunction( double x, double b, double sigma );
std::vector<double> GaussianMask(int mask_apothem);

#endif

#ifndef _MASK_H_
#define _MASK_H_

#include <vector>
#include <cmath>
#include "gauss.h"

class Mask {
    public:
    enum class MaskType{ FOCUS, BLUR, EDGE_ENHANCEMENT, EMBOSSED, EDGE_DETECTION, GAUSSIAN_BLUR };

    Mask();
    Mask(MaskType mask_type, int mask_apothem = 1);
    Mask(std::vector<double> mask_vector);

    bool Set(MaskType mask_type, int mask_apothem = 1);
    bool Set(std::vector<double> mask_vector);

    // Herramientas
    double At(int x, int y);
    std::vector<double> GetVectorMask();
    int MaskLength();
    int MaskApothem();
    int MaskSize();

    private:
    std::vector<double> m_mask;
    int m_length;
    int m_apothem;
    bool MaskSelector(MaskType mask_type);
};


#endif
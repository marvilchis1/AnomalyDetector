#ifndef _LBP_H_
#define _LBP_H_

#include "image.h"
#include "fconvolution.h"

namespace LBP {
    Image GetLBPImage(const Image input);
    std::vector<int> LBP(Image input);

    unsigned char RotationInvariant( unsigned char pattern );
    unsigned char Uniform( unsigned char pattern );
}

#endif
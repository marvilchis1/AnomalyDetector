#ifndef _COLORCONVERTER_H_
#define _COLORCONVERTER_H_

//#include <iostream>
#include <cmath>
#include "color.h"
#include "xyz.h"

class ColorConverter {
    public:
    ColorConverter();
    void RGBtoXYZ(Color &color, XYZ &xyz);
    void SRGBtoXYZ(Color &color, XYZ &xyz);
    void XYZtoRGB(Color &color, XYZ &xyz, int alpha = 255);
    void XYZtoSRGB(Color &color, XYZ &xyz, int alpha = 255);
    // Black and White (Y Luminescence)
    int RGBtoY(Color &color);
    int RGBtoY(int r, int g, int b);

};

#endif
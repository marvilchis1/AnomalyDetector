#ifndef _FCONVOLUTION_H_
#define _FCONVOLUTION_H_

//#include <iostream>
//#include <vector>
//#include <cmath>
#include "image.h"
//#include "color.h"
#include "mask.h"


int Reflect(int size, int index);

int Index(int x, int y, int width);

Image Convolution_NoBorder(Image input, Mask cmask);

Image Convolution_Reflect(Image input, Mask cmask);





#endif
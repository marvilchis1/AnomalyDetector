#include "colorconverter.h"

ColorConverter::ColorConverter() {
}

void ColorConverter::RGBtoXYZ(Color &color, XYZ &xyz) {
    // Se escalan los datos rgb en una escala de 0 a 1,
    // por lo tanto se divide cada valor de 8 bit entre 255
    double red = color.r / 255.0;
    double green = color.g / 255.0;
    double blue = color.b / 255.0;

    xyz.x = 100 * (red*0.4124564 + green*0.3575761 + blue*0.1804375);
	xyz.y = 100 * (red*0.2126729 + green*0.7151522 + blue*0.0721750);
	xyz.z = 100 * (red*0.0193339 + green*0.1191920 + blue*0.9503041);

}

void ColorConverter::SRGBtoXYZ(Color &color, XYZ &xyz) {
    // Se escalan los datos rgb en una escala de 0 a 1,
    // por lo tanto se divide cada valor de 8 bit entre 255
    double red = color.r / 255.0;
    double green = color.g / 255.0;
    double blue = color.b /255.0;

	red = ((red > 0.04045) ? pow((red + 0.055) / 1.055, 2.4) : (red / 12.92)) * 100.0;
	green = ((green > 0.04045) ? pow((green + 0.055) / 1.055, 2.4) : (green / 12.92)) * 100.0;
	blue = ((blue > 0.04045) ? pow((blue + 0.055) / 1.055, 2.4) : (blue / 12.92)) * 100.0;

    xyz.x = red*0.4124564 + green*0.3575761 + blue*0.1804375;
	xyz.y = red*0.2126729 + green*0.7151522 + blue*0.0721750;
	xyz.z = red*0.0193339 + green*0.1191920 + blue*0.9503041;
}

void ColorConverter::XYZtoRGB(Color &color, XYZ &xyz, int alpha) {
    double x = xyz.x / 100.0;
    double y = xyz.y / 100.0;
    double z = xyz.z / 100.0;

    double red = 255 * (3.240479*x - 1.537150*y - 0.498535*z);
    double green = 255 * (-0.969256*x + 1.875992*y + 0.041556*z);
    double blue = 255 * (0.055648*x - 0.204043*y/100 + 1.057311*z); 

    color.r = red;
    color.g = green;
    color.b = blue;
    color.a = alpha;
}

void ColorConverter::XYZtoSRGB(Color &color, XYZ &xyz, int alpha) {
    double x = xyz.x / 100.0;
    double y = xyz.y / 100.0;
    double z = xyz.z / 100.0;

    double red = x * 3.2404542 + y * -1.5371385 + z * -0.4985314;
	double green = x * -0.9692660 + y * 1.8760108 + z * 0.0415560;
	double blue = x * 0.0556434 + y * -0.2040259 + z * 1.0572252;

	red = ((red > 0.0031308) ? (1.055*pow(red, 1 / 2.4) - 0.055) : (12.92*red)) * 255.0;
	green = ((green > 0.0031308) ? (1.055*pow(green, 1 / 2.4) - 0.055) : (12.92*green)) * 255.0;
	blue = ((blue > 0.0031308) ? (1.055*pow(blue, 1 / 2.4) - 0.055) : (12.92*blue)) * 255.0;

    color.r = red;
    color.g = green;
    color.b = blue;  
    color.a = alpha;
}


int ColorConverter::RGBtoY(Color &color) {
    double red = color.r;
    double green = color.g;
    double blue = color.b;

    int Y = 0.59*red + 0.30*green + 0.11*blue;


    return Y;
}

int ColorConverter::RGBtoY(int r, int g, int b) {
    int Y = 0.59*r + 0.30*g + 0.11*b;

    return Y;
}
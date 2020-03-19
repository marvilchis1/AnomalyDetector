#include "color.h"


Color::Color() {
    r = 0;
    g = 0;
    b = 0;
    a = 0;
    y = 0.0;
}

Color::Color( int gray, int alpha, bool bits16) {
    
    if (bits16 == true) {
        r = gray;
        g = gray;
        b = gray;
        a = alpha;
    }
    if (bits16 == false) {
        y = gray;
        a = alpha;
    }
}

Color::Color( int red, int green, int blue, int alpha ) {
    r = red;
    g = green;
    b = blue;
    a = alpha;
}

Color::Color( Name name ) {

    a = 255;
    switch( name ) {
        case Name::BLACK:
            r = 0;
            g = 0;
            b = 0;
            break;
        case Name::GRAY:
            r = 128;
            g = 128;
            b = 128;
            break;
        case Name::SILVER:
            r = 192;
            g = 192;
            b = 192;
            break;
        case Name::WHITE:
            r = 255;
            g = 255;
            b = 255;
            break;
        case Name::MAROON:
            r = 128;
            g = 0;
            b = 0;
            break;
        case Name::RED:
            r = 255;
            g = 0;
            b = 0;
            break;
        case Name::OLIVE:
            r = 128;
            g = 128;
            b = 0;
            break;
        case Name::YELLOW:
            r = 255;
            g = 255;
            b = 0;
            break;
        case Name::GREEN:
            r = 0;
            g = 128;
            b = 0;
            break;
        case Name::LIME:
            r = 0;
            g = 255;
            b = 0;
            break;
        case Name::TEAL:
            r = 0;
            g = 128;
            b = 128;
            break;
        case Name::AQUA:
        case Name::CYAN:
            r = 0;
            g = 255;
            b = 255;
            break;
        case Name::NAVY:
            r = 0;
            g = 0;
            b = 128;
            break;
        case Name::BLUE:
            r = 0;
            g = 0;
            b = 255;
            break;
        case Name::PURPLE:
            r = 128;
            g = 0;
            b = 128;
            break;
        case Name::FUCHSIA:
        case Name::MAGENTA:
            r = 255;
            g = 0;
            b = 255;
            break;
        case Name::CLEAR:
        default:
            r = 0;
            g = 0;
            b = 0;
            a = 0;
    }
}

void Color::print() {
    std::cout << "RGBA";
    std::cout << "(" << r << "," << g << "," << b;
    std::cout << "," << a << ")\t";
    std::cout << "Y" << "(" << y << ")" << std::endl;
}


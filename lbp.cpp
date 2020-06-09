#include "lbp.h"

Image LBP::GetLBPImage(Image input) {
    Image output(input.width(), input.height());
    // Copiar el espacio de color, entre otros;
    output = input;
    for (int y = 0; y < input.height(); ++y) {
        for (int x = 0; x < input.width(); ++x) {
                                   //x+1,y+1
            int center = input.at(x, y).y;
            unsigned char bitssum = 0;

            bitssum |=  ( input.at(Reflect(input.width(), x-1), Reflect(input.height(), y-1)).y >= center ) << 0;
            bitssum |=  ( input.at(Reflect(input.width(), x), Reflect(input.height(), y-1)).y >= center ) << 1;
            bitssum |=  ( input.at(Reflect(input.width(), x+1), Reflect(input.height(), y-1)).y >= center ) << 2;
            bitssum |=  ( input.at(Reflect(input.width(), x+1), Reflect(input.height(), y)).y >= center ) << 3;
            bitssum |=  ( input.at(Reflect(input.width(), x+1), Reflect(input.height(), y+1)).y >= center ) << 4;
            bitssum |=  ( input.at(Reflect(input.width(), x), Reflect(input.height(), y+1)).y >= center ) << 5;
            bitssum |=  ( input.at(Reflect(input.width(), x-1), Reflect(input.height(), y+1)).y >= center ) << 6;
            bitssum |=  ( input.at(Reflect(input.width(), x-1), Reflect(input.height(), y)).y >= center ) << 7;

            bitssum = LBP::Uniform(bitssum);
            bitssum = LBP::RotationInvariant(bitssum);
            output.at(x,y).y = bitssum;
        }
    }
    return output;
}

std::vector<int> LBP::LBP(Image input) {
    std::vector<int> output(input.height() * input.width());

    int i = 0;
    for (int y = 0; y < input.height(); ++y) {
        for (int x = 0; x < input.width(); ++x) {
            double center = input.at(x,y).y;
            unsigned char bitssum = 0;

            bitssum |=  ( input.at(Reflect(input.width(), x-1), Reflect(input.height(), y-1)).y >= center ) << 0;
            bitssum |=  ( input.at(Reflect(input.width(), x), Reflect(input.height(), y-1)).y >= center ) << 1;
            bitssum |=  ( input.at(Reflect(input.width(), x+1), Reflect(input.height(), y-1)).y >= center ) << 2;
            bitssum |=  ( input.at(Reflect(input.width(), x+1), Reflect(input.height(), y)).y >= center ) << 3;
            bitssum |=  ( input.at(Reflect(input.width(), x+1), Reflect(input.height(), y+1)).y >= center ) << 4;
            bitssum |=  ( input.at(Reflect(input.width(), x), Reflect(input.height(), y+1)).y >= center ) << 5;
            bitssum |=  ( input.at(Reflect(input.width(), x-1), Reflect(input.height(), y+1)).y >= center ) << 6;
            bitssum |=  ( input.at(Reflect(input.width(), x-1), Reflect(input.height(), y)).y >= center ) << 7;

            output[i] = bitssum;
            i += 1;
        }
    }
    return output;
}

unsigned char LBP::RotationInvariant( unsigned char pattern ) {
    // Variable auxiliar
    unsigned char test = pattern;
    // Variable que guarda el patron binario mas pequeño
    unsigned char pmin = pattern;
    // Variable acarreo
    bool carry = false;

    for (int i = 0; i < 7; ++i) {
        // Si el bit 0 esta ocupado
        carry = test & 0x01;
        test >>= 1; //test = test >> 1;

        if( carry ) test += 0x80;

        if(test < pmin) pmin = test; 
    }
    return pmin;
}

unsigned char LBP::Uniform( unsigned char pattern ) {
    // Por medio de XOR, se ubica los bits cambiantes
    unsigned char aux = pattern ^ (pattern >> 1);
    // Si el bit num 7 es uno, lo quita
    aux = aux & 0x7F;
    int transitions = 0;
    while (aux) {
        transitions++;
        if (transitions > 2) return 0x00;
        // aux-1 entrega un vector con el cual se va eliminando
        // de derecha a izquierda los bits cambiantes
        aux = aux & (aux - 1);
    }

    return pattern;

}


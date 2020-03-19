#ifndef _COLOR_H_
#define _COLOR_H_

#include <iostream>

// Estructura Color
// Las estructuras tienen atributos y métodos públicos por default.
// Fuera de eso, son idénticas a las clases, aunque se usan para tipos de datos
// más simples, como Color. Nótese que los atributos se pueden accesar
// directamente porque son públicos. Aún así, se cuenta con algunas comodidades
// como los constructores.
//
// Ejemplos de uso:
//
// Color px1(0, 128, 0);
// Color px2 = px1;
// Color px3;
// Color px4(35);
// px3 = Color(0, 0, 255);
// px1.b = 255;
// px2.r = 255;
// px4.a = 128;
//
struct Color {

    // colores enumerados
    enum class Name { CLEAR, BLACK, GRAY, SILVER, WHITE, MAROON, RED, OLIVE,
                      YELLOW, GREEN, LIME, TEAL, AQUA, CYAN, NAVY, BLUE,
                      PURPLE, FUCHSIA, MAGENTA };

    // constructor por defecto, inicializa todo en cero
    // el color resultante es completamente transparente
    Color();

    // constructor que inicializa el color con un tono de gris
    // el canal alpha es opcional, y por default es 255 (completamente opaco)
    Color( int gray, int alpha=255, bool bits16 = true);

    // constructor que inicializa el color con un color RGB
    // el canal alpha es opcional, y por default es 255 (completamente opaco)
    Color( int red, int green, int blue, int alpha=255 );

    // constructor que usa una constantes de color predefinida
    Color( Name name );

    // imprime el color en stdout
    void print();
    
    int r, g, b, a;
    int y;
/*
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
*/
};

#endif


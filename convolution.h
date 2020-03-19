#ifndef _CONVOLUTION_H_
#define _CONVOLUTION_H_

#include <iostream>
#include <vector>
#include <cmath>
#include "image.h"
#include "color.h"
#include "mask.h"

class Convolution {
    std::vector<Color> m_image;
    Mask m_kernel;
    //std::vector<Color> m_result;
    Image m_result;
    // Variables que guardan el ancho y la altura de la imagen
    int img_width;
    int img_height;
    // Longitud de uno de los lado de la mascara cuadrada
    int kernel_length;
    // bandera necesaria para recorrer la mascara cuadrada, responde a:
    // kernel_length = 2 * kernel_apothem + 1
    int kernel_apothem;

    // Envia la posicion dentro del vector que guarda los datos de la imagen
    int ImgIndex(int x, int y);
    // Envia la posicon dentro del vector que guarda los datos de la mascara
    int KernelIndex(int x, int y);

    public:
    Convolution();
    // Recibe la imagen original y la mascara el resultado de la convolicion se guarda en el vector interno "m_result"
    Convolution(Image img, Mask kernel);
    // Recibe la imagen original y la mascara el resultado de la convolicion se guarda en el vector interno "m_result"
    //Convolution(std::vector<Color> img, std::vector<double> kernel, int image_width, int image_height);
    // Se considera que img es un vector de valores Y
    //Convolution(std::vector<double> img, std::vector<double> kernel, int image_width, int image_height);

    // Tipos de convolucion
    // Convolucion sin tomar en cuenta los bordes
    Image Convolution_NoBorder();
    // Convolucion que refleja los bordes
    Image Convolution_Reflection();

    // Herramientas publicas
    bool Set(Image img, Mask kernel);
    //bool Set(std::vector<Color> img, std::vector<double> kernel, int image_width, int image_height);
    //bool Set(std::vector<double> img, std::vector<double> kernel, int image_width, int image_height);
    // Obtiene el valor del resultado de la convolucion en un determinado pixel
    //Color ResultAt(int x, int y);
    // Devuelve el vector entero el cual es el resultado de la convolucion
    //std::vector<double> GetResult();
    // Refleja los pixeles fuera del rango 
    int Reflect(int size, int index);
};

#endif
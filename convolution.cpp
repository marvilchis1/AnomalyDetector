#include "convolution.h"

Convolution::Convolution() {
    img_width = 0;
    img_height = 0;
    kernel_length = 0;
}
/*
Convolution::~Convolution() {
}
*/
Convolution::Convolution(Image img, Mask kernel) {
    Set(img, kernel);
}
/*
Convolution::Convolution(std::vector<Color> img, std::vector<double> kernel, int image_width, int image_height) {
    Set(img, kernel, image_width, image_height);
}

Convolution::Convolution(std::vector<double> img, std::vector<double> kernel, int image_width, int image_height) {
    Set(img, kernel, image_width, image_height);
}
*/
bool Convolution::Set(Image img, Mask kernel) {
    //if (img.width() <= 0 && img.height() <= 0) return false;
    //if (kernel.MaskLength() == 0) return false;

    img_width = img.width();
    img_height = img.height();
    for(int y = 0; y < img_height; ++y) {
        for (int x = 0; x < img_width; ++x) {
            m_image.push_back( img.at(x, y) );
        }
    }

    m_kernel = kernel;
    kernel_length = kernel.MaskLength();
    kernel_apothem = (kernel_length - 1)/2;
    
    m_result.set(img_width, img_height);
    m_result.setcolortype( img.getcolortype() );

    return true;
}

/*
bool Convolution::Set(std::vector<Color> img, std::vector<double> kernel, int image_width, int image_height) {
    if (img.size() == 0) return false;
    if (kernel.size() == 0) return false;

    img_width = image_width;
    img_height = image_height;
    m_image = img;

    m_kernel = kernel;
    kernel_length = sqrt(kernel.size());
    kernel_apothem = (kernel_length - 1)/2;
    //m_RGB = IsRGB();
    //m_result.resize(img_width*img_height);
    m_result.set(img_width, img_height);
    m_result.setcolortype( img.getcolortype() );

    return true;
}

bool Convolution::Set(std::vector<double> img, std::vector<double> kernel, int image_width, int image_height) {
    if (img.size() == 0) return false;
    if (kernel.size() == 0) return false;

    img_width = image_width;
    img_height = image_height;
    for(int i = 0; i < img.size(); ++i)
        m_image[i].y = img[i];
    
    m_kernel = kernel;
    kernel_length = sqrt(kernel.size());
    kernel_apothem = (kernel_length - 1)/2;
    //m_RGB = IsRGB();
    //m_result.resize(img_width*img_height);
    m_result.set(img_width, img_height);
    m_result.setcolortype( img.getcolortype() );

    return true;
}
*/

/*
Color Convolution::ResultAt(int x, int y) {
    return m_result[ImgIndex(x, y)];
}

std::vector<Color> Convolution::GetResult() {
    return m_result;
}
*/
int Convolution::ImgIndex(int x, int y) {
    return img_width*y + x;
}

int Convolution::KernelIndex(int x, int y) {
    return kernel_length*y + x;
}

int Convolution::Reflect(int size, int index) {
    int i = (index < 0) ? -index: index;

    if(i >= 2*size) i %= 2*size;
    if(i >= size) i = 2*size - i - 2;

    return i;
}

Image Convolution::Convolution_NoBorder() {
    if (m_result.getcolortype() == Image::ColorType::CT_RGB) {
        double suma_r, suma_g, suma_b;
        for (int y = 1; y < img_height-1; ++y){
            for (int x = 1; x < img_width-1; ++x){
                suma_r = 0.0;
                suma_g = 0.0;
                suma_b = 0.0;
                for (int i = -kernel_apothem; i <= kernel_apothem; ++i){
                    for (int j = -kernel_apothem; j <= kernel_apothem; ++j){
                        suma_r += m_kernel.At(j+kernel_apothem, i+kernel_apothem) * m_image[ImgIndex(x+j, y+i)].r;
                        suma_g += m_kernel.At(j+kernel_apothem, i+kernel_apothem) * m_image[ImgIndex(x+j, y+i)].g;
                        suma_b += m_kernel.At(j+kernel_apothem, i+kernel_apothem) * m_image[ImgIndex(x+j, y+i)].b;
                    }
                }
                m_result.at(x, y).r = suma_r;
                m_result.at(x, y).g = suma_g;
                m_result.at(x, y).b = suma_b;
            }
        }
    }
    else {
        double suma;
        for(int y = 1;  y < img_height-1; ++y) {
            for(int x = 1; x < img_width-1; ++x) {
                suma = 0.0;
                for (int i = -kernel_apothem; i <= kernel_apothem; ++i) {
                    for (int j = -kernel_apothem; j <= kernel_apothem; ++j) {
                        suma += m_kernel.At(j+kernel_apothem, i+kernel_apothem) * m_image[ImgIndex(x+j, y+i)].y;
                    }
                }
                m_result.at(x, y) = suma;
            }
        }
    }
    return m_result;
}

Image Convolution::Convolution_Reflection() {
    if (m_result.getcolortype() == Image::ColorType::CT_RGB) {
        double suma_r, suma_g, suma_b;
        int aux_x, aux_y;
        for(int y = 0; y < img_height; ++y) {
            for(int x = 0; x < img_width; ++x) {
                suma_r = 0.0;
                suma_g = 0.0;
                suma_b = 0.0;
                for (int i = -kernel_apothem; i <= kernel_apothem; ++i) {
                    for(int j = -kernel_apothem; j <= kernel_apothem; ++j) {
                        aux_x = Reflect(img_width, x + j);
                        aux_y = Reflect(img_height, y + i);
                        suma_r += m_kernel.At(j+kernel_apothem, i+kernel_apothem) * m_image[ImgIndex(aux_x, aux_y)].r;
                        suma_g += m_kernel.At(j+kernel_apothem, i+kernel_apothem) * m_image[ImgIndex(aux_x, aux_y)].g;
                        suma_b += m_kernel.At(j+kernel_apothem, i+kernel_apothem) * m_image[ImgIndex(aux_x, aux_y)].b;
                    }
                }
                m_result.at(x, y).r = suma_r;
                m_result.at(x, y).g = suma_g;
                m_result.at(x, y).b = suma_b;
                m_result.at(x, y).a = 255;

            }
        }
    }
    if (m_result.getcolortype() == Image::ColorType::CT_GREY){
        double suma;
        int aux_x, aux_y;

        for(int y = 0; y < img_height; ++y) {
            for(int x = 0; x < img_width; ++x) {
                suma = 0.0;

                for (int i = -kernel_apothem; i <= kernel_apothem; ++i) {
                    for(int j = -kernel_apothem; j <= kernel_apothem; ++j) {
                        aux_x = Reflect(img_width, x + j);
                        aux_y = Reflect(img_height, y + i);
                        suma += m_kernel.At(j+kernel_apothem, i+kernel_apothem) * m_image[ImgIndex(aux_x, aux_y)].y;
                    }
                }
                m_result.at(x, y).y = suma;
            }
        }
    }
    return m_result;
}


#include "fconvolution.h"

int Reflect(int size, int index ) {
    int i = (index < 0) ? -index : index;

    if (i >= 2*size) i %= 2*size;
    if (i >= size) i = 2*size - i - 2;

    return i;
}

int Index(int x, int y, int width) {
    return (width * y + x);

}

Image Convolution_NoBorder(Image input, Mask cmask) {
    Image result(input.width(), input.height());
    result.setcolortype(input.getcolortype());

    if (result.getcolortype() == Image::ColorType::CT_RGB || result.getcolortype() == Image::ColorType::CT_RGBA) {
        double suma_r, suma_g, suma_b;
        for (int y = 1; y < input.height()-1; ++y){
            for (int x = 1; x < input.width()-1; ++x){
                suma_r = 0.0;
                suma_g = 0.0;
                suma_b = 0.0;
                for (int i = -cmask.MaskApothem(); i <= cmask.MaskApothem(); ++i){
                    for (int j = -cmask.MaskApothem(); j <= cmask.MaskApothem(); ++j){
                        suma_r += cmask.At(j+cmask.MaskApothem(), i+cmask.MaskApothem()) * input.at(x+j, y+i).r;//m_image[ImgIndex(x+j, y+i)].r;
                        suma_g += cmask.At(j+cmask.MaskApothem(), i+cmask.MaskApothem()) * input.at(x+j, y+i).g;//m_image[ImgIndex(x+j, y+i)].g;
                        suma_b += cmask.At(j+cmask.MaskApothem(), i+cmask.MaskApothem()) * input.at(x+j, y+i).b;//m_image[ImgIndex(x+j, y+i)].b;
                    }
                }
                result.at(x, y).r = suma_r;
                result.at(x, y).g = suma_g;
                result.at(x, y).b = suma_b;
                result.at(x, y).a = 255;
            }
        }
    }
    if (result.getcolortype() == Image::ColorType::CT_GREY) {
        double suma;
        for(int y = 1;  y < input.height()-1; ++y) {
            for(int x = 1; x < input.width()-1; ++x) {
                suma = 0.0;
                for (int i = -cmask.MaskApothem(); i <= cmask.MaskApothem(); ++i) {
                    for (int j = -cmask.MaskApothem(); j <= cmask.MaskApothem(); ++j) {
                        suma += cmask.At(j+cmask.MaskApothem(), i+cmask.MaskApothem()) * input.at(x+j, y+i).y;
                    }
                }
                result.at(x, y).y = suma;
            }
        }
    }
    return result;
}

Image Convolution_Reflect(Image input, Mask cmask) {
    Image result(input.width(), input.height());
    result.setcolortype(input.getcolortype());

    if (result.getcolortype() == Image::ColorType::CT_RGB || result.getcolortype() == Image::ColorType::CT_RGBA ) {
        //(Image::ColorType::CT_GREY && input.raw_size() == 4*input.width()*input.height() ) || 
        //(Image::ColorType::CT_GREY_ALPHA && input.raw_size() == 4*input.width()*input.height() ) ) {
        
        double suma_r, suma_g, suma_b;
        int aux_x = 0, aux_y = 0;
        for(int y = 0; y < input.height(); ++y) {
            for(int x = 0; x < input.width(); ++x) {
                suma_r = 0.0;
                suma_g = 0.0;
                suma_b = 0.0;
                for (int i = -cmask.MaskApothem(); i <= cmask.MaskApothem(); ++i) {
                    for(int j = -cmask.MaskApothem(); j <= cmask.MaskApothem(); ++j) {
                        aux_x = Reflect(input.width(), x + j);
                        aux_y = Reflect(input.height(), y + i);
                        suma_r += cmask.At(j+cmask.MaskApothem(), i+cmask.MaskApothem()) * input.at(aux_x, aux_y).r;
                        suma_g += cmask.At(j+cmask.MaskApothem(), i+cmask.MaskApothem()) * input.at(aux_x, aux_y).g;
                        suma_b += cmask.At(j+cmask.MaskApothem(), i+cmask.MaskApothem()) * input.at(aux_x, aux_y).b;
                    }
                }
                result.at(x, y).r = suma_r;
                result.at(x, y).g = suma_g;
                result.at(x, y).b = suma_b;
                result.at(x, y).a = 255;
            }
        }
    }
    if (result.getcolortype() == Image::ColorType::CT_GREY) {
        double suma;
        int aux_x = 0, aux_y = 0;
        for(int y = 0; y < input.height(); ++y) {
            for(int x = 0; x < input.width(); ++x) {
                suma = 0.0;

                for (int i = -cmask.MaskApothem(); i <= cmask.MaskApothem(); ++i) {
                    for(int j = -cmask.MaskApothem(); j <= cmask.MaskApothem(); ++j) {
                        aux_x = Reflect(input.width(), x + j);
                        aux_y = Reflect(input.height(), y + i);
                        suma += cmask.At(j+cmask.MaskApothem(), i+cmask.MaskApothem()) * input.at(aux_x, aux_y).y;
                    }
                }
                result.at(x, y).y = suma;
            }
        }
    }
    return result;
}
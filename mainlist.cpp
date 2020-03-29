#include <iostream>
#include "lodepng.h"
#include <string>
#include <vector>
#include "image.h"
#include "fconvolution.h"
#include "mask.h"
#include "lbp.h"
#include "histogram.h"

#include "filename.h"
#include "distance.h"

using namespace std;

void print_histogram(std::vector<float> hist) {
        std::cout << hist[8] << " " 
                  << hist[7] << " "
                  << hist[6] << " "
                  << hist[5] << " "
                  << hist[4] << " "
                  << hist[3] << " "
                  << hist[2] << " "
                  << hist[1] << " "
                  << hist[0] << std::endl; 

}
/*
bool load_file( const std::string filename ) {
    std::ifstream fs;
    std::string nm;
    bool bad = false;

    fs.open(filename);

    if ( !fs.is_open() ) return false;

    if ( fs.eof() ) {
        fs.close();
        return false;
    }

    int i = 0;
    string aux;
    while ( !fs.eof() ) {
        fs >> aux;
        if ( aux == ' ' ) continue;

        i++;
    }

    fs.close();
    return true;
}

*/

int main( int argc, char** argv) {

    if ( argc != 3 ) {
        std::cout << "usage: mainlist <dir> <name_output>" << std::endl;
        return 1;
    }

    // Argumentos
    string direction = argv[1];
    string name_output = argv[2];

    Image image_input;
    if ( !image_input.load(direction) ) { std::cout << "El archivo no pudo abrirse" << std::endl; }

    image_input.ConvertToScaleGray(); 

    Image input_lbp;
    input_lbp = LBP::GetLBPImage(image_input);
            
    Histogram input_hist;
    vector<float> normalized_input;

    normalized_input = input_hist.NormalizedHistogram(input_lbp, 9);

    print_histogram(normalized_input);

    return 0;
}
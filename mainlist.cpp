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

void print_histogram(Histogram hist, string name_img ) {
        std::cout << hist.At(8) << " " 
                  << hist.At(7) << " "
                  << hist.At(6) << " "
                  << hist.At(5) << " "
                  << hist.At(4) << " "
                  << hist.At(3) << " "
                  << hist.At(2) << " "
                  << hist.At(1) << " "
                  << hist.At(0) << " "
                  << name_img << std::endl; 

}


int main() {
    string filename = "photo.png"; // saveresult = "imagelpb.png";

    // Archivos a comparar
    std::vector <string> cr_filenames;

    // Obtiene todos los nombres de los png
    GetFilename::GetAll("cr/", ".png", cr_filenames);

    // Vectores que guardan las distancias calculadas
    std::vector <DistType> intersection_distance, error_distance;

    for (std::string cr_it : cr_filenames) {
        Image image_input;
        // Se cargan ambas imagenes
        image_input.load("cr/"+cr_it);

            if ( !image_input.load("cr/"+cr_it) ) { cout << " - image_input no pudo abrirse" << endl; break; }


        image_input.ConvertToScaleGray(); 

        Image input_lbp;
        input_lbp = LBP::GetLBPImage(image_input);
            
        Histogram input_hist;
        vector<float> normalized_input;

        //normalized_input = input_hist.NormalizedHistogram(input_lbp, 9);
        input_hist.GetHistogram(input_lbp, 9);

        print_histogram(input_hist, cr_it);
    }
    
    return 0;
}
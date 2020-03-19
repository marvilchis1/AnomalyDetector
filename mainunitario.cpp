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

int main() {
    //unsigned error;
    //Image convolution, imagelbp;
    string filename = "photo.png"; // saveresult = "imagelpb.png";
    //std::vector<double> kernel = GaussianMask(2);
    //Mask kernel(Mask::MaskType::GAUSSIAN_BLUR, 9);
    //std::vector <unsigned int> hist;
    //Histogram histcomparacion;
    //std::vector <std::vector <int>> submaps;
    //std::vector <int> distances

    std::vector < std::vector<std::string>  > intersection_distance;
    std::vector < std::vector<std::string>  > error_distance;

    //Archivo de entrada
    //std::vector <string> ct_filenames(1);
    // Archivos a comparar
    //std::vector <string> cr_filenames;

    //GetFilename::GetAll("ct/", ".png", ct_filenames);

    //ct_filenames[0].append("1.1.01.png");

    std::cout << std::endl;
    //GetFilename::GetAll("cr/", ".png", cr_filenames);

    std::vector <DistType> int_dist;
    
    std::string ct_it("1.1.01.png");
    std::string cr_it("1.3.10.png");

//    for (std::string ct_it : ct_filenames) {

        int numcr = 1;
//        for (std::string cr_it : cr_filenames) {
            // image_source es una de las 5 imagenes principales
            // image_input sirve para cada una de las imagenes a comparar
            Image image_source, image_input;
            // Se cargan ambas imagenes
            image_source.load("ct/"+ct_it);
            image_input.load("cr/"+cr_it);
/*
            if ( image_source.load("ct/"+ct_it) ) { cout << " - image_source ha sido cargado" << endl; }
            else { cout << " - image_source no pudo abrirse" << endl; break; }
            if ( image_input.load("cr/"+cr_it) ) { cout << numcr << " - image_input ha sido cargado" << endl; }
            else { cout << " - image_input no pudo abrirse" << endl; break; }
*/
            
            // Amabas imagenes se convierten a GrayScale Single-Channel
            image_source.ConvertToScaleGray();
            image_input.ConvertToScaleGray();
                // Temporal
                //image_source.save("sourcegray.png");
                //image_input.save("inputgray.png");

            // Se le realiza LBP a ambas imagenes
            Image source_lbp, input_lbp;
            source_lbp = LBP::GetImageLBP(image_source);
            input_lbp = LBP::GetImageLBP(image_input);
                // Temporal
                //source_lbp.save("source_lbp.png");
                //input_lbp.save("input_lbp.png");

            // Se calcula el histograma global de ambas imagenes
            Histogram source_hist, input_hist;
            source_hist.GetHistogram(source_lbp);
            input_hist.GetHistogram(input_lbp);

            // Se calcula la ditancia entre ambos histogramas
            DistType aux;

            // Se guarda el valor de la distancia
            aux.d =  Distance::Intersection(source_hist, input_hist);
            // Se guarda el nombre del archivo origen y el de entrada
            aux.ref1 = ct_it;
            aux.ref2 = cr_it;
            int_dist.push_back(aux);
            ++numcr;
//        }
//    }

    //std::sort(int_dist.begin()->d, int_dist.end()->d);

    for(int i = 0; i < int_dist.size(); ++i) 
        std::cout << "distancia: " << int_dist[i].d << "    par: " << int_dist[i].ref1 << " & " << int_dist[i].ref2 << std::endl;

    return 0;
}
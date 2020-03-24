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

    string filename = "photo.png"; // saveresult = "imagelpb.png";

    //Archivo de entrada
    std::vector <string> ct_filenames;
    // Archivos a comparar
    std::vector <string> cr_filenames;

    // Obtiene todos los nombres de los png
    GetFilename::GetAll("ct/", ".png", ct_filenames);
    std::cout << std::endl;
    GetFilename::GetAll("cr/", ".png", cr_filenames);

    // Vectores que guardan las distancias calculadas
    std::vector <DistType> intersection_distance, error_distance;
            Histogram source_hist, input_hist;

    for (std::string ct_it : ct_filenames) {
        //int numcr = 1;
        for (std::string cr_it : cr_filenames) {
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
//                image_source.save("sourcegray.png");
//                image_input.save("inputgray.png");

            // Se le realiza LBP a ambas imagenes
            Image source_lbp, input_lbp;
            source_lbp = LBP::GetLBPImage(image_source);
            input_lbp = LBP::GetLBPImage(image_input);
                // Temporal
                source_lbp.save("source_lbp.png");
                input_lbp.save("input_lbp.png");

            // Se calcula el histograma global de ambas imagenes
            //Histogram source_hist, input_hist;
            vector<float> normalized_source, normalized_input;

            normalized_source = source_hist.NormalizedHistogram(source_lbp, 9);
            normalized_input = input_hist.NormalizedHistogram(input_lbp, 9);
            //source_hist.GetHistogram(source_lbp, 256);
            //input_hist.GetHistogram(input_lbp, 256);


            // Se calcula la ditancia entre ambos histogramas
            DistType aux;

            // Se guarda el valor de la distancia
            //aux.d = Distance::Intersection(source_hist, input_hist);
            aux.d =  Distance::Intersection(normalized_source, normalized_input);
            // Se guarda el nombre del archivo origen y el de entrada
            aux.ref1 = ct_it;
            aux.ref2 = cr_it;
            intersection_distance.push_back(aux);

            //aux.d = Distance::Error(source_hist, input_hist);
            aux.d = Distance::Error(normalized_source, normalized_input);

            error_distance.push_back(aux);
            //++numcr;
        }
    }


    std::sort(intersection_distance.begin(), intersection_distance.end(), Distance::IsGreater);

    for(int i = 0; i < intersection_distance.size(); ++i) 
        std::cout << "distancia: " << intersection_distance[i].d << "    par: " << intersection_distance[i].ref1 << " & " << intersection_distance[i].ref2 << std::endl;

    std::cout << "\n\n\n" << std::endl;

    std::sort(error_distance.begin(), error_distance.end(), Distance::IsLess);
    
    for(int i = 0; i < error_distance.size(); ++i)
        std::cout << "distancia: " << error_distance[i].d << "  par: " << error_distance[i].ref1 << " & " << " & " << error_distance[i].ref2 << std::endl;

//    for (int i = 0; i < 9; ++i) 
//        std::cout << source_hist.At(i) << std::endl;
    
//    for (int i = 0; i < 256; ++i)
//        std::cout << source_hist.At(i) << std::endl;


/*
    unsigned char eje = 0xA0;
    eje = LBP::RotationInvariant(eje);
    std::cout << "Experimento" << std::endl;
    std::cout << int(eje) << std::endl;
    unsigned char pat = 0x0F;
    unsigned char aux = LBP::Uniform(pat);

    std::cout << "Experimento" << std::endl;
    std::cout << int(aux) << std::endl;
*/
    return 0;
}
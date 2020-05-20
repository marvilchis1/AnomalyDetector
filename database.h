#ifndef _DATABASE_H_
#define _DATABASE_H_

#include <vector>
//#include <map>
#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <sstream>
//#include <Eigen/Dense>
#include <tuple>
#include "distance.h"

using namespace std;

namespace Database {
    typedef tuple<vector<double>, double> my_tuple;
    typedef vector < my_tuple > vector_tuple; 
    typedef tuple<vector<double>, vector<double>> tuple_vector_double;

    
    // ****************** Transformacion de datos ******************
    // Procesa cada linea string y los almacena en una matrix de tipo double
    // en donde contiene los valores caracteristicos y la etiqueta
    vector<vector<double>> DataMatrix(vector<string> str_matrix);
    // Procesa cada linea string y los almacena en un vector de tuplas
    // donde cada tupla esta formada por: (vector_caracteristicas, etiqueta)
    vector_tuple TaggedVectors(vector<string> str_matrix);

    
    // ******************* Operaciones con los datos *****************
    // Saca el vector promedio de clase recibiendo los vectores sin procesar y la etiqueta
    my_tuple AverageVector(vector<string> str_matrix, double label);
    // "" ""  "" """ recibiendo una matriz con los vectores ya transformados
    my_tuple AverageVector(vector< vector<double> > d_matrix, double label);

    void Show_Distances(vector<vector<double>> average_vectors, vector<vector<double>> test_vectors);

    // ***************** Visualizacion de datos **********************
    void ShowAll(vector<vector<double>> d_matrix);
    void ShowAll(vector_tuple classcontainer);



}

#endif
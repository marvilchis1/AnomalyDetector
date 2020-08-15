#ifndef _DATABASE_H_
#define _DATABASE_H_

#include <vector>
//#include <map>
#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <sstream>
#include "Eigen/Dense"
#include <tuple>
#include "distance.h"
#include <random>

using namespace std;

namespace Database {
    typedef tuple<vector<double>, double> my_tuple;
    typedef vector < my_tuple > vector_tuple; 
    typedef tuple<vector<double>, vector<double>> tuple_vector_double;
    typedef tuple <Eigen::MatrixXd, Eigen::MatrixXd> eigen_tuple;

    
    // ****************** Transformacion de datos ******************
    // Procesa cada linea string y los almacena en una matrix de tipo double
    // en donde contiene los valores caracteristicos y la etiqueta
    vector<vector<double>> DataMatrix(vector<string> str_matrix);
    // Procesa cada linea string y los almacena en un vector de tuplas
    // donde cada tupla esta formada por: (vector_caracteristicas, etiqueta)
    vector_tuple TaggedVectors(vector<string> str_matrix);
    // Procesa cada linea string y los almacena en una matrix Eigen
    // en donde contiene los valores caracteristicos
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> DataEigenMatrix(vector<string> str_matrix);

    
    // ******************* Operaciones con los datos *****************
    // Generador de numeros aleatorios
    int GetRandom(const int min, const int max);
    // Eliminador de renglon
    Eigen::MatrixXd RemoveRow(Eigen::MatrixXd matrix, int row_to_remove);
    // Obtener clases
    vector<double> ClassLabels(Eigen::MatrixXd matrix);
    // Contar cuantos datos pertenencen a cierta matriz
    int ClassCount(Eigen::MatrixXd matrix, double class_label);

    // Funcion para obtener los vectores de entrenamiento y testeo
    eigen_tuple TrainTestVectors( Eigen::MatrixXd data_matrix);

    // Modificar la clase de algunos renglones
    Eigen::MatrixXd ModifyClass(Eigen::MatrixXd matrix);

    // Saca el vector promedio de clase recibiendo los vectores sin procesar y la etiqueta
    my_tuple AverageVector(vector<string> str_matrix, double label);
    // "" ""  "" """ recibiendo una matriz con los vectores ya transformados
    my_tuple AverageVector(vector< vector<double> > d_matrix, double label);
    // """"
    Eigen::MatrixXd AverageMatrix(Eigen::MatrixXd matrix);

    // Calculo de la distancia euclidiana entre un vector de testeo y el conjunto de vectores promedio
    vector<double> CalculateDistance(Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> average_matrix, Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> test_matrix);
    // Asignacion de clase estimada a un vector de testeo
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> ClassAssignment (Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> average_matrix, Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> test_matrix);
    
    // Conteo de aciertos y desaciertos
    void HitsMisses(Eigen::MatrixXd estimated_classes, Eigen::MatrixXd real_classes);
    
    // Clasificacion
    void Classify(Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> average_matrix, Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> test_matrix);
    
    // Comparador de aciertos-fallos
    bool LabelComparator(Eigen::Matrix<double, 1, Eigen::Dynamic> vector, double label_input);
    //int ClassifyVector(Eigen)

    // ***************** Visualizacion de datos **********************
    void ShowAll(vector<vector<double>> d_matrix);
    void ShowAll(vector_tuple classcontainer);



}

#endif
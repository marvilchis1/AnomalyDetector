#ifndef _FILEMANAGER_H_
#define _FILEMANAGER_H_

#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <tuple>
#include <sstream>

#include "Eigen/Dense"

#include "database.h"


using namespace std;

namespace FileManager{
    // Comprobar que el archivo sea valido
    bool CheckFile(string direction);
    // Lee y guarda cada linea del archivo
    vector<string> ReadFile(string direction);
    // Lee y guarda cada linea del archivo, ademas de enviar el num de renglones y columnas
    tuple<vector<string>,int,int> ProcessData(string direction);
    // Convierte un archivo ya previamente leido en una matrix de tipo eigen
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> ToEigenMatrix(vector<string> direction, int nrows, int ncols);
    // Convertir un objeto string a una matriz de tipo double
    //vector<vector<double>> ToDoubleMatrix (string direction);

    // No necesario
    vector<string> Split(const std::string line, char lim);

    // Impresiones
    void PrintVector(vector<double> d_vector);
    void PrintMatrix(vector<vector<double>> d_matrix);
    //void PrintEigenMatrix

}

#endif
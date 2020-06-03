#include <iostream>
#include <fstream>
#include "database.h"
#include "Eigen/Dense"
#include "distance.h"
#include "filemanager.h"

using namespace std;
typedef vector < tuple<vector<float>, string> > vector_tuple; 
typedef tuple<vector<float>, string > my_tuple;

int main( int argc, char** argv ) {

    if ( argc != 4 ) {
        std::cout << "usage:classifier <dir1> <dir2> <dir3>" << std::endl;
        std::cout << "<dir1> Text file with average class vectors." << std::endl;
        std::cout << "<dir2> Text file cointaining the database with feature vectors." << std::endl;
        std::cout << "<dir3> Text file with vectors to test." << std::endl;
        return 1;
    }
    std::string direction1 = argv[1];
    std::string direction2 = argv[2];        
    std::string direction3 = argv[3];
    if ( !( FileManager::CheckFile(direction1) ) ) { return 0; }
    if ( !( FileManager::CheckFile(direction2) ) ) { return 0; }
    if ( !( FileManager::CheckFile(direction3) ) ) { return 0; }
    vector<string> str_matrix1; //= FileManager::ReadFile(direction1);
    vector<string> str_matrix2; //= FileManager::ReadFile(direction2);
    vector<string> str_matrix3; //= FileManager::ReadFile(direction2);

    Eigen::IOFormat CleanFmt(4, 0, ", ", "\n", "[", "]");

    // Obtengo numero de renglones y columnas
    int rows = 0, cols = 0;
    //std::tie(str_matrix1, rows, cols) = FileManager::ProcessData(direction1);
    //std::cout << "Renglones = " << rows << " Columnas = " << cols << std::endl;





    // ************** Se obtienen las matrices de caracteristicas *****************
    // Matriz con vectores de clase promedio
    cout << endl;
    std::tie(str_matrix1, rows, cols) = FileManager::ProcessData(direction1);
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> prom_vects = FileManager::ToEigenMatrix(str_matrix1, rows, cols);
    std::cout << prom_vects << std::endl;
    
    // Matriz con la base de datoss (vectores de carateristicas + etiqueta)
    cout << endl;
    std::tie(str_matrix2, rows, cols) = FileManager::ProcessData(direction2);
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> bd_vects = FileManager::ToEigenMatrix(str_matrix2, rows, cols);
    std::cout << bd_vects << std::endl;
    
    std::cout << "Test Matrix " << std::endl;

    // Vectores para el testeo
    std::tie(str_matrix3, rows, cols) = FileManager::ProcessData(direction3);
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> test_vects = FileManager::ToEigenMatrix(str_matrix3, rows, cols);
    std::cout << test_vects << std::endl;

    
    Database::Classify(prom_vects, test_vects);






    //vector<vector<double>> prom_vects = FileManager::ToDoubleMatrix(direction1);
    //vector<vector<double>> base_datos = FileManager::ToDoubleMatrix(direction2);
    //vector<vector<double>> test_vects = FileManager::ToDoubleMatrix(direction3);



    //std::cout << "\nVectores de clase promedio: " << std::endl;
    //Database::ShowAll(ACV_DB);
    //std::cout << "\nVectores de caracteristicas: " << std::endl;
    //Database::ShowAll(FV_DB);
    //std::cout << "\nVectores de Test: " << std::endl;
    //Database::ShowAll(VT_DB);



    return 0;
}
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

    if ( argc != 2 ) {
        std::cout << "usage:classifier <dir>" << std::endl;
        //std::cout << "<dir1> Text file with average class vectors." << std::endl;
        std::cout << "<dir> Text file cointaining the database with feature vectors." << std::endl;
        //std::cout << "<dir3> Text file with vectors to test." << std::endl;
        return 1;
    }

    std::string direction = argv[1];        
    if ( !( FileManager::CheckFile(direction) ) ) { return 0; }
    vector<string> str_matrix;
    //Eigen::IOFormat CleanFmt(4, 0, ", ", "\n", "[", "]");

    // Obtengo numero de renglones y columnas
    int rows = 0, cols = 0;

    // Matriz con la base de datos (vectores de carateristicas + etiqueta)
    cout << endl;
    std::tie(str_matrix, rows, cols) = FileManager::ProcessData(direction);
    Eigen::MatrixXd bd_matrix = FileManager::ToEigenMatrix(str_matrix, rows, cols);
    
    // Se fragmenta una clase para obligar a que se equivoque
    //Eigen::MatrixXd mod_matrix = Database::ModifyClass(bd_matrix);
    //Eigen::MatrixXd mod_matrix2 = Database::ModifyClass(mod_matrix);

    // Se obtiene la matrix de entrenamiento y la de testeo
    Eigen::MatrixXd train_matrix, test_matrix;
    std::tie(train_matrix, test_matrix) = Database::TrainTestVectors(bd_matrix);
    
    Eigen::MatrixXd average_matrix = Database::AverageMatrix(train_matrix);


    cout << "Average Matrix" << endl;
    cout << average_matrix << endl;
    //std::cout << std::endl;

    //cout << "Test Matrix" << endl;
    //cout << test_matrix << endl;
    
    Database::Classify(average_matrix, test_matrix);
    //Database::Classify(average_matrix, test_matrix);

    return 0;
}
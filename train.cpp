#include <iostream>
#include <fstream>
#include "database.h"
//#include <Eigen/Dense>

using namespace std;
typedef tuple<vector<double>, double> my_tuple;
typedef vector < my_tuple > vector_tuple; 


void print_vector(my_tuple tp) {

    std::vector<double> auxvalues;
    double auxlabel;

    std::tie(auxvalues, auxlabel) = tp;

    for(int j = 0; j < auxvalues.size(); ++j)
        std::cout << auxvalues[j] << " ";

    std::cout << auxlabel << std::endl;

}


int main( int argc, char** argv) {

    if ( argc != 2 ) {
        std::cout << "usage: train <dir>" << std::endl;
        std::cout << "<dir> Text file location." << std::endl;
        return 1;
    }

    // Argumentos
    std::string direction = argv[1];

    ifstream input(direction);

    if ( !input.is_open()) {
        std::cout << "El archivo: " << direction << "no pudo abrirse" << std::endl;
        return 0;
    }

    if ( input.eof() ) {
        input.close();
        return 0;
    }

    std::string aux_line;
    std::vector <std::string> container;

    while( getline(input, aux_line) ) 
        container.push_back(aux_line);
    
    vector<vector<double>> DBD = Database::DataMatrix(container);
    vector_tuple DBT = Database::TaggedVectors(container);


    my_tuple v_tuples1, v_tuples2;

    std::cout << "\nVectores Promedio: " << std::endl;
    v_tuples1 = Database::AverageVector(container, 1);
    print_vector(v_tuples1);
    v_tuples2 = Database::AverageVector(DBD, 1);
    print_vector(v_tuples2);


    std::cout << "\nVectores Promedio: " << std::endl;
    v_tuples1 = Database::AverageVector(container, 2);
    print_vector(v_tuples1);
    v_tuples2 = Database::AverageVector(DBD, 2);
    print_vector(v_tuples2);




    return 0;
}
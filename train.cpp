#include <iostream>
#include <fstream>
#include "database.h"
//#include <Eigen/Dense>

using namespace std;

void print_vector(std::vector<std::string> vect) {
    for (int i = 0; i < vect.size(); ++i)
        std::cout << vect[i] << " "; 
    std::cout << std::endl;
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
    
    Database DB(container);

    DB.ShowAll();

    std::vector<std::string> vc;

    std::cout << "\nVectores Promedio: " << std::endl;
    vc = DB.AverageVector("1");
    print_vector(vc);
    vc = DB.AverageVector("2");
    print_vector(vc);



    cout << "\n\nDatos y etiqueta\n" << endl;

    Data dt;

    dt = DB.Classify(container);
    for (int i = 0; i < dt.Label.size(); ++i) {
        for (int j = 0; j < dt.Data[i].size(); ++j) {
            std::cout << dt.Data[i][j] << " "; 
        }
        std::cout << dt.Label[i] << std::endl;
    }

    return 0;
}
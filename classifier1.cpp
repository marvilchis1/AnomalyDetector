#include <iostream>
#include <fstream>
#include "database.h"
//#include <Eigen/Dense>

//for
// Funcion(vector_prueba, vectorclase_promedio) {

//return double;
//}


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

    ifstream input1(direction1);
    ifstream input2(direction2);
    ifstream input3(direction3);


    //**************** Abertura y comprobacion de los archivos de texto ********************
    if ( !input1.is_open()) {
        std::cout << "El archivo: " << direction1 << "no pudo abrirse" << std::endl;
        return 0;
    }

    if ( input1.eof() ) {
        input1.close();
        return 0;
    }


    if ( !input2.is_open()) {
        std::cout << "El archivo: " << direction2 << "no pudo abrirse" << std::endl;
        return 0;
    }

    if ( input2.eof() ) {
        input2.close();
        return 0;
    }


    if ( !input3.is_open()) {
        std::cout << "El archivo: " << direction3 << "no pudo abrirse" << std::endl;
        return 0;
    }

    if ( input3.eof() ) {
        input3.close();
        return 0;
    }





    return 0;
}
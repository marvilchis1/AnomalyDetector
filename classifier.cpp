#include <iostream>
#include <fstream>
#include "database.h"
//#include <Eigen/Dense>
#include "distance.h"

//for
// Funcion(vector_prueba, vectorclase_promedio) {

//return double;
//}

using namespace std;
typedef vector < tuple<vector<float>, string> > vector_tuple; 
typedef tuple<vector<float>, string > my_tuple;


void print_vector(vector<double> d_matrix) {
    std::cout  << std::endl;
    for (int i = 0; i < d_matrix.size(); ++i) 
        std::cout << d_matrix[i] << " ";
    std::cout << std::endl;
        
    
}

bool ReadFile(string direction) {
    ifstream input(direction);
    if ( !input.is_open()) {
        std::cout << "El archivo: " << direction << "no pudo abrirse" << std::endl;
        return false;
    }

    if ( input.eof() ) {
        input.close();
        return false;
    }
    return true;
}

// Obtencion de la matriz con los vectores de caracteristicas y su etiquetas
vector<vector<double>> GetDataMatrix (string direction) {
    ifstream input(direction);

    // Average Class Vectors
    string aux_line;
    vector <string> container;
    while( getline(input, aux_line) ) 
        container.push_back(aux_line);

    return Database::DataMatrix(container);
}

// Se calcula la distancia ecludiana de cada vector de testeo por cada vector promedio de clase.
// Se imprime en pantalla tanto el vector de testeo analizado así como la distancia respecto a cada clase.
void ShowDistances(vector<vector<double>> average_vectors, vector<vector<double>> test_vectors) {
    // El vector almacena en la posicion 0 la distancia al vector promedio analizado, y en el 1 la etiqueta del mismo
    vector<double> distance_label;
    distance_label.resize(2);
    // Vector auxiliar que obtendra las distancias del vector test respecto a cada vector promedio
    vector<vector<double>> my_distances;
    // Se itera cada vector test presente en el contenedor
    for (int i = 0; i < test_vectors.size(); ++i) {
        my_distances.clear();
        for (int j = 0; j < average_vectors.size(); ++j) {
            //test_vectors[i] = vector<double>(test_vectors[i].begin(), test_vectors[i].end()-1 )
            //average_vectors[j] = vector<double>(average_vectors[j].begin(), average_vectors[j].end()-1 )
            distance_label[0] =  Distance::EuclideanDistance( vector<double>(test_vectors[i].begin(), test_vectors[i].end()-1), vector<double>(average_vectors[j].begin(), average_vectors[j].end()-1) ) ;            
            distance_label[1] = average_vectors[j].back();
            my_distances.push_back(distance_label);
        }
        print_vector(test_vectors[i]);
        Database::ShowAll(my_distances);
    }
}



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

    if ( !ReadFile(direction1) ) { return 0; }
    if ( !ReadFile(direction2) ) { return 0; }
    if ( !ReadFile(direction3) ) { return 0; }


    // Matriz con vectores de clase promedio
    vector<vector<double>> prom_vects = GetDataMatrix(direction1);
    // Matriz con la base de datoss (vectores de carateristicas + etiqueta)
    vector<vector<double>> base_datos = GetDataMatrix(direction2);
    // Vectores para el testeo
    vector<vector<double>> test_vects = GetDataMatrix(direction3);


    ShowDistances(prom_vects, test_vects);




    //std::cout << "\nVectores de clase promedio: " << std::endl;
    //Database::ShowAll(ACV_DB);
    //std::cout << "\nVectores de caracteristicas: " << std::endl;
    //Database::ShowAll(FV_DB);
    //std::cout << "\nVectores de Test: " << std::endl;
    //Database::ShowAll(VT_DB);



    return 0;
}
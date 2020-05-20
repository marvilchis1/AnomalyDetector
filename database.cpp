#include "database.h"

typedef tuple<vector<double>, double> my_tuple;
typedef vector < my_tuple > vector_tuple; 
typedef tuple<vector<double>, vector<double>> tuple_vector_double;

// Regresa un matrix tipo double, de tamaño n columas de caracteristicas + etiqueta
// por medio de un vector de lineas string sin procesar
vector< vector<double> > Database::DataMatrix(vector<string>  str_matrix ){
    vector < vector<double> > dmatrix;

    for (int i = 0; i != str_matrix.size(); ++i){
        vector<double> aux_vector;
        std::istringstream str_values(str_matrix[i]);
        double d = 0.0;

        while ( str_values >> d )
            aux_vector.push_back(d);
        
        dmatrix.push_back(aux_vector);
    }

    return dmatrix;
}

// Se obtiene un vector de tuplas donde cada tupla tiene contenido en tipo double 
// el vector de caracteristicas + la etiqueta, port medio de un vector de lineas string
vector_tuple Database::TaggedVectors(vector<string> str_matrix) {
    vector_tuple classcontainer;

    for (int i = 0; i != str_matrix.size(); ++i){
        vector<double> aux_vector;
        std::istringstream str_values(str_matrix[i]);
        double d = 0.0;

        while ( str_values >> d )
            aux_vector.push_back(d);
        
        classcontainer.push_back( std::make_tuple( vector<double>(aux_vector.begin(), aux_vector.end()-1 ), aux_vector.back() ) );
    }

    return classcontainer;
}

my_tuple Database::AverageVector(vector<string> str_matrix, double label) {
    // Se saca el vector de tuplas
    vector_tuple classcontainer = TaggedVectors(str_matrix);

    // Se obtiene el vector de caracteristicas y la etiqueta por medio de variables auxiliares
    vector<double> auxvalues;
    double auxlabel;
    vector<double> sumvector(std::get<0>(classcontainer[0]).size());

    int cont = 0;
    for (int i = 0; i < classcontainer.size(); ++i) {
        // tie desempaqueta los dos valores contenidos de la tupla en las variables auxiliares
        std::tie(auxvalues, auxlabel) = classcontainer[i];
        // Se realiza la sumatoria solo si la etiqueta a evaluar es igual a la que se desea sacar el promedio
        if (auxlabel == label) {
            for (int j = 0; j < auxvalues.size(); ++j)
                sumvector[j] += auxvalues[j];
            cont++;
        }
    }

    // Se divide entre el total de vectores correspondientes a la etiqueta
    for (int i = 0; i < sumvector.size(); ++i)
        sumvector[i] /= cont;
    
    return std::make_tuple(sumvector, label);
}

my_tuple Database::AverageVector(vector< vector<double> > d_matrix, double label) {
    // la longitud de la matriz son n columnas de caracteristicas + etiqueta
    // Vector auxiliar para realizar la sumatoria de cada columna
    vector<double> sumvector( d_matrix[0].size() - 1);

    int cont = 0;
    for (int i = 0; i < d_matrix.size(); ++i) {
        // Debido a que la etiqueta esta en la ultima posicion de la matriz, se
        // compara el valor ahi ubicado, y se procede a realizar la sumatoria
        if (d_matrix[i].back() == label) {
            for (int j = 0; j < d_matrix[i].size() - 1; ++j)
                sumvector[j] += d_matrix[i][j];
            cont++;
        }
    }

    // Se divide entre el total de vectores correspondientes a la etiqueta
    for (int i = 0; i < sumvector.size(); ++i)
        sumvector[i] /= cont;
    
    return std::make_tuple(sumvector, label);
}

/*
void Distance::ShowDistances(vector<vector<double>> average_vectors, vector<vector<double>> test_vectors) {
    double idclass = 0;

    // El vector almacena en el posicion 0 la distancia al vector promedio analizado, 
    // y en el 1 la etiqueta del mismo
    vector<double> distance_label(2);
    // Vector auxiliar que obtendra las distancias del vector test respecto a cada vector promedio
    vector<vector<double>> my_distances;

    // Tupla (vector_test, distancia, preddicion_etiqueta)


    // Se itera cada vector test presente en el contenedor
    for (int i = 0; i < test_vectors.size(); ++i) {
        distance_label.clear();
        my_distances.clear();
        
        for (int j = 0; j < average_vectors.size(); ++j) {
            //test_vectors[i] = vector<double>(test_vectors[i].begin(), test_vectors[i].end()-1 )
            //average_vectors[j] = vector<double>(average_vectors[j].begin(), average_vectors[j].end()-1 )

            distance_label[0] =  Distance::EuclideanDistance( vector<double>(test_vectors[i].begin(), test_vectors[i].end()-1), vector<double>(average_vectors[j].begin(), average_vectors[j].end()-1) ) ;            
            distance_label[1] = average_vectors[j].back();
            my_distances.push_back(distance_label);
        }
    }

    

    //return std::make_tuple( );
}
*/



void Database::ShowAll(vector<vector<double>> d_matrix) {
    for(int i = 0; i < d_matrix.size(); ++i) {
        for (int j = 0; j < d_matrix[i].size(); ++j) 
            std::cout << d_matrix[i][j] << " ";
        std::cout << std::endl;
        
    }
}

void Database::ShowAll(vector_tuple classcontainer) {
    std::vector<double> auxvalues;
    std::string auxlabel;

    for(int i = 0; i < classcontainer.size(); ++i ){

        std::tie(auxvalues, auxlabel) = classcontainer[i];

        for(int j = 0; j < auxvalues.size(); ++j)
            std::cout << auxvalues[j] << " ";
        
        std::cout << auxlabel << std::endl;
        
    }
}

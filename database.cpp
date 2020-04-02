#include "database.h"

Database::Database() {

}

Database::Database( std::vector< std::string > data ) {
    Classify(data);
}

std::vector<std::string> Database::Split(const std::string line, char lim){
    std::stringstream str(line);
    std::string token;
    std::vector<std::string> aux_vect;

    while( std::getline(str, token, lim))
        aux_vect.push_back(token);

    return aux_vect;
}

bool Database::Classify( std::vector<std::string> data ) {
    for(int i = 0; i < data.size(); ++i) {
        std::vector<std::string> line = Split(data[i]);
        classcontainer.push_back(line);
    }

    return true;
/*
    for (int i = 0; i < data.size(); ++i){
        // Se obtiene cada elemento del vector analizado
        std::vector<std::string> line = Split( data[i] );
        
        // Se crea un vector auxiliar que guardara los valores float
        std::vector<float> aux( line.size() - 1);
        for ( int j = 0; j < aux.size(); ++j)
            aux[j] = stof(line[i]);

        // Se asigna a la clave correspondiente el vector con los valores numericos
        databasecontainer[ line.back() ] = aux;
    }
*/
}

std::vector<std::string> Database::AverageVector(std::string label) {

    std::vector<float> aux_values( classcontainer[1].size() - 1);
    int cont = 0;
    for (int i = 0; i < classcontainer.size(); ++i) {
        if (classcontainer[i].back() == label) {
            for (int j = 0; j < aux_values.size(); ++j)
                aux_values[j] += stof( classcontainer[i][j] );
            cont++;
        }
    }

    // Se divide entre el total de vectores correspondientes a la etiqueta
    std::vector<std::string> result;
    for (int i = 0; i < aux_values.size(); ++i) {
        aux_values[i] /= cont;
        result.push_back( std::to_string(aux_values[i]) );
    }
        result.push_back(label);
    
    return result;
}

void Database::ShowAll() {
    for(int i = 0; i < classcontainer.size(); ++i ){
        for(int j = 0; j < classcontainer[i].size(); ++j)
            std::cout << classcontainer[i][j] << " ";
        std::cout << std::endl;
    }
}

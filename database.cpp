#include "database.h"

typedef vector < tuple<vector<float>, string> > vector_tuple; 
typedef tuple<vector<float>, string > my_tuple;

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

std::vector<float>  Database::Transform(std::vector<std::string> stringVector) {
    std::vector<float> floatVector(stringVector.size());
    std::transform(stringVector.begin(), stringVector.end(), floatVector.begin(), [](const std::string& val)
    {
        return std::stof(val);
    });
    return floatVector;
}

/*
bool Database::GetLines( std::vector<std::string> data ) {
    for(int i = 0; i < data.size(); ++i) {
        std::vector<std::string> line = Split(data[i]);
        //classcontainer.push_back(line);
    }

    return true;
}
*/

vector_tuple Database::Classify( std::vector<std::string> stringvector ) {
    for(int i = 0; i < stringvector.size(); ++i) {
        std::vector<std::string> line = Split(stringvector[i]);

        std::vector<float> featvect = Transform( std::vector<std::string>( line.begin(), line.end() - 1) );
        
        classcontainer.push_back( std::make_tuple(featvect, line.back()) );
    }

    return classcontainer;
}

my_tuple Database::AverageVector(std::string label) {
    std::vector<float> auxvalues;
    std::string auxlabel;

    std::vector<float> sumvector(std::get<0>(classcontainer[1]).size());

    int cont = 0;
    for (int i = 0; i < classcontainer.size(); ++i) {
        
        std::tie(auxvalues, auxlabel) = classcontainer[i];

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

void Database::ShowAll() {
    std::vector<float> auxvalues;
    std::string auxlabel;

    for(int i = 0; i < classcontainer.size(); ++i ){

        std::tie(auxvalues, auxlabel) = classcontainer[i];

        for(int j = 0; j < auxvalues.size(); ++j)
            std::cout << auxvalues[j] << " ";
        
        std::cout << auxlabel << std::endl;
        
    }
}

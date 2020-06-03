#include "filemanager.h"

bool FileManager::CheckFile(string direction) {
    ifstream input(direction);
    if ( !input.is_open()) {
        std::cout << "El archivo: " << direction << " no pudo abrirse" << std::endl;
        return false;
    }

    if ( input.eof() ) {
        input.close();
        return false;
    }
    return true;
}

vector<string> FileManager::ReadFile(string direction){
    ifstream input(direction);
    // Average Class Vectors
    string aux_line;
    vector <string> container;
    //int num_rows = 0;
    while( getline(input, aux_line) )
        container.push_back(aux_line);

    return container;
}

vector<string> FileManager::Split(const std::string line, char lim){
    std::stringstream str(line);
    std::string token;
    std::vector<std::string> aux_vect;

    while( std::getline(str, token, lim))
        aux_vect.push_back(token);

    return aux_vect;
}


tuple<vector<string>,int,int> FileManager::ProcessData(string direction) {
    ifstream input(direction);
    // Average Class Vectors
    string aux_line;
    vector <string> container;
    //int num_rows = 0;
    while( getline(input, aux_line) )
        container.push_back(aux_line);

    std::stringstream str(container[0]);
    std::string token;
    std::vector<std::string> aux_vect;

    int num_rows = container.size();
    int num_columns = 0;

    while( std::getline(str, token, ' ')) num_columns++;



    return std::make_tuple(container, num_rows, num_columns);
}

/*
vector<vector<double>> FileManager::ToDoubleMatrix(string direction) {
    ifstream input(direction);
    // Average Class Vectors
    string aux_line;
    vector <string> container;
    //int num_rows = 0;
    while( getline(input, aux_line) )
        container.push_back(aux_line);


    return Database::DataMatrix(container);
}
*/

Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> FileManager::ToEigenMatrix(vector<string> str_matrix, int nrows, int ncols) {    
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> M;

    M.resize(nrows, ncols);

    for (int i = 0; i != str_matrix.size(); ++i){
        vector<double> aux_vector;
        std::istringstream str_values(str_matrix[i]);
        double d = 0.0;
        //std::cout << "Hola" << std::endl;
        //M.resize(i+1, 0);
        int j = 0;
        while ( str_values >> d ) {
            //std::cout << "Hola2" << std::endl;
            //cout << d << endl;
            //M.resize(i+1, j+1);
            M(i,j) = d;
            ++j;
        }
    }

    return M;

}

void FileManager::PrintVector(vector<double> d_vector) {
    std::cout  << std::endl;
    for (int i = 0; i < d_vector.size(); ++i) 
        std::cout << d_vector[i] << " ";
    std::cout << std::endl;
        
    
}

void FileManager::PrintMatrix(vector<vector<double>> d_matrix) {
    for(int i = 0; i < d_matrix.size(); ++i) {
        for (int j = 0; j < d_matrix[i].size(); ++j) 
            std::cout << d_matrix[i][j] << " ";
        std::cout << std::endl;
        
    }
}
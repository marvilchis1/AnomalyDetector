#include "database.h"

typedef tuple<vector<double>, double> my_tuple;
typedef vector < my_tuple > vector_tuple; 
typedef tuple<vector<double>, vector<double>> tuple_vector_double;
typedef tuple<Eigen::MatrixXd, Eigen::MatrixXd> eigen_tuple;

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



Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> Database::DataEigenMatrix(vector<string>  str_matrix ){
    //vector < vector<double> > dmatrix;
    //int rows = str_matrix.size();
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> M;
    
    for (int i = 0; i != str_matrix.size(); ++i){
        vector<double> aux_vector;
        std::istringstream str_values(str_matrix[i]);
        double d = 0.0;

        int j = 0;
        while ( str_values >> d ) {
            //aux_vector.push_back(d);
            M(i,j) = d;
            ++j;
        }

        //dmatrix.push_back(aux_vector);
    }

    return M;
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

// Cambiar a functor
int Database::GetRandom(const int min, const int max) {
    static std::random_device randDev;
    static std::mt19937 twister(randDev());
    static std::uniform_int_distribution<int> distribution;

    distribution.param(std::uniform_int_distribution<int>::param_type(min, max));
    return distribution(twister);
}

Eigen::MatrixXd Database::RemoveRow(Eigen::MatrixXd matrix, int row_to_remove) {
    int num_rows = matrix.rows() - 1;
    int num_cols = matrix.cols();

    if ( row_to_remove < num_rows )
        // Block of size (p, q), starting at (i, j) ... matrix.block(i, j, p, q)
        matrix.block(row_to_remove, 0, num_rows - row_to_remove, num_cols) = matrix.bottomRows(num_rows - row_to_remove);
    
    matrix.conservativeResize(num_rows, num_cols);

    return matrix;
}

int Database::ClassCount(Eigen::MatrixXd matrix, double class_label) {
    int count = 0;

    for (int i = 0; i < matrix.rows(); ++i) {
        if ( matrix(i, matrix.cols() - 1) == class_label)
            ++count;
    }

    return count;
}

vector<double> Database::ClassLabels(Eigen::MatrixXd matrix){
    vector<double> label_values;

    for (int i = 0; i < matrix.rows(); ++i)
        label_values.push_back( matrix(i, Eigen::last) );

    std::sort(label_values.begin(), label_values.end());

    vector<double>::iterator it;

    it = std::unique(label_values.begin(), label_values.end());

    label_values.resize( std::distance(label_values.begin(), it) );

    return label_values;
}

eigen_tuple Database::TrainTestVectors( Eigen::MatrixXd data_matrix ) {
    int num_test = 0.30 * data_matrix.rows() + 0.5;
    int num_max_data = data_matrix.rows() - 1;

    Eigen::MatrixXd train_matrix = data_matrix;
    Eigen::MatrixXd test_matrix(num_test, data_matrix.cols());

    for (int i = 0; i < num_test; ++i) {
        int num_rand = Database::GetRandom(0, num_max_data);
        test_matrix.row(i) = data_matrix.row(num_rand);
        train_matrix = RemoveRow(train_matrix, num_rand);
    }

    return std::make_tuple(train_matrix, test_matrix);
}


Eigen::MatrixXd Database::ModifyClass(Eigen::MatrixXd matrix) {
    // Se obtiene las clases existentes en la base de datos
    vector<double> labels = Database::ClassLabels(matrix);
    // Se obtiene una clase random, la cual se va a fragmentar
    double rand_class = Database::GetRandom(1, labels.back());
    cout << "Clase random = " << rand_class << endl;
    // Se obtiene el numero total de elementos pertenecientes a esa clase
    int num_ctotal = Database::ClassCount(matrix, rand_class);
    num_ctotal = num_ctotal/2;
    // Se asigna el numero de la "nueva clase"
    double new_class = 8;
    
    for (int i = 0; i < num_ctotal; ++i) {
        if ( matrix(i, matrix.cols() - 1) == rand_class)
            matrix(i, matrix.cols() - 1) = new_class;
    }
    
    return matrix;
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

Eigen::MatrixXd Database::AverageMatrix(Eigen::MatrixXd matrix) {

    vector<double> labels = Database::ClassLabels(matrix);

    Eigen::MatrixXd average_matrix(labels.size(), matrix.cols());
    average_matrix = Eigen::MatrixXd::Zero(labels.size(), matrix.cols());

    for (int i = 0; i < labels.size(); ++i) {
        int cont = 0;
        for (int j = 0; j < matrix.rows(); ++j) {
            if (matrix(j, Eigen::last) == labels[i]) {
                average_matrix(i, Eigen::seq(0, Eigen::last-1)) += matrix(j, Eigen::seq(0, Eigen::last-1));
                cont++;
            }
        }

        average_matrix(i, Eigen::seq(0, Eigen::last-1) ) /= cont;
        average_matrix(i, average_matrix.cols() - 1) = labels[i];
    }

    return average_matrix;
}

vector<double> Database::CalculateDistance(Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> average_matrix, Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> test_row) {
    // El vector almacena en la posicion 0 la distancia al vector promedio analizado, y en el 1 la etiqueta del mismo
    vector<double> distance_label;
    distance_label.resize(2);
    // Vector auxiliar que obtendra las distancias del vector test respecto a cada vector promedio

    double max_distance = 1;
    double current_distance = 1;
    double max_label;
    double current_label;

    for (int i = 0; i < average_matrix.rows(); ++i) {
        current_distance =  Distance::EuclideanDistance( test_row(0, Eigen::seq(0, Eigen::last-1)), average_matrix(i, Eigen::seq(0, Eigen::last-1)) );                        
        current_label = average_matrix(i, average_matrix.cols()-1);
            
        if ( current_distance < max_distance ){
            max_distance = current_distance;
            max_label = current_label;
        }

    }
        
    distance_label[0] = max_distance;
    distance_label[1] = max_label;


    return distance_label;
}

Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> Database::ClassAssignment(Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> average_matrix, Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> test_matrix) {
    // El vector almacena en la posicion 0 la distancia al vector promedio analizado, y en el 1 la etiqueta del mismo
    vector<double> distance_label;

    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic > estimated_classes;

    estimated_classes.resize(test_matrix.rows(), test_matrix.cols() );

    // Se itera cada vector test presente en el contenedor
    for (int i = 0; i < test_matrix.rows(); ++i) {
        // Se obtiene la etiqueta con el valor más menor
        distance_label =  Database::CalculateDistance( average_matrix, test_matrix(i, Eigen::all )); // ACA EL ERROR                     
        estimated_classes(i, Eigen::seq(0, Eigen::last-1) ) = test_matrix(i, Eigen::seq(0, Eigen::last-1) );
        estimated_classes(i, estimated_classes.cols() - 1) = distance_label[1];
    }

    return estimated_classes;
}

void Database::HitsMisses(Eigen::MatrixXd estimated_classes, Eigen::MatrixXd real_classes) {
    if (estimated_classes.rows() != real_classes.rows()) return;
    if (estimated_classes.cols() != real_classes.cols()) return;
    
    int hits = 0;
    int misses = 0;
    
    for(int i = 0; i < estimated_classes.rows(); ++i){

        if ( estimated_classes(i, estimated_classes.cols() - 1) == real_classes(i, real_classes.cols() - 1) ) {
            hits++;
        }
        else{
            misses++;
        }
        
    }

    std::cout << "Aciertos: "<< (hits*100) / estimated_classes.rows() << "%" << std::endl;
    std::cout << "Errores: "<< (misses*100) / estimated_classes.rows() << "%" << std::endl;
}


void Database::Classify(Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> average_matrix, Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> test_matrix) {
    
    Eigen::MatrixXd estimated_classes = Database::ClassAssignment(average_matrix, test_matrix);
    //std::cout <<  "Estimated Classes" << std::endl;
    //std::cout << estimated_classes << std::endl;
    //std::cout << std::endl;
    Database::HitsMisses(estimated_classes, test_matrix);


}

bool Database::LabelComparator(Eigen::Matrix<double, 1, Eigen::Dynamic> vector, double label_input){

    if (vector(0, Eigen::last) == label_input )
        return true;

    return false;
}










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

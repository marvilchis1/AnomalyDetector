#include <iostream>
#include <fstream>
//#include "database.h"
#include "Eigen/Dense"
//#include "AnomalyDetector/Eigen/Core"



int main( int argc, char** argv ) {

    Eigen::Matrix<double, 3, 3> A;
    //Eigen::MatrixXi A;

    //std::cout << "OK" << std::endl;    

    A << 3, 2, 3,
         1, 5, 6,
         7, 8, 9;

    //std::cout << A << std::endl;
    //std::cout << A.rows() << " " << A.cols() << std::endl;
   
    int num_cols = A.cols();

    for (int i = 0; i < A.rows(); ++i) {

        //std::cout << A(i, Eigen::all) << std::endl;
        //std::cout << A.block(i, 0, 1, num_cols -1)  << std::endl;
        //std::cout << A(i, Eigen::seq(0, Eigen::last-1));
        std::cout << A(i, Eigen::last);
        
        std::cout << "---" << std::endl;
    }


    return 0;
}
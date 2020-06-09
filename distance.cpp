#include "distance.h"

float Distance::Intersection(Histogram Ct, Histogram Cr) {    
    if (Ct.Size() != Cr.Size() ) return 0;

    int distance = 0;
    for (int i = 0; i < Ct.Size(); ++i) 
        distance += std::min(int (Ct.At(i)), int(Cr.At(i)));

    return distance;
}

float Distance::Error(Histogram Ct, Histogram Cr) {
    if (Ct.Size() != Cr.Size() ) return 0;
    
    float distance = 0;
    for (int i = 0; i < Ct.Size(); ++i) 
        distance += ( Ct.At(i) - Cr.At(i) ) * ( Ct.At(i) - Cr.At(i) );
    
    distance = std::sqrt(distance) / Ct.Size();

    return distance;
}

float Distance::Intersection(std::vector<float> Ct, std::vector<float> Cr) {
    if (Ct.size() != Cr.size() ) return 0;
    
    float distance = 0;
    for (int i = 0; i < Ct.size(); ++i) 
        distance += std::min(Ct[i], Cr[i]);

    return distance;
}

float Distance::Error(std::vector<float> Ct, std::vector<float> Cr) {
    if (Ct.size() != Cr.size() ) return 0;
    
    float distance = 0;

    for (int i = 0; i < Ct.size(); ++i) 
            distance += ( Ct[i] - Cr[i] ) * ( Ct[i] - Cr[i] );
    distance = std::sqrt(distance) / Ct.size();

    return distance;
}
/*
double Distance::EuclideanDistance(double value1, double value2){
    //if (vector1.size() != vector2.size() ) return 0;

    double distance = 0.0;

    //for(int i = 0; i < vector1.size(); ++i ) {
    distance = (value2 - value1) * (value2 - value1);

    distance = std::sqrt((distance) / )

    //}


    return distance;
}
*/

double Distance::EuclideanDistance(std::vector<double> vector1, std::vector<double> vector2){
    if (vector1.size() != vector2.size()) return -1;

    double distance = 0.0;
    for(int i = 0; i < vector1.size(); ++i )
        distance += (vector2[i] - vector1[i]) * (vector2[i] - vector1[i]);
    
    distance = std::sqrt(distance);

    return distance;
}

double Distance::EuclideanDistance(Eigen::Matrix<double, 1, Eigen::Dynamic> vector1, Eigen::Matrix<double, 1, Eigen::Dynamic> vector2){
    

    if (vector1.rows() != vector2.rows()) return -1;
    if (vector1.cols() != vector2.cols()) return -1;

    //std::cout << "Rows" << vector1.cols() << std::endl;
    //std::cout << "Cols" << vector1.cols() << std::endl;

    double distance = 0.0;
    for (int i = 0; i < vector1.cols(); ++i)
        distance += (vector2(0,i) - vector1(0,i)) * (vector2(0,i) - vector1(0,i));
    
    distance = std::sqrt(distance);

    return distance;
}



double GetGreater(double A, double B){
    if ( A > B ) return A;
    return B;
}


bool Distance::IsGreater(double A, double B) {
    return (A > B);
}

bool Distance::IsGreaterD(DistType A, DistType B) {
    return (A.d > B.d);
}

bool Distance::IsLessD(DistType A, DistType B) {
    return (A.d < B.d);
}


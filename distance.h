#ifndef _DISTANCE_H_
#define _DISTANCE_H_

#include "histogram.h"
#include <algorithm>
#include <cmath>
#include <vector>
#include "Eigen/Dense"

struct DistType {
    float d;
    std::string ref1;
    std::string ref2;
};

namespace Distance {
    float Intersection(Histogram Ct, Histogram Cr);
    float Error (Histogram Ct, Histogram Cr);

    float Intersection(std::vector<float> Ct, std::vector<float> Cr);
    float Error (std::vector<float> Ct, std::vector<float> Cr);

    double EuclideanDistance(std::vector<double> vector1, std::vector<double> vector2);
    double EuclideanDistance(Eigen::Matrix<double, 1, Eigen::Dynamic> vector1, Eigen::Matrix<double, 1,Eigen::Dynamic> vector2);

    double GetGreater(double A, double B);


    bool IsGreater(double A, double B);
    bool IsGreaterD(DistType A, DistType B);
    bool IsLessD(DistType A, DistType B);
}

#endif

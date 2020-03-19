#ifndef _DISTANCE_H_
#define _DISTANCE_H_

#include "histogram.h"
#include <algorithm>
#include <cmath>
#include <vector>

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

    bool IsGreater(DistType A, DistType B);
    bool IsLess(DistType A, DistType B);
}

#endif

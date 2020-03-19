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

bool Distance::IsGreater(DistType A, DistType B) {
    return (A.d > B.d);
}

bool Distance::IsLess(DistType A, DistType B) {
    return (A.d < B.d);
}


#ifndef _HISTOGRAM_H_
#define _HISTOGRAM_H_

#include "image.h"
#include "lbp.h"
//#include "distance.h"
#include <algorithm>
#include <cmath>

class Histogram {

    std::vector<unsigned int> m_histogram; //(256, 0);
    int Index(int x, int y, int length);
    void Inicialize(int histogram_size);

    void SelectHistogram(Image map, int histogram_size);
    void SelectHistogram(std::vector<int> map, int histogram_size);
    
    void CreateHistogram(Image map);
    void CreateHistogram(std::vector<int> map);
    void CreateUniformHistogram(Image map);
    void CreateUniformHistogram(std::vector<int> map);

    public:
        Histogram();
        Histogram(Image map, int histogram_size = 256);
        Histogram( std::vector<int> map, int histogram_size = 256);

        std::vector<unsigned int> GetHistogram(Image map, int histogram_size = 256);
        std::vector<unsigned int> GetHistogram(std::vector<int> map, int histogram_size = 256);
        std::vector<float> NormalizedHistogram(Image map, int histogram_size = 256);
        int At(int index);
        int Size();

        //void CreateHistogram(Image map );
        //std::vector<unsigned int> GetHistogram( Image map );
        //void CreateHistogram(std::vector<int> map );
};

/*
namespace Distance {
    int Intersection(Histogram Ct, Histogram Cr);
    int Error (Histogram Ct, Histogram Cr);
}
*/

std::vector< std::vector<int> > SubmapsLBPImage( Image map, int submap_length );

std::vector< std::vector<int> > SubmapsLBPVector( std::vector<int> map, int submap_length, int mapwidth, int mapheight);



#endif
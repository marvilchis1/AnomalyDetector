#include "histogram.h"

Histogram::Histogram() {

}

Histogram::Histogram(Image map, int histogram_size) {
    GetHistogram(map, histogram_size);
}

Histogram::Histogram(std::vector<int> map, int histogram_size) {
    GetHistogram(map, histogram_size);
}

void Histogram::SelectHistogram(Image map, int histogram_size) {

    if ( histogram_size == 9) { CreateUniformHistogram(map); }
    else { CreateHistogram(map); }
}

void Histogram::SelectHistogram(std::vector<int> map, int histogram_size) {
    if ( histogram_size == 9 ) { CreateUniformHistogram(map); }
    else { CreateHistogram(map); }
}

std::vector<unsigned int> Histogram::GetHistogram(Image map, int histogram_size) {
    Inicialize(histogram_size);
    SelectHistogram(map, histogram_size);
    return m_histogram;
}

std::vector<unsigned int> Histogram::GetHistogram(std::vector<int> map, int histogram_size) {
    Inicialize(histogram_size);
    SelectHistogram(map, histogram_size);
    return m_histogram;
}   

std::vector<float> Histogram::NormalizedHistogram(Image map, int histogram_size) {
    Inicialize(histogram_size);
    SelectHistogram(map, histogram_size);

    std::vector<float> normalized_histogram;
    float num_elements = map.width() * map.height();
    
    //std::cout << m_histogram.size() << std::endl;
    for(int i = 0; i < histogram_size; ++i) {
        normalized_histogram.push_back( m_histogram[i]/num_elements);
        //std::cout << i <<" = " << normalized_histogram[i] << std::endl;
    }

    return normalized_histogram;
}

void Histogram::Inicialize(int histogram_size) {
    m_histogram.resize(0);
    m_histogram.resize(histogram_size, 0);
}

int Histogram::At(int index) {
    return m_histogram[index];
}

int Histogram::Size() {
    return m_histogram.size();
}

int Histogram::Index(int x, int y, int length) {
    return length * y + x;
}

void Histogram::CreateHistogram(Image map) {
    for( int y = 0; y < map.height(); ++y) {
        for( int x = 0; x < map.width(); ++x) {
            m_histogram[ map.at(x, y).y ] += 1;
        }
    }
}

void Histogram::CreateHistogram(std::vector<int> map) {
    for( int i = 0; i < map.size(); ++i) {
        m_histogram[ map[i] ] += 1;
    }
}

void Histogram::CreateUniformHistogram(Image map) {
    int aux = 0;
    for( int y = 0; y < map.height(); ++y) {
        for( int x = 0; x < map.width(); ++x) {
            // Se suma 1 para que sea multiplo de 2
            aux = log2( map.at(x,y).y + 1);
            //std::cout << "Map " << map.at(x,y).y << std::endl;
            m_histogram[aux] += 1;
        }
    }

}

void Histogram::CreateUniformHistogram(std::vector<int> map) {
    for ( int i = 0; i < map.size(); ++i) {
        m_histogram[ map[ log2(map[i] + 1) ] ] += 1;
    }
}

std::vector< std::vector<int> > SubmapsLBPImage( Image map, int submaplength) {
    
    std::vector < std::vector<int> > submaps;
    std::vector <int> minimap(submaplength * submaplength);

    for (int y = 0; y < map.height() - submaplength; ++y) {
        for (int x = 0; x < map.width() - submaplength; ++x) {
            
            for (int i = 0; i < submaplength; ++i) {
                for (int j = 0; j < submaplength; ++j) {
                    minimap[ Index(j, i, submaplength) ] = map.at(x+j, y+i).y;
                }
            }
            
            submaps.push_back(minimap);
        }
    }
    return submaps;
}

/*
std::vector< std::vector<unsigned int> > SubmapsLBPVector( std::vector<int> map, int submap_length, int mapwidth, int mapheight) {

}
*/


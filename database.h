#ifndef _DATABASE_H_
#define _DATABASE_H_

#include <vector>
//#include <map>
#include <string>
#include <iostream>
//#include "dataclass.h"
#include <algorithm>
#include <iterator>
#include <sstream>
//#include <Eigen/Dense>
#include <tuple>

struct Data {
    std::vector<std::vector<float>> Data;
    std::vector<std::string> Label;
};

using namespace std;

class Database {
    //std::vector< std::vector<std::string> > classcontainer;
    //Data DataTuple;
    typedef vector < tuple<vector<float>, string> > vector_tuple; 
    typedef tuple<vector<float>, string > my_tuple;
    vector_tuple classcontainer;

    //std::map<std::string, std::vector<float> > databasecontainer;
    std::vector<std::string> Split(const std::string line, char lim = ' ');
    std::vector<float> Transform(std::vector<std::string> stringVector);

    public:
        Database();
        Database( std::vector<std::string> data );
        //bool GetLines(std::vector<std::string> data);
        vector_tuple Classify(std::vector<std::string> stringvector);
        my_tuple AverageVector(std::string label);

        void ShowAll();


};

#endif
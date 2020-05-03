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


struct Data {
    std::vector<std::vector<std::string>> Data;
    std::vector<std::string> Label;
};


class Database {
    std::vector< std::vector<std::string> > classcontainer;
    Data DataTuple;
    //std::map<std::string, std::vector<float> > databasecontainer;
    std::vector<std::string> Split(const std::string line, char lim = ' ');

    public:
        Database();
        Database( std::vector<std::string> data );
        bool GetLines(std::vector<std::string> data);
        Data Classify(std::vector<std::string> data);
        std::vector<std::string> AverageVector(std::string label);

        void ShowAll();


};

#endif
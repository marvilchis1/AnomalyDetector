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


class Database {
    std::vector< std::vector<std::string> > classcontainer;
    //std::map<std::string, std::vector<float> > databasecontainer;
    std::vector<std::string> Split(const std::string line, char lim = ' ');

    public:
        Database();
        Database( std::vector<std::string> data );
        bool Classify(std::vector<std::string> data);
        std::vector<std::string> AverageVector(std::string label);
        void ShowAll();


};

#endif
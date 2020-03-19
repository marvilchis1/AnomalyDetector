#ifndef _FILENAME_H_
#define _FILENAME_H_

#define BOOST_FILESYSTEM_VERSION 3
#define BOOST_FILESYSTEM_NO_DEPRECATED 
#include <boost/filesystem.hpp>
#include <iostream>
#include <string>


//using namespace std;

namespace GetFilename {

    namespace fs = ::boost::filesystem;
    void GetAll(std::string directory, std::string extension, std::vector<std::string>& vector_filename);
    void GetAll(const fs::path& directory, const std::string& extension, std::vector<fs::path>& vector_filename);

}




#endif
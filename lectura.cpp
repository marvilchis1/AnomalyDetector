#include <iostream>
#include <string>
#include <fstream>
#include <vector>

int main() {

    std::string filename = "salida.txt";
    std::vector<std::string> data;
        
    std::ifstream fs;
    std::string nm;
    bool bad = false;

    fs.open(filename);

    if ( !fs.is_open() ) return 0;

    if ( fs.eof() ) {
        fs.close();
        return 0;
    }

    int i = 0;
    std::string aux;
    while ( !fs.eof() ) {
        fs >> aux;
        //cif ( aux == ' ' ) continue;

        i++;
    }

    return 0;
}
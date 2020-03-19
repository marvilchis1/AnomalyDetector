#include "filename.h"

// Regresa el nombre junto la extension de todos los archivos que coinciden
// con una extension especifica en un directorio determinado (y todos sus directorios)

void GetFilename::GetAll(std::string directory, std::string extension, std::vector<std::string>& vector_filename) {
    if(!fs::exists(directory) || !fs::is_directory(directory)) {
        std::cout << "No existe la ruta" << std::endl;
        return;
    }
    
    fs::recursive_directory_iterator it(directory);
    fs::recursive_directory_iterator endit;

    //int i = 0;
    while(it != endit)
    {
        if(fs::is_regular_file(*it) && it->path().extension() == extension) {
            //fs::path aux_path = it->path().filename();
            //std::string path_string = aux_path.string();
            std::string path_string = it->path().filename().string();
            vector_filename.push_back(path_string);
            //std::cout << i << "  " << it->path().filename() << std::endl;
        //++i;
        }
        ++it;
    }
}






// Regresa el nombre junto la extension de todos los archivos que coinciden
// con una extension especifica en un directorio determinado (y todos sus directorios)
void GetFilename::GetAll(const fs::path& directory, const std::string& extension, std::vector<fs::path>& vector_filename)
{
    if(!fs::exists(directory) || !fs::is_directory(directory)) {
        std::cout << "No existe la ruta" << std::endl;
        return;
    }

    fs::recursive_directory_iterator it(directory);
    fs::recursive_directory_iterator endit;

    //int i = 0;
    while(it != endit)
    {
        if(fs::is_regular_file(*it) && it->path().extension() == extension) {
            vector_filename.push_back(it->path().filename());
            //std::cout << i << "  " << it->path().filename() << std::endl;
        //++i;
        }
        ++it;
    }
}




/*
int main() {
    fs::path root = "textures";
    std::vector<fs::path> re;

    get_all("textures/", ".png", re);

    std::cout << "Abierto" << std::endl;
    return 0;
}
*/

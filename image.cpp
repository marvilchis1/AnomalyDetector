#include "image.h"

Image::Image() {
    m_width = 0;
    m_height = 0;
    //m_data = nullptr;
}


Image::Image( int width, int height ) : Image() {
    set(width, height);
}


Image::Image( const std::string filename ) : Image() {
    load(filename);
}


Image::Image( const Image& cp ) : Image() {
    copy(cp);
}


Image::~Image() {
    clear();
}

bool Image::clear() {
    //if ( m_data != nullptr ) { 
    if (m_data.size() != 0) {
        m_width = 0;
        m_height = 0;
/*   
        if (m_data != nullptr ){
            delete [] m_data;
            m_data = nullptr;
        }
*/
        return true;
    }

    return false;
}


bool Image::set( int width, int height ) {

    if ( width < 1 || height < 1 ) return false;

    clear();

    m_width = width;
    m_height = height;
    //m_data = new Color[width*height];
    m_data.resize(width * height);

    return true;
}

// copia los datos de cp en el objeto actual (*this)
bool Image::copy( const Image& cp ) {

    if ( set(cp.m_width, cp.m_height) == false ) return false;

    if ( m_data.size() != 0 ) {
        //for ( int i=0; i<m_width*m_height; i++ ) {
        //    m_data[i] = cp.m_data[i];
        //}

        m_data = cp.m_data;

        //buffer = cp.buffer;
        //state = cp.state;
        m_colortype = cp.m_colortype;
        m_channels = cp.m_channels;
        return true;
    }

    return false;
}

// Obtiene la imagen Y sin eliminar el RGB
Image Image::GetScaleGray() {
    Image img_aux(m_width, m_height);
    ColorConverter conv;
    if ( m_data.size() != 0 ){
        for (int i=0; i < m_width*m_height; i++) {
            img_aux.m_data[i].y = conv.RGBtoY(m_data[i]);
        }
        img_aux.setcolortype(ColorType::CT_GREY);
    }
    return img_aux;
}

// Convierte a ScaleGray y elimina el RGB
bool Image::ConvertToScaleGray(){
    ColorConverter conv;
    if ( m_data.size() != 0){
        for (int i=0; i < m_width*m_height; i++) {
            m_data[i].y = conv.RGBtoY(m_data[i]);
            m_data[i].r = 0;
            m_data[i].g = 0;
            m_data[i].b = 0;
        }
        m_colortype = CT_GREY;
        return true;
    }
    return false;
}


bool Image::load( const std::string filename ) {
    bool good;

    unsigned int width, height, error;
    std::vector<unsigned char> raw;

    std::vector<unsigned char> buffer;
    lodepng::State state;

    lodepng::load_file(buffer, filename);
    error = lodepng::decode(raw, width, height, state, buffer);
    if ( error ) { return false; }

    m_rawsize = raw.size();
    
    set(width, height);

    // Se determina que espacio de color es la imagen (RGB, GrayScale, ect)
    LodePNGInfo info = state.info_png;
    m_colortype = (ColorType) info.color.colortype;
    m_channels = lodepng_get_channels( &(info.color) );

    if (m_colortype == CT_RGB){
        good = load_rgb(raw);
        if ( good ) return true;
    }

    if (m_colortype == CT_RGBA){
        good = load_rgb(raw);
        if ( good ) return true;
    }

    if ( (m_colortype == CT_GREY  || m_colortype == CT_GREY_ALPHA) && raw.size() == 4*width*height ) {
            m_colortype = CT_RGBA;
            good = load_rgb(raw);
            if ( good ) return true;
    }

    if (m_colortype == CT_GREY) {
        good = load_gray(raw);
        if ( good ) return true;
    }

    if (m_colortype == CT_GREY_ALPHA){
        good = load_gray(raw);
        if ( good ) return true;
    }
    return false;
}


bool Image::save( const std::string filename) const {
    switch ( m_colortype ) {
        //case Format::PPM:
        //    return save_ppm(filename);
        case ColorType::CT_GREY:
            //if (m_rawsize == 4*m_width*m_height) return save_rgb(filename);
            
            return save_gray(filename);

        case ColorType::CT_RGB:
            return save_rgb(filename);

        case ColorType::CT_RGBA:
            return save_rgb(filename);
        default: ;

    }

    return false;
}


Color& Image::at( int x, int y ) {
    return m_data[index(x, y)];
}

int Image::width() const {
    return m_width;
}


int Image::height() const {
    return m_height;
}

int Image::raw_size() const {
    return m_rawsize;
}

Image::ColorType Image::getcolortype() {
    return m_colortype;
}

void Image::setcolortype(ColorType colortype) {
    m_colortype = colortype;
}

Image& Image::operator=( const Image& im ) {
    copy(im);
    return *this;
}

Color& Image::operator()( int x, int y ) {
    return m_data[index(x,y)];
}

bool Image::operator==( const Image& im ) {
    if ( m_width  != im.m_width  ) return false;
    if ( m_height != im.m_height ) return false;

    for ( int i=0; i<m_width*m_height; i++ ) {
        // implementar comparación de colores
        if ( m_data[i].r != im.m_data[i].r ) return false;
        if ( m_data[i].g != im.m_data[i].g ) return false;
        if ( m_data[i].b != im.m_data[i].b ) return false;
        if ( m_data[i].a != im.m_data[i].a ) return false;
        if ( m_data[i].y != im.m_data[i].y ) return false; 
    }

    return true;
}

bool Image::operator!=( const Image& im ) {
    return !operator==(im);
}

int Image::index( int x, int y ) const {
    return (m_width*y + x);
}


bool Image::load_ppm( const std::string filename ) {
    std::ifstream fs;
    std::string ppmid;
    int width;
    int height;
    int level;
    bool bad = false;

    fs.open(filename);

    if ( !fs.is_open() ) return false;

    fs >> ppmid;
    fs >> width;
    fs >> height;
    fs >> level;

    // comprobaciones
    if ( fs.eof() ) bad = true;
    if ( ppmid != "P3" ) bad = true;
    if ( width < 1 ) bad = true;
    if ( height < 1 ) bad = true;
    if ( level < 1 || level > 255 ) bad = true;

    if ( bad ) {
        fs.close();
        return false;
    }

    set(width, height);

    int red;
    int green;
    int blue;
    for ( int i=0; i<width*height; i++ ) {
        fs >> red;
        fs >> green;
        fs >> blue;

        if ( fs.eof() ) {
            bad = true;
            break;
        }

        m_data[i] = Color(red, green, blue);
    }

    fs.close();

    if ( bad ) return false;
    return true;
}


bool Image::save_ppm( const std::string filename ) const {
    std::ofstream fs;

    fs.open(filename);

    if ( !fs.is_open() ) return false;

    // se escribe el identificador
    fs << "P3" << std::endl;

    // se escribe el ancho de la imagen en píxeles
    fs << m_width << std::endl;

    // se escribe el alto de la imagen en píxeles
    fs << m_height << std::endl;

    // se escribe el nivel de intensidad máximo
    fs << 255 << std::endl;

    // se escriben los datos RGB
    for ( int i=0; i<m_width*m_height; i++ ) {
        // se requiere un casting int() porque queremos imprimir el número que
        // representa cada canal, y no un caracter ASCII.
        fs << int(m_data[i].r) << " ";
        fs << int(m_data[i].g) << " ";
        fs << int(m_data[i].b) << std::endl;
    }

    fs.close();

    return true;
}

/*
bool Image::load_rgb( std::vector<unsigned char> raw ) {
    int red, green, blue;//, alpha;
    for ( int i=0; i<int(m_width*m_height); i++ ) {
        red   = raw[3*i+0];
        green = raw[3*i+1];
        blue  = raw[3*i+2];
        //alpha = raw[4*i+3];

        m_data[i] = Color(red, green, blue);//, alpha);
        m_data[i].y = 0;
    }

    return true;
}

bool Image::save_rgb( const std::string filename ) const {
    std::vector<unsigned char> raw;
    unsigned int error;

    raw.resize(3*m_width*m_height);

    for ( int i=0; i<m_width*m_height; i++ ) {
        raw[3*i+0] = m_data[i].r;
        raw[3*i+1] = m_data[i].g;
        raw[3*i+2] = m_data[i].b;
        //raw[4*i+3] = 255;
    }

    error = lodepng::encode(filename, raw, m_width, m_height, LCT_RGB);

    if ( error ) return false;
    return true;
}
*/
bool Image::load_rgb( std::vector<unsigned char> raw ) {
    int red, green, blue, alpha;
    for ( int i=0; i<int(m_width*m_height); i++ ) {
        red   = raw[4*i+0];
        green = raw[4*i+1];
        blue  = raw[4*i+2];
        alpha = raw[4*i+3];
        

        m_data[i] = Color(red, green, blue, alpha);
        m_data[i].y = 0.0;
        //m_data[i].print();
    }
    return true;
}

bool Image::save_rgb( const std::string filename ) const {
    std::vector<unsigned char> raw;
    unsigned int error;

    raw.resize(4*m_width*m_height);

    for ( int i=0; i<m_width*m_height; i++ ) {
        raw[4*i+0] = m_data[i].r;
        raw[4*i+1] = m_data[i].g;
        raw[4*i+2] = m_data[i].b;
        raw[4*i+3] = m_data[i].a;
    }

    error = lodepng::encode(filename, raw, m_width, m_height);

    if ( error ) return false;
    return true;
}

bool Image::load_gray( std::vector<unsigned char> raw ) {
    
    for ( int i=0; i<int(m_width*m_height); i++ ) {
        m_data[i].y = raw[i];
    }
    return true;
}

bool Image::save_gray( const std::string filename ) const {
    std::vector<unsigned char> raw;
    unsigned int error;

    raw.resize(m_width*m_height);

    for ( int i=0; i<m_width*m_height; i++ ) {
        raw[i] = m_data[i].y;
    }


    error = lodepng::encode(filename, raw, m_width, m_height, LCT_GREY);

    if ( error ) return false;
    return true;
}




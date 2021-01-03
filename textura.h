#ifndef TEXTURA_H_INCLUDED
#define TEXTURA_H_INCLUDED

#include "aux.h"
#include "string"
#include "jpg_imagen.hpp"


class Textura{
    private:
        GLuint textura_id = 0;
        std::vector<unsigned char> data;
        int width, height;
        jpg::Imagen * pimg = NULL;
        unsigned char * texels; 

    public:
        Textura();
        Textura(const std::string &archivo);
        Textura(const Textura &aux);
        void activar(); 
};

#endif
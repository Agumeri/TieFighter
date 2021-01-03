#ifndef LUZ_H_INCLUDED
#define LUZ_H_INCLUDED

#include "aux.h"

class Luz
{
    public:
        void activar();
        inline float getX(){return this->posicion[0];}
        inline float getY(){return this->posicion[1];}
        inline float getZ(){return this->posicion[2];}
        
    protected:
        Tupla4f posicion;
        GLenum id;
        Tupla4f colorAmbiente,
                colorDifuso,
                colorEspecular;
};

#endif
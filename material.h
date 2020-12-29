#ifndef MATERIAL_H_INCLUDED
#define MATERIAL_H_INCLUDED

#include "aux.h"

class Material
{
    private:
        Tupla4f difuso,
                especular,
                ambiente;
        float brillo;

    public:
        Material();
        Material(const Material & m);
        Material(Tupla4f mdifuso, Tupla4f mespecular, Tupla4f mambiente, float brillo);
        void aplicar();

        // funciones setter y getter
        inline void setDifuso(Tupla4f t_aux){ this->difuso = t_aux;}
        inline void setEspecular(Tupla4f t_aux){ this->especular = t_aux;}
        inline void setAmbiente(Tupla4f t_aux){ this->ambiente = t_aux;}
        inline Tupla4f getDifuso(){return this->difuso;}
        inline Tupla4f getEspecular(){return this->especular;}
        inline Tupla4f getAmbiente(){return this->ambiente;}

        
};

#endif
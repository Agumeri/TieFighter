#ifndef ESFERA_H_INCLUDED
#define ESFERA_H_INCLUDED

#include "aux.h"
#include "objrevolucion.h"

class Esfera : public ObjRevolucion
{
    public:
        Esfera(int num_vert_perfil = 10, int num_instancias_perf = 20, float r = 40.0, bool tsup = true, bool tinf = false);

    private:
        float radio;

} ;


#endif

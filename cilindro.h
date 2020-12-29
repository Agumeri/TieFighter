#ifndef CILINDRO_H_INCLUDED
#define CILINDRO_H_INCLUDED

#include "aux.h"
#include "objrevolucion.h"

class Cilindro : public ObjRevolucion
{
    public:
        Cilindro(int num_vert_perfil = 2, int num_instancias_perf = 20, float h = 80.0, float r = 40.0, bool tsup = true, bool tinf = true);

    private:
        float altura,
              radio;

} ;


#endif

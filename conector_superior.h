#ifndef CONECTOR_SUPERIOR_H_INCLUDED
#define CONECTOR_SUPERIOR_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "cilindro.h"
#include "esfera.h"

class ConectorSuperior : public Malla3D
{
   private:
    Esfera * e1 = new Esfera(10,20,4,true,true);
    Cilindro * c1 = new Cilindro(2,20,20,4,true,true);

   public:
    ConectorSuperior();
    void dibuja(int modo_dibujado, bool puntos, bool lineas,bool solido, bool ajedrez);
} ;




#endif
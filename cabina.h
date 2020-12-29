#ifndef CABINA_H_INCLUDED
#define CABINA_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "cilindro.h"
#include "esfera.h"

class Cabina : public Malla3D
{
   private:
    Esfera * e1 = new Esfera(10,20,4,true,true);

   public:
    Cabina();
    void dibuja(int modo_dibujado, bool puntos, bool lineas,bool solido, bool ajedrez);
} ;




#endif

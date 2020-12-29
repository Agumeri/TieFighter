#ifndef ALA_H_INCLUDED
#define ALA_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "aleron.h"
#include "conector_superior.h"
#include "conector_inferior.h"

class Ala : public Malla3D
{
   private:
    Aleron * aleron = new Aleron();
    ConectorSuperior * con_sup = new ConectorSuperior();
    ConectorInferior * con_inf = new ConectorInferior();

    float grado_giro_aleron;
    float grado_giro_conector;
    float altura_giro_conector;
   public:
    Ala();
    void dibuja(int modo_dibujado, bool puntos, bool lineas,bool solido, bool ajedrez);
    
    void setGradoGiro(float angulo);
    void setGiroConector(float angulo, float altura);
    void rotar(float angulo);

} ;




#endif
#ifndef TIEFIGHTER_H_INCLUDED
#define TIEFIGHTER_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "ala.h"
#include "esfera.h"

class TieFighter : public Malla3D
{
   private:
    Ala * ala_derecha = new Ala();
    Ala * ala_izquierda = new Ala();
    Esfera * cabina = new Esfera(10,20,4,true,true);

    float pos_ala_izq = 0;
    float pos_ala_der = 0;
    float giroAlerones;
    float giroConector;
    float altura_conector;
    bool rotar_alas;
   public:
    TieFighter();
    void dibuja(int modo_dibujado, bool puntos, bool lineas,bool solido, bool ajedrez);
    void posicionVelocidad(float grado_giro);
    void posicionAtaque(float grado_giro);
    void posicionSaltoET(bool parar_rotacion);
    void rotarAleron();
    void rotarConector();
    void rotarAlas(bool rotar=true);
    void desplegarAlas();
} ;




#endif
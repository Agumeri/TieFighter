#include "aux.h"
#include "luz.h"
#include "luzposicional.h"

LuzPosicional::LuzPosicional(const Tupla3f & posicion){
    // Posicion luz 
    for(int i=0; i<3; i++) this->posicion(i) = posicion(i);
    this->posicion(3) = 1.0;
}

LuzPosicional::LuzPosicional(Tupla3f direccion, GLenum idLuzOpenGL, Tupla4f colorAmbiente, Tupla4f colorEspecular, Tupla4f colorDifuso){
    //Asignamos los valores por parametro a su correspondiente lugar 
    
    // Posicion luz 
    for(int i=0; i<3; i++) posicion(i) = direccion(i);
    posicion(3) = 1.0;

    // IdLuz
    id = idLuzOpenGL;

    // Colores
    this->colorAmbiente = colorAmbiente;
    this->colorDifuso = colorDifuso;
    this->colorEspecular = colorEspecular;
}

void LuzPosicional::modificarPosicion(float x, float y, float z){
    posicion(0) = x;
    posicion(1) = y;
    posicion(2) = z;
}
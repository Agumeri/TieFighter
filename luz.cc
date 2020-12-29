#include "aux.h"
#include "luz.h"

void Luz::activar(){
    // Habilitamos la luz a partir de su id (GL_LIGHTi)
    glEnable(this->id);

    // dibujamos la luz
    glLightfv(this->id,GL_DIFFUSE,this->colorDifuso);
    glLightfv(this->id,GL_SPECULAR,this->colorEspecular);
    glLightfv(this->id,GL_AMBIENT,this->colorAmbiente);
    glLightfv(this->id,GL_POSITION,this->posicion);

    // std::cout << "\nPOSICION: " << "A: " << posicion[0] << " B: " << posicion[1] << " C: " << posicion[2] << " D: " << posicion[3] << std::endl;
}
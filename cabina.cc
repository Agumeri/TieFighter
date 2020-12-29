#include "aux.h"
#include "cabina.h"

Cabina::Cabina(){}

void Cabina::dibuja(int modo_dibujado, bool puntos, bool lineas,bool solido, bool ajedrez){
    glPushMatrix();
        glTranslatef(-20,0,0);
        e1->VerTapas(true);
        e1->draw(modo_dibujado,puntos,lineas,solido,ajedrez);
    glPopMatrix();
}
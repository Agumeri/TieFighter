#include "aux.h"
#include "conector_inferior.h"

ConectorInferior::ConectorInferior(){
    Tupla4f perla_ambiente(0.25,0.20725,0.20725,1.0),
              perla_difuso(1,0.829,0.829,1.0),
              perla_especular(0.296648,0.296648,0.296648,1.0);

    Material perla = Material(perla_difuso,perla_especular,perla_ambiente,0.088*128.0);

    e2->setMaterial(perla);
    e3->setMaterial(perla);
    c2->setMaterial(perla);
}

void ConectorInferior::dibuja(int modo_dibujado, bool puntos, bool lineas,bool solido, bool ajedrez){
    
    glPushMatrix();
        glScalef(1.3,1.3,1.3);
        glTranslatef(-10,0,0);
        e2->VerTapas(true);
        e2->draw(modo_dibujado,puntos,lineas,solido,ajedrez);
    glPopMatrix();glPushMatrix();
        glRotatef(-90.0,0.0,0.0,1.0);
        c2->VerTapas(true);
        c2->draw(modo_dibujado,puntos,lineas,solido,ajedrez);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(10,0,0);
        e3->VerTapas(true);
        e3->draw(modo_dibujado,puntos,lineas,solido,ajedrez);
    glPopMatrix();
}
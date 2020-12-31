#include "aux.h"
#include "conector_superior.h"

ConectorSuperior::ConectorSuperior(){
     Tupla4f perla_ambiente(0.25,0.20725,0.20725,1.0),
              perla_difuso(1,0.829,0.829,1.0),
              perla_especular(0.296648,0.296648,0.296648,1.0);

    Material perla = Material(perla_difuso,perla_especular,perla_ambiente,0.088*128.0);

    e1->setMaterial(perla);
    c1->setMaterial(perla);
}

void ConectorSuperior::dibuja(int modo_dibujado, bool puntos, bool lineas,bool solido, bool ajedrez){
    glMatrixMode(GL_MODELVIEW);
    
    glPushMatrix();
        glTranslatef(-10,0,0);
        e1->VerTapas(true);
        e1->draw(modo_dibujado,puntos,lineas,solido,ajedrez);
    glPopMatrix();
    glPushMatrix();
        glRotatef(90.0,0.0,0.0,1.0);
        c1->VerTapas(true);
        c1->draw(modo_dibujado,puntos,lineas,solido,ajedrez);
    glPopMatrix();
    // glPushMatrix();
    //     glTranslatef(10,0,0);
    //     e2->VerTapas(true);
    //     e2->draw(modo_dibujado,puntos,lineas,solido,ajedrez);
    // glPopMatrix();
}
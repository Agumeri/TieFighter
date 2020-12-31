#include "aux.h"
#include "ala.h"

Ala::Ala(){
    grado_giro_aleron = 0;
    grado_giro_conector = 0;
}

void Ala::dibuja(int modo_dibujado, bool puntos, bool lineas,bool solido, bool ajedrez){
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
        glTranslatef(0.0,altura_giro_conector,0.0);
        glRotatef(grado_giro_conector,0.0,0.0,1.0);

        glPushMatrix();
            glScalef(3,3,3);
            glTranslatef(-11,0,0);
            glRotatef(grado_giro_aleron,1.0,0.0,0.0);
            glRotatef(90.0,0.0,1.0,0.0);
            aleron->draw(modo_dibujado,puntos,lineas,solido,ajedrez);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(-23,0,0);
            con_sup->dibuja(modo_dibujado,puntos,lineas,solido,ajedrez); // cambiar a conector superior
        glPopMatrix();
    glPopMatrix();
    
    
    glPushMatrix();
        con_inf->dibuja(modo_dibujado,puntos,lineas,solido,ajedrez);
    glPopMatrix();
    
}

void Ala::setGradoGiro(float angulo){
    this->grado_giro_aleron = angulo;
}

void Ala::setGiroConector(float angulo, float altura){
    this->grado_giro_conector = angulo;
    this->altura_giro_conector = altura;

    // if(altura_giro_conector <= 0) altura_giro_conector = 0;
}

void Ala::Idle(){
    grado_giro_aleron = 0;
    grado_giro_conector = 0;
}
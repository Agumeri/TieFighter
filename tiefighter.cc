#include "aux.h"
#include "tiefighter.h"

TieFighter::TieFighter(){
    Tupla4f goma_negra_ambiente(0.02,0.02,0.02,1.0),
              goma_negra_difuso(0.01,0.01,0.01,1.0),
              goma_negra_especular(0.4,0.4,0.4,1.0);

    Material goma_negra = Material(goma_negra_difuso,goma_negra_especular,goma_negra_ambiente,1.0*128.0);

    cabina->setMaterial(goma_negra);

    giroAlerones = 0;
    giroConector = 0;
}

void TieFighter::dibuja(int modo_dibujado, bool puntos, bool lineas,bool solido, bool ajedrez){
    glPushMatrix();
        glScalef(5,5,5);
        cabina->VerTapas(true);
        cabina->draw(modo_dibujado,puntos,lineas,solido,ajedrez);
    glPopMatrix();

    // this->desplegarAlas(true);
    // this->rotarAlas(rotar_alas);
    glPushMatrix();
        glPushMatrix();
            // glScalef(3,3,3);
            this->rotarAleron();
            this->rotarConector();
            glTranslatef(pos_ala_izq,0,0);
            ala_izquierda->dibuja(modo_dibujado,puntos,lineas,solido,ajedrez);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(pos_ala_der,0,0);
            this->rotarAleron();
            this->rotarConector();
            glRotatef(180.0,0.0,0.0,1.0);
            ala_derecha->dibuja(modo_dibujado,puntos,lineas,solido,ajedrez);
        glPopMatrix();
    glPopMatrix();
}

void TieFighter::posicionVelocidad(float grado_giro){
    if(giroAlerones < 90) giroAlerones += grado_giro;
}

void TieFighter::posicionAtaque(float grado_giro){
    if(giroConector < 45){
        giroConector += grado_giro;
        altura_conector += 0.00111;
    } 
}

void TieFighter::posicionSaltoET(bool parar_rotacion){
    // if(parar_rotacion){
        if(pos_ala_izq > -25 && pos_ala_der < 25){
            pos_ala_izq -= 0.005;
            pos_ala_der += 0.005;
        }
    // } else {
    //     if(pos_ala_izq < 0 && pos_ala_der > 0){
    //         pos_ala_izq += 0.005;
    //         pos_ala_der -= 0.005;
    //     }
    // }   
}

void TieFighter::rotarAleron(){
    ala_izquierda->setGradoGiro(giroAlerones);
    ala_derecha->setGradoGiro(-giroAlerones);
}

void TieFighter::rotarConector(){
    ala_izquierda->setGiroConector(giroConector,altura_conector);
    ala_derecha->setGiroConector(-giroConector,-altura_conector);
}

void TieFighter::rotarAlas(bool rotar){
    if(rotar){
        glRotatef(0.005,0.0,0.0,1.0);
        ala_derecha->rotar(-0.005);
    }
}

void TieFighter::desplegarAlas(){
    // ala_izquierda->anguloRotacion(giroConector);
    // ala_derecha->anguloRotacion(-giroConector);
    printf("\nSOY UNA PRUEBA\n");
}
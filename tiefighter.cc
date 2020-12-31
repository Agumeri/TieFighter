#include "aux.h"
#include "tiefighter.h"

TieFighter::TieFighter(){
    Tupla4f perla_ambiente(0.25,0.20725,0.20725,1.0),
              perla_difuso(1,0.829,0.829,1.0),
              perla_especular(0.296648,0.296648,0.296648,1.0);

    Material perla = Material(perla_difuso,perla_especular,perla_ambiente,0.088*128.0);


    cabina->setMaterial(perla);

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
    if(puede_girar_aleron){
        if(giroAlerones < 90) giroAlerones += grado_giro;

        if(giroAlerones >= 90) puede_girar_aleron = false;
    }

    if(!puede_girar_aleron){
        if(giroAlerones > 0) giroAlerones -= grado_giro;

        if(giroAlerones <= 0) puede_girar_aleron = true;
    }
}

void TieFighter::posicionAtaque(float grado_giro){
    if(puede_girar_conector)
    {  
        if(giroConector < 30){
            giroConector += grado_giro;
            altura_conector += 0.0011;
        }

        if(giroConector >= 30) puede_girar_conector = false;
    }

    if(!puede_girar_conector)
    {  
        if(giroConector > 0){
            giroConector -= grado_giro;
            altura_conector -= 0.0011;
        }

        if (altura_conector < 0) altura_conector = 0;
        if(giroConector <= 0) puede_girar_conector = true;
    }


}

void TieFighter::posicionSaltoET(float velocidad){
    if(puede_desplegar)
    {
        if(pos_ala_izq > -30 && pos_ala_der < 30)
        {
            pos_ala_izq -= velocidad;
            pos_ala_der += velocidad;
        }

        if(pos_ala_izq <= -30) puede_desplegar = false;
    }

    if(!puede_desplegar)
    {
        if(pos_ala_izq < 0 && pos_ala_der > 0){
            pos_ala_izq += velocidad;
            pos_ala_der -= velocidad;
        }
    
        if(pos_ala_izq >= 0) puede_desplegar = true;
    }
    // std::cout << "VALOR POS_ALA_IZQ: " << pos_ala_izq << std::endl;
    
}

void TieFighter::rotarAleron(){
    ala_izquierda->setGradoGiro(giroAlerones);
    ala_derecha->setGradoGiro(-giroAlerones);
}

void TieFighter::rotarConector(){
    ala_izquierda->setGiroConector(giroConector,altura_conector);
    ala_derecha->setGiroConector(-giroConector,-altura_conector);
}

void TieFighter::IdlePosition(){
    pos_ala_izq = 0;
    pos_ala_der = 0;
    altura_conector = 0;
    giroAlerones = 0;
    giroConector = 0;
}
#include "aux.h"
#include "material.h"

Material::Material(){}

Material::Material(const Material & m){
    this->difuso = m.difuso;
    this->especular = m.especular;
    this->ambiente = m.ambiente;
    this->brillo = m.brillo;
}

Material::Material(Tupla4f mdifuso, Tupla4f mespecular, Tupla4f mambiente, float brillo){
    // Asignamos cada parámetro a su campo correspondiente
    this->difuso = mdifuso;
    this->especular = mespecular;
    this->ambiente = mambiente;
    this->brillo = brillo;
}


void Material::aplicar(){
    // "dibujamos" el material 
    glMaterialfv(GL_FRONT,GL_DIFFUSE,this->difuso);
    glMaterialfv(GL_FRONT,GL_SPECULAR,this->especular);
    glMaterialfv(GL_FRONT,GL_AMBIENT,this->ambiente);

    // Asignamos el valor de brillo a un GLfloat para poder habilitarlo
    const GLfloat * brillo_valido = new GLfloat(this->brillo);
    glMaterialfv(GL_FRONT,GL_SHININESS,brillo_valido);
}
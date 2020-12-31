#include "textura.h"

Textura::Textura(std::string archivo){

}

Textura::Textura(const Textura &aux){
    this->data = aux.data;
    this->width = aux.width;
    this->height = aux.height;
    this->pimg = aux.pimg;
}

void Textura::activar(){

}
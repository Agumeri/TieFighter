#include "textura.h"

Textura::Textura(){}

Textura::Textura(const std::string &archivo){
    // nos aseguramos de que no se ha cargado la imagen todavía
    // pimg = new jpg::Imagen(archivo);
    if(pimg == NULL){
        // this->textura_id = _id;
        data.clear();

        pimg = new jpg::Imagen(archivo);
        texels = pimg->leerPixels();

        // std::cout << "\nAAAAAAA\n" << pimg->tamX() << " " << pimg->tamY() << std::endl;
        width = pimg->tamX();
        height = pimg->tamY();

        // Se asigna a textura_id un indice que no esté ocupado 
        // por otra textura
        glGenTextures(1,&textura_id);
    }
}

Textura::Textura(const Textura &aux){
    // this->data = aux.data;
    this->width = aux.width;
    this->height = aux.height;
    this->pimg = aux.pimg;
    this->texels = aux.texels;
}

void Textura::activar(){
    // activamos textura con el id 
    glBindTexture( GL_TEXTURE_2D, textura_id );
    // std::cout << "\nACTIVANDO TEXTURA\n"<< std::endl;
    // CONFIGURACION DE LAS TEXTURAS
        // El color de la textura se use en lugar de todas las reflectividades 
        // del material, MA,MD y MS
        // glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SINGLE_COLOR);

        // El color de la textura se usa en lugar de MA y MD, pero no MS, esto permite
        // brillos especulares de color blanco cuando hay texturas de color.
        glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);
        //

        // Interpolación lineal
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
        //
    //

    // Construimos la textura
    gluBuild2DMipmaps( GL_TEXTURE_2D,
                       GL_RGB,
                       width,
                       height,
                       GL_RGB,
                       GL_UNSIGNED_BYTE,
                       texels
    );
}
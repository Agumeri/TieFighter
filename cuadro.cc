#include "cuadro.h"

Cuadro::Cuadro(float lado)
{

   // inicializar la tabla de vértices

   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)


   // Redimensionamos las tuplas v y f
   v.resize(4);
   f.resize(2);

   // Lista de vertices
   //Primera cara
   v[0] = {-lado, -lado, 0};    //v0
   v[1] = {lado, -lado, 0};     //v1
   v[2] = {-lado, lado, 0};     //v2
   v[3] = {lado, lado, 0};      //v3
   
   // Tabla de caras
   // Cara 1
   f[0] = {0, 1, 2};
   f[1] = {1, 3, 2};

   tam_f = f.size();
}

void Cuadro::asignarCoordenadasTexturas(){
   // Nos aseguramos de que el objeto tiene el vector ct limpio
   ct.clear();

   // asignamos la coordenadas de textura al vector ct
   ct.push_back({1,1});
   ct.push_back({0,1});
   ct.push_back({1,0});
   ct.push_back({0,0});
}

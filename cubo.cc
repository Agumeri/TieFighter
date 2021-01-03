#include "aux.h"
#include "malla.h"
#include "cubo.h"

Cubo::Cubo(float lado)
{

   // inicializar la tabla de vértices

   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)


   // Redimensionamos las tuplas v y f
   v.resize(8);
   f.resize(12);

   // Lista de vertices
   //Primera cara
   v[0] = {-lado/2, -lado/2, lado/2};    //v0
   v[1] = {lado/2, -lado/2, lado/2};     //v1
   v[2] = {-lado/2, lado/2, lado/2};     //v2
   v[3] = {lado/2, lado/2, lado/2};      //v3
   v[4] = {lado/2, -lado/2, -lado/2};    //v4
   v[5] = {lado/2, lado/2, -lado/2};     //v5
   v[6] = {-lado/2, lado/2, -lado/2};    //v6
   v[7] = {-lado/2, -lado/2, -lado/2};   //v7
   v[7] = {-lado/2, -lado/2, -lado/2};   //v7
   

   // Tabla de caras
   // Cara 1
   f[0] = {0, 1, 2};
   f[1] = {1, 3, 2};

   // Cara 2
   f[2] = {1, 4, 5};
   f[3] = {1, 5, 3};

   // Cara 3
   f[4] = {3, 5, 2};
   f[5] = {2, 5, 6};

   // Cara 4
   f[6] = {0, 2, 7};
   f[7] = {7, 2, 6};
   
   // Cara 5
   f[8] = {7, 5, 4};
   f[9] = {7, 6, 5};

   // Cara 6
   f[10] = {7, 4, 1};
   f[11] = {0, 7, 1};

   tam_f = f.size();
}

void Cubo::asignarCoordenadasTexturas(){
   // Nos aseguramos de que el objeto tiene el vector ct limpio
   ct.clear();

   // asignamos la coordenadas de textura al vector ct
   ct.push_back({1,1});
   ct.push_back({0,1});
   ct.push_back({1,0});
   ct.push_back({0,0});

   ct.push_back({1,1});
   ct.push_back({1,0});
   ct.push_back({0,0});
   ct.push_back({0,1});
}

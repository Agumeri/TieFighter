#include "aux.h"
#include "malla.h"
#include "tetraedro.h"
#include "math.h"

Tetraedro::Tetraedro(float lado)
{
   // Calculamos la altura del triangulo equilatero, y la dividimos
   // en dos variables para poder asignar la posición de los vértices
   float altura = sqrt(pow(lado,2) - pow(lado/2, 2));
   float altura_superior = altura * 0.667;      // altura * 2/3
   float altura_inferior = altura / 3;

   // Calculamos tambien la altura de la base al vertice superior
   float altura_base_vertexsup = sqrt(pow(lado,2) - pow(altura_superior,2));

   // hacemos resize de v y f
   v.resize(4);
   f.resize(4);

   // inicializar la tabla de vértices
   v[0] = { -altura_superior, -altura_inferior, 0};
   v[1] = { altura_inferior, -altura_inferior, lado/2 };
   v[2] = { 0, altura_base_vertexsup, 0 };
   v[3] = { altura_inferior, -altura_inferior, -lado/2 };
    
   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)
   f[0] = { 0, 1, 2};
   f[1] = { 1, 3, 2};
   f[2] = { 0, 2, 3};
   f[3] = { 0, 3, 1};

   tam_f = f.size();
}


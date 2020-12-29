#include "aux.h"
#include "objrevolucion.h"
#include "objply.h"
#include "math.h"
#include <algorithm>


// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************


// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)
ObjRevolucion::ObjRevolucion() {}

ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_sup, bool tapa_inf) {
   // completar ......(práctica 2)

   // creamos el vector de los vectores del perfil (perfil_original) y leemos los vertices
   std::vector<Tupla3f> perfil_original;
   ply::read_vertices(archivo, perfil_original);
   
   // creamos la malla para el perfil escogido
   
   crearMalla(perfil_original, num_instancias, tapa_sup, tapa_inf);

}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)

 
ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapa_sup, bool tapa_inf) {
    crearMalla(archivo, num_instancias, tapa_sup, tapa_inf);
}

void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias, bool tapa_sup, bool tapa_inf) {
   // std::cout<<"quito el vertice 1 de perfil original" << perfil_original[0] << std::endl;
   // NUMERO PARA DIVIDIRLO POR N DENTRO DE LAS TABLAS
   float angulo_radianes = 2*M_PI;
   
   // creacion de la tabla de vertices (la dejamos vacia)
   this->v.clear();

   // cambiar orientacion si es necesario del perfil si es necesario
   if (perfil_original[0][1] > perfil_original[perfil_original.size()-1][1]){
      std::reverse(perfil_original.begin(), perfil_original.end());
   }

   // Selección del vertice de la tapa superior e inferior
   //******************************************************
   // Usar los booleanos para la parte extra
   //******************************************************
   //******************************************************
   Tupla3f polo_sur, polo_norte;
   
   // polo sur
   if(perfil_original[0][0] == 0.0){
      polo_sur = perfil_original[0];
      perfil_original.erase(perfil_original.begin());
   }else{
      polo_sur = {0,perfil_original[0][1],0};
   } 
   //

   // polo norte
   if(perfil_original[perfil_original.size()-1][0] == 0.0){
      polo_norte = perfil_original[perfil_original.size()-1];
      perfil_original.pop_back();
   }else{
      polo_norte = {0,perfil_original[perfil_original.size()-1][1],0};
   } 
   //

   // asignamos el valor correspondiente M y N
   this->N = num_instancias;
   this->M = perfil_original.size();

   // Añadimos los vertices a la tabla de vertices
   for(int i=0; i<=N-1; i++){
      for(int j=0; j<=M-1; j++){
         // creamos un objeto tupla3f auxiliar para ir obteniendo
         // los valores {x, y, z} correspondientes al punto actual
         Tupla3f aux;
         aux[0] = sin(angulo_radianes*i/N) * perfil_original[j][0]; // pos x
         aux[1] = perfil_original[j][1];                            // pos y
         aux[2] = cos(angulo_radianes*i/N) * perfil_original[j][0]; // pos z
         // ya obtenidas las coordenadas, metemos el vertice trasladado
         // en la tabla de vertices
         this->v.push_back(aux); 
      }
   }

   // // añadimos las tapas necesarias a la tabla de vertices
   this->v.push_back(polo_sur);     // N*M
   this->v.push_back(polo_norte);   // N*M+1

   // for(int i=0; i<v.size(); i++)
   //    std::cout << "Vertice " << i << ": " << v[i] << std::endl;

   // creacion de la tabla de caras (la dejamos vacia)
   this->f.clear();

   // Añadimos los triangulos correspondientes a la tabla de triangulos (menos los de las tapas)
   for(int i=0; i<=N-1; i++){
      for(int j=0; j<=M-2; j++){
         int a = M*i + j;
         int b = M*((i+1)%N) + j;

         // creamos dos tupla3i auxiliar para la cara a obtener (2 triangulos por cara)
         Tupla3i cara1(a,b,b+1), 
                 cara2(a,b+1,a+1);

         // añadimos ambos triangulos a la tabla de triangulos
         this->f.push_back(cara1);
         this->f.push_back(cara2);

      }
   }   

   // añadimos los triangulos
   // primero la tapa inferior
   tam_sin_tapas = f.size();

   if (tapa_inf)
   {
      
      for (int i = 0; i < N; i++)
      {
         Tupla3i aux(
             M * ((i + 1) % N), // pinta una cara 2 veces, revisar con pablo
             M * i,
             N * M);

         this->f.push_back(aux);
      }
   }

   // // ahora la tapa superior
   if (tapa_sup)
   {
      
      for (int i = 0; i < N; i++)
      {
         Tupla3i aux(
             M * (i + 1) - 1,
             M * (((i + 1) % N) + 1) - 1, // pinta una cara 2 veces, revisar con pablo
             N * M + 1
            );

         this->f.push_back(aux);
      }
      
   }
   //******************************************************

}

void ObjRevolucion::VerTapas(bool tapas){
   if(tapas) tam_f = f.size();
   else tam_f = tam_sin_tapas;
}


#include "aux.h"
#include "malla.h"
#include "aleron.h"

Aleron::Aleron()
{
   // Redimensionamos las tuplas v y f
   v.resize(14);
   f.resize(24);

   // Lista de vertices
   v[0] = {0,0,0.0025};
   v[1] = {5,-15,0.0025};
   v[2] = {10,0,0.0025};
   v[3] = {5,15,0.0025};
   v[4] = {-5,15,0.0025};
   v[5] = {-10,0,0.0025};
   v[6] = {-5,-15,0.0025};

   v[7] = {0,0,-0.0025};
   v[8] = {5,-15,-0.0025};
   v[9] = {10,0,-0.0025};
   v[10] = {5,15,-0.0025};
   v[11] = {-5,15,-0.0025};
   v[12] = {-10,0,-0.0025};
   v[13] = {-5,-15,-0.0025};

   
   // Tabla de caras

   //Parte de delante
   f[0]={0,1,2};
   f[1]={0,2,3};
   f[2]={0,3,4};
   f[3]={0,4,5};
   f[4]={0,5,6};
   f[5]={0,6,1};
   
   //Parte de por detras
   f[6]={7,9,8};
   f[7]={7,10,9};
   f[8]={7,11,10};
   f[9]={7,12,11};
   f[10]={7,13,12};
   f[11]={7,8,13};

   //Caras laterales visibles
   f[12]={1,8,9};
   f[13]={1,9,2};
   f[14]={2,9,10};
   f[15]={2,10,3};
   f[16]={3,10,11};
   f[17]={3,11,4};

   //Caras laterales no visibles
   f[18]={4,11,12};
   f[19]={4,12,5};
   f[20]={5,12,13};
   f[21]={5,13,6};
   f[22]={6,13,8};
   f[23]={6,8,1};

   

   tam_f = f.size();



   // asignamos el material
   Tupla4f goma_negra_ambiente(0.02,0.02,0.02,1.0),
            goma_negra_difuso(0.01,0.01,0.01,1.0),
            goma_negra_especular(0.4,0.4,0.4,1.0);

   Material goma_negra = Material(goma_negra_difuso,goma_negra_especular,goma_negra_ambiente,1.0*128.0);       

   this->setMaterial(goma_negra); 
}

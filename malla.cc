#include "aux.h"
#include "malla.h"
#include "math.h"

// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************
// Visualizacion en modo ajedrez 
void Malla3D::draw_ModoAjedrezInmediato(){
   // Utilizamos auxiliares para pintar las caras impares y pares
   std::vector<Tupla3i> f_aux, f_a, f_b;
   f_aux = f;

   // Distribuimos los indices de las caras en dos variables
   for(int i=0; i<tam_f; i+=2){
      f_a.push_back(f_aux[i]);
      f_b.push_back(f_aux[i+1]);
   }

   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_COLOR_ARRAY);

   glColorPointer(3, GL_FLOAT, 0, c_inm.data());
   glVertexPointer( 3, GL_FLOAT, 0, v.data() );
   glDrawElements( GL_TRIANGLES, (f_a.size())*3, GL_UNSIGNED_INT, f_a.data());

   glColorPointer(3, GL_FLOAT, 0, c_dif.data());
   glVertexPointer( 3, GL_FLOAT, 0, v.data() );
   glDrawElements( GL_TRIANGLES, (f_b.size())*3, GL_UNSIGNED_INT, f_b.data());

   // deshabilitar array de vertices
   glDisableClientState( GL_VERTEX_ARRAY );
   glDisableClientState( GL_COLOR_ARRAY );
}

// modificar a ajedrez diferido y hacer ajedrez inmediato
void Malla3D::draw_ModoAjedrezDiferido(){
   // Utilizamos auxiliares para pintar las caras impares y pares
   std::vector<Tupla3i> f_aux, f_a, f_b;
   f_aux = f;

   // Distribuimos los indices de las caras en dos variables
   for(int i=0; i<tam_f; i+=2){
      f_a.push_back(f_aux[i]);
      f_b.push_back(f_aux[i+1]);
   }

   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_COLOR_ARRAY);

   // habilitamos vbo de color para colorear y el de las caras y vertices
   if (id_vbo_color_chess_a == 0 && id_vbo_color_chess_b == 0 && id_vbo_ver_chess == 0 && id_vbo_tri_a == 0 && id_vbo_tri_b == 0){
      id_vbo_ver_chess = CrearVBO(GL_ARRAY_BUFFER,3*sizeof(float) * v.size(), v.data());       // id para los vertices
      id_vbo_tri_a = CrearVBO(GL_ELEMENT_ARRAY_BUFFER,3*sizeof(int) * f_a.size(), f_a.data()); // id para las caras
      id_vbo_tri_b = CrearVBO(GL_ELEMENT_ARRAY_BUFFER,3*sizeof(int) * f_b.size(), f_b.data()); // id para las caras
      id_vbo_color_chess_a = CrearVBO(GL_ELEMENT_ARRAY_BUFFER,3*sizeof(float) * c_inm.size(), c_inm.data());
      id_vbo_color_chess_b = CrearVBO(GL_ELEMENT_ARRAY_BUFFER,3*sizeof(float) * c_dif.size(), c_dif.data());
   } 

   // activamos los VBO de los vertices
      // activar VBO de vertices
      glBindBuffer(GL_ARRAY_BUFFER, id_vbo_ver_chess);

      // especifica formato y ofsset (=0)
      glVertexPointer(3, GL_FLOAT, 0, 0);

      // desactivar VBO de vertices
      glBindBuffer(GL_ARRAY_BUFFER, 0);
   //

   // Activamos los VBO de caras pares e impares
   // una vez hecho, nos ponemos a colorear los triangulos, primero los pares (f_a) y luego los impares (f_b)
   //
      // activar VBO de color para caras pares
      glBindBuffer(GL_ARRAY_BUFFER, id_vbo_color_chess_a);

      // Inicializamos el color a pintar de los vertices a 0 (no apuntaría a ninguna tabla de color)   
      glColorPointer(3, GL_FLOAT, 0, 0);

      // desactivar VBO de color
      glBindBuffer(GL_ARRAY_BUFFER, 0);

      //Activamos el VBO de triangulos (pares)
         // activar VBO de triangulos
         glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri_a);

         // dibujamos los triangulos
         glDrawElements(GL_TRIANGLES, 3*f_a.size(), GL_UNSIGNED_INT, 0);

         // desactivar VBO de triangulos
         glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
      //
   //
      // activar VBO de color para caras impares
      glBindBuffer(GL_ARRAY_BUFFER, id_vbo_color_chess_b);

      // Inicializamos el color a pintar de los vertices a 0 (no apuntaría a ninguna tabla de color)   
      glColorPointer(3, GL_FLOAT, 0, 0);

      // desactivar VBO de color
      glBindBuffer(GL_ARRAY_BUFFER, 0);

      //Activamos el VBO de triangulos (pares)
         // activar VBO de triangulos
         glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri_b);

         // dibujamos los triangulos
         glDrawElements(GL_TRIANGLES, 3*f_b.size(), GL_UNSIGNED_INT, 0);

         // desactivar VBO de triangulos
         glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
      //
   //

   // deshabilitar array de vertices
   glDisableClientState( GL_VERTEX_ARRAY );
   glDisableClientState( GL_COLOR_ARRAY );

}


// Visualización en modo inmediato con 'glDrawElements'
void Malla3D::draw_ModoInmediato(std::string color_pintar)
{ 
  // habilitar uso de un array de vertices
  glEnableClientState( GL_VERTEX_ARRAY );
  glEnableClientState( GL_COLOR_ARRAY );

  // indicar el formato y la direccion de memoria del array de vertices
  // (son tuplas de 3 valores float, sin espacio entre ellas)
  glVertexPointer( 3, GL_FLOAT, 0, v.data() );
  
  // indicamos el color con el que se van a pintar las caras (dependiendo de que modo se ha cogido)
  if(color_pintar == "puntos") glColorPointer(3, GL_FLOAT, 0, c_point.data());
  else if(color_pintar == "lineas") glColorPointer(3, GL_FLOAT, 0, c_line.data());
  else if(color_pintar == "solido") glColorPointer(3, GL_FLOAT, 0, c_inm.data());

  // visualizar, indicando: tipo de primitiva, numero de indices,
  // tipo de los indices, y direccion de la tabla de indices
  glEnableClientState(GL_NORMAL_ARRAY);
  glNormalPointer(GL_FLOAT, 0, nv.data());

  // si fuese objeto revolucion, M tiene que ser hasta SIN TAPAS o M + tapas
//   glDrawElements( GL_TRIANGLES, f.size()*3, GL_UNSIGNED_INT, f.data());
  glDrawElements( GL_TRIANGLES, tam_f*3, GL_UNSIGNED_INT, f.data());
   // std::cout << "HOLA NO ME HE ROTO" << std::endl;
  // deshabilitar array de vertices y el color
  glDisableClientState( GL_VERTEX_ARRAY );
  glDisableClientState( GL_COLOR_ARRAY );
  glDisableClientState( GL_NORMAL_ARRAY );
  
}
// -----------------------------------------------------------------------------
// Funcion utilizada para producir un identificador de VBO

GLuint Malla3D::CrearVBO( GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram){
   GLuint id_vbo; // resultado: identificador de VBO

   glGenBuffers(1, & id_vbo); // crear nuevo VBO, obtener identificador (nunca 0)

   glBindBuffer(tipo_vbo, id_vbo); // activar el VBO usando su identificador

   // esta instruccion hace la transferencia de datos desde RAM hacia GPU
   glBufferData(tipo_vbo, tamanio_bytes, puntero_ram, GL_STATIC_DRAW);

   glBindBuffer(tipo_vbo, 0); // desactivación del VBO (activar 0);

   return id_vbo; // devolver el identificador resultado
}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void Malla3D::draw_ModoDiferido(std::string color_pintar)
{
   // (la primera vez, se deben crear los VBOs y guardar sus identificadores en el objeto)
   // completar (práctica 1)
   // .....

   // creamos los identificadores del VBO para las caras y para los vertices
   if (id_vbo_ver == 0 && id_vbo_tri == 0 && id_vbo_color_point == 0 && id_vbo_color_line == 0 && id_vbo_color_dif == 0)
   {
      id_vbo_ver = CrearVBO(GL_ARRAY_BUFFER,3*sizeof(float) * v.size(), v.data());       // id para los vertices
      id_vbo_tri = CrearVBO(GL_ELEMENT_ARRAY_BUFFER,3*sizeof(int) * tam_f, f.data()); // id para las caras
      id_vbo_color_point = CrearVBO(GL_ELEMENT_ARRAY_BUFFER,3*sizeof(float) * c_point.size(), c_point.data());
      id_vbo_color_line = CrearVBO(GL_ELEMENT_ARRAY_BUFFER,3*sizeof(float) * c_line.size(), c_line.data());
      id_vbo_color_dif = CrearVBO(GL_ELEMENT_ARRAY_BUFFER,3*sizeof(float) * c_dif.size(), c_dif.data());
   }

   // una vez creados, procedemos a visualizar la malla

   //especificar localización y formato de la tabla de vértices, habilitar tabla
   // activar VBO de vertices
   glBindBuffer(GL_ARRAY_BUFFER, id_vbo_ver);

   // especifica formato y ofsset (=0)
   glVertexPointer(3, GL_FLOAT, 0, 0);

   // desactivar VBO de vertices
   glBindBuffer(GL_ARRAY_BUFFER, 0);
  
   // habilitar tabla de vertices y de colores
   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_COLOR_ARRAY);


   // indicamos el color con el que se van a pintar las caras (dependiendo de que modo se ha cogido)

   // ACTIVAMOS LOS VBO DE LAS TABLAS DE COLOR
   //
      if(color_pintar == "puntos") glBindBuffer(GL_ARRAY_BUFFER, id_vbo_color_point);
      else if(color_pintar == "lineas") glBindBuffer(GL_ARRAY_BUFFER, id_vbo_color_line);
      else if(color_pintar == "solido") glBindBuffer(GL_ARRAY_BUFFER, id_vbo_color_dif);

      // Inicializamos el color a pintar de los vertices a 0 (no apuntaría a ninguna tabla de color)   
      glColorPointer(3, GL_FLOAT, 0, 0);

      // desactivar VBO de color
      glBindBuffer(GL_ARRAY_BUFFER, 0);
   //

   glEnableClientState(GL_NORMAL_ARRAY);
   glNormalPointer(GL_FLOAT, 0, nv.data());
   
   // visualizar triangulos con glDrawElements (puntero a tabla == 0)
   // activar VBO de triangulos
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri);

   // dibujamos los triangulos
   glDrawElements(GL_TRIANGLES, 3*tam_f, GL_UNSIGNED_INT, 0);

   // desactivar VBO de triangulos
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

   // desactivar uso de array de vertices y color
   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_COLOR_ARRAY);
   glDisableClientState(GL_NORMAL_ARRAY);

}
// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void Malla3D::draw(int modo_dibujado, bool puntos, bool lineas,bool solido, bool ajedrez)
{
   // completar .....(práctica 1)
   glEnable(GL_CULL_FACE);
   this->inicializarColores();
   color_pintar = "solido";

   // ponemos un filtro que hace que las normales sole se calculen una vez (si nv esta vacio)
   if(nv.empty()) this->calcular_normales(); 

   // aplicamos el material si está indicado en la malla
   if(m != nullptr) m->aplicar();

   // contemplar que aspectos se van a visualizar (puntos, lineas, solido, ajedrez)
   // solido y ajedrez serán independientes, mientras este ajedrez, no se podran ver los otros 3
   if (puntos){
      glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
      // hacemos que los puntos sean mas grandes y aumentamos su tamaño para que sean visibles
      glEnable(GL_PROGRAM_POINT_SIZE);
      glPointSize(3);
      color_pintar = "puntos";
      if(modo_dibujado == 1) this->draw_ModoInmediato(color_pintar);
      else if(modo_dibujado == 2) this->draw_ModoDiferido(color_pintar);
   }

   if (lineas){
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      color_pintar = "lineas";
      if(modo_dibujado == 1) this->draw_ModoInmediato(color_pintar);
      else if(modo_dibujado == 2) this->draw_ModoDiferido(color_pintar);
   }

   if (solido){
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      color_pintar = "solido";
      if(modo_dibujado == 1) this->draw_ModoInmediato(color_pintar);
      else if(modo_dibujado == 2) this->draw_ModoDiferido(color_pintar);
   }
   
   if(!puntos && !lineas && !solido && ajedrez){
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      if(modo_dibujado == 1) this->draw_ModoAjedrezInmediato();
      else if(modo_dibujado == 2) this->draw_ModoAjedrezDiferido();
      
   } 
}

void Malla3D::inicializarColores(){
   // establecemos el tamaño de cada tabla de color según el número de vértices
   c_inm.resize(v.size());
   c_dif.resize(v.size());
   c_line.resize(v.size());
   c_point.resize(v.size());

   // asignamos los valores a cada tabla
   for(int i=0; i<v.size(); i++){
      c_inm[i] = {1.0, 0.5, 0.0};
      c_dif[i] = {1.0, 0.0, 1.0};
      c_line[i] = {0.0, 0.0, 0.0};
      c_point[i] = {0.0, 1.0, 1.0};
   }
}

void Malla3D::calcular_normales(){
   Tupla3f p, q, r,        // vertices
           a, b, m, n;        // vectores
   float prod_esc;

   nc.clear();
   // recorremos el vector de caras para ir haciendo las normales
   // de cada una e ir almacenandolas dentro de la tupla nc
   for(int i=0; i<f.size(); i++){
      // obtenemos los vértices de la cara
      p = v[f[i][0]];
      q = v[f[i][1]];
      r = v[f[i][2]];

      // obtenemos los vectores a y b a partir de los vertices
      a = q - p;
      b = r - p;

      // obtenemos el vector m haciendo el producto vectorial de a y b
      // m[0] = a[1]*b[2] - a[2]*b[1];
      // m[1] = a[0]*b[2] - a[2]*b[0];
      // m[2] = a[0]*b[1] - a[1]*b[0];
      // usar dot¿?¿¿?¿?¿?¿?
      m = a.cross(b);

      // finalmente, obtenemos el vector normal de la cara y lo
      // almacenammos dentro del vector de normales nc
      prod_esc = sqrt(pow(m[0],2) + pow(m[1],2) + pow(m[2],2));
      for(int i=0; i<3; i++) n[i] = m[i] / prod_esc;
      
      // una vez calculado el vector normal, lo almacenamos
      nc.push_back(n);
   }

   nv.clear();
   nv.resize(v.size());
   // recorremos el vector de vertices para ir haciendo las normales
   // de cada uno e ir almacenandolas dentro de la tupla nv
   for(int i=0; i<f.size(); i++){
      nv[f[i][0]] = nv[f[i][0]] + nc[i];
      nv[f[i][1]] = nv[f[i][1]] + nc[i];
      nv[f[i][2]] = nv[f[i][2]] + nc[i];
   }

   // normalizamos cada uno de los vectores;
   for(int i=0; i<nv.size(); i++){
      prod_esc = sqrt(pow(nv[i][0],2) + pow(nv[i][1],2) + pow(nv[i][2],2));
      nv[i][0] = nv[i][0] / prod_esc;
      nv[i][1] = nv[i][1] / prod_esc;
      nv[i][2] = nv[i][2] / prod_esc;
   } 
   // for(int i=0; i<nv.size(); i++) nv[i] = nv[i].normalized();

   // std::cout << "X: " << nv[0][0] << " Y: " << nv[0][1] << " Z: " << nv[0][2] << std::endl;
}

void Malla3D::setMaterial(Material mat){
   m = new Material(mat);
}
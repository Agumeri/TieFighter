#include "aux.h"
#include "objrevolucion.h"
#include "math.h"
#include "esfera.h"


Esfera::Esfera(int num_vert_perfil, int num_instancias_perf, float r, bool tsup, bool tinf){
    // establecemos el valor del radio
    this->radio = r;

    // creamos un vector de tuplas3f auxiliar para pasarlo como tabla de vertices
    std::vector<Tupla3f> tabla_vertices_aux;

    // Pasamos a crear los vertices del perfil. Como lo hemos orientado para que el objeto se cree de 
    // abajo hacia arriba, primero pondremos el vertice inferior, luego el resto de vertices
    // hasta llegar al último, el vértice superior (todo mediante un for)
    float x, y;

    for(int i=1; i<num_vert_perfil; i++){
        x = sin(2.0*i*M_PI/num_instancias_perf)*radio;
        y = cos(2.0*i*M_PI/num_instancias_perf)*radio;
        tabla_vertices_aux.push_back( {x,-y,0.0} ); 
    }


    // crear malla del cono
    crearMalla(tabla_vertices_aux,num_instancias_perf,tsup,tinf);
}
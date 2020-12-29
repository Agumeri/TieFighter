#include "aux.h"
#include "objrevolucion.h"
#include "cilindro.h"

Cilindro::Cilindro(int num_vert_perfil, int num_instancias_perf, float h, float r, bool tsup, bool tinf){
    // establecemos el valor de altura y radio
    this->altura = h;
    this->radio = r;

    // creamos un vector de tuplas3f auxiliar para pasarlo como tabla de vertices
    std::vector<Tupla3f> tabla_vertices_aux;

    // introducimos dos vertices en el vector, uno para asignar la altura y el otro para el radio
    tabla_vertices_aux.push_back( {radio,-altura/2,0.0} );
    tabla_vertices_aux.push_back( {radio,altura/2,0.0} );

    

    // crear malla del cono
    crearMalla(tabla_vertices_aux,num_instancias_perf,tsup,tinf);

}
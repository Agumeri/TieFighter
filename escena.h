#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "malla.h"
#include "objply.h"
#include "objrevolucion.h"
#include "cubo.h"
#include "tetraedro.h"
#include "cono.h"
#include "cilindro.h"
#include "esfera.h"
#include "luz.h"
#include "luzposicional.h"
#include "luzdireccional.h"
#include "material.h"
#include "aleron.h"
#include "conector_superior.h"
#include "conector_inferior.h"
#include "ala.h"
#include "tiefighter.h"

typedef enum {NADA, SELOBJETO,SELVISUALIZACION,SELDIBUJADO, TAPASEJECUCION, ANIMACION, MODGRADOS} menu;
typedef enum {VACIO, CUBO, TETRAEDRO, OBJPLY, PEON, LATA, BETH, CONO, CILINDRO, ESFERA, OBJSIMULTANEOS, TIEFIGHTER} objetos;
typedef enum {INMEDIATO, DIFERIDO} dibujado;
typedef enum {DEFAULT, PUNTOS, LINEAS, SOLIDO, AJEDREZ, ILUMINACION} visualizado;

class Escena
{

   private:
 // ** PARÁMETROS DE LA CÁMARA (PROVISIONAL)
       
       // variables que definen la posicion de la camara en coordenadas polares
   GLfloat Observer_distance;
   GLfloat Observer_angle_x;
   GLfloat Observer_angle_y;

   // variables que controlan la ventana y la transformacion de perspectiva
   GLfloat Width, Height, Front_plane, Back_plane;

    // Transformación de cámara
	void change_projection( const float ratio_xy );
	void change_observer();
    


   void clear_window();

   // inicialización de los enum
   menu modoMenu=NADA;
   objetos obj=VACIO;
   dibujado tipo_dibujo=INMEDIATO;
   visualizado tipo_visual=SOLIDO;

   
   // Objetos de la escena
   Ejes ejes;
   Cubo * cubo = nullptr ; // es importante inicializarlo a 'nullptr'
   Tetraedro * tetraedro = nullptr ; // es importante inicializarlo a 'nullptr'
   // objetos PLY
    ObjPLY * obj_ply = nullptr; // creamos un objeto para poder dibujar los objetos ply
    ObjPLY * beethoven = nullptr;
   //
   ObjRevolucion * peon = nullptr;
   ObjRevolucion * lata_inf = nullptr;
   ObjRevolucion * lata_sup = nullptr;
   ObjRevolucion * lata_cue = nullptr;

   ObjRevolucion * peon_silver = nullptr;
   ObjRevolucion * peon_goma_negra = nullptr;

   Cono * cono = nullptr;
   Cilindro * cilindro = nullptr;
   Esfera * esfera = nullptr;
   Esfera * esfera_aux = nullptr;

   // objetos del modelo jerárquico
    Aleron * aleron = nullptr;
    ConectorSuperior * conec_sup = nullptr;
    ConectorInferior * conec_inf = nullptr;
    Ala * ala = nullptr;
    TieFighter * tiefighter = nullptr;
   //

   // luces
   LuzPosicional * luz_p = nullptr;
   LuzDireccional * luz_d = nullptr;
   LuzDireccional * luz_d2 = nullptr;

    //Array para comprobar que modos de visualizacion esta activado
    bool modo_visual[5] = {false,false,true,false,false}; // puntos, lineas, solido, ajedrez, iluminado

    // Booleanos para las tapas
    bool tapas = true;
    bool pos_activada = false;
    bool direc_activada = false;
    bool alfa = false;
    bool beta = false;

    // Booleanos para los grados de libertad
    bool animacion_activada = false;

    bool grado_uno = false,
         grado_dos = false,
         grado_tres = false;

    
   public:

    Escena();
	void inicializar( int UI_window_width, int UI_window_height );
	void redimensionar( int newWidth, int newHeight ) ;

	// Dibujar
	void dibujar() ;

	// Interacción con la escena
	bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
	void teclaEspecial( int Tecla1, int x, int y );
    
    void animarModeloJerarquico();
};
#endif

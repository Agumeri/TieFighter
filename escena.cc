#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "material.h"
#include "malla.h" // objetos: Cubo y otros....

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena()
{
   glEnable(GL_NORMALIZE);

   Front_plane       = 50.0;
   Back_plane        = 2000.0;
   Observer_distance = 2*Front_plane;
   Observer_angle_x  = 5.0 ;
   Observer_angle_y  = -10.0 ;
   ejes.changeAxisSize( 5000 );

   // iluminacion
      // colores de la luz
      Tupla4f colAmb(1.0,1.0,1.0,1.0),
              colEspc(1.0,1.0,1.0,1.0),
              colDif(1.0,1.0,1.0,1.0);
      //
      Tupla3f pos_luz(50,50,0);  // posicion de la luz
      Tupla2f dir_luz(0,0); // direccion de la luz
      luz_p = new LuzPosicional(pos_luz,GL_LIGHT1,colAmb,colEspc,colDif);
      luz_d = new LuzDireccional(dir_luz,GL_LIGHT2,colAmb,colEspc,colDif);
   
   
   //

   // Materiales
      // dependiendo del tipo de luz
      Tupla4f silver_ambiente(0.19225,0.19225,0.19225,1.0),
              silver_difuso(0.50754,0.50754,0.50754,1.0),
              silver_especular(0.508273,0.508273,0.508273,1.0);
      
      Tupla4f ruby_ambiente(0.1745,0.01175,0.1175,1.0),
              ruby_difuso(0.61424,0.04136,0.04136,1.0),
              ruby_especular(0.727811,0.626959,0.626959,1.0);

      Tupla4f bronze_ambiente(0.2125,0.1275,0.054,1.0),
              bronze_difuso(0.714,0.4284,0.18144,1.0),
              bronze_especular(0.393548,0.271906,0.166721,1.0);
      
      Tupla4f goma_negra_ambiente(0.02,0.02,0.02,1.0),
              goma_negra_difuso(0.01,0.01,0.01,1.0),
              goma_negra_especular(0.4,0.4,0.4,1.0);
      //

      // creamos los materiales a usar
      Material silver = Material(silver_difuso,silver_especular,silver_ambiente,0.5 * 128.0);
      Material ruby = Material(ruby_difuso,ruby_especular,ruby_ambiente,0.5*128.0);
      Material bronze = Material(bronze_difuso,bronze_especular,bronze_ambiente,1.0*128.0);
      Material goma_negra = Material(goma_negra_difuso,goma_negra_especular,goma_negra_ambiente,1.0*128.0);
      //
   //

   // crear los objetos de la escena....
   // .......COMPLETAR: ...
   // ..... CREAR DATOS, NO LA ESTRUCTURA DE LA ESCENA.

   // creados "a mano"
      cubo = new Cubo();
      tetraedro = new Tetraedro();
   //

   // objetos de revolución
      cono = new Cono(2,20,80,40,true,false);
      esfera = new Esfera(10,20,40,true,true);
      esfera_aux = new Esfera(10,20,10,true,true);
      cilindro = new Cilindro(2,20,40,20,true,true);
   
      // objetos que cargan archivos ply
      obj_ply = new ObjPLY("plys/big_dodge.ply");  // Este objeto sirve para cargar los 3 primeros archivos
      beethoven = new ObjPLY("plys/beethoven.ply");
      peon = new ObjRevolucion("plys/peon.ply",10,true,true); 
      lata_cue = new ObjRevolucion("plys/lata-pcue.ply",10,true,true);
      lata_inf = new ObjRevolucion("plys/lata-pinf.ply",10,true,true);
      lata_sup = new ObjRevolucion("plys/lata-psup.ply",10,true,true);

      peon_silver = new ObjRevolucion("plys/peon.ply",10,true,true); 
      peon_goma_negra = new ObjRevolucion("plys/peon.ply",10,true,true);  
      //
   //

   // objetos del modelo jerárquico
      aleron = new Aleron();
      conec_sup = new ConectorSuperior();
      conec_inf = new ConectorInferior();
      ala = new Ala();
      tiefighter = new TieFighter();
   //

   // asignamos los materiales a los objetos
      cubo->setMaterial(bronze);
      tetraedro->setMaterial(silver);
      cono->setMaterial(silver);
      esfera->setMaterial(bronze);
      cilindro->setMaterial(ruby);
      obj_ply->setMaterial(silver);
      peon->setMaterial(ruby);
      lata_cue->setMaterial(silver);
      lata_inf->setMaterial(silver);
      lata_sup->setMaterial(silver);
      beethoven->setMaterial(ruby);

      peon_silver->setMaterial(silver);
      peon_goma_negra->setMaterial(ruby);

      esfera_aux->setMaterial(ruby);
   //

}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar( int UI_window_width, int UI_window_height )
{
	glClearColor( 1.0, 1.0, 1.0, 1.0 );// se indica cual sera el color para limpiar la ventana	(r,v,a,al)

	glEnable( GL_DEPTH_TEST );	// se habilita el z-bufer

	Width  = UI_window_width/10;
	Height = UI_window_height/10;

   change_projection( float(UI_window_width)/float(UI_window_height) );
	glViewport( 0, 0, UI_window_width, UI_window_height );
}



// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::dibujar()
{
   // creamos un entero que pasaremos a draw para indicar el modo de dibujado
   int modo_dibujado = 0;

   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla

	change_observer();
   
   // Desactivamos la iluminacion para que se vean los ejes
   if(glIsEnabled(GL_LIGHTING)) glDisable(GL_LIGHTING);

   ejes.draw();

   // si el booleano de luz esta activaddo, activamos luz
   if(modo_visual[4]){
      glEnable(GL_LIGHTING);

      // glShadeModel(GL_SMOOTH);
      glShadeModel(GL_FLAT);

      if (pos_activada)
      {
         // glEnable(GL_LIGHT1);
         this->luz_p->activar();
      }
      else
      {
         glDisable(GL_LIGHT1);
      }

      if (direc_activada)
      {
         // glEnable(GL_LIGHT2);
         this->luz_d->activar();
      }
      else
      {
         glDisable(GL_LIGHT2);
      }
   }

   // seleccion del modo de dibujado
   if(tipo_dibujo==INMEDIATO) modo_dibujado = 1;
   
   if(tipo_dibujo==DIFERIDO) modo_dibujado = 2;



   // Seleccion del objeto a dibujar
   if(obj == TIEFIGHTER){
      // aleron
      // aleron->draw(modo_dibujado, modo_visual[0], modo_visual[1], modo_visual[2], modo_visual[3]);

      // conector_superior
      // conec_sup->dibuja(modo_dibujado, modo_visual[0], modo_visual[1], modo_visual[2], modo_visual[3]);
   
      // conector_inferior
      // conec_inf->dibuja(modo_dibujado, modo_visual[0], modo_visual[1], modo_visual[2], modo_visual[3]);
   
      // ala (por defecto es la derecha)
      // ala->dibuja(modo_dibujado, modo_visual[0], modo_visual[1], modo_visual[2], modo_visual[3]);

      // TieFighter (ambas alas y cabina (una esfera))
      tiefighter->dibuja(modo_dibujado, modo_visual[0], modo_visual[1], modo_visual[2], modo_visual[3]);
   
   }


   if(obj == CUBO){
      glMatrixMode(GL_MODELVIEW);
      glPushMatrix();
         cubo->draw(modo_dibujado, modo_visual[0], modo_visual[1], modo_visual[2], modo_visual[3]);
      glPopMatrix();
   } 

   if(obj == TETRAEDRO){  
      tetraedro->draw(modo_dibujado, modo_visual[0], modo_visual[1], modo_visual[2], modo_visual[3]);
   } 
   
   //Distintos casos segun el objeto PLY
   if(obj == OBJPLY) {
      glScalef(5,5,5);
      beethoven->draw(modo_dibujado, modo_visual[0], modo_visual[1], modo_visual[2], modo_visual[3]);
   }

   if(obj == PEON) {
      glScalef(40,40,40);
      peon->VerTapas(tapas);
      peon->draw(modo_dibujado, modo_visual[0], modo_visual[1], modo_visual[2], modo_visual[3]);
   }
   
   if(obj == CONO){
      cono->VerTapas(tapas);
      cono->draw(modo_dibujado, modo_visual[0], modo_visual[1], modo_visual[2], modo_visual[3]);
   }

   if(obj == CILINDRO){
      cilindro->VerTapas(tapas);
      cilindro->draw(modo_dibujado, modo_visual[0], modo_visual[1], modo_visual[2], modo_visual[3]);

   }

   if(obj == ESFERA){
      esfera->VerTapas(tapas);
      esfera->draw(modo_dibujado, modo_visual[0], modo_visual[1], modo_visual[2], modo_visual[3]);

   }

   // Se van a imprimir 5 figuras: cubo tetraedro cono cilindro y esfera
   if(obj == OBJSIMULTANEOS){
      glMatrixMode(GL_MODELVIEW);

      // esfera de la luz (BOMBILLA)
      glPushMatrix();
         glTranslatef(50,50,0);
         esfera_aux->VerTapas(tapas);
         esfera_aux->draw(modo_dibujado, modo_visual[0], modo_visual[1], modo_visual[2], modo_visual[3]);
      glPopMatrix();


      // peon1
      glPushMatrix();
         glTranslatef(-50,0,0);
         glScalef(10,10,10);
         peon_silver->VerTapas(tapas);
         peon_silver->draw(modo_dibujado, modo_visual[0], modo_visual[1], modo_visual[2], modo_visual[3]);
      glPopMatrix();
      //

      // peon2
      glPushMatrix();
         glTranslatef(50,0,0);
         glScalef(10,10,10);
         peon_goma_negra->VerTapas(tapas);
         peon_goma_negra->draw(modo_dibujado, modo_visual[0], modo_visual[1], modo_visual[2], modo_visual[3]);
      glPopMatrix();
      //

      // // cubo
      // glPushMatrix();
      //    glTranslatef(0,0,50);
      //    cubo->draw(modo_dibujado, modo_visual[0], modo_visual[1], modo_visual[2], modo_visual[3]);
      // glPopMatrix();

   }
}
//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

bool Escena::teclaPulsada( unsigned char tecla, int x, int y )
{
   using namespace std ;
   // cout << "Tecla pulsada: '" << tecla << "'" << endl;
   bool salir=false;
   switch( toupper(tecla) )
   {
      case 'Q' :
         if (modoMenu!=NADA){
            modoMenu=NADA;
            printf("\nSelecciona un modo de los disponibles:\n");
            printf("'O': Seleccion de objeto\n");
            printf("'V': Seleccion de modo de visualización\n");
            printf("'D': Seleccion de dibujado\n");
            printf("'Z': Seleccionar tapas a dibujar\n");
            printf("'A': Activar/Desactivar animación modelo jerárquico\n");
            printf("'E': Mover manualmente el grado de libertad de los objetos jerárquicos\n");
            printf("'Q': Salir del programa\n");       
         }else {
            salir=true ;
         }
         break ;
      case 'O' :
         // ESTAMOS EN MODO SELECCION DE OBJETO
         modoMenu=SELOBJETO; 
         printf("Opciones disponibles: \n'C': Cubo \n'T': Tetraedro \n'Y': ObjetoPLY \n'H': Peon \n'W': TieFighter \n'B': Cilindro \n'N': Esfera \n'M': OBJETOS SIMULTANEOS \n");
         break ;
        case 'V' :
         // ESTAMOS EN MODO SELECCION DE MODO DE VISUALIZACION
         printf("Opciones disponibles: \n'L': Linea; \n'P': Puntos \n'S': Solido\n'M': Ajedrez\n'I': Iluminacion\n");
         modoMenu=SELVISUALIZACION;
         break ;
       case 'D' :
         // ESTAMOS EN MODO SELECCION DE DIBUJADO
         printf("Opciones disponibles: \n'1': Modo inmediato; \n'2': Modo diferido\n");
         modoMenu=SELDIBUJADO;
         break ;
       case 'Z' :
         printf("Opciones disponibles: \n'8': Activar/Desactivar tapas\n");
         modoMenu=TAPASEJECUCION;
         break ;

       case 'A' :
         printf("Opciones disponibles: \n'+': Aumentar velocidad\n'-': Disminuir velocidad\n");
            if (!animacion_activada )
            {
               printf("Animación activada.\n");
               animacion_activada = true;
            }
            else
            {
               printf("Animación desactivada.\n");
               animacion_activada = false;
            }
         break ;

       case 'E' :
         printf("Opciones disponibles: \n'F': Posicion por defecto\n'5': Posicion Velocidad\n'6': Posicion Ataque\n'7': Posicion salto Espacio-Tiempo\n");
         modoMenu=ANIMACION;;
         break ;
         // COMPLETAR con los diferentes opciones de teclado
      

      // MENUS DE LAS FIGURAS SELECCIONADAS
         //CUBO
         case 'C':
         // ESTAMOS EN MODO CUBO SELECCIONADO
         if(modoMenu==SELOBJETO){
            if(obj != CUBO){
               printf("Cubo seleccionado.\n");
               obj=CUBO;
            }else{
               printf("Ocultando cubo\n");
               obj=VACIO;
            }
         }
         break;

         //-------------------------------------------------
         //TETRAEDRO
         case 'T':
         // ESTAMOS EN MODO Tetraedro SELECCIONADO
         if(modoMenu==SELOBJETO){
            if(obj != TETRAEDRO){
               printf("Tetraedro seleccionado.\n");
               obj=TETRAEDRO;
            }else{
               printf("Ocultando Tetraedro\n");
               obj=VACIO;
            }
         }
         break;

         //-------------------------------------------------
         //OBJETO PLY
         case 'Y':
         // ESTAMOS EN MODO Tetraedro SELECCIONADO
         if(modoMenu==SELOBJETO){
            if(obj != OBJPLY){
               printf("Objeto PLY seleccionado.\n");
               obj=OBJPLY;
            }else{
               printf("Ocultando objeto PLY\n");
               obj=VACIO;
            }
         }
         break;

         //-------------------------------------------------
         //OBJETO PLY "PEON"
         case 'H':
         // ESTAMOS EN MODO Tetraedro SELECCIONADO
         if(modoMenu==SELOBJETO){
            if(obj != PEON){
               printf("Objeto PLY 'PEON' seleccionado.\n");
               obj=PEON;
            }else{
               printf("Ocultando objeto PLY 'PEON'\n");
               obj=VACIO;
            }
         }
         break;

         //-------------------------------------------------
         //OBJETO JERARQUICO "TieFighter"
         case 'W':
         if(modoMenu==SELOBJETO){
            if(obj != TIEFIGHTER){
               printf("Objeto TIE FIGHTER seleccionado.\n");
               obj=TIEFIGHTER;
            }else{
               printf("Ocultando objeto TIE FIGHTER\n");
               obj=VACIO;
            }
         }
         break;

         //-------------------------------------------------
         //OBJETO REVOLUCIÓN "CONO"
         // case 'J':
         // // ESTAMOS EN MODO Tetraedro SELECCIONADO
         // if(modoMenu==SELOBJETO){
         //    if(obj != CONO){
         //       printf("Cono seleccionado.\n");
         //       obj=CONO;
         //    }else{
         //       printf("Ocultando cono\n");
         //       obj=VACIO;
         //    }
         // }
         // break;

         //-------------------------------------------------
         //OBJETO REVOLUCIÓN "CILINDRO"
         case 'B':
         // ESTAMOS EN MODO Tetraedro SELECCIONADO
         if(modoMenu==SELOBJETO){
            if(obj != CILINDRO){
               printf("Cilindro seleccionado.\n");
               obj=CILINDRO;
            }else{
               printf("Ocultando Cilindro\n");
               obj=VACIO;
            }
         }
         break;

         //-------------------------------------------------
         //OBJETO REVOLUCIÓN "ESFERA"
         case 'N':
         // ESTAMOS EN MODO Tetraedro SELECCIONADO
         if(modoMenu==SELOBJETO){
            if(obj != ESFERA){
               printf("Esfera seleccionado.\n");
               obj=ESFERA;
            }else{
               printf("Ocultando Esfera\n");
               obj=VACIO;
            }
         }
         break;

         //-------------------------------------------------
         //OBJETOs SIMULTANEOS EN LA ESCENA
         case 'M':
         // ESTAMOS EN MODO Tetraedro SELECCIONADO
         if(modoMenu==SELOBJETO){
            if(obj != OBJSIMULTANEOS){
               printf("Objetos simultaneos en la escena seleccionado.\n");
               obj=OBJSIMULTANEOS;
            }else{
               printf("Ocultando objetos simultaneos\n");
               obj=VACIO;
            }
         }
         break;
      //*********************************************************************

      // MENU DEL MODO DE DIBUJADO
         // INMEDIATO
         case '1':
            if (modoMenu == SELDIBUJADO)
            {
               if (tipo_dibujo != INMEDIATO)
               {
                  printf("Modo de dibujado INMEDIATO seleccionado.\n");
                  tipo_dibujo = INMEDIATO;
               } else {
                  printf("El modo de dibujado actual es el INMEDIATO.\n");
               }
            }
         break;

         // DIFERIDO
         case '2':
            if (modoMenu == SELDIBUJADO)
            {
               if (tipo_dibujo != DIFERIDO)
               {
                  printf("Modo de dibujado DIFERIDO seleccionado.\n");
                  tipo_dibujo = DIFERIDO;
               } else {
                  printf("El modo de dibujado actual es el DIFERIDO.\n");
               }
            }
         break;
      //**************************************************************************

      // MENU DEL MODO DE VISUALIZACION
         // PUNTOS
         case 'P':
            if (modoMenu == SELVISUALIZACION)
            {
               if (tipo_visual != PUNTOS && !modo_visual[4] && !modo_visual[0])
               {
                  printf("Visualizacion en modo PUNTOS activada.\n");
                  tipo_visual = PUNTOS;
                  modo_visual[0] = true;
                  modo_visual[4] = false;
                  break;
               }
               else
               {
                  printf("Visualizacion en modo PUNTOS desactivada.\n");
                  tipo_visual = DEFAULT;
                  modo_visual[0] = false;
               }
            }
         break;

         // LINEAS
         case 'L':
            if (modoMenu == SELVISUALIZACION)
            {
               if (tipo_visual != LINEAS && !modo_visual[4] && !modo_visual[1])
               {
                  printf("Visualizacion en modo LINEAS activada.\n");
                  tipo_visual = LINEAS;
                  modo_visual[1] = true;
                  modo_visual[4] = false;
                  break;
               }
               else
               {
                  printf("Visualizacion en modo LINEAS desactivada.\n");
                  tipo_visual = DEFAULT;
                  modo_visual[1] = false;
               }
            }
         break;

         // SOLIDO
         case 'S':
            if (modoMenu == SELVISUALIZACION)
            {
               if (tipo_visual != SOLIDO && !modo_visual[4] && !modo_visual[2])
               {
                  printf("Visualizacion en modo SOLIDO activada.\n");
                  tipo_visual = SOLIDO;
                  modo_visual[2] = true;
                  modo_visual[4] = false;
                  break;
               }
               else
               {
                  printf("Visualizacion en modo SOLIDO desactivada.\n");
                  tipo_visual = DEFAULT;
                  modo_visual[2] = false;
               }
            }
         break;


         // // // AJEDREZ
         // case 'M':
         //    if (modoMenu == SELVISUALIZACION)
         //    {
         //       if (tipo_visual != AJEDREZ && !modo_visual[4] && !modo_visual[3])
         //       {
         //          printf("Visualizacion en modo AJEDREZ activada.\n");
         //          tipo_visual = AJEDREZ;
         //          modo_visual[3] = true;
         //          modo_visual[4] = false;
         //          break;
         //       }
         //       else
         //       {
         //          printf("Visualizacion en modo AJEDREZ desactivada.\n");
         //          tipo_visual = DEFAULT;
         //          modo_visual[3] = false;
         //       }
         //    }
         // break;

         // ILUMINADO
         case 'I':
            if (modoMenu == SELVISUALIZACION)
            {
               if (tipo_visual != ILUMINACION && !modo_visual[4])
               {
                  printf("Visualizacion en modo ILUMINADO activada.\n");
                  printf("Opciones disponibles: \n'0': Luz posicional; \n'4': Luz diferida\n'X': Activar variacion angulo alfa\n'K': Activar variacion angulo beta\n'>': Incrementar angulo\n'<' Decrementar angulo\n");
                  tipo_visual = ILUMINACION;
                  modo_visual[4] = true;
                  break;
               }
               else
               {
                  printf("Visualizacion en modo ILUMINADO desactivada.\n");
                  tipo_visual = DEFAULT;
                  modo_visual[4] = false;
               }
            }
         break;

         case '0':
            if (modoMenu == SELVISUALIZACION)
            {
               if (tipo_visual == ILUMINACION && modo_visual[4] && !pos_activada)
               {
                  printf("Luz posicional activada\n");
                  // this->luz_p->activar();
                  pos_activada = true;
                  direc_activada = false;
               }
               else
               {
                  printf("Luz posicional desactivada\n");
                  // glDisable(GL_LIGHT1);
                  pos_activada = false;
               }
            }
         break;

         case '4':
            if (modoMenu == SELVISUALIZACION)
            {
               if (tipo_visual == ILUMINACION && modo_visual[4] && !direc_activada)
               {
                  printf("Luz posicional activada\n");
                  // this->luz_d->activar();
                  direc_activada = true;
                  pos_activada = false;
               }
               else
               {
                  printf("Luz posicional desactivada\n");
                  // glDisable(GL_LIGHT2);
                  direc_activada = false;
               }
            }
         break;

         case 'X':
            if (modoMenu == SELVISUALIZACION)
            {
               if (tipo_visual == ILUMINACION && modo_visual[4] && direc_activada && !alfa)
               {
                  printf("ACTIVADA VARIACION ANGULO ALFA\n");
                  alfa = true;
                  beta = false;
               }
               else
               {
                  printf("DESACTIVADA VARIACION ANGULO ALFA\n");
                  alfa = false;
               }
            }
         break;

         case 'K':
            if (modoMenu == SELVISUALIZACION)
            {
               if (tipo_visual == ILUMINACION && modo_visual[4] && direc_activada && !beta)
               {
                  printf("ACTIVADA VARIACION ANGULO BETA\n");
                  beta = true;
                  alfa = false;
               }
               else
               {
                  printf("DESACTIVADA VARIACION ANGULO BETA\n");
                  beta = false;
               }
            }
         break;

         case '>':
            if (modoMenu == SELVISUALIZACION)
            {
               if (tipo_visual == ILUMINACION && modo_visual[4] && direc_activada)
               {
                  printf("Incrementando angulo\n");
                  if(alfa) this->luz_d->variarAnguloAlpha(10);
                  else if(beta) this->luz_d->variarAnguloBeta(10);
               }
            }
         break;

         case '<':
            if (modoMenu == SELVISUALIZACION)
            {
               if (tipo_visual == ILUMINACION && modo_visual[4] && direc_activada)
               {
                  printf("Decrementar angulo\n");
                  if(alfa) this->luz_d->variarAnguloAlpha(-10);
                  else if(beta) this->luz_d->variarAnguloBeta(-10);
               }
            }
         break;

         
      //**************************************************************************

      // MENU DEL MODO DE VISUALIZACIÓN DE TAPAS
         case '8':
            if (modoMenu == TAPASEJECUCION)
            {
               if (tapas)
               {
                  printf("Tapas del objeto desactivadas.\n");
                  tapas = false;
               } else {
                  printf("Tapas del objeto activadas. \n");
                  tapas = true;
               }
            }
         break;
      //**************************************************************************

      
      // // ACTIVAR/DESACTIVAR ANIMACION
      // case 'A':
      //    if (modoMenu == ANIMACION)
      //    {

      //       if (!animacion_activada )
      //       {
      //          printf("Animación activada.\n");
      //          animacion_activada = true;
      //       }
      //       else
      //       {
      //          printf("Animación desactivada.\n");
      //          animacion_activada = false;
      //       }
      //    }
      //    else
      //    {
      //       modoMenu = NADA;
      //    }
      // break;

      case 'F':
         if(modoMenu == ANIMACION)
         {
            animacion_activada = false;
            tiefighter->IdlePosition();
            // if(!grado_uno)
            // {
            //    printf("Grado uno activado.\n");
            //    grado_uno = true;
            // } 
            // else
            // {
            //    printf("Grado uno desactivado.\n");
            //    grado_uno = false;
            // } 

         }
      break;

      case '5':
         if(modoMenu == ANIMACION)
         {
            animacion_activada = false;
            tiefighter->posicionVelocidad(5);
            // if(!grado_uno)
            // {
            //    printf("Grado uno activado.\n");
            //    grado_uno = true;
            // } 
            // else
            // {
            //    printf("Grado uno desactivado.\n");
            //    grado_uno = false;
            // } 

         }
      break;

      case '6':
         if(modoMenu == ANIMACION)
         {
            animacion_activada = false;
            tiefighter->posicionAtaque(1);
            // if(!grado_dos)
            // {
            //    printf("Grado dos activado.\n");
            //    grado_dos = true;
            // } 
            // else
            // {
            //    printf("Grado dos desactivado.\n");
            //    grado_dos = false;
            // }
         }
      break;

      case '7':
         if(modoMenu == ANIMACION)
         {
            animacion_activada = false;
            tiefighter->posicionSaltoET(5);
            // if(!grado_tres)
            // {
            //    printf("Grado tres activado.\n");
            //    grado_tres = true;
            // } 
            // else
            // {
            //    printf("Grado tres desactivado.\n");
            //    grado_tres = false;
            // } 
         }
      break;
      //**************************************************************************
   }
   


   return salir;
}
//**************************************************************************

void Escena::teclaEspecial( int Tecla1, int x, int y )
{
   switch ( Tecla1 )
   {
	   case GLUT_KEY_LEFT:
         Observer_angle_y-- ;
         break;
	   case GLUT_KEY_RIGHT:
         Observer_angle_y++ ;
         break;
	   case GLUT_KEY_UP:
         Observer_angle_x-- ;
         break;
	   case GLUT_KEY_DOWN:
         Observer_angle_x++ ;
         break;
	   case GLUT_KEY_PAGE_UP:
         Observer_distance *=1.2 ;
         break;
	   case GLUT_KEY_PAGE_DOWN:
         Observer_distance /= 1.2 ;
         break;
	}

	//std::cout << Observer_distance << std::endl;
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

void Escena::change_projection( const float ratio_xy )
{
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   const float wx = float(Height)*ratio_xy ;
   glFrustum( -wx, wx, -Height, Height, Front_plane, Back_plane );
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
   Width  = newWidth/10;
   Height = newHeight/10;
   change_projection( float(newHeight)/float(newWidth) );
   glViewport( 0, 0, newWidth, newHeight );
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer()
{
   // posicion del observador
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef( 0.0, 0.0, -Observer_distance );
   glRotatef( Observer_angle_y, 0.0 ,1.0, 0.0 );
   glRotatef( Observer_angle_x, 1.0, 0.0, 0.0 );
}

void Escena::animarModeloJerarquico() {
   if(animacion_activada){
      tiefighter->posicionVelocidad(0.005);
      tiefighter->posicionAtaque(0.005);
      tiefighter->posicionSaltoET(0.005);
   }
}

// void Escena::animarGradosLibertad() {
//    if(!animacion_activada){
//       if(grado_uno) tiefighter->posicionVelocidad(0.005);
//       if(grado_dos) tiefighter->posicionAtaque(0.005);
//       if(grado_tres) tiefighter->posicionSaltoET();
//    }
// }
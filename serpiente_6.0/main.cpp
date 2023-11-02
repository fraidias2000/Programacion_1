#include <iostream>
#include "terminal.h"
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

const int RETARDO_TECLA = 20;
const char ESQUINA = '+';
const char HORIZONTAL = '-';
const char VERTICAL = '|';
const char INTERIOR = ' ';
const int RETARDO_JUEGO = 200;
const char LIMITE_CUADRO = 0;
const char ARRIBA = 'Q';
const char ABAJO = 'A';
const char IZQUIERDA = 'O';
const char DERECHA = 'P';
const char FIN = 'F';
const char CABEZA_SERPIENTE = '@';
const int MOVER_ABAJO = 1 ;
const int MOVER_ARRIBA = 2;
const int MOVER_DERECHA = 3;
const int MOVER_IZQUIERDA = 4;
const int BASE = 45;
const int ALTURA = 20;
const int LONGITUD_SERPIENTE = 30;

struct posicion{
    int fila,columna;
    };
struct serpiente{
    posicion cabeza;
    posicion cuerpo[LONGITUD_SERPIENTE];
    };

void pantalla_bienvenida();
void dibujar_tablero(const int base,const int altura);
void crear_presa(int &f, int &c);
bool presa_capturada(int fila_serpiente, int columna_serpiente,
                     int fila_presa, int columna_presa);
void pintar_serpiente();
void mover_serpiente( char &tecla, int &direccion, int longitud,
                      serpiente la_serpiente);
void actualizar_posicion( int &fila_serpoente , int &columna_serpiente,
                          int direccion,  serpiente &la_serpiente);
void pintar_pantalla_despedida();
bool finalizado(const int columna,
                const int fila, const char tecla);


int main(void)
{
   int fila_serpiente = 10;
   int columna_serpiente = 5;
   int x_cuerpo = 9;
   int y_cuerpo = 5;
   int fila_presa = 0;
   int columna_presa = 0;
   char tecla = '\0';
   int direccion = MOVER_DERECHA;
   int puntuacion = 0;
   int longitud = 2;
   serpiente la_serpiente = { {15, 10}, { {14, 10}, {13, 10} , {12, 10}, {12, 9}, {12, 8}, {13, 8}, {14, 8},
                          {15, 8} }};
   srand(time(NULL));

   habilitar_modo_crudo_terminal();
   cursor_visible(false);
   pantalla_bienvenida();
   borrar_terminal();
   dibujar_tablero(BASE, ALTURA);
   crear_presa(fila_presa, columna_presa);

   while( ! finalizado(fila_serpiente, columna_serpiente, tecla)){
            mover_serpiente(tecla, direccion, longitud, la_serpiente);
            actualizar_posicion(fila_serpiente, columna_serpiente, direccion,  la_serpiente);

        if(presa_capturada(fila_serpiente, columna_serpiente, fila_presa, columna_presa)){
            crear_presa( fila_presa , columna_presa);

            puntuacion = puntuacion + 100;
            poner_cursor(13, ALTURA + 1);
            cout << puntuacion;
            longitud++;
        }
   }

    borrar_terminal();
    pintar_pantalla_despedida();
    deshabilitar_modo_crudo_terminal();
}


void pantalla_bienvenida(){
    habilitar_modo_crudo_terminal();
    //Introducción
    poner_cursor(10, 2);
    cout << "*****************************" << endl;

    poner_cursor(10, 3);
    cout <<  "* Juego de la serpiente 1.0 *"<<endl;

    poner_cursor(10, 4);
    cout <<  "*****************************"<<endl;

    //Línea 0
    poner_cursor(6,6);
    cout << "___"<<setw(23) << "______";

    //Línea 1
    poner_cursor(6,7);
    cout << "\\  \\" << setw(16) << "/"<<setw(5)<<"    0 \\";

    //Línea 2
    poner_cursor(7,8);
    cout << "|  |" <<setw(15) << "|" << setw(10) << "|_/";

    //Línea 3
    poner_cursor(7,9);
    cout << "\\_ \\_ " << setw(13) << " |" << setw(9) << "    __/  \\";

    //Línea 4
    poner_cursor(9,10);
    cout << "|  |" << setw(17) << "|   /";

    //Línea 5
    poner_cursor(10,11);
    cout << "\\_ \\_" << setw(14) << "|  |";

    //Línea 6
    poner_cursor(10,12);
    cout << "  |  |_________/  |";

    //Línea 7
    poner_cursor(12,13);
    cout << "\\_______________/";
    poner_cursor(12,14);
    cout << "Pulsa una tecla para continuar ";
    while(leer_tecla() == 0) {
        retardo (RETARDO_TECLA);
    }

    deshabilitar_modo_crudo_terminal();
}

void dibujar_tablero(const int base,const int altura){
     cursor_visible(false);
    poner_cursor( 0, 0 );
    cout << ESQUINA;

    for (int g = 0; g < (BASE - 2); g++){
        cout << HORIZONTAL;
    }

    cout << ESQUINA;
    poner_cursor (altura/2, 0);
    cout << "JUEGO DE LA SERPIENTE 2.0";
    poner_cursor (0,1);

    for (int i = 0; i < altura - 2; i++) {
        cout << VERTICAL;
        for (int j = 0; j < base - 2; j++) {
            cout << INTERIOR;
    }
    cout << VERTICAL << endl;
    }
    cout << ESQUINA;

    for (int i = 0; i < BASE - 2; i++) {
        cout << HORIZONTAL;
    }

    cout << ESQUINA << endl;
    poner_cursor(15, 15);

    poner_cursor(1 , altura );
    cout << ABAJO << "-> Bajar " << ARRIBA << "-> Subir ";
    cout << IZQUIERDA << "->Izq " << DERECHA << "->Dcha ";
    cout << FIN << "-> Fin" <<endl;
  cursor_visible(false);
    poner_cursor( 0, 0 );
    cout << ESQUINA;
    poner_cursor(1, altura + 1);
            cout<<"Puntuacion: 0";


}
void crear_presa(int &f, int &c){
    f = rand()%(BASE-2);
    c = rand()%(ALTURA-2);

    poner_cursor(f,c);
    cout << "*" << endl;

}
bool presa_capturada(int fila_serpiente, int columna_serpiente,
                     int fila_presa, int columna_presa){
    return fila_serpiente == fila_presa && columna_serpiente == columna_presa;

        }
void pintar_serpiente(){

    int j = 0;
    int tmp = 0;
    char serpiente[LONGITUD_SERPIENTE];
    for(int i = 1; i < 5; i--) {
        tmp = serpiente[i];
         j = i -1;
        while ((j >= 0) && (serpiente[j] > tmp)) {
                serpiente[j + 1] = serpiente[j];
                j--;
                cout << '0';
        }
    serpiente[j + 1] = tmp;
    }
}

void mover_serpiente( char &tecla, int &direccion, int longitud,   serpiente la_serpiente){

  tecla = toupper(leer_tecla());
  switch ( tecla ){
    case ABAJO :
        direccion =  MOVER_ABAJO;
        break;

    case ARRIBA:
        direccion = MOVER_ARRIBA ;
        break;

    case IZQUIERDA:
        direccion = MOVER_IZQUIERDA ;
        break;

    case DERECHA:
        direccion = MOVER_DERECHA ;
        break;
  }              //fila_cabeza                  //columna_cabeza
  poner_cursor(la_serpiente.cabeza.fila, la_serpiente.cabeza.columna);
  cout << CABEZA_SERPIENTE;
/*
  for (int j =  0 ;j < longitud ; j++){
    poner_cursor(la_serpiente.cuerpo[j].fila, la_serpiente.cuerpo[j].columna);
    cout << "0";
  }
*/
  retardo(RETARDO_JUEGO);
  poner_cursor(la_serpiente.cabeza.fila, la_serpiente.cabeza.columna);
  cout << " ";

  for (int j = 0; j < longitud; j++){
    poner_cursor(la_serpiente.cuerpo[j].fila, la_serpiente.cuerpo[j].columna);
    cout << " ";
  }

}
void actualizar_posicion( int &fila_serpiente , int &columna_serpiente, int direccion,  serpiente &la_serpiente){

  switch (direccion){
     case MOVER_ABAJO:
              columna_serpiente++;
              break;

            case MOVER_ARRIBA:
              columna_serpiente--;
              break;

            case MOVER_IZQUIERDA :
              fila_serpiente--;
              break;

            case MOVER_DERECHA:
              fila_serpiente++;
              break;
  }

  for (int i = LONGITUD_SERPIENTE - 1; i >= 0; i--){
    la_serpiente.cuerpo[i].fila = la_serpiente.cuerpo[i - 1].fila;
    la_serpiente.cuerpo[i].columna = la_serpiente.cuerpo[i- 1].columna;

  }
  la_serpiente.cabeza = { fila_serpiente, columna_serpiente};
}
bool finalizado(const int columna, const int fila, const char tecla){
    return fila == LIMITE_CUADRO || columna == LIMITE_CUADRO || columna == (BASE -1) ||
        fila == (ALTURA -1)   || FIN == toupper(tecla);


}
void pintar_pantalla_despedida(){
    habilitar_modo_crudo_terminal();
    borrar_terminal();
    poner_cursor(10,5);

    cout << "El juego se ha acabado"<<endl;
    cout << "Pulse cualquier tecla para cerrar el programa";

    poner_cursor(10,20);
    deshabilitar_modo_crudo_terminal();
}

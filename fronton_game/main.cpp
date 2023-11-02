#include <iostream>
#include "terminal.h"
#include <cstdlib>
#include <ctime>
using namespace std;

const int RETARDO = 175;
const int BASE_Y = 15;
const int ALTURA_X = 62;
const int RETARDO_TECLA = 20;
const int LIMITE_ANCHURA = 63;
const int LIMITE_ALTURA = 15;
const int NOR_OESTE = 0;
const int SUR_OESTE = 1;
const int SUR_ESTE = 2;
const int NOR_ESTE = 3;
const char TECLA_FINAL = 'f';
const char TECLA_ARRIBA = 'q';
const char TECLA_ABAJO = 'a';
const char SIMBOLO = '|';
const char PELOTA = '*';
const int LONG_RAQUETA = 3;
const int LIMITE_RAQUETA = 2;

struct posicion{
    int x;
    int y;
};
struct raqueta{
    posicion posicion_raqueta;
    char simbolo;
};
struct pelota{
    posicion posicion_pelota;
    int trayectoria;
    char simbolo;
};

void pintar_pantalla();
void dibujar_cuadro();
bool finalizado(char tecla, int pelotas);
void crear_pelota(pelota &mi_pelota);
void mover_pelota(pelota &mi_pelota);
void calcular_trayectoria_pelota(pelota &mi_pelota);
void cambiar_trayectoria_pelota(pelota &mi_pelota, raqueta mi_raqueta, int &numero_pelotas);
void pintar_raqueta(raqueta &mi_raqueta);
void borrar_raqueta(raqueta &mi_raqueta);
void calcular_posicion_raqueta(char tecla, raqueta &mi_raqueta);

int main(){
    void habilitar_modo_crudo_terminal();
    srand(time(NULL));
    char tecla = '\0';
    int numero_pelotas = 9;
    raqueta mi_raqueta = {LIMITE_RAQUETA, 5, SIMBOLO};
    pelota mi_pelota = {20,5,SUR_OESTE,PELOTA};

    pintar_pantalla();
    borrar_terminal();
    dibujar_cuadro();
    crear_pelota(mi_pelota);
    pintar_raqueta(mi_raqueta);

    while(!finalizado(tecla,numero_pelotas)){
        tecla = leer_tecla();
        poner_cursor(0,17);
        cout << "Número de pelotas: " << numero_pelotas << endl;

        borrar_raqueta(mi_raqueta);
        calcular_posicion_raqueta(tecla,mi_raqueta);
        pintar_raqueta(mi_raqueta);

        mover_pelota(mi_pelota);
        calcular_trayectoria_pelota(mi_pelota);
        cambiar_trayectoria_pelota(mi_pelota, mi_raqueta,numero_pelotas);
    }
    deshabilitar_modo_crudo_terminal();
    return 0;
}
void pintar_pantalla(){
    habilitar_modo_crudo_terminal();
    poner_cursor(0,0);
    cout << "************************    " << endl;
    cout << "* Juego de frontón 1.0 *    " << endl;
    cout << "************************    " <<endl;
    poner_cursor(0,3);
    cout << "         _____              " << endl;
    cout << "        /.....\\            " << endl;
    cout << "        |.....|     _       " << endl;
    cout << "        |.....|    (_)      " << endl;
    cout << "         \\.../             " << endl;
    cout << "          \\./              " << endl;
    cout << "          ||                " << endl;
    cout << "          ||                " << endl;
    cout << "          ||                " << endl;
    cout << "          []                " << endl;
    cout << "Pulsa una tecla para continuar" << endl;
    while(leer_tecla() == 0) {
        retardo(RETARDO_TECLA);
    }
    borrar_terminal();
}
void dibujar_cuadro(){
    cursor_visible(false);
    poner_cursor(0,0);
    cout << "+--------------------juego de frontón 2.0--------------------+" << endl;
    for(int i = 2; i < LIMITE_ALTURA; i++){
        poner_cursor(0,i);
        cout << "|                                                            |" << endl;
    }
    poner_cursor(0,LIMITE_ALTURA);
    cout << "+------------------------------------------------------------+ " << endl;
    cout << "Pulsa la tecla F para finalizar la aplicación" << endl;
}
void crear_pelota(pelota &mi_pelota){
            int trayectoria_aleatoria = 1 + rand() % (3 - 1);
            int posicion_aleatoria = 3 + rand() % ((LIMITE_ALTURA - 3)-3);
            if( trayectoria_aleatoria == 1){
                mi_pelota.trayectoria = NOR_OESTE;
            }else{
                mi_pelota.trayectoria = SUR_OESTE;
            }
            mi_pelota.posicion_pelota.x = LIMITE_ANCHURA - 3;
            mi_pelota.posicion_pelota.y = posicion_aleatoria;
}
void mover_pelota(pelota &mi_pelota){
    poner_cursor(mi_pelota.posicion_pelota.x,mi_pelota.posicion_pelota.y);
    cout << mi_pelota.simbolo << endl;
    retardo(RETARDO);
    poner_cursor(mi_pelota.posicion_pelota.x,mi_pelota.posicion_pelota.y);
    cout << " " << endl;
}
void pintar_raqueta(raqueta &mi_raqueta){
    for(int i = 0; i < LONG_RAQUETA ; i++){
        poner_cursor(LIMITE_RAQUETA, mi_raqueta.posicion_raqueta.y + i);
        cout <<  mi_raqueta.simbolo << endl;
    }
}
void borrar_raqueta(raqueta &mi_raqueta){
    for(int i = 0; i < LONG_RAQUETA ; i++){
        poner_cursor(LIMITE_RAQUETA, mi_raqueta.posicion_raqueta.y + i);
        cout << " " << endl;
    }
}
void calcular_posicion_raqueta(char tecla, raqueta &mi_raqueta){
        switch(tecla){
            case TECLA_ARRIBA:
                if(mi_raqueta.posicion_raqueta.y != 2){
                    mi_raqueta.posicion_raqueta.y --;
                }
               break;
            case TECLA_ABAJO:
                if(mi_raqueta.posicion_raqueta.y != LIMITE_ALTURA - 3){
                    mi_raqueta.posicion_raqueta.y ++;
                }
                break;
        }
}
void calcular_trayectoria_pelota(pelota &mi_pelota){
    switch (mi_pelota.trayectoria){
        case NOR_OESTE:
            mi_pelota.posicion_pelota.x--;
            mi_pelota.posicion_pelota.y--;
            break;
        case NOR_ESTE:
            mi_pelota.posicion_pelota.x++;
            mi_pelota.posicion_pelota.y--;
            break;
        case SUR_ESTE:
            mi_pelota.posicion_pelota.x++;
            mi_pelota.posicion_pelota.y++;
            break;
        case SUR_OESTE:
            mi_pelota.posicion_pelota.x--;
            mi_pelota.posicion_pelota.y++;
            break;
    }
}
void cambiar_trayectoria_pelota(pelota &mi_pelota, raqueta mi_raqueta, int &numero_pelotas){
    //pared 1
     if(mi_pelota.posicion_pelota.y == 2 && mi_pelota.trayectoria == NOR_ESTE){
                mi_pelota.trayectoria = SUR_ESTE;
        }else if(mi_pelota.posicion_pelota.y == 2 && mi_pelota.trayectoria == NOR_OESTE){
                mi_pelota.trayectoria = SUR_OESTE;
        }
        //pared 2
     if(mi_pelota.posicion_pelota.x == LIMITE_ANCHURA - 2 && mi_pelota.trayectoria == SUR_ESTE ){
                mi_pelota.trayectoria =  SUR_OESTE;
        }else if(mi_pelota.posicion_pelota.x == LIMITE_ANCHURA - 2 && mi_pelota.trayectoria == NOR_ESTE){
                mi_pelota.trayectoria = NOR_OESTE;
        }
        //pared 3
     if(mi_pelota.posicion_pelota.y == LIMITE_ALTURA - 1  && mi_pelota.trayectoria == SUR_OESTE){
                mi_pelota.trayectoria = NOR_OESTE;
        }else if(mi_pelota.posicion_pelota.y == LIMITE_ALTURA - 1 && mi_pelota.trayectoria == SUR_ESTE){
                mi_pelota.trayectoria = NOR_ESTE;
        }
        //Raqueta
     if(((mi_pelota.posicion_pelota.y == mi_raqueta.posicion_raqueta.y) &&
         (mi_pelota.posicion_pelota.x == LIMITE_RAQUETA + 1) &&
         (mi_pelota.trayectoria == NOR_OESTE))||//1º posibilidad
        ((mi_pelota.posicion_pelota.y == mi_raqueta.posicion_raqueta.y + 1) &&
         (mi_pelota.posicion_pelota.x == LIMITE_RAQUETA + 1) &&
         (mi_pelota.trayectoria == NOR_OESTE))||//2º posibilidad
        ((mi_pelota.posicion_pelota.y == mi_raqueta.posicion_raqueta.y + 2) &&
         (mi_pelota.posicion_pelota.x == LIMITE_RAQUETA + 1) &&
         (mi_pelota.trayectoria == NOR_OESTE))){//3º posibilidad
                    mi_pelota.trayectoria = NOR_ESTE;
     }else if(((mi_pelota.posicion_pelota.y == mi_raqueta.posicion_raqueta.y) &&
               (mi_pelota.posicion_pelota.x == LIMITE_RAQUETA + 1) &&
               (mi_pelota.trayectoria == SUR_OESTE)) ||//4º posibilidad
              ((mi_pelota.posicion_pelota.y == mi_raqueta.posicion_raqueta.y + 1) &&
               (mi_pelota.posicion_pelota.x == LIMITE_RAQUETA + 1) &&
               (mi_pelota.trayectoria == SUR_OESTE))||//5º posibilidad
              ((mi_pelota.posicion_pelota.y == mi_raqueta.posicion_raqueta.y + 2) &&
               (mi_pelota.posicion_pelota.x == LIMITE_RAQUETA + 1) &&
               (mi_pelota.trayectoria == SUR_OESTE))){//6º posibilidad
                    mi_pelota.trayectoria = SUR_ESTE;
        }
        //pared 4
        if(mi_pelota.posicion_pelota.x == 2){
            numero_pelotas --;
            poner_cursor(mi_pelota.posicion_pelota.x,mi_pelota.posicion_pelota.y);
            cout << " " << endl;
            crear_pelota(mi_pelota);
        }
}
bool finalizado(char tecla, int pelotas){
    return ((tecla == TECLA_FINAL) || (pelotas == 0 ));
}

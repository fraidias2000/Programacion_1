/*Programación 1 (GII)
*ejercicio_4.cpp
*Alvaro Fraidias Monteagudo
*27/11/2019
*/
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
const string TIJERAS_EXT = "tijeras";
const string PIEDRA_EXT = "piedra";
const string PAPEL_EXT = "papel";
const int TIJERAS = 0;
const int PIEDRA = 1;
const int PAPEL = 2;
const int POSIBILIDADES = 3;
const int FINAL = 0;


int obtener_jugada_usuario(string elemento);
int obtener_jugada_PC();
void obtener_ganador(string nombre,int jugada_usuario, int jugada_pc,
                     int &triunfos_usuario,int &triunfos_PC, int &turno,
                     int &contador_rondas);
void indicar_ganador(string nombre, int turno,int triunfos_usuario,
                     int triunfos_PC,int contador_rondas);

int main(){
    string nombre = "";
    int turnos = 0;
    srand(time(NULL));
    int triunfos_usuario = 0;
    int triunfos_PC = 0;
    int contador_rondas = 0;
    int iterador_ronda = 1;
    string decision_usuario = "";
    int mi_jugada = 0;
    int jugada_PC = 0;

    cout << "Juego de Piedra, papel o tijera." << endl;
    cout << "Nombre jugador: ";
    cin >> nombre;
    cout << "Número de jugadas a realizar: ";
    cin >> turnos;

    while(turnos != FINAL){
        cout << "Introduce tu jugada " << iterador_ronda <<": ";
        cin >> decision_usuario;
        mi_jugada = obtener_jugada_usuario(decision_usuario);
        jugada_PC = obtener_jugada_PC();
        obtener_ganador(nombre,mi_jugada, jugada_PC, triunfos_usuario,
                        triunfos_PC, turnos,contador_rondas);
        iterador_ronda++;
    }
    indicar_ganador(nombre,turnos,triunfos_usuario,
                    triunfos_PC,contador_rondas);
    return 0;
}
int obtener_jugada_PC(){
    string jugada ="";
    int numero = rand() % POSIBILIDADES;
    switch(numero){
        case 0:
            jugada = TIJERAS_EXT ;
            break;
        case 1:
            jugada = PIEDRA_EXT ;
            break;
        case 2:
            jugada = PAPEL_EXT ;
            break;
    }
    cout << "El ordenador juega: " << jugada <<endl;
    return numero;
}
int obtener_jugada_usuario(string elemento){
    if(elemento == TIJERAS_EXT){
        return TIJERAS;
    }
    if(elemento == PIEDRA_EXT){
        return PIEDRA;
    }
    if(elemento == PAPEL_EXT){
        return PAPEL;
    }
}
void obtener_ganador(string nombre,int jugada_usuario, int jugada_pc,
                     int &triunfos_usuario,int &triunfos_PC,
                     int &turno,int &contador_rondas){
    if(jugada_usuario == TIJERAS && jugada_pc == PIEDRA){
        cout << "Gana el ordenador" <<endl;
        triunfos_PC++;
    }
    if(jugada_usuario == TIJERAS && jugada_pc == PAPEL){
        cout << "Ganas tu" <<endl;
        triunfos_usuario++;
    }
    if(jugada_usuario == PIEDRA && jugada_pc == TIJERAS){
        cout << "Ganas tu" <<endl;
        triunfos_usuario++;
    }
    if(jugada_usuario == PIEDRA && jugada_pc == PAPEL){
        cout << "Gana el ordenador" <<endl;
        triunfos_PC++;
    }
    if(jugada_usuario == PAPEL && jugada_pc == TIJERAS){
        cout << "Gana el ordenador" <<endl;
        triunfos_PC++;
    }
    if(jugada_usuario == PAPEL && jugada_pc == PIEDRA){
        cout << "Ganas tu" <<endl;
        triunfos_usuario++;
    }
    if(jugada_usuario == TIJERAS && jugada_pc == TIJERAS ||
       jugada_usuario == PIEDRA && jugada_pc == PIEDRA ||
       jugada_usuario == PAPEL && jugada_pc == PAPEL ){
            cout << "Empate" << endl;

    }
    turno--;
    contador_rondas++;
}
void indicar_ganador(string nombre, int turno,int triunfos_usuario,
                     int triunfos_PC, int contador_rondas){
    if(triunfos_usuario > triunfos_PC){
        cout << nombre << ", despues de " << contador_rondas
             << " jugadas ganas tú";
    }else{
        cout << "El ordenador despues de " << contador_rondas
             << " jugadas ha ganado";
    }
}

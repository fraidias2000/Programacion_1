#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
const int NUM_CARTAS = 52;
enum valores {AS = 1, DOS, TRES, CUATRO, CINCO, SEIS, SIETE,
              OCHO, NUEVE, DIEZ, JOKER = 11, REINA = 12, REY = 13
};
enum palos {PICAS = 1, CORAZONES , DIAMANTES, TREBOLES = 4};

struct carta{
    int valor, palo;
};
void mostrar_carta (const carta &carta);
void mostrar_cartas(const carta cartas[], const int longitud);
void mover_cartas(carta cartas[], int movimientos);
void hacer_movimiento(carta cartas[], const int p1, const int p2);
int main()
{
    carta cartas[NUM_CARTAS];
    int j = 1;
    int k = 0;
    srand(time(NULL));
    for (int i = 1; j < 5 ; i++ ){
        cartas[k].palo = j;
        cartas[k].valor = i;
        k++;
        if (i == 13){
            j++;
            i = 0;
        }
    }
    cout << "********Cartas antes de barajar********* " << endl;
    mostrar_cartas(cartas, NUM_CARTAS);
    cout << "\n";
    cout << "********Cartas despues de barajar********* " << endl;
    mover_cartas(cartas, NUM_CARTAS);
    mostrar_cartas(cartas, NUM_CARTAS);
    return 0;
}

void mostrar_cartas(const carta cartas[], const int longitud) {
    for (int n = 0; n < longitud; n++) {
    mostrar_carta(cartas[n]);
    }
    cout << endl;
}

void mostrar_carta (const carta &carta){
    switch (carta.valor){
        case AS:
            cout << "\"As de ";
            break;
        case DOS:
            cout << "\" Dos de ";
            break;
        case TRES:
            cout << "\"Tres de ";
            break;
        case CUATRO:
            cout <<"\"Cuatro de ";
            break;
        case CINCO:
            cout << "\"Cinco de ";
            break;
        case SEIS:
            cout << "\"Seis de ";
            break;
        case SIETE:
            cout <<"\"Siete de ";
            break;
        case OCHO:
            cout << "\"Ocho de ";
            break;
        case NUEVE:
            cout <<"\"Nueve de ";
            break;
        case DIEZ:
            cout << "\"Diez de ";
            break;
        case JOKER:
            cout <<"\"Joker de ";
            break;
        case REINA:
            cout <<"\"Reina de ";
            break;
        case REY:
            cout << "\" Rey de ";
            break;
    }
    switch( carta.palo) {
        case PICAS:
            cout << "picas\", ";
            break;
        case CORAZONES:
            cout << "corazones\", ";
            break;
        case DIAMANTES:
            cout << "diamantes\", ";
            break;
        case TREBOLES:
            cout << "treboles\", ";
            break;
    }
}
void mover_cartas(carta cartas[], int movimientos){
    int p1 = 0;
    int p2 = 0;
    for(int n = 0; n < movimientos; n++) {
        do {
        p1 = rand() % NUM_CARTAS;
        p2 = rand() % NUM_CARTAS;
        }
        while (p1 == p2);
            hacer_movimiento(cartas, p1, p2);
        }
}
void hacer_movimiento(carta cartas[], const int p1, const int p2){
    carta aux = cartas[p1];
    cartas[p1] = cartas[p2];
    cartas[p2] = aux;
}

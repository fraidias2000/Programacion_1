/*Programación 1 (GII)
*Alvaro Fraidias Monteagudo
*ejercicio_1.cpp
*27/11/2019
*/
#include <iostream>
#include <cmath>
using namespace std;
const char SIMB_ESQ = '+';
const char SIMB_HOR = '-';
const char SIMB_VER = '|';
const char SIMB_INT = ' ';
void dibujar_rectangulo(const int base, const int altura, string palabra = "");
void escribir_linea(const char caracter_ext, const char caracter_int,
                    const int largo,const string palabra = "");
int main(void) {
    int base = 0;
    int altura = 0;
    string palabra = "";
    cout << "Base, altura del rectángulo: ";
    cin >> base;
    cin >> altura;
    cout << "Palabra: ";
    cin >> palabra;
    dibujar_rectangulo(base, altura, palabra);
}
void dibujar_rectangulo(const int base, const int altura, const string palabra) {
    if(base > ( palabra.length() + 2 ) && altura > 3 ){
        escribir_linea(SIMB_ESQ, SIMB_HOR, base);
        for (int i = 0; i < (altura - 3)/ 2 ; i++){
            escribir_linea(SIMB_VER,SIMB_INT, base);
        }
        escribir_linea(SIMB_VER,SIMB_INT, base, palabra);
        for (int i = 0; i < (altura - 3)/ 2 ; i++){
            escribir_linea(SIMB_VER,SIMB_INT, base);
        }
        escribir_linea(SIMB_ESQ, SIMB_HOR, base);
    }else {
        cout << "Palabra no cumple con el requisito";
    }
}
void escribir_linea(const char caracter_ext, const char caracter_int,
                    const int largo,const string palabra) {
    int i = 0;
    cout << caracter_ext;
    for (i = 0; i < (largo- palabra.length()- 2) / 2; i++){
        cout << caracter_int;
    }
    cout << palabra;
    if ( ( palabra.length() % 2) == 0){
        for (i = 0; i <= (largo - palabra.length()- 2) / 2; i++){
            cout << caracter_int;
        }
        cout << caracter_ext << endl;
    }else{
        if (largo % 2 != 0){
            for (i = 0; i <= (largo- palabra.length()- 3) / 2 ; i++){
                cout << caracter_int;
            }
        }else{
            for (i = 0; i <= (largo- palabra.length()- 2) / 2 + 1; i++){
                cout << caracter_int;
            }
        }
        cout << caracter_ext << endl;
    }
}

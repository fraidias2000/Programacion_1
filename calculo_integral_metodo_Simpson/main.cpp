/*Programación 1 (GII)
*ejercicio_1.cpp
*Alvaro Fraidias Monteagudo
*16/12/2019
*/
#include <iostream>
#include <cmath>
using namespace std;
double f(double x);
double simpson(double a, double b, int tramos);
int main(void) {
    int a = 0;
    int b = 0;
    int tramos = 0;
    cout << "Introduce a, b y tramos: ";
    cin >> a >> b >> tramos;
    cout << simpson(a, b, tramos) << endl;
}
double f(double x) {
    return sin(x); // función a integrar, p.e. sin(x)
}
double simpson(double a, double b, int tramos) {
    double h = (b - a) / tramos;
    int indice_funcion = 0;
    double sumatorio_par = 0;
    double sumatorio_impar = 0;
    double sumatorio_total = 0;
    double integral = 0;
    while (a < b){
        sumatorio_total = sumatorio_total + f(a);
        if(indice_funcion % 2 == 0){
            sumatorio_par = sumatorio_par + (f(a)* h);
        }else{
            sumatorio_impar = sumatorio_impar + (f(a) * h);
        }
        indice_funcion++;
        a = a + h;
    }
    integral = h/3 * (sumatorio_total + 4 *(sumatorio_impar) + 2 * (sumatorio_par) );
    return integral;

}

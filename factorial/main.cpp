/*Trabajo6.cpp
*Ejercicio 1
*Álvaro Fraidias Monteagudo
*17/12/2018
*/
#include <iostream>

using namespace std;

long long factorial(int a);

 int main(){
      for (int n = 0; n < 20; n++){
           cout << factorial(n) << endl;
      }
}

long long factorial(int a) {
    long long  resultado = 1;
    for(int i = 1; i < a ;i++){
        resultado += resultado*i;
    }
    return resultado;
}

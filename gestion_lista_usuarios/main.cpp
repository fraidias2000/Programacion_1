#include <iostream>

using namespace std;

struct alumno{
    string nombre,apellido1,apellido2,dni;
};
const int MAX_ALUMNO = 50;
const int CREAR = 1;
const int LISTAR = 2;
const int BUSCAR = 3;
const int BORRAR = 4;
const int ACABAR = 5;

void crear_alumno( alumno personas[],int &numero_alumnos);
void listar_alumnos(alumno personas[],int &numero_alumnos);
void buscar_alumnos(alumno personas[]);
void eliminar_alumno(alumno personas[], int &numero_alumnos);




int main()
{
    int i = 0;
    int numero = 6;
    int numero_alumnos = 1;
    alumno personas[MAX_ALUMNO];

    while(numero != ACABAR){
        cout << "1->Nuevo alumno 2->Listar 3->Buscar 4->Borrar 5->Acabar: "<<endl;
        cin >> numero;
        switch(numero){
            case CREAR:
                crear_alumno(personas,numero_alumnos);
                break;
            case LISTAR:
                listar_alumnos(personas,numero_alumnos);
            case BUSCAR:
                buscar_alumnos(personas);
                break;
            case BORRAR:
                eliminar_alumno(personas,numero_alumnos);
                break;
        }
    }
    return 0;
}

void crear_alumno(alumno personas[],int &numero_alumnos){
    int i = 0;
    while(i < MAX_ALUMNO){
        cout << "Nombre del alumno " << i << "   (0->Acabar):"<<endl;
        cin >> personas[i].nombre;

        if(personas[i].nombre != "0"){
        cout << "Primer apellido del alumno " << i << endl;
        cin >> personas[i].apellido1;
        cout << "Segundo apellido del alumno " << i << endl;
        cin >> personas[i].apellido2;
        cout << "DNI del alumno " << i << endl;
        cin >> personas[i].dni;
        i++;
        }
        else if (personas[i].nombre == "0"){
            break;
        }
        numero_alumnos++;
    }
}
void listar_alumnos(alumno personas[],int &numero_alumnos){
    for( int i = 0; i < numero_alumnos-1; i++){
    cout << i+1 << ") " << personas[i].dni << " " << personas[i].apellido1 <<
            " " << personas[i].apellido2 << "," << personas[i].nombre << endl;

    }

}
void buscar_alumnos(alumno personas[]){
    string identificacion;
    cout << "Dime el Dni " << endl;
    cin >> identificacion;
    for( int i = 0;i < MAX_ALUMNO; i++){
        if(personas[i].dni == identificacion){
                cout << personas[i].dni << " " << personas[i].apellido1 <<
                        " " << personas[i].apellido2 << "," << personas[i].nombre << endl;
        }
    }

}
void eliminar_alumno(alumno personas[], int &numero_alumnos) {
    int numero;
    cout<< "Número: ";
    cin>> numero;
    numero=numero-1;
    for(int i = 0; i < numero_alumnos; i++) {
            if(i == (numero -1)) {
            personas[i] = personas[numero_alumnos-1];
            numero_alumnos--;
            return;
            }
    }
}

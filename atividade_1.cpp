#include <iostream>
#include <math.h>

using namespace std;

//FUNCAO 1
void Trocar(int * a, int * b) {
    int aux;

    cout << "ANTES" << endl;
    cout << "A = " << *a << endl;
    cout << "B = " << *b << endl << endl;

    aux = *a;
    *a = *b;
    *b = aux;

    cout << "TROCADO" << endl;
    cout << "A = " << *a << endl;
    cout << "B = " << *b << endl;
}

//FUNCAO 2
void Modificar(int * a, int * b) {
    *a = *a - 1;
    *b = *b + 1;

    cout << "A = " << *a << endl;
    cout << "B = " << *b << endl;
}

//FUNCAO 3
void Calcular(float raio, float * perimetro, float * area) {
    float pi = 3.14159;

    *perimetro = 2*pi*raio;
    *area = pi*(raio*raio);

    cout << "Perimetro: " << *perimetro << endl;
    cout << "Area: " << *area << endl;
}

//FUNCAO 4
void AcharRaiz(float a, float b, float c, float * x1, float * x2) {
    float delta;

    delta = b*b - 4 * a * c;
    if(delta >= 0 && a != 0)
    {
        *x1 = (-b + sqrt(delta))/(2*a);
        *x2 = (-b - sqrt(delta))/(2*a);

        cout << "Raizes: S={" << *x1 << ", " << *x2 << "}" << endl;
    }
}

int main() {

    return 0;
}

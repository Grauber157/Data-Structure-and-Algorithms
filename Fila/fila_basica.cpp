/*
Made by Gabriel F. Dias for Valtemorte >:)
09/03/2026
*/
#include <iostream>

using namespace std;

struct No {
    int numero;
    No * next;
};

struct Fila {
    No * inicio;
    No * fim;
};

void Inicializar(Fila * fila) {
    fila->inicio = NULL;
    fila->fim = NULL;
}

No * Alocar(int numero) {
    No * pt = (No*) malloc(sizeof(No));

    if(pt != NULL)
    {
        pt->numero = numero;
        pt->next = NULL;
    }
    else
    {
        pt = Alocar(numero);
    }

    return pt;
}

void Enqueue(Fila * fila, int numero) {
    No * pt = Alocar(numero);

    if(fila->fim != NULL) //Há algo na fila
    {
        fila->fim->next = pt;
        fila->fim = pt;
    }
    else
    {
        if(fila->inicio == NULL)
        {
            fila->fim = pt;
            fila->inicio = pt;
        }
    }
}

void Dequeue(Fila * fila) {
    No * pt;

    if(fila->inicio != NULL)
    {
        pt = fila->inicio;
        fila->inicio = fila->inicio->next;
        cout << "Numero removido: " << pt->numero << endl;
        free(pt);
    }
    else
    {
        cout << "Fila vazia! Dequeue negado!" << endl;
    }
}

void Imprimir(No * pt) {
    //Sempre enviar o início da lista como pt
    if(pt != NULL)
    {
        cout << "Numero: " << pt->numero << endl;
        Imprimir(pt->next);
    }
}

int main() {
    Fila fila;

    Inicializar(&fila);

    Enqueue(&fila, 10);
    Enqueue(&fila, 20);
    Enqueue(&fila, 30);
    Enqueue(&fila, 40);
    Enqueue(&fila, 50);

    Imprimir(fila.inicio);

    Dequeue(&fila);
    Dequeue(&fila);
    Dequeue(&fila);
    Dequeue(&fila);

    Imprimir(fila.inicio);

    return 0;
}

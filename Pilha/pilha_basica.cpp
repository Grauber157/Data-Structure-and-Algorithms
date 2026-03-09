/*
Made by Gabriel F. Dias for Valtinho
09/03/2026
*/
#include <iostream>

using namespace std;

struct No { //Cada nó da pilha
    int numero;
    No * next;
};

struct Pilha { //Cabeçalho
    No * topo;
};

void Inicializar(Pilha * pil) {
    pil->topo = NULL;
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

void Push(Pilha * pil, int numero) {
    No * pt = Alocar(numero);

    if(pil->topo != NULL) //Há algo na pilha
    {
        pt->next = pil->topo;
        pil->topo = pt;
    }
    else //Pilha vazia
    {
        pil->topo = pt;
    }
}

void Pop(Pilha * pil) {
    No * pt;

    if(pil->topo != NULL)
    {
        pt = pil->topo;
        pil->topo = pt->next;
        cout << "Numero removido: " << pt->numero << endl;
        free(pt);
    }
    else
    {
        cout << "Pilha vazia! Pop negado!" << endl;
    }

}

void Imprimir(No * pt) {

    if(pt != NULL)
    {
        cout << "Numero: " << pt->numero << endl;
        Imprimir(pt->next);
    }
}

int main() {
    Pilha pil;

    Inicializar(&pil);

    Push(&pil, 10);
    Push(&pil, 20);
    Push(&pil, 30);
    Push(&pil, 40);
    Push(&pil, 50);

    Imprimir(pil.topo);

    Pop(&pil);
    Pop(&pil);

    Imprimir(pil.topo);

    return 0;
}

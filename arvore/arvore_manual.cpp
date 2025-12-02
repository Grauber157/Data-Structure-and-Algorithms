#include <iostream>

using namespace std;

struct No {
    No * esq;
    No * dir;
    float numero;
};

struct Arvore {
    No * raiz;
};

void Inicializar(Arvore * arv) {
    arv->raiz = NULL;
}

No * Alocar(float num) {
    No * pt;

    pt = (No*) malloc(sizeof(No));

    if(pt == NULL)
    {
        pt = Alocar(num);
    }

    pt->esq = NULL;
    pt->dir = NULL;
    pt->numero = num;

    return pt;
}

No * Inserir(Arvore * arv, No * pai, float num, string lado) {
    No * pt;

    pt = Alocar(num);

    if(arv->raiz == NULL)
    {
        arv->raiz = pt;
    }
    else
    {
        if(lado == "E")
        {
            pai->esq = pt;
        }
        else
        {
            pai->dir = pt;
        }
    }
    return pt;
}

void Imprimir(No * pt) {

    if(pt != NULL)
    {
        cout << "Numero: " << pt->numero << endl;
        Imprimir(pt->esq);
        Imprimir(pt->dir);
    }
}

int main() {
    Arvore arv;
    No * pai, * esq, * dir;

    Inicializar(&arv);

    /*
    ==INSERÇÃO MANUAL==

    - Utilizar os ponteiros 'pai', 'esq' e 'dir' para percorrer e salvar posições na árvore;

    - Parâmetros da função: Inserir(Arvore*, No*, float, string);

    (Arvore*): A Árvore Binária no qual você está inserindo.
    (No*): Posição dentro da Árvore no qual você está.
    (float): Valor do número a ser inserido.
    (string): A partir da posição definida pelo (No*), qual lado será inserido.

    *obs: As inserções abaixo está na ordem da minha cabeça :)

    *obs2: Para de usar essa bomba de inserção manual. Utilize uma árvore ordenada (ex: Binary Search Tree), muito mais coisa de gente
    */

    pai = Inserir(&arv, NULL, 1, "");
    esq = Inserir(&arv, pai, 2, "E");
    dir = Inserir(&arv, pai, 3, "D");

    pai = Inserir(&arv, esq, 4, "E");
    esq = Inserir(&arv, pai, 7, "E");
    Inserir(&arv, esq, 10, "E");
    Inserir(&arv, esq, 11, "D");

    //Direita da raiz

    Inserir(&arv, dir, 5, "E");
    pai = Inserir(&arv, dir, 6, "D");
    esq = Inserir(&arv, pai, 8, "E");
    Inserir(&arv, pai, 9, "D");
    Inserir(&arv, esq, 12, "E");

    Imprimir(arv.raiz);

    return 0;
}

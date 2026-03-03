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

No * Alocar(float numero) {
    No * pt = (No*) malloc(sizeof(No));

    if(pt == NULL)
    {
        pt = Alocar(numero);
    }
    else
    {
        pt->numero = numero;
        pt->esq = NULL;
        pt->dir = NULL;
    }

    return pt;
}

No * Inserir(Arvore * arv, No * pt, float numero) {
    No * resul;

    if(pt != NULL)
    {
        resul = pt;
        if(numero < pt->numero) //Recursao esquerda
        {
            pt->esq = Inserir(arv, pt->esq, numero);
        }
        else
        {
            if(numero > pt->numero) //Recursao direita
            {
                pt->dir = Inserir(arv, pt->dir, numero);
            }
            else
            {
                cout << "Numero ja existente" << endl;
            }
        }
    }
    else //Ponteiro vazio
    {
        pt = Alocar(numero);
        resul = pt;

        if(arv->raiz == NULL)
        {
            arv->raiz = resul;
        }
    }

    return resul;
}

void Imprimir(No * pt) {

    if(pt != NULL)
    {
        cout << "Numero: " << pt->numero << endl;
        Imprimir(pt->esq);
        Imprimir(pt->dir);
    }
}

/*
    3 condições

    - Nó folha, basta dar free() e retornar um valor NULL ao nó pai

    - Nó pai com 1 filho, basta retornar o filho para o nó avô

    - Nó pai com 2 filhos, faz 1 recursão à direita e o máximo para à esquerda, afim de encontrar o menor valor e o retorna para substituir o nó pai.

*/

No * AcharMenor(No * pt) {
    No * resul;

    if(pt->esq != NULL)
    {
        resul = AcharMenor(pt->esq);
    }
    else
    {
        resul = pt;
    }

    return resul;
}

No * Remover(Arvore * arv, No * pt, float numero) {
    No * resul, * aux;


    if(pt != NULL)
    {
        resul = pt;

        if(numero < pt->numero)
        {
            pt->esq = Remover(arv, pt->esq, numero);
        }
        else
        {
            if(numero > pt->numero)
            {
                pt->dir = Remover(arv, pt->dir, numero);
            }
            else //Item encontrado
            {
                if(pt->esq == NULL && pt->dir == NULL) //No folha
                {
                    free(pt);
                    resul = NULL;
                }
                else
                {
                    if(pt->esq == NULL) //1 filho
                    {
                        resul = pt->dir;
                    }
                    else
                    {
                        if(pt->dir == NULL) //1 filho
                        {
                            resul = pt->esq;
                        }
                        else //2 filhos
                        {
                            aux = AcharMenor(pt->dir);
                            pt->numero = aux->numero;

                            pt->dir = Remover(arv, pt->dir, aux->numero);
                        }
                    }
                }
            }
        }

    }

    return resul;
}

int main() {

    Arvore arv;

    Inicializar(&arv);

    Inserir(&arv, arv.raiz, 10);
    Inserir(&arv, arv.raiz, 8);
    Inserir(&arv, arv.raiz, 12);
    Inserir(&arv, arv.raiz, 14);
    Inserir(&arv, arv.raiz, 1);
    Inserir(&arv, arv.raiz, 3);
    Inserir(&arv, arv.raiz, 11);
    Inserir(&arv, arv.raiz, 0.5);
    Inserir(&arv, arv.raiz, 2);

    Imprimir(arv.raiz);

    Remover(&arv, arv.raiz, 8);

    system("pause");

    Imprimir(arv.raiz);

    return 0;
}

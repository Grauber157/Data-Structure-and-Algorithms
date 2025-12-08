#include <iostream>

using namespace std;

/**STRUCTS**/
struct No {
    float numero;
    No * esq;
    No * dir;
};

struct Arvore {
    No * raiz;
};

/**FUNÇÕES**/
void Inicializar(Arvore * arv) {
    arv->raiz = NULL;
}

No * Alocar(float numero) {
    No * pt = NULL;

    pt = (No*) malloc(sizeof(No));

    if(pt == NULL)
    {
        pt = Alocar(numero);
    }
    else
    {
        pt->esq = NULL;
        pt->dir = NULL;
        pt->numero = numero;
    }

    return pt;
}

No * Inserir(Arvore * arv, No * pt, float numero) {
    No * resul = NULL;
    //Caso haja algo no ponteiro
    if(pt != NULL)
    {
        resul = pt;
        if(pt->numero > numero)
        {
            resul->esq = Inserir(arv, pt->esq, numero);
        }
        else
        {
            if(pt->numero < numero)
            {
                resul->dir = Inserir(arv, pt->dir, numero);
            }
            else
            {
                cout << "Este número já está inserido!" << endl;
            }
        }
    }
    else
    {
        //Caso não tenha raiz
        if(arv->raiz == NULL)
        {
            resul = Alocar(numero);
            arv->raiz = resul;
            cout << "Nova Raiz: " << numero << endl;
        }
        //Caso tenha raiz
        else
        {
            resul = Alocar(numero);

            pt = resul;
            cout << "Novo No: " << pt->numero << endl;
        }
    }
    return resul;
}

No * AcharMenor(No * pt) {
    No * resul;

    if(pt != NULL)
    {
        resul = pt;
        if(pt->esq != NULL)
        {
            resul = AcharMenor(pt->esq);
        }
    }

    return resul;
}

/*
    *3 casos de remoção*

    - Nó folha: Basta remover

    - Nó com 1 filho: O nó anterior vai receber o nó filho do atual (O nó avô vai receber o nó neto)

    - Nó com 2 filhos: O nó 'pt->dir' assumirá a posição do 'pt', tendo em vista que o 'pt->dir' é maior que o 'pt->esq', assim mantendo a organização da árvore
*/

No * Remover(No * pt, float numero) {
    No * resul, * aux;

    if(pt != NULL)
    {
        resul = pt;

        if(pt->numero > numero) //Numero menor, esquerda
        {
            cout << "Recursao esq" << endl;
            resul->esq = Remover(pt->esq, numero);
        }
        else
        {
            if(pt->numero < numero) //Numero maior, direita
            {
                cout << "Recursao dir" << endl;
                resul->dir = Remover(pt->dir, numero);
            }
            else //Numero igual
            {

                //NÓ FOLHA
                if(pt->esq == NULL && pt->dir == NULL)
                {
                    cout << "No folha: " << pt->numero << endl;
                    resul = NULL;
                    free(pt);
                }
                else
                {
                    /*Ideia deste e do próximo if()*/
                    /*
                        - Como o nó avô está em aberto, esperando um endereço para encadear 'resul->esq = ...',
                        posso simplesmente
                    */
                    if(pt->esq == NULL)
                    {
                        cout << "No 1 filho DIR" << endl;
                        resul = pt->dir;
                        free(pt);
                    }
                    else
                    {
                        if(pt->dir == NULL)
                        {
                            cout << "No 1 filho ESQ" << endl;
                            resul = pt->esq;
                            free(pt);
                        }
                        else
                        {
                            //2 FILHOS
                            if(pt->esq != NULL && pt->dir != NULL)
                            {
                                cout << "No 2 filhos" << endl;
                                aux = AcharMenor(pt->dir);
                                pt->numero = aux->numero;
                                resul->dir = Remover(pt->dir, aux->numero);
                            }
                        }
                    }
                }

            }

        }
    }
    else
    {
        //NULO
    }

    return resul;
}

void Imprimir(No * pt, string ordem) {
    if(pt != NULL)
    {
        if(ordem == "PRE")
        {
            cout << "Numero: " << pt->numero << endl;
            Imprimir(pt->esq, "PRE");
            Imprimir(pt->dir, "PRE");
        }
        else
        {
            if(ordem == "CEN")
            {
                Imprimir(pt->esq, "CEN");
                cout << "Numero: " << pt->numero << endl;
                Imprimir(pt->dir, "CEN");
            }
            else
            {
                if(ordem == "POS")
                {
                    Imprimir(pt->esq, "POS");
                    Imprimir(pt->dir, "POS");
                    cout << "Numero: " << pt->numero << endl;
                }
                else
                {
                    cout << "Ordem Invalida!" << endl;
                }
            }
        }

    }
}

int main() {
    Arvore arv;

    Inicializar(&arv);

    Inserir(&arv, arv.raiz, 12);
    Inserir(&arv, arv.raiz, 9);
    Inserir(&arv, arv.raiz, 2);
    Inserir(&arv, arv.raiz, 5);
    Inserir(&arv, arv.raiz, 19);
    Inserir(&arv, arv.raiz, 18);
    Inserir(&arv, arv.raiz, 25);
    Inserir(&arv, arv.raiz, 30);
    Inserir(&arv, arv.raiz, 17);
    Inserir(&arv, arv.raiz, 17.5);
    Inserir(&arv, arv.raiz, 16);
    Inserir(&arv, arv.raiz, 29);

    cout << endl;

    Imprimir(arv.raiz, "PRE");

    cout << endl;

    Remover(arv.raiz, 17);

    cout << endl;

    Imprimir(arv.raiz, "PRE");

    return 0;
}

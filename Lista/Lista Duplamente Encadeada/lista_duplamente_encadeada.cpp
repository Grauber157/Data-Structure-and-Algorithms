/*
Made by Gabriel F. Dias for Valtemiro
09/03/2026
*/
#include <iostream>

using namespace std;

struct No {
    int numero;
    No * prev;
    No * next;
};

struct Lista {
    No * inicio;
    No * fim;
};

void Inicializar(Lista * lis) {
    lis->inicio = NULL;
    lis->fim = NULL;
}

No * Alocar(int numero) {
    No * pt = (No*) malloc(sizeof(No));

    if(pt != NULL)
    {
        pt->numero = numero;
        pt->prev = NULL;
        pt->next = NULL;
    }
    else
    {
        pt = Alocar(numero);
    }

    return pt;
}

No * Inserir(Lista * lis, No * pt, int numero) { //Inserir Recursivo, 'return resul' realiza o reencadeamento dos nós
    No * resul;

    if(pt != NULL)
    {
        resul = pt;
        if(numero < pt->numero) //Número menor
        {
            resul = Alocar(numero);
            if(pt == lis->inicio) //Estou no início da lista
            {
                lis->inicio = resul;
            }
            resul->next = pt;
            resul->prev = pt->prev; //Ponteiro atual aponta para o ponteiro detrás
            pt->prev = resul; //Ponteiro maior irá apontar para o ponteiro atual
        }
        else //Número maior
        {
            pt->next = Inserir(lis, pt->next, numero);
        }
    }
    else //Final da lista ou Lista vazia
    {
        pt = Alocar(numero);

        pt->prev = lis->fim; //Final da lista
        lis->fim = pt;

        if(lis->inicio == NULL) //Lista vazia
        {
            lis->inicio = pt;
        }

        resul = pt;
    }

    return resul;
}

No * Remover(Lista * lis, No * pt, int numero ) {
    No * resul;

    if(pt != NULL)
    {
        resul = pt;
        if(numero != pt->numero)
        {
            pt->next = Remover(lis, pt->next, numero);
        }
        else //ACHEI!
        {

            resul = pt->next;

            if(pt == lis->fim) //Para não quebrar, basta retornar nulo, e indicar o novo fim
            {
                lis->fim = pt->prev;
            }
            else //Esta condição serve tanto pro 'pt == lis->inicio' ou Meio da lista
            {
                if(pt == lis->inicio)
                {
                    lis->inicio = pt->next;
                }

                resul->prev = pt->prev; //'pt->next->prev = pt->prev', caso 'pt->next' fosse nulo, não faria sentido retornar o anterior de um vetor nulo
            }

            free(pt);
        }
    }
    else
    {
        resul = pt; //Importante para não quebrar o encadeamento
        cout << "Nao encontrado! Encerrando Remover!" << endl;
    }

    return resul;
}

void Imprimir(No * pt, int inverso) {

    if(inverso == 0) //Impressao padrao
    {
        if(pt != NULL)
        {
            cout << "Numero: " << pt->numero << endl;
            Imprimir(pt->next, inverso);
        }
    }
    else //Impressao inversa
    {
        if(pt != NULL)
        {
            cout << "Numero: " << pt->numero << endl;
            Imprimir(pt->prev, inverso);
        }
    }
}

int main() {
    Lista lis;

    Inicializar(&lis);

    Inserir(&lis, lis.inicio, 40);
    Inserir(&lis, lis.inicio, 10);
    Inserir(&lis, lis.inicio, 50);
    Inserir(&lis, lis.inicio, 30);
    Inserir(&lis, lis.inicio, 20);

    cout << "Padrao: " << endl;
    Imprimir(lis.inicio, 0);
    cout << "\nInverso: " << endl;
    Imprimir(lis.fim, 1);

    Remover(&lis, lis.inicio, 0);

    cout << "\n==POS REMOCAO==" << endl;

    cout << "Padrao: " << endl;
    Imprimir(lis.inicio, 0);
    cout << "\nInverso: " << endl;
    Imprimir(lis.fim, 1);

    return 0;
}

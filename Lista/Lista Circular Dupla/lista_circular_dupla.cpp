/*
Made by Gabriel F. Dias for Valtus
10/03/2026
*/
#include <iostream>

using namespace std;

struct No {
    int numero;
    No * prev;
    No * next;
};

struct Lista { //Cabeçalho
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

No * Inserir(Lista * lis, No * pt, int numero) {
    No * resul;

    if(pt != NULL) //Há algo na lista
    {
        resul = pt;
        if(numero < pt->numero) //Numero menor
        {
            resul = Alocar(numero);
            resul->next = pt;
            pt->prev = resul;
            resul->prev = lis->fim;
            lis->inicio = resul;
            lis->fim->next = lis->inicio;
        }
        else //Numero maior
        {
            if(pt->next == lis->inicio) //CASO ESPECIAL, para evitar de voltar pro inicio da lista, evitando loop infinito (inserção final da lista)
            {
                resul = Alocar(numero);
                pt->next = resul;
                resul->next = lis->inicio;
                resul->prev = pt;
                lis->fim = resul;
                lis->inicio->prev = lis->fim;
                resul = pt;
            }
            else //Numero maior e não esta no final da lista. Logo, vai pro próximo
            {
                pt->next = Inserir(lis, pt->next, numero);
            }

        }
    }
    else //Lista vazia
    {
        pt = Alocar(numero);
        if(lis->inicio == NULL) //Lista vazia. Então terei apenas 1 nó, e ele apontará para si mesmo
        {
            lis->inicio = pt;
            lis->fim = pt;

            pt->next = lis->inicio;
            pt->prev = lis->fim;
        }
    }

    return resul;
}

No * Remover(Lista * lis, No * pt, int numero) {
    No * resul;

    if(pt != NULL)
    {
        resul = pt;

        if(numero == pt->numero) //ACHEI!
        {
            if(pt == lis->inicio) //Caso 1: Inicio da lista
            {
                lis->inicio = pt->next;
                pt->next->prev = pt->prev;
                lis->fim->next = pt->next;
                free(pt);
            }
            else
            {
                if(pt == lis->fim) //Caso 2: Fim da lista
                {
                    lis->fim = pt->prev;
                    //pt->prev->next = lis->inicio;
                    lis->inicio->prev = lis->fim;
                    resul = lis->inicio; //Retorna o inicio da lista para o nó anterior, mantendo a circularidade
                    free(pt);
                }
                else //Caso 3: Meio da lista
                {
                    pt->next->prev = pt->prev; //Encadeia o 'próximo->prev' com o detrás
                    resul = pt->next; //Encadeia o 'anterior->next' com o da frente utilizando recursividade
                    free(pt);
                }
            }
        }
        else //Vai pro próximo
        {
            pt->next = Remover(lis, pt->next, numero);
        }
    }
    else
    {
        cout << "Numero nao encontrado! Encerrando Remover()!" << endl;
    }

    return resul;
}

void Imprimir(Lista * lis, No * pt, int inverso) {

    if(pt != NULL)
    {
        cout << "Numero: " << pt->numero << endl;

        if(inverso == 0)
        {
            if(pt->next != lis->inicio)
            {
                Imprimir(lis, pt->next, inverso);
            }
        }
        else //Impressão Inversa
        {
            if(pt->prev != lis->fim)
            {
                Imprimir(lis, pt->prev, inverso);
            }
        }
    }

}

int main() {
    Lista lis;

    Inicializar(&lis);

    Inserir(&lis, lis.inicio, 40);
    Inserir(&lis, lis.inicio, 50);
    Inserir(&lis, lis.inicio, 10);

    Imprimir(&lis, lis.inicio, 0);
    cout << "\nInverso: " << endl;
    Imprimir(&lis, lis.fim, 1);

    cout << "\n==POS REMOCAO==" << endl;
    Remover(&lis, lis.inicio, 40);

    Imprimir(&lis, lis.inicio, 0);
    cout << "\nInverso: " << endl;
    Imprimir(&lis, lis.fim, 1);

    return 0;
}

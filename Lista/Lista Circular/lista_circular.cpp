/*
Made by Gabriel F. Dias for Valtinhus
09/03/2026
*/
#include <iostream>

using namespace std;

struct No {
    int numero;
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

    if(pt != NULL)
    {
        resul = pt;
        if(numero < pt->numero) //Numero menor
        {
            resul = Alocar(numero);
            resul->next = pt;

            if(pt == lis->inicio) //Inicio lista
            {
                lis->inicio = resul;
                lis->fim->next = resul;
            }
        }
        else //Número maior ou igual
        {
            if(pt == lis->fim) //Caso insira número novo no final
            {
                resul = Alocar(numero);
                pt->next = resul; //Aponto para o meu novo final
                resul->next = lis->inicio; //Aponto para o inicio da lista
                lis->fim = resul;
                resul = pt; //Corrijo para o encadeamento fechar corretamente
            }
            else //Recursão padrão
            {
                pt->next = Inserir(lis, pt->next, numero);
            }
        }
    }
    else //Lista vazia ou Final da lista
    {
        pt = Alocar(numero);
        resul = pt;

        if(lis->inicio == NULL)
        {
            lis->inicio = pt;
            lis->fim = pt;
            pt->next = pt;
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
            if(pt == lis->inicio) //Esta no inicio
            {
                lis->inicio = pt->next;
                lis->fim->next = lis->inicio;
                free(pt);
            }
            else //Esta no meio
            {
                resul = pt->next;
                free(pt);
            }
        }
        else
        {
            if(pt->next == lis->fim) //Esta no fim
            {
                pt->next = lis->inicio;
                free(lis->fim);
                lis->fim = pt;
                resul = pt;
            }
            else
            {
                if(pt->next != lis->inicio) //Checagem para não entrar em loop infinito
                {
                    pt->next = Remover(lis, pt->next, numero);
                }
            }
        }
    }

    return resul;
}

void Imprimir(Lista * lis, No * pt) {

    if(pt != NULL)
    {
        cout << "Numero: " << pt->numero << endl;

        if(pt->next != lis->inicio)
        {
            Imprimir(lis, pt->next);
        }
    }
}

int main() {
    Lista lis;

    Inicializar(&lis);

    Inserir(&lis, lis.inicio, 40);
    Inserir(&lis, lis.inicio, 10);
    Inserir(&lis, lis.inicio, 60);
    Inserir(&lis, lis.inicio, 50);
    Inserir(&lis, lis.inicio, 30);
    Inserir(&lis, lis.inicio, 70);
    Inserir(&lis, lis.inicio, 20);

    Imprimir(&lis, lis.inicio);

    Remover(&lis, lis.inicio, 10);
    Remover(&lis, lis.inicio, 70);

    cout << "\nPos Remocao: " << endl;
    Imprimir(&lis, lis.inicio);

    return 0;
}

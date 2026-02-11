#include <iostream>

using namespace std;

struct No {
    No * next;
    float valor;
};

struct Lista {
    No * inicio;
};

void Inicializar(Lista * lis) {
    lis->inicio = NULL;
}

No * Alocar(float numero) {

    No * pt = (No*) malloc(sizeof(No));

    if(pt != NULL)
    {
        pt->next = NULL;
        pt->valor = numero;
    }
    else
    {
        pt = Alocar(numero);
    }

    return pt;
}

void InserirInicio(Lista * lis, float numero) {
    No * pt = Alocar(numero);

    pt->next = lis->inicio;
    lis->inicio = pt;
}


/*
    Meu resul->next vai ser o next que meu 'pt' selecionado vai receber após a recursão;


*/
No * InserirOrdenado(Lista * lis, No * pt, float numero) {
    No * resul;

    if(pt != NULL)
    {
        resul = pt;

        if(pt->valor >= numero)
        {
            resul = Alocar(numero);

            if(pt == lis->inicio)
            {
                resul->next = lis->inicio;
                lis->inicio = resul;
            }
            else
            {
                resul->next = pt;
            }
        }
        else
        {
            pt->next = InserirOrdenado(lis, pt->next, numero);

        }
    }
    else
    {
        resul = Alocar(numero);

        if(lis->inicio == NULL)
        {
            resul->next = lis->inicio; //Retorna o próximo quando voltar da recursão, mantendo a amarração da lista
            lis->inicio = resul; //Atribui valor ao novo inicio da lista
        }
    }

    return resul;
}

void Imprimir(No * pt) {

    if(pt != NULL)
    {
        cout << "numero: " << pt->valor << endl;
        Imprimir(pt->next);
    }

}

No * Remover(Lista * lis, No * pt, float numero) {
    No * resul;

    if(pt != NULL)
    {
        resul = pt;

        if(pt->valor == numero)
        {
            resul = pt->next;

            if(pt == lis->inicio)
            {
                lis->inicio = resul;
            }

            free(pt);
        }
        else
        {
            pt->next = Remover(lis, pt->next, numero);
        }

    }
    else
    {
        cout << "Numero nao encontrado!" << endl;
    }

    return resul;
}

int main() {
    Lista lista;

    Inicializar(&lista);

    /*
    InserirInicio(&lista, 10);
    InserirInicio(&lista, 2);
    InserirInicio(&lista, 1);
    InserirInicio(&lista, 9);
    */

    InserirOrdenado(&lista, lista.inicio, 10);
    InserirOrdenado(&lista, lista.inicio, 2);
    InserirOrdenado(&lista, lista.inicio, 1);
    InserirOrdenado(&lista, lista.inicio, 9);

    Imprimir(lista.inicio);

    Remover(&lista, lista.inicio, 10);

    cout << endl << endl;

    Imprimir(lista.inicio);

    return 0;
}

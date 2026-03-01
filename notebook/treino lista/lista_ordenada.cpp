#include <iostream>

using namespace std;

/**STRUCTS**/
struct Lista {
    int numero;
    Lista * next;
};

struct Cab {
    Lista * inicio;
};

/**FUNCOES**/
void Inicializar(Cab * c) {
    c->inicio = nullptr;
}

Lista * Alocar() {
    Lista * pt;

    pt = (Lista*) malloc(sizeof(Lista));

    if(pt == nullptr)
    {
        pt = Alocar();
    }

    return pt;
}

Lista * CriarLista(int numero) {
    Lista * pt;

    pt = Alocar();

    pt->numero = numero;

    return pt;
}

Lista * InserirOrdenado(Cab * c, Lista * pt, int numero) {
    Lista * resul;

    if(pt != NULL)
    {
        resul = CriarLista(numero);
        if(pt->numero >= numero) //Caso correto
        {
            if(pt == c->inicio)
            {

            }

        }
    }
}

void Imprimir(Lista * pt) {

    if(pt != nullptr)
    {
        cout << "Numero: " << pt->numero << endl;
        Imprimir(pt->next);
    }

}

Lista * Remover(Cab * c, Lista * pt, int numero) {
    Lista * resul;

    if(pt != nullptr)
    {
        //cout << "entrou" << endl;
        resul = pt;
        if(pt->numero == numero)
        {
            //cout << "igual" << endl;
            resul = pt->next;
            if(pt == c->inicio)
            {
                c->inicio = resul; //Substitui o inicio da lista pelo pt->next
            }
            free(pt);
        }
        else
        {
            //cout << "recursao" << endl;
            pt->next = Remover(c, pt->next, numero);
        }
    }
    return resul;
}

/**MAIN**/
int main() {
    Cab lista;

    Inicializar(&lista);

    InserirOrdenado(&lista, lista.inicio, 10);
    InserirOrdenado(&lista, lista.inicio, 9);
    InserirOrdenado(&lista, lista.inicio, 0);
    InserirOrdenado(&lista, lista.inicio, 90);
    InserirOrdenado(&lista, lista.inicio, 42);
    InserirOrdenado(&lista, lista.inicio, 17);
    InserirOrdenado(&lista, lista.inicio, 39);

    Imprimir(lista.inicio);

    Remover(&lista, lista.inicio, 10);

    cout << "\n\nApos o Remover(): " << endl;

    Imprimir(lista.inicio);

    return 0;
}

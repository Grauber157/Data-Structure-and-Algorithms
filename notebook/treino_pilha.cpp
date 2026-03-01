#include <iostream>

using namespace std;

struct Registro {
    float valor;
    Registro * next;
};

struct Cab {
    int quant;
    Registro * topo;
};

void InicializarPilha(Cab * c) {
    c->quant = 0;
    c->topo = nullptr;
}

void Push(Cab * c, float valor) {
    Registro * pt;

    pt = (Registro*) malloc(sizeof(Registro)); // Aloca dinamicamente

    pt->valor = valor; // Atribui valor ao registro

    pt->next = c->topo; // Aponta pro registro que estava no topo

    c->topo = pt; // O ponteiro pt agora é o novo topo

    c->quant++;
}

float Pop(Cab * c) {
    float resul = 0;
    Registro * pt = c->topo;

    if(pt != nullptr)
    {
        resul = pt->valor;
        c->topo = pt->next;
        free(pt);
    }
    else
    {
        cout << "Lista esta vazia!" << endl;
    }

    return resul;
}

void Imprimir(Registro * pt) {

    if(pt != nullptr)
    {
        cout << "Registro: " << pt->valor << endl;

        Imprimir(pt->next);
    }
}

int main() {
    Cab pilha;
    Registro * reg;
    int op;
    float num;

    InicializarPilha(&pilha);

    do
    {
        system("cls");
        cout << "1 - Inserir" << endl;
        cout << "2 - Retirar" << endl;
        cout << "3 - Imprimir" << endl;
        cout << "opcao: " << endl;
        cin >> op;

        switch(op)
        {
            case 1:
                cout << "Digite um numero: " << endl;
                cin >> num;
                Push(&pilha, num);
                break;

            case 2:
                cout << "Numero Removido: " << Pop(&pilha) << endl;
                system("pause");
                break;

            case 3:
                reg = pilha.topo;
                Imprimir(reg);
                system("pause");
                break;

            case 0:
                cout << "Encerrando o programa..." << endl;
                break;
        }

    }while(op != 0);

    return 0;
}

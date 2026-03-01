#include <iostream>

using namespace std;

struct Registro {
    int chave;
    int valor;
    Registro * next;
};

struct Cab {
    Registro * inicio;
    int quant;
    int incremento;
};

void InicializarCab(Cab * c) {
    c->inicio = nullptr;
    c->quant = 0;
    c->incremento = 0;
};

/**CRUDZÃO DA MASSA**/

void Create(Cab * c, int valor) {
    Registro * pt;

    pt = (Registro*) malloc(sizeof(Registro)); // Alocacao dinamica

    pt->chave = c->incremento;
    pt->valor = valor;

    pt->next = c->inicio;
    c->inicio = pt;

    c->quant++;
    c->incremento++;
}

void Read(Cab c) {
    Registro * pt = c.inicio;

    if(pt != nullptr)
    {
        cout << "Registro [" << pt->chave << "]: " << pt->valor << endl;

        c.inicio = pt->next;

        Read(c);
    }
}

void Update() {

}

Registro * Delete(Cab * c, Registro * pt, int chave) {
    Registro * resul;

    if(pt != nullptr)
    {
        if(pt->chave == chave) // CASO SEJA O PRIMEIRO ELEMENTO
        {
            resul = pt->next; // já deixo o proximo registro indicado pra substituir o atual
            if(pt == c->inicio)
            {
                c->inicio = resul; // Substitui quem vai ser o inicio
            }
            free(pt);
        }
        else
        {
            pt->next = Delete(c, pt->next, chave);
        }
    }
}

int main() {
    int op, num;
    Cab lista;
    Registro * reg;

    InicializarCab(&lista);

    do
    {
        system("cls");
        cout << "1 - Inserir (Create)" << endl;
        cout << "2 - Imprimir (Read)" << endl;
        cout << "3 - Atualizar (Update)" << endl;
        cout << "4 - Deletar (Delete)" << endl;
        cout << "0 - Sair" << endl;
        cout << "opcao: " << endl;
        cin >> op;

        switch(op)
        {
            case 1:
                cout << "Digite o valor: ";
                cin >> num;
                system("cls");
                Create(&lista, num);
                system("pause");
                break;

            case 2:
                system("cls");
                cout << "====CABECALHO====" << endl;
                cout << "=quantidade: " << lista.quant << "=" << endl << endl;
                Read(lista);
                system("pause");
                break;

            case 3:
                Update();
                break;

            case 4:
                cout << "Digite um numero: " << endl;
                cin >> num;

                reg = lista.inicio;

                Delete(&lista, reg, num);
                break;

            case 0:

                break;
        }

    } while(op != 0);

    return 0;
}

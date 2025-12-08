#include <iostream>

using namespace std;

/**STRUCTS*/
struct No {
    string nome;
    No * esq;
    No * dir;
};

struct Arvore {
    No * raiz;
};

/**FUNÇÕES*/

void Inicializar(Arvore * arv) {
    arv->raiz = NULL;
}

No * Alocar(string nome) {
    No * pt = new No;

    pt->esq = NULL;
    pt->dir = NULL;
    pt->nome = nome;

    return pt;
}

No * Inserir(Arvore * arv, No * pt, string nome) {
    No * resul;

    if(pt != NULL)
    {
        resul = pt;

        if(pt->nome > nome)
        {
            resul->esq = Inserir(arv, pt->esq, nome);
        }
        else
        {
            if(pt->nome < nome)
            {
                resul->dir = Inserir(arv, pt->dir, nome);
            }
            else
            {
                cout << "Já existe esse registro!";
            }
        }

    }
    else
    {
        //Caso haja raiz, então inserimos um nó padrão
        if(arv->raiz != NULL)
        {
            resul = Alocar(nome);
        }
        //Caso não haja raiz
        else
        {
            resul = Alocar(nome);
            arv->raiz = resul;
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
    else
    {
        resul = NULL;
    }

    return resul;
}

No * Remover(No * pt, string nome) {
    No * resul, * aux;

    //1º parte: Encontrar o número/nome que quero excluir dentro dos nós;
    //2º parte: Examinar o caso do nó que vamos remover(nó folha, 1 filho ou 2 filhos);

    //1ºPARTE
    if(pt != NULL)
    {
        resul = pt;
        if(pt->nome > nome) //Nome menor, vou pro nó da esquerda
        {
            resul->esq = Remover(pt->esq, nome);
        }
        else
        {
            if(pt->nome < nome) //Nome maior, vou pro nó da direita
            {
                resul->dir = Remover(pt->dir, nome);
            }
            //Nome igual, achamos o nó a ser excluido, logo...
            //2ºPARTE
            else
            {
                //Nó folha
                if(pt->esq == NULL && pt->dir == NULL)
                {
                    resul = NULL;
                    free(pt);
                }
                else
                {
                    //Nó com 1 filho
                    if(pt->esq == NULL)
                    {
                        resul = pt->dir;
                        free(pt);
                    }
                    else
                    {
                        if(pt->dir == NULL)
                        {
                            resul = pt->esq;
                            free(pt);
                        }
                        //Nó com 2 filhos
                        else
                        {
                            aux = AcharMenor(pt->dir);

                            pt->nome = aux->nome;
                            resul->dir = Remover(pt->dir, aux->nome);
                        }
                    }
                }
            }
        }
    }
    else
    {
        resul = NULL;
        cout << "Arvore Vazia!" << endl;
    }

    return resul;
}

void Imprimir(No * pt, string ordem) {
    if(pt != NULL)
    {
        if(ordem == "PRE")
        {
            cout << "Nome: " << pt->nome << endl;
            Imprimir(pt->esq, ordem);
            Imprimir(pt->dir, ordem);
        }
        else
        {
            if(ordem == "CEN")
            {
                Imprimir(pt->esq, ordem);
                cout << "Nome: " << pt->nome << endl;
                Imprimir(pt->dir, ordem);
            }
            else
            {
                if(ordem == "POS")
                {
                    Imprimir(pt->esq, ordem);
                    Imprimir(pt->dir, ordem);
                    cout << "Nome: " << pt->nome << endl;
                }
                else
                {
                    cout << "Ordem invalida!" << endl;
                }
            }
        }
    }
}

int main() {
    Arvore arv;

    Inicializar(&arv);

    //A-B-C-D-E-F-G-H-I-J-K-L-M-N-O-P-Q-R-S-T-U-V-W-X-Y-Z

    Inserir(&arv, arv.raiz, "Jorge");
    Inserir(&arv, arv.raiz, "Gabriel");
    Inserir(&arv, arv.raiz, "Maria");
    Inserir(&arv, arv.raiz, "Douglas");
    Inserir(&arv, arv.raiz, "Mario");
    Inserir(&arv, arv.raiz, "Valter");
    Inserir(&arv, arv.raiz, "Rogerio");
    Inserir(&arv, arv.raiz, "Roberto");
    Inserir(&arv, arv.raiz, "Jensen");
    Inserir(&arv, arv.raiz, "Marie");
    Inserir(&arv, arv.raiz, "Udison");

    Imprimir(arv.raiz, "PRE");

    cout << endl;

    Remover(arv.raiz, "Rogerio");

    Imprimir(arv.raiz, "PRE");

    return 0;
}

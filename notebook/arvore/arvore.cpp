#include <iostream>

using namespace std;

struct Arvore {
    Arvore * esq;
    Arvore * dir;
    int numero;
};

struct Cab {
    Arvore * raiz;
};

void Inicializar(Cab * c) {
    c->raiz = NULL;
}

Arvore * Alocar() {
    Arvore * pt;

    pt = (Arvore*) malloc(sizeof(Arvore));

    if(pt == NULL)
    {
        pt = Alocar();
    }

    return pt;
}

Arvore * InserirBST(Cab * c, Arvore * pt, int numero) {
    Arvore * resul = NULL;

    if(c->raiz != NULL)
    {
        if(pt != NULL) // pt NÃO NULO
        {
            resul = pt;
            if(pt->numero == numero)
            {
                resul = NULL;
            }
            else
            {
                if(pt->numero > numero) //Vai para a esquerda
                {
                    pt->esq = InserirBST(c, pt->esq, numero);
                }
                else
                {
                    pt->dir = InserirBST(c, pt->dir, numero);
                }
            }
        }
        else //pt NULO
        {
            pt = Alocar();
            pt->esq = NULL;
            pt->dir = NULL;
            pt->numero = numero;
            resul = pt;
        }

    }
    else
    {
        pt = Alocar();
        pt->esq = NULL;
        pt->dir = NULL;
        pt->numero = numero;
        c->raiz = pt;
    }

    return resul;
}

Arvore * Remover(Cab * c, Arvore * pt) {
    Arvore * resul = NULL;

    if(c->raiz != NULL)
    {
        if(c->raiz == pt && pt->esq == NULL && pt->dir == NULL) //Caso tenha apenas a raiz na árvore
        {
            cout << "Raiz Removida: " << pt->numero << endl;
            free(pt);
            c->raiz = NULL;
        }
        else //Caso tenha mais nós além da raiz
        {
            resul = pt;
            if(pt->esq != NULL)
            {
                pt->esq = Remover(c, pt->esq);
            }
            else
            {
                if(pt->dir != NULL)
                {
                    pt->dir = Remover(c, pt->dir);
                }
                else //esq && dir == NULL
                {
                    cout << "Numero removido: " << pt->numero << endl;
                    pt = NULL;
                    resul = pt;
                    free(pt);
                }
            }
        }
    }
    else
    {
        cout << "Arvore Vazia!" << endl;
    }

    return resul;
}

int Altura(Arvore * pt) { //Mede a altura
    int resul, resul_esq, resul_dir;

    if(pt != NULL)
    {
        resul_esq = Altura(pt->esq) + 1;
        resul_dir = Altura(pt->dir) + 1;
        if(resul_esq >= resul_dir)
        {
            resul = resul_esq;
        }
        else
        {
            resul = resul_dir;
        }
    }
    else
    {
        resul = -1;
    }

    return resul;
}

void Imprimir(Arvore * pt, string tipo) { //TERMINAR
    if(tipo == "PRE")
    {
        if(pt != NULL)
        {
            cout << "Numero: " << pt->numero << endl;
            Imprimir(pt->esq, tipo);
            Imprimir(pt->dir, tipo);

        }
    }
    else
    {
        if(tipo == "CEN")
        {
            if(pt != NULL)
            {
                Imprimir(pt->esq, tipo);
                cout << "Numero: " << pt->numero << endl;
                Imprimir(pt->dir, tipo);

            }
        }
        else
        {
            if(tipo == "POS")
            {
                if(pt != NULL)
                {
                    Imprimir(pt->esq, tipo);
                    Imprimir(pt->dir, tipo);
                    cout << "Numero: " << pt->numero << endl;
                }
            }
        }
    }

}

int main() {
    Cab arvore;

    Inicializar(&arvore);

    InserirBST(&arvore, arvore.raiz, 10);
    InserirBST(&arvore, arvore.raiz, 9);
    InserirBST(&arvore, arvore.raiz, 12);
    InserirBST(&arvore, arvore.raiz, 2);

    Imprimir(arvore.raiz, "PRE");
    cout << endl;
    Remover(&arvore, arvore.raiz);
    Remover(&arvore, arvore.raiz);
    Remover(&arvore, arvore.raiz);
    Remover(&arvore, arvore.raiz);
    Remover(&arvore, arvore.raiz);
    cout << endl;
    Imprimir(arvore.raiz, "PRE");

    return 0;
}

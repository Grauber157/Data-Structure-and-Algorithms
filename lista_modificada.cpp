#include <iostream>

using namespace std;

/** STRUCTS **/

struct Lista { // LISTA
    int num;
    Lista * next;
};

struct Cab { // CABEÇALHO DA LISTA
    Lista * inicio;
    int quant;
};

/** FUNÇÕES **/

void IniciarLista(Cab * c) { // INICIALIZA
    c->inicio = nullptr;
    c->quant = 0;
}

Lista * CriarPonteiro() { // ALOCACAO DINAMICA
    Lista * pt, * resul;

    pt = (Lista *) malloc(sizeof(Lista));

    if(pt != nullptr)
    {
        resul = pt;
    }
    else
    {
        resul = CriarPonteiro();
    }

    return resul;
}

void Inserir(Cab * c, int n) { // QUESTAO 1
    Lista * pt;

    pt = CriarPonteiro(); // Aloca Dinamicamente a nova lista

    pt->num = n; // Atribui os valores na lista

    pt->next = c->inicio; // Nova lista aponta para a 'antiga' lista de inicio dita pelo cabeçalho
    c->inicio = pt; // O cabeçalho indica a nova lista como lista de inicio
    c->quant++;
}

Lista * Remover(Cab * c, Lista * pt, int n) { // QUESTAO 2
	Lista * resul;

    if(pt != nullptr)
    {
    	resul = pt;
    	if(pt->num == n) // Caso deletar o primeiro registro
    	{
    		// Elimina o elemento
    		resul = pt->next;
    		
    		if(pt == c->inicio) // Assegura o caso para deletar o primeiro registro
    		{
    			c->inicio = resul;
			}
			// Atualiza totais
			c->quant--;
		}
		else
		{
			pt->next = Remover(c, pt->next, n);
		}
	}
	
	return resul;
}

void Imprimir(Cab c) { // QUESTAO 3
    Lista * pt;

    pt = c.inicio;

    if(pt != nullptr)
    {
        cout << "Numero: " << pt->num << endl;

        c.inicio = pt->next; // Usar o auxiliar 'pt' para passar o 'c' para o proximo registro
        Imprimir(c);
    }

}

int MedirComprimento(Cab c) { // QUESTAO 4
    int total = 0;
    Lista * pt = c.inicio;

    if(pt != nullptr)
    {
        total += sizeof(pt);

        c.inicio = pt->next; // proxima lista

        total += MedirComprimento(c); // Recursividade
    }

    return total;
}

int Buscar(Cab c, int n) { // QUESTAO 5
    Lista * pt = c.inicio;
    int cont = 0;

    if(pt != nullptr)
    {
        if(pt->num == n)
        {
            cont++;
        }

        c.inicio = pt->next;

        cont += Buscar(c, n); // Recursividade
    }

    return cont;
}

void Substituir(Cab c, int n_atual, int n_novo) { // QUESTAO 6
    Lista * pt = c.inicio;

    if(pt != nullptr) // Ponteiro nao nulo
    {
        if(pt->num == n_atual) // Numero a ser substituido igual ao da lista atual
        {
            pt->num = n_novo; // Substituicao pelo numero novo
        }

        c.inicio = pt->next;

        Substituir(c, n_atual, n_novo);
    }
}

void Dividir(Cab c, int n, Cab * divi_maior, Cab * divi_menor) { // QUESTAO 7
    Lista * pt = c.inicio;

    // Criar duas listas auxiliares para guardar os valores e imprimir elas
    /*
	Cab lista_maior;
    Cab lista_menor;
    IniciarLista(&lista_maior);
    IniciarLista(&lista_menor);
	*/

    while(pt != nullptr) // Percorre todos os registros da lista
    {
        if(pt->num > n)
        {
            Inserir(divi_maior, pt->num);
        }
        else if(pt->num < n)
        {
            Inserir(divi_menor, pt->num);
        }

        // Anda para o proximo registro da lista principal
        c.inicio = pt->next;
        pt = c.inicio;
    }

    cout << "\n\n+---LISTA MAIOR---+\n\n";
    Imprimir(*divi_maior);
    cout << "\n-----------------------\n";

    cout << "\n\n+---LISTA MENOR---+\n\n";
    Imprimir(*divi_menor);
    cout << "\n-----------------------\n";

    //free(&lista_maior);
    //free(&lista_menor);
}

void Intersecao(Cab c1, Cab c2) { // QUESTAO 8
    Lista * pt1 = c1.inicio;
    Lista * pt2 = c2.inicio;
    Lista * aux = c2.inicio;
    Cab inter;

    IniciarLista(&inter);

    // Escolher o primeiro elemento da lista 1 e comparar com os elementos da lista 2

    while(pt1 != nullptr)
    {
        while(pt2 != nullptr)
        {
            if(pt1->num == pt2->num)
            {
                Inserir(&inter, pt1->num);
            }

            c2.inicio = pt2->next;

             pt2 = c2.inicio;

            //Intersecao(c1, c2);
        }
        pt2 = aux;

        c1.inicio = pt1->next;
        pt1 = c1.inicio;
    }

    Imprimir(inter);
}

/** OPÇÕES DO 'switch()' **/

void Opcao1(Cab * lista1, Cab * lista2) { // CASE INSERIR - 1
    int op, numero;

    cout << "\n---INSERIR EM:---" << endl;
    cout << "1 - Lista 1" << endl;
    cout << "2 - Lista 2" << endl;
    cin >> op;

    switch(op)
    {
        case 1:
            system("cls");
            cout << "--INSERIR LISTA 1--" << endl;
            cout << "Digite um numero(Lista 1): ";
            cin >> numero;
            Inserir(lista1, numero);
        break;
        case 2:
            system("cls");
            cout << "--INSERIR LISTA 2--" << endl;
            cout << "Digite um numero(Lista 2): ";
            cin >> numero;
            Inserir(lista2, numero);
        break;
    }
    system("pause");
    system("cls");
}

void Opcao2(Cab * lista1, Cab * lista2) { // CASE REMOVER - 2
    int op, numero;
    Lista * pt;

    cout << "\n+---REMOVER DE---+" << endl;
    cout << "1 - Lista 1" << endl;
    cout << "2 - Lista 2" << endl;
    cin >> op;

    switch(op)
    {
        case 1:
            system("cls");
            cout << "+---REMOVER DE LISTA 1---+" << endl << endl;
            cout << "Digite um numero: ";
            cin >> numero;
            cout << "-------------" << endl;
            pt = lista1->inicio; // Atribui valor de pt
            Remover(lista1, pt, numero);
            system("pause");
            system("cls");
        break;
        case 2:
            system("cls");
            cout << "+---REMOVER DE LISTA 2---+" << endl << endl;
            cout << "Digite um numero: ";
            cin >> numero;
            cout << "-------------" << endl;
            pt = lista2->inicio; // Atribui valor de pt
            Remover(lista2, pt, numero);
            system("pause");
            system("cls");
        break;
    }
}

void Opcao3(Cab lista1, Cab lista2) { // CASE IMPRIMIR - 3
    system("cls");
    cout << "+----------VISUALIZACAO------------+" << endl << endl;
    cout << "-------------LISTA 1------------" << endl;
    Imprimir(lista1);
    cout << "+-------+" << endl;
    cout << "Quantidade Total: " << lista1.quant << endl << endl;
    cout << "--------------------------------" << endl << endl << endl;

    cout << "-------------LISTA 2------------" << endl;
    Imprimir(lista2);
    cout << "+-------+" << endl;
    cout << "Quantidade Total: " << lista2.quant << endl << endl;
    cout << "--------------------------------" << endl << endl;

    system("pause");
    system("cls");
}

void Opcao4(Cab lista1, Cab lista2) { // CASE MEDIR COMPRIMENTO - 4
    system("cls");
    cout << "---Comprimento Lista 1---" << endl;
    cout << "Quantidade de Elementos: " << lista1.quant << endl;
    cout << "Memoria Alocada: " << MedirComprimento(lista1) << endl << endl;

    cout << "---Comprimento Lista 2---" << endl;
    cout << "Quantidade de Elementos: " << lista2.quant << endl;
    cout << "Memoria Alocada: " << MedirComprimento(lista2) << endl << endl;

    system("pause");
    system("cls");
}

void Opcao5(Cab lista1, Cab lista2) { // CASE BUSCAR - 5
    int num, op;
    system("cls");

    cout << "+---BUSCAR EM---+" << endl;
    cout << "1 - Lista 1" << endl;
    cout << "2 - Lista 2" << endl;
    cin >> op;

    switch(op)
    {
        case 1:
            system("cls");
            cout << "+---BUSCAR EM LISTA 1---+" << endl << endl;
            cout << "Digite o numero: ";
            cin >> num;

            cout << "\n\nQuantidades de ocorrencia: " << Buscar(lista1, num) << endl;
            system("pause");
            system("cls");
        break;

        case 2:
            system("cls");
            cout << "+---BUSCAR EM LISTA 2---+" << endl << endl;
            cout << "Digite o numero: ";
            cin >> num;

            cout << "\n\nQuantidades de ocorrencia: " << Buscar(lista2, num) << endl;
            system("pause");
            system("cls");
        break;
    }


}

void Opcao6(Cab lista1, Cab lista2) { // CASE SUBSTITUIR - 6
    int op, num_atual, num_novo;

    system("cls");

    cout << "+---SUBSTITUIR EM---+" << endl;
    cout << "1 - Lista 1" << endl;
    cout << "2 - Lista 2" << endl;
    cin >> op;

    switch(op)
    {
        case 1:
            system("cls");
            cout << "+---SUBSTITUIR EM LISTA 1---+" << endl << endl;

            cout << "Digite o numero a ser substituido: " << endl;
            cin >> num_atual;

            cout << "\nDigite o substituto: " << endl;
            cin >> num_novo;

            Substituir(lista1, num_atual, num_novo);

            cout << "\n\n-----------------------\n\n";

            Imprimir(lista1);

            system("pause");
            system("cls");
        break;

        case 2:
            system("cls");
            cout << "+---SUBSTITUIR EM LISTA 2---+" << endl << endl;

            cout << "Digite o numero a ser substituido: " << endl;
            cin >> num_atual;

            cout << "\nDigite o substituto: " << endl;
            cin >> num_novo;

            Substituir(lista2, num_atual, num_novo);

            cout << "\n\n-----------------------\n\n";

            Imprimir(lista2);

            system("pause");
            system("cls");
        break;
    }
}

void Opcao7(Cab lista1, Cab lista2, Cab * divi_maior, Cab * divi_menor) { // CASE DIVIDIR - 7
    int op, num;
	
	IniciarLista(divi_maior);
	IniciarLista(divi_menor);
	
    system("cls");

    cout << "+---DIVIDIR EM---+" << endl;
    cout << "1 - Lista 1" << endl;
    cout << "2 - Lista 2" << endl;
    cin >> op;
    
    switch(op)
    {
        case 1:
            system("cls");
            cout << "+---DIVIDIR EM LISTA 1---+" << endl << endl;

            cout << "Digite o numero para dividir: " << endl;
            cin >> num;

            Dividir(lista1, num, divi_maior, divi_menor);

            //cout << "\n\n-----------------------\n\n";

            system("pause");
            system("cls");
        break;

        case 2:
            system("cls");
            cout << "+---DIVIDIR EM LISTA 2---+" << endl << endl;

            cout << "Digite um numero para dividir: " << endl;
            cin >> num;

            Dividir(lista2, num, divi_maior, divi_menor);

            //cout << "\n\n-----------------------\n\n";

            system("pause");
            system("cls");
        break;
    }
}

void Opcao8(Cab lista1, Cab lista2) { // INTERSECAO - 8
    system("cls");
    cout << "+---INTERSECAO---+\n\n";

    Intersecao(lista1, lista2);
    system("pause");
    system("cls");
}

int main() {
    Cab lista1;
    Cab lista2;
    Cab dividir1;
    Cab dividir2;
    int op, numero;

    IniciarLista(&lista1);
    IniciarLista(&lista2);

    do {
        cout << "-----------TESTE DE OPERACAO COM LISTAS-----------" << endl;
        cout << "1 - Inserir em lista (Lista 1 ou Lista 2)" << endl;
        cout << "2 - Remover da lista (Lista 1 ou Lista 2)" << endl;
        cout << "3 - Imprimir as listas" << endl;
        cout << "4 - Calcular comprimento das listas" << endl;
        cout << "5 - Contar ocorrencias de um numero em uma lista (Lista 1 ou Lista 2)" << endl;
        cout << "6 - Substituicao de ocorrencias de um numero em uma lista (Lista 1 ou Lista 2)" << endl;
        cout << "7 - Dividir uma lista em duas (Lista 1 ou Lista 2)" << endl;
        cout << "8 - Intersecao das listas" << endl;
        cout << "0 - Sair" << endl;
        cout << "Opcao: ";
        cin >> op;

        switch(op)
        {
            case 1:
                Opcao1(&lista1, &lista2);
            	break;

            case 2:
                Opcao2(&lista1, &lista2);
            	break;

            case 3:
                Opcao3(lista1, lista2);
            	break;

            case 4:
                Opcao4(lista1, lista2);
            	break;

            case 5:
                Opcao5(lista1, lista2);
            	break;

            case 6:
                Opcao6(lista1, lista2);
            	break;

            case 7:
                Opcao7(lista1, lista2, &dividir1, &dividir2);
                
                /*
                cout << "\n\n\n\n";
                cout << "POS-FUNCAO\n"; 
				cout << "MAIOR\n";
                Imprimir(dividir1);
                cout << "\nMENOR\n";
                Imprimir(dividir2);
                */
                
            	break;

            case 8:
                Opcao8(lista1, lista2);
            	break;

            case 0:
                system("cls");
                cout << "Finalizando programa..." << endl;
            	break;

            default:
                system("cls");
            	break;
        }
    } while(op != 0);
    return 0;
}

#include <stdlib.h>	      // malloc, free, exit
#include <stdio.h>	      // scanf, printf
#include <stdbool.h>	  //true, false
#include <string.h>	      //funções de string

#define  MAXF  3	// máximo de elementos permitidos na fila
#define MAXI 2      // máximo de itens permitidos por cliente
//necessário o número máximo de itens apenas para comparações nos laços de repetições
#define MAXE 15     //número de elementos do arquivo cardapio.txt

struct cliente{                    //definindo e declarando a struct cliente
	char cliente[100];             //nome do cliente
	item comanda[15];	           //vetor de itens chamado comanda
	float totalConsumido;          //total consumido em R$ por cada cliente
};
typedef struct cliente cliente;    //redefinindo o nome struct cliente para cliente

struct filaClientes{                     //definindo e declarando a struct cliente
	cliente elementos[MAXF];             //conjunto de elementos do tipo cliente
	int n_elem;		                     //número de elementos
	int primeiro;	                     //posição do primeiro elemento
	int ultimo;		                     //primeira posicao livre
};
typedef struct filaClientes filaClientes;    //redefinindo o nome struct filaClientes para filaClientes

filaClientes *criar()                           //função *criar* do tad filaClientes
{	
	filaClientes *FC;                           //declaração da filaClientes FC por referência
		
	FC = (filaClientes*) malloc(sizeof(filaClientes));
	//alocando memória para a filaClientes FC
	if (FC != NULL) {                           // alocou corretamente
		FC->n_elem = 0;
		//número de elementos da filaClientes FC recebe 0
		FC->primeiro = 0;
		//posição do primeiro elemento recebe 0 (vazia)
		FC->ultimo = 0;
		//posição do último elemento recebe 0 (vazia)
	}
	
	return FC;                                  //retorna a filaClientes FC
}

void destruir(filaClientes *FC)                 //função  *destruir* do tad filaClientes
{ 
	if(FC != NULL) free(FC);
	//caso a alocação da fila tenha dado certo (!= NULL), libera a memória da filaClientes
}

bool vazia(filaClientes *FC)                    //função *vazia* do tad filaClientes 
{    
	if(FC->n_elem == 0) return true;            //se o número de elementos for = 0, retorna true
	else return false;                          //senão, retorna false
}

bool cheia(filaClientes *FC)                    //função *cheia* do tad filaClientes
{
	if(FC->n_elem == MAXF) return true;
	//se o número de elementos da filaClientes for = ao máximo permitido, retorna true (está cheia)
	else return false;                          //senão, retorna false
}

cliente leItensCliente(item *menu, cliente X){
	
	scanf("%s", &X.cliente);                      //lendo o campo cliente de cada elemento
	for(int i=0; i<(MAXI); i++){                  //for para percorrer o campo comanda de cada elemento
		scanf("%d", &X.comanda[i].codigo);        //lendo o campo codigo da comanda de itens
		scanf("%s", &X.comanda[i].refeicao);        //lendo o campo refeição da comanda de itens
		scanf("%f", &X.comanda[i].preco);         //lendo o campo preço da comanda de itens
	}

	return X;
}

bool insere(filaClientes *FC, cliente X)        //função *insere* do tad filaClientes
{
		
	if(cheia(FC) == true) {                     //se a filaClientes estiver cheia
		return false;                           //retorna false, não tem como inserir
	}
	//senão:
	FC->elementos[FC->ultimo] = X;                //recebe X na posição do último elemento
	FC->n_elem = FC->n_elem + 1;                  //adiciona 1 no número de elementos
	
	if(FC->ultimo == (MAXF-1)) FC->ultimo = 0;
	//se a posição (número) do último elemento for igual ao máximo permitido - 1, então a posição
	//do último elemento recebe 0 (a posição disponível é a posição 0)
	else FC->ultimo = FC->ultimo + 1;
	//senão a posição do último elemento recebe a própria posição + 1; a posição disponível recebe
	//a próxima posição
	
	return true;                                //retorna true
}

void imprimeElemento(cliente *Y)                 //função *auxiliar* imprimeElemento
{

	printf("\n\nCliente: %s\n", Y->cliente);                    //imprime o campo cliente de cada elemento
	for(int i=0; i<(MAXI); i++){
	//for para percorrer o vetor do campo comanda de cada elemento
		printf("\tCódigo da refeição: %d\n", Y->comanda[i].codigo);    
		//imprime o campo codigo da comanda de itens de cada elemento
		printf("\tRefeição: %s\n", Y->comanda[i].refeicao); 
		//imprime o campo refeição da comanda de itens de cada elemento
		printf("\tPreço refeição: %.2f\n", Y->comanda[i].preco);
		//imprime o campo preço da comanda de itens de cada elemento
	}
	printf("  Preço total: R$%.2f\n", Y->totalConsumido);
}

bool retira(filaClientes *FC, cliente *X)        //função *retira* do tad filaClientes
{

	if(vazia(FC) == true) {                     //se a filaClientes estiver vazia
		return false;                           //retorna false, não tem como retirar
	}
	// senão:
	*X = FC->elementos[FC->primeiro];           //o elemento recebe a posição do primeiro elemento
	FC->n_elem = FC->n_elem - 1;                //subtrai 1 do número de elementos

	if(FC->primeiro == (MAXF-1)) FC->primeiro = 0;
	//se a posição do primeiro elemento é igual ao máximo permitido - 1, então a posição do primeiro
	//elemento recebe 0
	else FC->primeiro = FC->primeiro + 1;
	//senão a posição do primeiro elemento recebe a própria posição + 1

	return true;                                //retorna true
}

filaClientes *total(filaClientes *FC, cliente X)
//função *auxiliar* para mostrar o total consumido por cada cliente
{

	int i;
	filaClientes *auxiliar;                    //definindo uma fila auxiliar
	auxiliar = criar();

	while(vazia(FC) == false){                 //enquanto a fila FC não for vazia
		float soma=0;                      //definindo a variável soma com um número pequeno
		retira(FC, &X);                        //retira os elemento
		for(i=0; i<(MAXI); i++){
			soma = soma + X.comanda[i].preco;          //soma os elementos
		}
		X.totalConsumido = soma;           //o campo totalConsumido recebe o valor da soma dos itens
		insere(auxiliar, X);               //insere os elemento na fila auxiliar
	}
	while(vazia(auxiliar) == false){           //voltando os elementos para a fila FC
		retira(auxiliar, &X);                  //retira os elementos da fila auxiliar
		insere(FC, X); 	                       //insere os elementos na fila FC
	}
	return FC;                                 //retorna a fila com oa soma total de cada clientes
}

void imprimeFilaClientes(filaClientes *FC, cliente X)
//função *auxiliar* para imprimir a filaClientes
{

	filaClientes *auxiliar;                         //definindo uma fila auxiliar
	auxiliar = criar();
	int i;

	while(vazia(FC) == false){                      //while para percorrer a lista FC
		retira(FC, &X);                             //retira os elementos da fila FC
		printf("Cliente: %s\n", X.cliente);                    //imprime o campo cliente de cada elemento
		for(i=0; i<(MAXI); i++){
		//for para percorrer o vetor do campo comanda de cada elemento
			printf("\tCódigo: %d\n", X.comanda[i].codigo);    
			//imprime o campo codigo da comanda de itens de cada elemento
			printf("\tRefeição: %s\n", X.comanda[i].refeicao); 
			//imprime o campo refeição da comanda de itens de cada elemento
			printf("\tPreço da refeição: R$%.2f\n", X.comanda[i].preco);
			//imprime o campo preço da comanda de itens de cada elemento
		}
		printf("  Preço total: R$%.2f\n\n", X.totalConsumido);
		//imprime o campo totalConsumido de cada elemento
		insere(auxiliar, X);                        //insere o elemento na fila auxiliar
	}

	while(vazia(auxiliar) == false){                //while para percorrer a lista auxiliar
		retira(auxiliar, &X);                       //retira os elementos da fila auxiliar
		insere(FC, X);                              //insere os elementos na fila FC
	}

}

int main(){

	filaClientes *FC;                          //declarando a filaClientes FC
	cliente fregues;                           //declarando a variável fregues do tipo cliente

	FC = criar();                              //criando a filaClientes FC
	if(FC == NULL){                            //tratamento de erro
		printf("ERRO na alocação da filaClientes\n");
	}

	item menu[MAXE];                           //declarando vetor de itens chamado menu
	cardapio(menu, MAXE);                      //abrindo o cardápio

	while(cheia(FC) == false){                 //enquanto a filaClientes não estiver vazia...
		printf("\nInsira o nome do cliente, o código, nome e preço da refeição, respectivamente.\n");
		insere(FC, fregues);	               //...insere elementos
	}

	printf("\nLista dos clientes, agora com o total consumido por cada um: \n\n");
	total(FC, fregues);
	//função total calcula o total consumido por cada cliente
	imprimeFilaClientes(FC, fregues);
	//função imprimeClientes imprime toda a filaClientes

	while (vazia(FC) == false){
		retira(FC, &fregues);
		imprimeElemento(&fregues);
	}
		
	destruir(FC);

	return 0;
}
#include "menuItem.h"
#include "TADLista.h"

#ifndef TADLISTA_CPP
#define TADLISTA_CPP

Lista::Lista() { //Construtor, inicializa primeiro e ultimo como NULL
	F = NULL;
}

MenuItem* Lista::get(char x){ //Retorna ponteiro para o noh desejado de acordo com a sua chave
	MenuItem* itemTemp = F;
	bool ok = (F != NULL);
	
	while(!((x == itemTemp->chave()) || (x-32 == itemTemp->chave()) || (itemTemp->next == NULL))){
		itemTemp = itemTemp->next;
	}
	
	if((x==itemTemp->chave()) || (x-32 == itemTemp->chave())){
		return itemTemp;
	}
	return F; //Retorna a primeira posicao (Caso default) caso o noh desejado nao exista
}

void Lista::insere(MenuItem* novoItem){ //Insere um noh a lista
	MenuItem* aux;
	if(F == NULL){
		F = novoItem;
		F->next = NULL;
	} else {
		aux = F;
		while(aux->next != NULL){
			aux = aux->next;
		}
		novoItem->next = NULL;
		aux->next = novoItem;
	}
}

void Lista::imprime(){ //Imprime a lista
	MenuItem* aux;
	aux = F;
	std::cout << std:: endl;
	std::cout << "Utilize as iniciais de cada funcao: (Inserir celula = I)" << std::endl;
	while(aux->next != NULL){
		aux->titulo();
		aux = aux->next;	
	}
	aux->titulo();
}


#endif

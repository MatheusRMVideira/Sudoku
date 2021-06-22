#include <iostream>

#ifndef TADLISTA_H
#define TADLISTA_H


class Lista {
	private:
		MenuItem* F; //Ponteiro para o primeiro noh da Fila
	public:
		Lista(); //Construtor
		MenuItem* get(char x); //Retorna ponteiro para o noh desejado de acordo com a sua chave
		void insere(MenuItem* novoItem); //Insere um noh a lista
		void imprime(); //Imprime a lista
};

#endif

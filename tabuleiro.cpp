#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>

#include "TADPilha.cpp"
#include "tabuleiro.h"

#ifndef TABULEIRO_CPP
#define TABULEIRO_CPP

void clear();

Tabuleiro::Tabuleiro(){
	int i, j;
	for(i = 0; i < 9; i++){
		for(j = 0; j < 9; j++){
			tabuleiro[i][j].setValor(0);
		}
	}
}

//Gera o tabuleiro a ser jogado
void Tabuleiro::geraTabuleiro(){
	int quantSol = 0;
	int x, y, valor;
	srand(time(NULL));
	bool terminou = false;
	Tabuleiro temp;
	
    resolveTabuleiro(&terminou, &quantSol, 0, false); //Cria um tabuleiro valido completo
    
    //Retira numeros aleatoriamente ate ficar com o minimo possivel para uma unica solucao
    quantSol = 0;
    while(quantSol < 2){
    	for(y = 0; y < 9; y++){
    		for(x = 0; x < 9; x++){
    			temp.tabuleiro[y][x].setValor(tabuleiro[y][x].getValor());
			}
		}
    	quantSol = 0;
    	x = rand() % 9;
    	y = rand() % 9;
    	valor = tabuleiro[y][x].getValor();
    	tabuleiro[y][x].setValor(0);
    	tabuleiro[y][x].setEditavel(true);
    	temp.tabuleiro[y][x].setValor(0);
    	temp.resolveTabuleiro(&terminou, &quantSol, 1, false); //Para cada numero removido, procura 2 solucoes
	}
	tabuleiro[y][x].setValor(valor);
	tabuleiro[y][x].setEditavel(false);
}

//Metodo para resolver, completar ou criar um tabuleiro de maneira valida
// modo = 0 para criar uma solucao e 1 para contar solucoes
//Utiliza backtracking para chegar a uma solucao
// TAD Pilha usado para armazenar os numeros impossiveis de serem utilizados
void Tabuleiro::resolveTabuleiro(bool* terminou, int* quantSol , int modo, bool imprimir){
		int i, x, y;
		int aux;
		int nroPossivel[9];
		Pilha* nroImpossivel = new Pilha;
	
		for(i = 0; i < 9; i++){
			nroPossivel[i] = i + 1;
		}
	
		for(y = 0; y < 9; y++){
			for(x = 0; x < 9; x++){
				if(tabuleiro[y][x].getValor() == 0){ //Percorre todo o tabuleiro e procura por espacos vazios
					getImpossivel(nroImpossivel, x, y);
					while(!nroImpossivel->vazia()){ //Transforma numeros impossiveis, em um array de numeros possiveis
						aux = nroImpossivel->desempilha();
						nroPossivel[aux - 1] = 0;
					}
					std::random_shuffle(&nroPossivel[0], &nroPossivel[8]); //Embaralha array de numeros possiveis para aleatoriedade
					for(i = 0; (i < 9) && (((modo == 0) && !*terminou) || ((modo == 1) && (*quantSol < 2))); i++){ //Testa todos os numeros possiveis
						if(nroPossivel[i] != 0){
							tabuleiro[y][x].setValor(nroPossivel[i]);
							tabuleiro[y][x].setEditavel(false);
							if(imprimir){
								clear();
								imprime();
							}
							resolveTabuleiro(terminou, quantSol, modo, imprimir); //Recursividade 
							if(((modo == 0) && !*terminou) || ((modo == 1) && (*quantSol < 2))){ //Volta posicao caso tenha esgotado todas as possibilidades seguintes
								tabuleiro[y][x].setValor(0);
								tabuleiro[y][x].setEditavel(true);
							}
						}
					}
					delete nroImpossivel;
					return; //fim do caminho, retornar recursividade
				}
			}
		}
		*terminou = true; //flag para indicar que o tabuleiro esta completo
		*quantSol = *quantSol+1; //quantidade de solucoes
};


//Retorna Pilha contendo todos os numeros impossiveis para uma posicao
Pilha* Tabuleiro::getImpossivel(Pilha* pilha, int x, int y){
	int i, j, x1, y1;
	
	for(i = 0; i < 9; i++){
		if(tabuleiro[y][i].getValor() != 0){ //Linha
			pilha->empilha(tabuleiro[y][i].getValor());
		}
	}
	for(i = 0; i < 9; i++){
		if(tabuleiro[i][x].getValor() != 0){ //Coluna
			pilha->empilha(tabuleiro[i][x].getValor());
		}
	}
	x1 = (x / 3) * 3;
	y1 = (y / 3) * 3;
	for(i = 0; i < 3; i++){
		for(j = 0; j < 3; j++){
			if(tabuleiro[y1 + i][x1 + j].getValor() != 0){ //Quadrado 3x3
				pilha->empilha(tabuleiro[y1 + i][x1 + j].getValor());
			}
		}
	}
	return pilha;
}

//Cast de char para int e reducao para [0;8]
//Utilizado pelos metodos insere(), apaga() e valido() com char y;
int Tabuleiro::castCharToInt(char y){ 
	int intY;
	intY = (int) (y);
	intY = (intY >= 65 && intY <= 73) ? intY + 32 : intY; //converte de letra maiuscula para minuscula
	intY = intY - 97; //Reduz para [0;8]
	if(intY >= 0 && intY < 9){
	return intY;
	}
	return -1;
}

//Criado para simplificar ifs de protecao de dado
bool Tabuleiro::checkLimite(int x, int y){ //int X [0;8]; int Y [0;8]
	return (x >= 0 && x <= 8 && y >= 0 && y <= 8);
}

//Insere um valor em uma posicao
bool Tabuleiro::insere(int valor, int x, char y){
	int intY = castCharToInt(y);
	x--; //Como a entrada vem direto do usuario e na interface x[1;9], converte para [0;8]
	if(checkLimite(x, intY) && tabuleiro[intY][x].getEditavel()){ //Editavel evita alterar posicoes criadas pelo programa
		tabuleiro[intY][x].setValor(valor);
		return true;
	}
	return false;
}

//Remove um valor de uma posicao
bool Tabuleiro::apaga(int x, char y){
	int intY = castCharToInt(y);
	x--;
	if(checkLimite(x, intY) && tabuleiro[intY][x].getEditavel()){
		tabuleiro[intY][x].setValor(0);
		return true;
	}
	return false;
}

//Imprime o tabuleiro e as coordenadas
void Tabuleiro::imprime(){
	int i, j, k, m, n, x, y;
	n = 0;
	y = 0;
	for(i = 0; i < 13; i++){
		if(i < 2 || i == 5 || i == 9){ //Coordenada X
			std::cout << "  ";
		} else {
			n++;
			std::cout << n <<" ";
		}
	}
	n = 0;
	std::cout << std::endl;
	for(i = 0; i < 3; i++){ //imprime tabuleiro inteiro
		std::cout << "  ";
		for(j = 0; j < 25; j++){ //Linhas divisorias
			std::cout << "-";
		}
		std::cout << std::endl;
		for(j = 0; j < 3; j++){ //imprime 3 linhas
			x = 0;
			n++;
			std::cout << (char)(64 + n) << " "; //Coordenada Y
			for(k = 0; k < 3; k++){ //imprime linha
				std::cout << "| "; //Colunas divisorias
				for(m = 0; m < 3; m++){
					if(tabuleiro[y][x].getValor() == 0){ //Imprime espaco em branco caso valor seja 0 (vazio)
						std::cout << "  ";
					} else {
					std::cout << tabuleiro[y][x].getValor() << " ";
					}
					x++;
				}
			}
			std::cout << "|" <<std::endl; //Imprime coluna para fechar o tabuleiro
			y++;
		}
	}
	std::cout << "  ";
	for(i = 0; i < 25; i++){ //Imprime linha para fechar o tabuleiro
			std::cout << "-";
	}
	std::cout << std::endl;
}

//Metodo similar a getImpossivel(), porem esta retorna se posicao eh valida
bool Tabuleiro::valido(int x, int y){
	int i, j, x1, y1;
	int valor = tabuleiro[y][x].getValor();
	if (checkLimite(x, y) && valor >=1 && valor <= 9){
		for(i = 0; i < 9; i++){
			if(tabuleiro[y][i].getValor() == valor && i != x){ //Linha
				return false;
			}
		}
		for(i = 0; i < 9; i++){
			if(tabuleiro[i][x].getValor() == valor && i != y){ //Coluna
				return false;
			}
		}
		x1 = (x / 3) * 3;
		y1 = (y / 3) * 3;
		for(i = 0; i < 3; i++){
			for(j = 0; j < 3; j++){
				if(tabuleiro[y1+i][x1+j].getValor() == valor && y1+i != y && x1+j != x){ //Quadrado 3x3
					return false;
				}
			}
		}
		return true;
	}
	return false;
}

//Versao alternativa de valido(int, int)
bool Tabuleiro::valido(int x, char y){
	int intY = castCharToInt(y);
	return valido(x, intY);
}



Quadrado::Quadrado(){
	valor = 0;
	editavel = true;
}

int Quadrado::getValor(){
	return valor;
}

void Quadrado::setValor(int x){
	if(x >= 0 && x <= 9){
		valor = x;
	}
}

bool Quadrado::getEditavel(){
	return editavel;
}

void Quadrado::setEditavel(bool x){
	editavel = x;
}


#endif

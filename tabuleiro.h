#ifndef TABULEIRO_H
#define TABULEIRO_H

class Quadrado{
	private:
		int valor;
		bool editavel; //Se eh possivel ou nao modificar o quadrado
	public:
		Quadrado();
		int getValor();
		void setValor(int x);
		bool getEditavel();
		void setEditavel(bool x);
};


class Tabuleiro{
	private:
		Quadrado tabuleiro[9][9]; //Tabuleiro que eh jogado
		int castCharToInt(char y); //Converte char [a;i] para int [0;8]
		bool checkLimite(int x, int y); //Verifica se x e y estao entre 0 e 8
		Pilha* getImpossivel(Pilha* pilha, int x, int y);
	public:
		Tabuleiro();
		bool insere(int valor, int x, char y); //Insere um valor no tabuleiro
		bool apaga(int x, char y); //Apaga um valor do tabuleiro
		void geraTabuleiro(); //Gera um novo tabuleiro valido
		void resolveTabuleiro(bool* terminou, int* quantSol, int modo, bool imprimir);
		void imprime();
		bool valido(int x, char y); //Verifica se uma posicao eh valida
		bool valido(int x, int y); //Verifica se uma posicao eh valida
};

#endif



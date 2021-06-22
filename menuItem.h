
#ifndef MENUITEM_H
#define MENUITEM_H

//Define as funcoes do menu, permitindo implementacao rapida e individual

class MenuItem{ //Noh de um TAD Fila
	private:
		MenuItem* next;
		friend class Lista;
	public:
		virtual char chave() = 0;
		virtual void comportamento(Tabuleiro* tabuleiro) = 0;
		virtual const void titulo() = 0;
};

class MenuPadrao : public MenuItem { //Caso default, eh o primeiro elemento da lista
	public:
		virtual char chave(){
			return 'Z';
		}
		virtual void comportamento(Tabuleiro* jogoAtual){
		}
		virtual const void titulo(){
		}
};

class MenuNovoJogo : public MenuItem { //Cria um novo jogo
	public:
		virtual char chave(){
		return 'N';
		}
		virtual void comportamento(Tabuleiro* jogoAtual){
			char x;
			Tabuleiro* temp;
			std::cout << "Deseja iniciar um novo jogo? [S/N]" << std::endl;
			std::cin >> x;
			if(x == 'S' || x == 's'){
				delete jogoAtual;
				jogoAtual = new Tabuleiro();
				jogoAtual->geraTabuleiro();
			} else {
				std::cout << "Retornando ao jogo" << std::endl;
			}
		}
		virtual const void titulo(){
			std::cout << "Novo Jogo" << std::endl;
		}
};

class MenuInserir : public MenuItem{ //Insere um valor no tabuleiro
	public:
		virtual char chave(){
		return 'I';
		}
		virtual void comportamento(Tabuleiro* jogoAtual){
			int valor, x;
			char y;
			std::cout << "Inserindo uma celula ao sudoku (y = letras, x = numeros)" << std::endl;
			std::cout << "Y: ";
			std::cin >> y;
			std::cout << "X: ";
			std::cin >> x;
			std::cout << "Valor: ";
			std::cin >> valor;
			if(!jogoAtual->insere(valor,x,y)){
				std::cout << "Por favor, insira parametros corretos (ENTER para continuar)" << std::endl;
				std::cin.ignore();
				std::cin.ignore();
			}
		}
		virtual const void titulo(){
			std::cout << "Inserir celula" << std::endl;
		}
};

class MenuRemover : public MenuItem{ //Remove um valor do tabuleiro
	public:
		virtual char chave(){
		return 'R';
		}
		virtual void comportamento(Tabuleiro* jogoAtual){
			int x;
			char y;
			std::cout << "Removendo uma celula do sudoku (y = letras, x = numeros)" << std::endl;
			std::cout << "Y: ";
			std::cin >> y;
			std::cout << "X: ";
			std::cin >> x;
			if(!jogoAtual->apaga(x,y)){
				std::cout << "Erro, celula nao editavel (ENTER para continuar)" << std::endl;
				std::cin.ignore();
				std::cin.ignore();
			}
		}
		virtual const void titulo(){
			std::cout << "Retirar celula" << std::endl;
		}	
};

class MenuVerificar : public MenuItem{ //Verifica se uma posicao esta correta
	public:	
		virtual char chave(){
		return 'V';
		}
		virtual void comportamento(Tabuleiro* jogoAtual){
			int valor, x;
			char y;
			
			std::cout << "Verificando se uma celula esta correta (y = letras, x = numeros)" << std::endl;
			std::cout << "Y: ";
			std::cin >> y;
			std::cout << "X: ";
			std::cin >> x;
			x--;
			if(jogoAtual->valido(x,y)){
				std::cout << "Essa celula eh valida (ENTER para continuar)" << std::endl;
				std::cin.ignore();
				std::cin.ignore();
			} else {
				std::cout << "Essa celula nao eh valida (ENTER para continuar)" << std::endl;
				std::cin.ignore();
				std::cin.ignore();
			}
		}
		virtual const void titulo(){
			std::cout << "Verificar celula" << std::endl;
		}
};

class MenuCreditos : public MenuItem{
	public:
		virtual char chave(){
		return 'C';
		}
		virtual void comportamento(Tabuleiro* jogoAtual){
			clear();
			std::cout << "Feito por:" << std::endl;
			std::cout << "Alexande dos Santos Gualberto" << std::endl;
			std::cout << "Guilherme Calca" << std::endl;
			std::cout << "Matheus Rezende Milani Videira" << std::endl;
			std::cout << "Para a disciplina Algoritmos e Estruturas de Dados 1" << std::endl <<std::endl;
			std::cout << "(ENTER para continuar)";
			std::cin.ignore();
			std::cin.ignore();
		}
		virtual const void titulo(){
			std::cout << "Creditos" << std::endl;
		}
};

class MenuResolver : public MenuItem{ //Resolve automaticamente o Sudoku
	public:
		virtual char chave(){
		return 'A';
		}
		virtual void comportamento(Tabuleiro* jogoAtual){
			bool semUt0;
			int semUt1;
			jogoAtual->resolveTabuleiro(&semUt0, &semUt1, 0, true);
			std::cout << "Aperte ENTER para voltar ao menu" << std::endl;
			std::cin.ignore();
			std::cin.ignore();
		}
		virtual const void titulo(){
			std::cout << "Auto-resolver" << std::endl;
		}
};

class MenuVerificarTudo : public MenuItem{ //Verifica se todas as posicoes estao corretas
	public:
		virtual char chave(){
		return 'E';
		}
		virtual void comportamento(Tabuleiro* jogoAtual){
			int x, y;
			for(y = 0; y < 9; y++){
				for(x = 0; x < 9; x++){
					if(!jogoAtual->valido(x, y)){
						std::cout << "Celula " << (char)(y+65) << x+1 << " invalida" << std::endl;
					}
				}
			}
			std::cout << "Aperte ENTER para voltar ao menu" << std::endl;
			std::cin.ignore();
			std::cin.ignore();
		}
		virtual const void titulo(){
			std::cout << "Exibir erros" << std::endl;
		}
};

class MenuSair : public MenuItem { //Sai do programa
	public:
		virtual char chave(){
			return 'S';
		}
		virtual void comportamento(Tabuleiro* jogoAtual){
			char x;
			std::cout << "Deseja sair do programa? [S/N]" << std::endl;
			std::cin >> x;
			if(x == 'S' || x == 's'){
				delete jogoAtual;
				exit(0);
			}
		}
		virtual const void titulo(){
			std::cout << "Sair do programa" << std::endl;
		}
};

#endif

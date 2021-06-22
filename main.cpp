/*  Alexandre dos Santos Gualberto
	Guilherme Calca
	Matheus Rezende Milani Videira
*/

#include <iostream>
#include "tabuleiro.cpp"
#include "TADLista.cpp"

void clear();

int main(int argc, char** argv) {
	Tabuleiro* jogo = new Tabuleiro();
	char entrada;
	Lista* menu = new Lista();
	
	jogo->geraTabuleiro();
	menu->insere(new MenuPadrao()); //Usado para prevenir execucao de ponteiro NULL
	menu->insere(new MenuNovoJogo()); //Cria um novo jogo
	menu->insere(new MenuInserir()); //Insere o numero em um quadrado
	menu->insere(new MenuRemover()); //Remove o numero de um quadrado
	menu->insere(new MenuVerificar()); //Verifica se o valor de um quadrado está correto
	menu->insere(new MenuVerificarTudo()); //Verifica se todos os quadrados estão corretos
	menu->insere(new MenuResolver()); //Resolve automaticamente o sudoku atual
	menu->insere(new MenuCreditos()); //Creditos
	menu->insere(new MenuSair()); //Termina a execucao do programa
	
	while(true){
		clear();
		jogo->imprime();
		menu->imprime();
		std::cin >> entrada;
		menu->get(entrada)->comportamento(jogo);
	}
}

//Retirado de https://stackoverflow.com/a/52895729
// Testado somente em Windows 10
void clear()
{
#if defined _WIN32
    system("cls");
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
#elif defined (__APPLE__)
    system("clear");
#endif
}


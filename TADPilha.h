#ifndef TADPILHA_H
#define TADPILHA_H
class Node {
	private:
		int valor;
		Node* prox;
		friend class Pilha;
};

class Pilha {
	private:
		Node* topo;
	public:
		Pilha(); //Construtor
		void empilha(int x); //Adiciona um n? com o valor fornecido ao topo da pilha
		int desempilha(); //Retira um n? do topo da pilha, retorna o valor dele
		bool vazia(); //Verifica se a pilha est? vazia
		~Pilha(); //Destrutor
};

#endif

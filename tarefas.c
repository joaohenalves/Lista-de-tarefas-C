/*
 Este é um esqueleto que deve ser utilzado como base para implementação da Lista de tarefas;
	- As funções não têm os parâmetros definidos; se necessário, estes devem ser incluídos;
 	- Devem ser respeitados os nomes atribuidos aos métodos e estruturas, porém, novas estruturas e funções podem ser criadas, caso julgue necessário;
	- Faça os includes necessários;
	- A organização das funções fica a critério do programador;
	- Códigos não indentados sofrerão duras penalidades;
	- Não serão toleradas variaveis globais;
	- Caso seja detectado plágio, os grupos envolvidos receberão nota 0.
*/

#include <stdio.h> 


#define EXIT 10  // valor fixo para a opção que finaliza a aplicação

//Struct que representa a data.
typedef struct {
	int day;
	int month;
} Date;

// Estrutura que contém os campos dos registros das tarefas
struct REC {
       char nome[50];
       int prioridade;
       Date entrega; 
	  struct REC *next; // implemente como lista, como árvore BST, AVL...
	  struct REC *prev;
};

// Tipo criado para instanciar variaveis do tipo acima
typedef struct REC Task;

// Apresenta o menu da aplicação e retorna a opção selecionada
int menu() {

     int op = 0;

     printf("Selecione a opção desejada:\n\n");
     printf("( 1 ) - Inserir tarefa /// ( 2 ) - Deletar tarefa /// ( 3 ) - Atualizar tarefa /// ( 4 ) - Consultar tarefa /// ( 5 ) - Listar Tarefas /// ( 10 ) - Finalizar programa\n");
     scanf("%d",&op);

     return op;
}

// Permite o cadastro de uma tarefa
void insTask() {
     printf("insere\n");
     return;
}

// Permite excluir uma tarefa
void delTask () {
     printf("deleta\n");
     return;
}

// Lista o conteudo da lista de tarefas (todos os campos)
void listTasks () {
     printf("lista\n");
     return;
}

// Permite consultar uma tarefa da lista pelo nome
void queryTask () {
     printf("procura\n");
     return;
}

// Permite a atualização dos dados de uma tarefa
void upTask () {
     printf("atualiza\n");
     return;
}

// Programa principal
int main() {
    int op = 0;
    Task t;

    printf("Programa de gerenciamento de tarefas - Desenvolvido por João Henrique Alves\n\n");

    while (op != EXIT) {
          op = menu();
          printf("%d\n", op);
          switch(op) {
              case 1 : insTask(); break;
              case 2 : delTask(); break;
              case 3 : upTask(); break;
              case 4 : queryTask(); break;
              case 5 : listTasks(); break;
              case 10 : break;
              default : printf("Erro! Selecione uma opção válida!\n\n");
          }
    }
    return 0;
}

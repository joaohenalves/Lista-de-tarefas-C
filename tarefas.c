#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define EXIT 10

typedef struct {
	int day;
	int month;
} Date;

struct REC {
       char nome[50];
       int prioridade;
       Date entrega; 
	  struct REC *filhoEsq;
	  struct REC *filhoDir;
};

typedef struct REC Task;


struct REC* newNode(char *novoNome, int novaPri, int novoDia, int novoMes) {
    struct REC *novaTask;
    novaTask = malloc(sizeof(struct REC));
    strcpy(novaTask->nome, novoNome);
    novaTask->prioridade = novaPri;
    novaTask->entrega.day = novoDia;
    novaTask->entrega.month = novoMes;
    novaTask->filhoEsq = NULL;
    novaTask->filhoDir = NULL;

    return novaTask;
}

struct REC* insTask(struct REC *raiz, char *novoNome, int novaPri, int novoDia, int novoMes) {

     if(raiz==NULL) {
          raiz = newNode(novoNome, novaPri, novoDia, novoMes);
     }
     else if(strcmp(novoNome, raiz->nome) > 0) {
          raiz->filhoDir = insTask(raiz->filhoDir, novoNome, novaPri, novoDia, novoMes);
     }
     else {
          raiz->filhoEsq = insTask(raiz->filhoEsq, novoNome, novaPri, novoDia, novoMes);
     }
     return raiz;
}

struct REC* queryTask(struct REC *raiz, char *nomeProcurado) {
     if(raiz==NULL || strcmp(raiz->nome, nomeProcurado)==0) {
          return raiz;
     }
     else if(strcmp(raiz->nome, nomeProcurado) < 0) {
          return queryTask(raiz->filhoDir, nomeProcurado);
     }
     else {
          return queryTask(raiz->filhoEsq, nomeProcurado);
     }
}


void delTask () {
     printf("deleta\n");
     return;
}

void listTasks(struct REC *raiz) {
     if(raiz!=NULL) {
          listTasks(raiz->filhoEsq);
          printf("Nome: %s - Prioridade: %d - Entrega: %d/%d", raiz->nome, raiz->prioridade, raiz->entrega.day, raiz->entrega.month);
          listTasks(raiz->filhoDir);
     }
}


void upTask () {
     printf("atualiza\n");
     return;
}

int menu() {

     int op = 0;

     printf("Selecione a opção desejada:\n\n");
     printf("( 1 ) - Inserir tarefa /// ( 2 ) - Deletar tarefa /// ( 3 ) - Atualizar tarefa /// ( 4 ) - Consultar tarefa /// ( 5 ) - Listar Tarefas /// ( 10 ) - Finalizar programa\n");
     scanf("%d", &op);

     return op;
}

int main() {

     printf("Programa de gerenciamento de tarefas - Desenvolvido por João Henrique Alves\n\n");

     int op = 0;
     struct REC *raiz;
     int first = 0;
     Task temp;

     FILE *arq = fopen("tarefas.txt", "r");

     while(fscanf(arq, "Nome: %s - Prioridade: %d - Entrega: %d/%d\n", &temp.nome, &temp.prioridade, &temp.entrega.day, &temp.entrega.month) > 0) {
          if(first != 0) {
               insTask(raiz, temp.nome, temp.prioridade, temp.entrega.day, temp.entrega.month);
          } else {
               raiz = newNode(temp.nome, temp.prioridade, temp.entrega.day, temp.entrega.month);
               first++;
          }
     }
     fclose(arq);
     



     // while (op != EXIT) {
     //      op = menu();
     //      printf("%d\n", op);
     //      switch(op) {
     //           case 1 : insTask(); break;
     //           case 2 : delTask(); break;
     //           case 3 : upTask(); break;
     //           case 4 : queryTask(); break;
     //           case 5 : listTasks(); break;
     //           case 10 : break;
     //           default : printf("Erro! Selecione uma opção válida!\n\n");
     //      }
     // }

     return 0;
}

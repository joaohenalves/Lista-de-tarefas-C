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
	struct REC* filhoEsq;
	struct REC* filhoDir;
};

typedef struct REC Task;

struct REC* newNode(char *novoNome, int novaPri, int novoDia, int novoMes) {
    struct REC* novaTask;
    novaTask = malloc(sizeof(struct REC));
    strcpy(novaTask->nome, novoNome);
    novaTask->prioridade = novaPri;
    novaTask->entrega.day = novoDia;
    novaTask->entrega.month = novoMes;
    novaTask->filhoEsq = NULL;
    novaTask->filhoDir = NULL;

    return novaTask;
}

struct REC* insTask(struct REC* raiz, char *novoNome, int novaPri, int novoDia, int novoMes) {

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

struct REC* queryTask(struct REC* raiz, char *nomeProcurado) {
     if(raiz==NULL || strcmp(raiz->nome, nomeProcurado) == 0) {
          return raiz;
     }
     else if(strcmp(raiz->nome, nomeProcurado) < 0) {
          return queryTask(raiz->filhoDir, nomeProcurado);
     }
     else {
          return queryTask(raiz->filhoEsq, nomeProcurado);
     }
}

struct REC* encontraMinimo(struct REC* raiz) {
     if(raiz == NULL) {
          return NULL;
     } else if(raiz->filhoEsq != NULL) {
          return encontraMinimo(raiz->filhoEsq);
     }
     return raiz;
}

struct REC* delTask(struct REC* raiz, char* nome) {

     struct REC* delTemp;

     if(raiz==NULL) {
          return NULL;
     }

     if (strcmp(nome, raiz->nome) > 0) {
          raiz->filhoDir = delTask(raiz->filhoDir, nome);
     } else if(strcmp(nome, raiz->nome) < 0) {
          raiz->filhoEsq = delTask(raiz->filhoEsq, nome);
     } else {
          if(raiz->filhoEsq==NULL && raiz->filhoDir==NULL) {
               free(raiz);
               return NULL;
          } else if(raiz->filhoEsq==NULL || raiz->filhoDir==NULL) {
               if(raiz->filhoEsq==NULL) {
                    delTemp = raiz->filhoDir;
               } else {
                    delTemp = raiz->filhoEsq;
               }
               free(raiz);
               return delTemp;
          } else {
               delTemp = encontraMinimo(raiz->filhoDir);
               strcpy(raiz->nome, delTemp->nome);
               raiz->prioridade = delTemp->prioridade;
               raiz->entrega.day = delTemp->entrega.day;
               raiz->entrega.month = delTemp->entrega.month;
               raiz->filhoDir = delTask(raiz->filhoDir, delTemp->nome);
          }
     }
     return raiz;
}

void listTasks(struct REC* raiz) {
     if(raiz!=NULL) {
          listTasks(raiz->filhoEsq);
          printf("Nome: %s - Prioridade: %d - Entrega: %d/%d\n", raiz->nome, raiz->prioridade, raiz->entrega.day, raiz->entrega.month);
          listTasks(raiz->filhoDir);
     }
}


void upTask (struct REC* raiz, int prior, int dia, int mes) {
     raiz->prioridade = prior;
     raiz->entrega.day = dia;
     raiz->entrega.month = mes;
     return;
}

void gravaNoArquivoPreOrder(struct REC* raiz, FILE *file){
	if(raiz == NULL) return;
	fprintf(file, "Nome: %s - Prioridade: %d - Entrega: %d/%d\n", raiz->nome, raiz->prioridade, raiz->entrega.day, raiz->entrega.month);
	gravaNoArquivoPreOrder(raiz->filhoEsq, file);
	gravaNoArquivoPreOrder(raiz->filhoDir, file);
}

int menu(struct REC* raiz) {

     int op = 0;
     Task temp;
     struct REC* tempRaiz;

     printf("\nSelecione a opcao desejada:\n\n");
     printf("( 1 ) - Inserir tarefa /// ( 2 ) - Deletar tarefa /// ( 3 ) - Atualizar tarefa /// ( 4 ) - Consultar tarefa /// ( 5 ) - Listar Tarefas /// ( 10 ) - Finalizar programa\n");
     scanf("%d", &op);

     if(op == 1) {

          printf("\nDigite o nome da tarefa a ser inserida:\n");
          scanf("%s", &temp.nome);
          printf("\nDigite a prioridade da tarefa a ser inserida:\n");
          scanf("%d", &temp.prioridade);
          printf("\nDigite o dia de entrega da tarefa a ser inserida:\n");
          scanf("%d", &temp.entrega.day);
          printf("\nDigite o mes de entrega da tarefa a ser inserida:\n");
          scanf("%d", &temp.entrega.month);
          insTask(raiz, temp.nome, temp.prioridade, temp.entrega.day, temp.entrega.month);
          printf("\nTarefa inserida com sucesso!\n");

     } else if(op == 2) {

          printf("\nDigite o nome da tarefa a ser removida:\n");
          scanf("%s", &temp.nome);
          tempRaiz = queryTask(raiz, temp.nome);
          if(tempRaiz != NULL) {
               delTask(raiz, temp.nome);
               printf("\nTarefa removida com sucesso!\n");
          } else {
               printf("\nErro! Tarefa nao encontrada!\n");
          }

     } else if(op == 3) {

          printf("\nDigite o nome da tarefa a ter sua prioridade e data de entrega atualizadas:\n");
          scanf("%s", &temp.nome);
          tempRaiz = queryTask(raiz, temp.nome);
          if(tempRaiz != NULL) {
               printf("\nDigite a nova prioridade da tarefa:\n");
               scanf("%d", &temp.prioridade);
               printf("Digite o novo dia de entrega da tarefa:\n");
               scanf("%d", &temp.entrega.day);
               printf("Digite o novo mes de entrega da tarefa:\n");
               scanf("%d", &temp.entrega.month);
               upTask(tempRaiz, temp.prioridade, temp.entrega.day, temp.entrega.month);
          } else {
               printf("\nErro! Tarefa nao encontrada!\n");
          }

     } else if(op == 4) {

          printf("\nDigite o nome da tarefa a ser procurada:\n");
          scanf("%s", &temp.nome);
          tempRaiz = queryTask(raiz, temp.nome);
          if(tempRaiz != NULL) {
               printf("\nNome: %s - Prioridade: %d - Entrega: %d/%d\n", tempRaiz->nome, tempRaiz->prioridade, tempRaiz->entrega.day, tempRaiz->entrega.month);
          } else {
               printf("\nErro! Tarefa nao encontrada!\n");
          }

     } else if(op == 5) {

          printf("\n");
          listTasks(raiz);

     } else if(op == 10) {

          FILE *arqAtt = fopen("tarefas.txt", "w");
          gravaNoArquivoPreOrder(raiz, arqAtt);
          fclose(arqAtt);
          
     } else {
          printf("\nErro! Por favor, selecione uma opcao valida!\n");
     }

     return op;
}

int main() {

     printf("\n----------------------------------------------------------------------------------\n");
     printf("Programa de gerenciamento de tarefas - Desenvolvido por Joao Henrique Alves\n");
     printf("----------------------------------------------------------------------------------\n");

     int op = 0;
     int counter = 0;
     struct REC* raiz;
     Task temp;

     FILE *arq = fopen("tarefas.txt", "r");

     while(fscanf(arq, "Nome: %s - Prioridade: %d - Entrega: %d/%d\n", &temp.nome, &temp.prioridade, &temp.entrega.day, &temp.entrega.month) > 0) {
          if(counter > 0) {
               insTask(raiz, temp.nome, temp.prioridade, temp.entrega.day, temp.entrega.month);
          } else {
               raiz = newNode(temp.nome, temp.prioridade, temp.entrega.day, temp.entrega.month);
          }
          counter++;
     }
     fclose(arq);

     if(counter > 0) {
          printf("\n%d tarefa(s) existente(s) no arquivo 'tarefas.txt' carregada(s) com sucesso!\n", counter);
     } else {
          printf("\nNenhuma tarefa armazenada no arquivo 'tarefas.txt'!\n");
     }
     
     while (op != EXIT) {
          op = menu(raiz);
     }

     return 0;
}

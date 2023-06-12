#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#define ALFABETO 26

typedef struct No{

    struct No *filho[ALFABETO];
    bool FimDePalavra;
} trie;

trie *criaNo(){
    trie *novo = NULL;
    novo = (trie*)malloc(sizeof(trie));

    for(int i = 0; i <ALFABETO; i++)
        novo->filho[i] = NULL;
    
    novo->FimDePalavra = false;
    return novo;
}

void insere(trie *raiz, char *chave){
    int nivel;
    int tamanho = strlen(chave);
    trie *p = raiz;

    for(nivel = 0; nivel < tamanho; nivel++){
        int i = ((int)chave[nivel] - (int)'A');

        if(!p->filho[i])
            p->filho[i] = criaNo();

        p = p->filho[i];
    }
    p->FimDePalavra = true;
}

bool busca(trie *raiz, char *chave){
    int nivel;
    int tamanho = strlen(chave);
    trie *p = raiz;

    for(nivel = 0; nivel < tamanho; nivel++){

        int i = ((int)chave[nivel] - (int)'A');

        if(!p->filho[i])
            return false;
        p = p->filho[i];
    }
    return(p != NULL && p->FimDePalavra);
    
}

void InsereArquivoNaArvore(trie *raiz, char *arquivo){
    FILE *file = fopen(arquivo, "r");
    char palavra[20];

    if(file == NULL)
        printf("Arquivo vazio ou nao encontrado");

    while(fscanf(file, "%s", palavra) != EOF){
        insere(raiz, palavra);
    }

    fclose(file);
}


int main(){
    system("cls"); //no vscode fica uns negocinhos irritantes em cima
    trie *raiz = criaNo();
    char *arquivo = "dicionario.txt";
    int op;
    char pdesejada[15];
    FILE *file;

    InsereArquivoNaArvore(raiz, arquivo);
    
    do{
    printf("Digite:\n1. Para exibir todas as palavras do dicionario\n2. Para procurar uma plavra especifica\n3. para encerrar o programa\nOpcao: ");
    scanf("%d", &op);
    

        switch(op){
            case 1:
                file = fopen("dicionario.txt", "r");
                printf("\nAs palavras que constam no dicionario sao: \n\n");
                char palavras[10];
                int count = 0;

                while(fgets(palavras,10,file) != NULL){
                    printf("%s", palavras);
                    count++;
                }
               
                fclose(file);
                printf("\nO numero de palavras eh: %d", count);
                printf("\n\n");
                break;

            case 2:
                printf("\nDigite a palavra que deseja buscar: ");
                scanf("%s", &pdesejada);
                printf("\n");
                char mensagem[][24] = {"Palavra nao encontrada!", "Palavra encontrada!"};

                    printf("%s --> %s\n",pdesejada, mensagem[busca(raiz, pdesejada)]);

                printf("\n\n");
                break;

            case 3:
                printf("Programa Encerrado!");
                break;
            
            default:
                printf("digite um numero valido");
                break;

        }
    }
    while(op != 3);
   
    
    return 0;
}
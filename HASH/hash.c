#include <stdio.h>
#include <stdlib.h>

#define TAM 13

typedef struct No {
    int chave; //indice
    char valor[26]; //dado
    struct No* prox;
} No;

typedef struct HashTable {
    No* lista[TAM];
} HashTable;

int hash(int chave) {
    return (chave % TAM) + 1000;
    //return chave % TAM;
}

No* criaNo(int chave, char *valor) {
    No* novo = (No*)malloc(sizeof(No));
    novo->chave = chave;
    strcpy(novo->valor, valor);
    novo->prox = NULL;
    return novo;
}

void insere(HashTable* hashtable, int chave, char *valor) {
    int indice = hash(chave);
    printf ("Chave %d -> indice %d \n", chave, indice);
    indice = indice - 1000;
    No* novo = criaNo(chave, valor);

    if (hashtable->lista[indice] == NULL) {
        // A posição da tabela está vazia, então insere o novo nó diretamente
        hashtable->lista[indice] = novo;
    } else {
        // Já existe um nó na posição da tabela, adiciona o novo nó no início da lista
        novo->prox = hashtable->lista[indice];
        hashtable->lista[indice] = novo;
    }
}

int busca(HashTable* hashtable, int chave) {
    int indice = hash(chave) - 1000;
    No* aux = hashtable->lista[indice];

    while (aux != NULL) {
        if (aux->chave == chave) {
            return aux->valor;  // Valor encontrado
        }
        aux = aux->prox;
    }

    return -1;  // Valor não encontrado
}

int main() {
    HashTable hashtable;
    int i;

    // Inicializa a tabela hash
    for (i = 0; i < TAM; i++) {
        hashtable.lista[i] = NULL;
    }

    // Insere valores na tabela hash
    insere(&hashtable, 1, "oi"); 
    insere(&hashtable, 10, "tudo"); 
    insere(&hashtable, 22, "bem"); 
    insere(&hashtable, 35, "eu"); 
    insere(&hashtable, 443, "to"); 
    insere(&hashtable, 534, "mutchobem"); 


    // Busca valores na tabela hash
    printf("Valor para chave 1: %s\n", busca(&hashtable, 1));
    printf("Valor para chave 10: %s\n", busca(&hashtable, 10));
    printf("Valor para chave 22: %s\n", busca(&hashtable, 22));
    printf("Valor para chave 35: %s\n", busca(&hashtable, 35));
    printf("Valor para chave 443: %s\n", busca(&hashtable, 443));
    printf("Valor para chave 534: %s\n", busca(&hashtable, 534));

    return 0;
}
\\teste
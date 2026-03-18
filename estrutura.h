#ifndef ESTRUTURA_H
#define ESTRUTURA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINHA 512

typedef struct NoDicionario {
    char* verbete;
    char* classificacao;
    char* significado;
    struct NoDicionario* proximo;
} NoDicionario;

typedef struct NoPilha {
    char* palavra;
    struct NoPilha* proximo;
} NoPilha;

int inserirOrdenado(NoDicionario** cabeca, const char* verbete, const char* classificacao, const char* significado);
NoDicionario* buscar(NoDicionario* cabeca, const char* verbete);
void exibirLista(NoDicionario* cabeca);
void liberarLista(NoDicionario** cabeca);

int empilhar(NoPilha** topo, const char* palavra);
char* desempilhar(NoPilha** topo); 
int pilhaVazia(NoPilha* topo);

void strToLower(char* str);
void limparPalavra(char* palavra);
void removerNovaLinha(char* str);

#endif
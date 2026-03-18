#include "estrutura.h"

static char* duplicarString(const char* s) {
    char* d = malloc(strlen(s) + 1);
    if (d == NULL) return NULL;
    strcpy(d, s);
    return d;
}


int inserirOrdenado(NoDicionario** cabeca, const char* verbete, const char* classificacao, const char* significado) {
    NoDicionario* novoNo = (NoDicionario*) malloc(sizeof(NoDicionario));
    if (novoNo == NULL) {
        perror("Falha ao alocar memoria para o no do dicionario");
        return 0; // Falha
    }
    
    novoNo->verbete = novoNo->classificacao = novoNo->significado = NULL;
    novoNo->proximo = NULL;

    novoNo->verbete = duplicarString(verbete);
    if(novoNo->verbete == NULL) { free(novoNo); return 0; }
    strToLower(novoNo->verbete);
    
    novoNo->classificacao = duplicarString(classificacao);
    if(novoNo->classificacao == NULL) { free(novoNo->verbete); free(novoNo); return 0; }
    
    novoNo->significado = duplicarString(significado);
    if(novoNo->significado == NULL) { free(novoNo->verbete); free(novoNo->classificacao); free(novoNo); return 0; }

    if (*cabeca == NULL || strcmp(novoNo->verbete, (*cabeca)->verbete) < 0) {
        novoNo->proximo = *cabeca;
        *cabeca = novoNo;
    } else {
        NoDicionario* atual = *cabeca;
        while (atual->proximo != NULL && strcmp(novoNo->verbete, atual->proximo->verbete) > 0) {
            atual = atual->proximo;
        }
        novoNo->proximo = atual->proximo;
        atual->proximo = novoNo;
    }
    return 1; // Sucesso
}

NoDicionario* buscar(NoDicionario* cabeca, const char* verbete_procurado) {
    char verbete_lower[MAX_LINHA];
    strncpy(verbete_lower, verbete_procurado, sizeof(verbete_lower) - 1);
    verbete_lower[sizeof(verbete_lower) - 1] = '\0';
    strToLower(verbete_lower);
    
    NoDicionario* atual = cabeca;
    while (atual != NULL) {
        if (strcmp(atual->verbete, verbete_lower) == 0) {
            return atual;
        }
        atual = atual->proximo;
    }
    return NULL;
}

void exibirLista(NoDicionario* cabeca) {
    if (cabeca == NULL) {
        printf("Dicionario vazio.\n");
        return;
    }
    printf("\n--- Verbetes no Dicionario (em ordem) ---\n");
    NoDicionario* atual = cabeca;
    while (atual != NULL) {
        printf("Verbete: %s\n", atual->verbete);
        printf("  - Classificacao: %s\n", atual->classificacao);
        printf("  - Significado: %s\n", atual->significado);
        atual = atual->proximo;
    }
    printf("------------------------------------------\n");
}


void liberarLista(NoDicionario** cabeca) {
    NoDicionario* atual = *cabeca;
    while (atual != NULL) {
        NoDicionario* temp = atual;
        atual = atual->proximo;

        free(temp->verbete);
        free(temp->classificacao);
        free(temp->significado);
        free(temp); 
    }
    *cabeca = NULL;
}

int empilhar(NoPilha** topo, const char* palavra) {
    NoPilha* novoNo = (NoPilha*) malloc(sizeof(NoPilha));
    if (novoNo == NULL) return 0;

    novoNo->palavra = duplicarString(palavra);
    if (novoNo->palavra == NULL) {
        free(novoNo);
        return 0;
    }

    novoNo->proximo = *topo;
    *topo = novoNo;
    return 1;
}

char* desempilhar(NoPilha** topo) {
    if (pilhaVazia(*topo)) {
        return NULL;
    }
    NoPilha* temp = *topo;
    *topo = (*topo)->proximo;
    
    char* palavra_retorno = temp->palavra;
    
    free(temp); 
    return palavra_retorno; 
}

int pilhaVazia(NoPilha* topo) {
    return topo == NULL;
}


void strToLower(char* str) {
    for (int i = 0; str[i]; i++) { str[i] = tolower(str[i]); }
}
void limparPalavra(char* palavra) {
    char buffer[MAX_LINHA];
    int j = 0;
    for (int i = 0; palavra[i] != '\0'; i++) {
        if (isalnum(palavra[i])) { buffer[j++] = tolower(palavra[i]); }
    }
    buffer[j] = '\0';
    strcpy(palavra, buffer);
}
void removerNovaLinha(char* str) {
    size_t len = strlen(str);
    if (len > 0 && str[len-1] == '\n') { str[len-1] = '\0'; }
}
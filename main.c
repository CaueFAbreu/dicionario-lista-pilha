#include "estrutura.h"

void criarArquivosExemplo() {
    FILE* f_dicionario = fopen("dicionario.txt", "w");
    if (f_dicionario) {
        fprintf(f_dicionario, "casa;substantivo feminino;Edificio de um ou poucos andares, destinado a habitacao.\n");
        fprintf(f_dicionario, "amor;substantivo masculino;Sentimento que predispoe a desejar o bem de outrem.\n");
        fprintf(f_dicionario, "belo;adjetivo;Que tem beleza ou qualidades que encantam.\n");
        fprintf(f_dicionario, "correr;verbo;Mover-se rapidamente, usando as pernas.\n");
        fprintf(f_dicionario, "felicidade;substantivo feminino;Estado de uma consciencia plenamente satisfeita.\n");
        fprintf(f_dicionario, "sabiamente;adverbio;De modo sabio; com sabedoria.\n");
        fclose(f_dicionario);
    }

    FILE* f_frases = fopen("frases.txt", "w");
    if (f_frases) {
        fprintf(f_frases, "O amor e belo.\n");
        fprintf(f_frases, "Correr para casa traz felicidade!\n");
        fprintf(f_frases, "Ele agiu sabiamente.\n");
        fclose(f_frases);
    }
    printf("Arquivos 'dicionario.txt' e 'frases.txt' criados/atualizados.\n");
}


NoDicionario* carregarDicionario(const char* nomeArquivo) {
    FILE* f = fopen(nomeArquivo, "r");
    if (f == NULL) {
        perror("Nao foi possivel abrir o arquivo do dicionario");
        return NULL;
    }

    NoDicionario* dicionario = NULL;
    char linha[MAX_LINHA];
    
    while (fgets(linha, sizeof(linha), f)) {
        char* verbete = strtok(linha, ";");
        char* classificacao = strtok(NULL, ";");
        char* significado = strtok(NULL, "\n"); 

        if (verbete && classificacao && significado) {
            if (!inserirOrdenado(&dicionario, verbete, classificacao, significado)) {
                fprintf(stderr, "ERRO: Falha ao alocar memoria para o verbete '%s'. Abortando.\n", verbete);
                liberarLista(&dicionario); 
                fclose(f);
                return NULL;
            }
        }
    }

    fclose(f);
    printf("\nDicionario carregado do arquivo '%s' e ordenado.\n", nomeArquivo);
    return dicionario;
}

void pesquisarVerbeteUsuario(NoDicionario* dicionario) {
    char buffer[MAX_LINHA];
    printf("\n--- Pesquisa de Verbetes ---\n");
    printf("Digite um verbete para buscar ou [Enter] para sair.\n");

    while (1) {
        printf("\n> Qual verbete voce deseja encontrar? ");
        fgets(buffer, sizeof(buffer), stdin);
        removerNovaLinha(buffer);
        
        if (strlen(buffer) == 0) {
            printf("Saindo da pesquisa.\n");
            break;
        }

        NoDicionario* resultado = buscar(dicionario, buffer);
        if (resultado) {
            printf("\n--- Dados para '%s' ---\n", buffer);
            printf("  - Classificacao: %s\n", resultado->classificacao);
            printf("  - Significado: %s\n", resultado->significado);
        } else {
            printf("\nVerbete '%s' nao encontrado no dicionario.\n", buffer);
        }
    }
}


void processarFrases(const char* nomeArquivo, NoDicionario* dicionario) {
    FILE* f = fopen(nomeArquivo, "r");
    if (f == NULL) {
        perror("Nao foi possivel abrir o arquivo de frases");
        return;
    }

    printf("\n\n--- Processamento de Frases com Pilha ---\n");
    char linha[MAX_LINHA];
    int num_frase = 1;

    while (fgets(linha, sizeof(linha), f)) {
        removerNovaLinha(linha);
        if(strlen(linha) == 0) continue;
        printf("\n[Frase %d]: \"%s\"\n", num_frase++, linha);
        
        NoPilha* pilha = NULL;
        char linha_copia[MAX_LINHA];
        strcpy(linha_copia, linha);
        
        char* palavra = strtok(linha_copia, " \t\r\n");
        while (palavra != NULL) {
            empilhar(&pilha, palavra);
            palavra = strtok(NULL, " \t\r\n");
        }

        printf("-> Desempilhando e buscando significados:\n");
        while(!pilhaVazia(pilha)) {
            char* palavra_original = desempilhar(&pilha);
            if (!palavra_original) continue;

            char palavra_limpa[MAX_LINHA];
            strcpy(palavra_limpa, palavra_original);
            limparPalavra(palavra_limpa);
            
            NoDicionario* resultado = buscar(dicionario, palavra_limpa);
            if (resultado) {
                printf("  - %-15s | %-25s | %s\n", palavra_original, resultado->classificacao, resultado->significado);
            } else {
                printf("  - %-15s | %-25s | ---\n", palavra_original, "Significado nao encontrado");
            }
            free(palavra_original);
        }
    }
    fclose(f);
}

int main() {
    criarArquivosExemplo();

    NoDicionario* meu_dicionario = carregarDicionario("dicionario.txt");
    if (meu_dicionario == NULL) {
        return 1;
    }
    
    exibirLista(meu_dicionario);

    pesquisarVerbeteUsuario(meu_dicionario);

    processarFrases("frases.txt", meu_dicionario);

    liberarLista(&meu_dicionario);
    printf("\nMemoria do dicionario liberada. Programa finalizado.\n");

    return 0;
}
# 📖 Dicionário com Lista Encadeada e Pilha

![C](https://img.shields.io/badge/C-A8B9CC?style=for-the-badge&logo=c&logoColor=white)
![Data Structure](https://img.shields.io/badge/Estruturas-Lista%20%2B%20Pilha-blue?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Concluído-brightgreen?style=for-the-badge)

> Implementação de um **dicionário de verbetes** em C utilizando **Lista Encadeada Ordenada** e **Pilha**, com carregamento de dados via arquivo `.txt` e análise semântica de frases.

---

## 📋 Índice

- [Sobre o Projeto](#-sobre-o-projeto)
- [Funcionalidades](#-funcionalidades)
- [Estruturas de Dados](#-estruturas-de-dados)
- [Pré-requisitos](#-pré-requisitos)
- [Como Compilar e Executar](#-como-compilar-e-executar)
- [Formato dos Arquivos](#-formato-dos-arquivos)
- [Estrutura do Projeto](#-estrutura-do-projeto)
- [Autor](#-autor)

---

## 📖 Sobre o Projeto

Sistema de dicionário desenvolvido em C que combina duas estruturas de dados clássicas: uma **Lista Encadeada Ordenada** para armazenar os verbetes em ordem alfabética, e uma **Pilha** para processar palavras de frases em ordem inversa. O sistema carrega verbetes de um arquivo `.txt`, permite pesquisa interativa e realiza análise semântica de frases, buscando o significado de cada palavra no dicionário.

---

## ✅ Funcionalidades

- [x] Carregamento de verbetes a partir de arquivo `dicionario.txt`
- [x] Inserção ordenada alfabeticamente na lista encadeada
- [x] Busca de verbetes com normalização (case-insensitive)
- [x] Exibição de todos os verbetes em ordem alfabética
- [x] Pesquisa interativa de verbetes pelo usuário via terminal
- [x] Processamento de frases via arquivo `frases.txt`
- [x] Empilhamento das palavras da frase e busca em ordem inversa
- [x] Limpeza automática de pontuação nas palavras
- [x] Liberação completa de memória ao encerrar
- [x] Geração automática de arquivos de exemplo na primeira execução

---

## 🏗️ Estruturas de Dados

### Lista Encadeada Ordenada — Dicionário
```c
typedef struct NoDicionario {
    char* verbete;
    char* classificacao;
    char* significado;
    struct NoDicionario* proximo;
} NoDicionario;
```
Mantém os verbetes ordenados alfabeticamente via inserção ordenada com `strcmp()`. Todas as strings são alocadas dinamicamente.

### Pilha — Processamento de Frases
```c
typedef struct NoPilha {
    char* palavra;
    struct NoPilha* proximo;
} NoPilha;
```
Cada palavra da frase é empilhada e depois desempilhada para busca no dicionário, processando as palavras em ordem inversa à da frase.

---

## ⚙️ Pré-requisitos

- Compilador **GCC** (ou compatível com C99+)

```bash
gcc --version
```

---

## 🚀 Como Compilar e Executar

**1. Clone o repositório:**
```bash
git clone https://github.com/CaueFAbreu/dicionario-lista-pilha.git
cd dicionario-lista-pilha
```

**2. Compile:**
```bash
gcc main.c estrutura.c -o dicionario
```

**3. Execute:**
```bash
./dicionario
```

Na primeira execução, o programa cria automaticamente os arquivos `dicionario.txt` e `frases.txt` com dados de exemplo.

---

## 📄 Formato dos Arquivos

**`dicionario.txt`** — cada linha segue o formato:
```
verbete;classificacao;significado
```
Exemplo:
```
casa;substantivo feminino;Edificio de um ou poucos andares, destinado a habitacao.
amor;substantivo masculino;Sentimento que predispoe a desejar o bem de outrem.
correr;verbo;Mover-se rapidamente, usando as pernas.
```

**`frases.txt`** — uma frase por linha:
```
O amor e belo.
Correr para casa traz felicidade!
```

---

## 📁 Estrutura do Projeto

```
📦 dicionario-lista-pilha
 ┣ 📄 main.c          # Ponto de entrada — carrega arquivos, menu e processamento de frases
 ┣ 📄 estrutura.c     # Implementação da lista encadeada ordenada e da pilha
 ┗ 📄 estrutura.h     # Definição das structs e protótipos de funções
```

---

## 👤 Autor

**Cauê F. Abreu**

[![GitHub](https://img.shields.io/badge/GitHub-CaueFAbreu-181717?style=flat&logo=github)](https://github.com/CaueFAbreu)

---

<p align="center">Feito com ☕ e C</p>

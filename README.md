# Tetris C - Sistema de Controle de Peças

## 📝 Descrição

Sistema de gerenciamento de peças para jogo desenvolvido em C, implementando estruturas de dados **Fila (Queue - FIFO)** e **Pilha (Stack - LIFO)** para controle de peças futuras e reservadas.

Este projeto foi desenvolvido como atividade acadêmica da disciplina de Estruturas de Dados da **Estácio** - Tema 3: Pilhas e Filas.

## ✨ Funcionalidades

O sistema implementa três ações principais:

1. **Jogar** - Remove a próxima peça da fila e a torna a peça atual
2. **Reservar** - Move a peça atual para o topo da pilha de reservas
3. **Recuperar** - Remove o topo da pilha de reservas e o torna a peça atual
4. **Adicionar** - Gera uma nova peça aleatória e adiciona à fila

## 🛠️ Estruturas de Dados Implementadas

### Structs Utilizadas

```c
typedef struct {
    int id;
    char tipo;  // I, J, L, O, S, T, Z
} Peca;

typedef struct {
    Peca itens[MAX_FILA];
    int frente;
    int tras;
    int quantidade;
} Fila;  // Implementação circular

typedef struct {
    Peca itens[MAX_PILHA];
    int topo;
} Pilha;

typedef struct {
    Peca pecaAtual;
    Fila filaFuturas;
    Pilha pilhaReserva;
    int jogoIniciado;
} Jogo;  // Estrutura aninhada principal
```

## 🚀 Como Compilar e Executar

### Pré-requisitos
- Compilador GCC instalado
- Sistema operacional: Windows, Linux ou macOS

### Compilação

```bash
gcc main.c -o tetris
```

### Execução

**Linux/macOS:**
```bash
./tetris
```

**Windows:**
```bash
tetris.exe
```

## 🎮 Menu do Sistema

```
=================================
 PEÇA ATUAL: [T] (ID: 0)
---------------------------------
 FILA (Futuras): [L] [O] [S] 
 PILHA (Reserva): [Vazia]
=================================

--- CONTROLE DE PEÇAS ---
1. Jogar (Pega próx. da fila)
2. Reservar (Guarda atual na pilha)
3. Recuperar (Pega do topo da pilha)
4. Adicionar Peça Futura
0. Sair
Escolha: 
```

## 📚 Conceitos Aplicados

- **Variáveis**: Armazenamento de dados das peças e estados
- **Structs**: Organização de dados complexos
- **Operadores**: Manipulação de índices e comparações
- **Condicionais**: Validações de fila/pilha cheia ou vazia
- **Estruturas Aninhadas**: Struct `Jogo` contém `Fila`, `Pilha` e `Peca`
- **Funções de Entrada/Saída**: Interface com o usuário via `printf` e `scanf`

## 📁 Estrutura do Projeto

```
tetris-c/
├── main.c          # Código fonte completo
└── README.md       # Documentação
```

## 👤 Autor

**andream001**

## 📝 Licença

Projeto acadêmico - Estácio 2025

---

**Desenvolvido para a disciplina de Estruturas de Dados - Tema 3: Pilhas e Filas**

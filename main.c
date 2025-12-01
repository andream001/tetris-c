#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// Definição de Constantes
#define MAX_FILA 10
#define MAX_PILHA 5

// STRUCTS
typedef struct {
    int id;
    char tipo;
} Peca;

typedef struct {
    Peca itens[MAX_FILA];
    int frente;
    int tras;
    int quantidade;
} Fila;

typedef struct {
    Peca itens[MAX_PILHA];
    int topo;
} Pilha;

typedef struct {
    Peca pecaAtual;
    Fila filaFuturas;
    Pilha pilhaReserva;
    int jogoIniciado;
} Jogo;

// Protótipos
void inicializarJogo(Jogo *j);
void criarPeca(Peca *p, int id);
int filaCheia(Fila *f);
int filaVazia(Fila *f);
void enfileirar(Fila *f, Peca p);
Peca desenfileirar(Fila *f);
int pilhaCheia(Pilha *p);
int pilhaVazia(Pilha *p);
void empilhar(Pilha *p, Peca item);
Peca desempilhar(Pilha *p);
void acaoJogar(Jogo *j);
void acaoReservar(Jogo *j);
void acaoRecuperar(Jogo *j);
void exibirEstado(Jogo j);

int main() {
    setlocale(LC_ALL, "Portuguese");
    Jogo jogo;
    int opcao;
    inicializarJogo(&jogo);

    do {
        exibirEstado(jogo);
        printf("\n--- CONTROLE DE PEÇAS ---\n");
        printf("1. Jogar (Pega próx. da fila)\n");
        printf("2. Reservar (Guarda atual na pilha)\n");
        printf("3. Recuperar (Pega do topo da pilha)\n");
        printf("4. Adicionar Peça Futura\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: acaoJogar(&jogo); break;
            case 2: acaoReservar(&jogo); break;
            case 3: acaoRecuperar(&jogo); break;
            case 4: {
                Peca nova;
                criarPeca(&nova, rand() % 100);
                if (!filaCheia(&jogo.filaFuturas)) {
                    enfileirar(&jogo.filaFuturas, nova);
                    printf("\n>> Nova peça gerada!\n");
                } else {
                    printf("\n[!] Fila cheia!\n");
                }
                break;
            }
            case 0: printf("Encerrando...\n"); break;
            default: printf("Opção inválida!\n");
        }
        printf("\nPressione Enter...");
        getchar(); getchar();
    } while(opcao != 0);
    return 0;
}

void inicializarJogo(Jogo *j) {
    j->filaFuturas.frente = 0;
    j->filaFuturas.tras = -1;
    j->filaFuturas.quantidade = 0;
    j->pilhaReserva.topo = -1;
    j->pecaAtual.id = -1;
    j->pecaAtual.tipo = ' ';
    j->jogoIniciado = 1;
    for(int i=0; i<3; i++) {
        Peca p;
        criarPeca(&p, i);
        enfileirar(&j->filaFuturas, p);
    }
}

void criarPeca(Peca *p, int id) {
    char tipos[] = {'I', 'J', 'L', 'O', 'S', 'T', 'Z'};
    p->id = id;
    p->tipo = tipos[rand() % 7];
}

int filaCheia(Fila *f) {
    return f->quantidade == MAX_FILA;
}

int filaVazia(Fila *f) {
    return f->quantidade == 0;
}

void enfileirar(Fila *f, Peca p) {
    if (filaCheia(f)) return;
    f->tras = (f->tras + 1) % MAX_FILA;
    f->itens[f->tras] = p;
    f->quantidade++;
}

Peca desenfileirar(Fila *f) {
    Peca p = {-1, ' '};
    if (filaVazia(f)) return p;
    p = f->itens[f->frente];
    f->frente = (f->frente + 1) % MAX_FILA;
    f->quantidade--;
    return p;
}

int pilhaCheia(Pilha *p) {
    return p->topo == MAX_PILHA - 1;
}

int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

void empilhar(Pilha *p, Peca item) {
    if (pilhaCheia(p)) {
        printf("\n[!] Pilha de reserva cheia!\n");
        return;
    }
    p->itens[++(p->topo)] = item;
}

Peca desempilhar(Pilha *p) {
    if (pilhaVazia(p)) {
        Peca vazia = {-1, ' '};
        return vazia;
    }
    return p->itens[(p->topo)--];
}

void acaoJogar(Jogo *j) {
    if (filaVazia(&j->filaFuturas)) {
        printf("\n[!] Não há peças futuras!\n");
        return;
    }
    j->pecaAtual = desenfileirar(&j->filaFuturas);
    printf("\n>> Você jogou! Nova peça atual: [%c]\n", j->pecaAtual.tipo);
}

void acaoReservar(Jogo *j) {
    if (j->pecaAtual.id == -1) {
        printf("\n[!] Não há peça atual para reservar!\n");
        return;
    }
    if (pilhaCheia(&j->pilhaReserva)) {
        printf("\n[!] A reserva está cheia!\n");
    } else {
        empilhar(&j->pilhaReserva, j->pecaAtual);
        printf("\n>> Peça [%c] movida para Reserva.\n", j->pecaAtual.tipo);
        if (!filaVazia(&j->filaFuturas)) {
            j->pecaAtual = desenfileirar(&j->filaFuturas);
            printf(">> Próxima peça assumiu o lugar.\n");
        } else {
            j->pecaAtual.id = -1;
            j->pecaAtual.tipo = ' ';
        }
    }
}

void acaoRecuperar(Jogo *j) {
    if (pilhaVazia(&j->pilhaReserva)) {
        printf("\n[!] Nenhuma peça reservada!\n");
        return;
    }
    Peca recuperada = desempilhar(&j->pilhaReserva);
    Peca atualAntiga = j->pecaAtual;
    j->pecaAtual = recuperada;
    printf("\n>> Peça [%c] recuperada!\n", recuperada.tipo);
    if (atualAntiga.id != -1) {
        empilhar(&j->pilhaReserva, atualAntiga);
        printf(">> Peça antiga [%c] guardada.\n", atualAntiga.tipo);
    }
}

void exibirEstado(Jogo j) {
    printf("\n=================================\n");
    printf(" PEÇA ATUAL: [%c] (ID: %d)\n", j.pecaAtual.tipo, j.pecaAtual.id);
    printf("---------------------------------\n");
    printf(" FILA (Futuras): ");
    if (filaVazia((Fila*)&j.filaFuturas)) printf("[Vazia]");
    else {
        int count = j.filaFuturas.quantidade;
        int idx = j.filaFuturas.frente;
        for(int i=0; i < count; i++) {
            printf("[%c] ", j.filaFuturas.itens[idx].tipo);
            idx = (idx + 1) % MAX_FILA;
        }
    }
    printf("\n");
    printf(" PILHA (Reserva): ");
    if (pilhaVazia((Pilha*)&j.pilhaReserva)) printf("[Vazia]");
    else {
        for(int i=0; i <= j.pilhaReserva.topo; i++) {
            printf("[%c] ", j.pilhaReserva.itens[i].tipo);
        }
        printf("<-- TOPO");
    }
    printf("\n=================================\n");
}

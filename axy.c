#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char f[200];
int p;

/* Cabeçalhos */
void e0(); // estado inicial e final
void e1(); // estado intermediário
void e2(); // estado final

void rejeita();
void aceita();

void proximaLetra();
void proximoEstado();
void proximoEstadoFinal();

int main(int argc, char const *argv[]) {
    if (argc == 2) {
        printf("A Palavra %s foi ", argv[1]);
        strcpy(f, argv[1]);
    }

    p = 0;

    e0();

    return 0;
}

void proximaLetra() {
    p++;
}

void proximoEstado(void (*proxEstado)()) {
    // necessário incrementar posição de letra a ser lida
    proximaLetra();

    // chama a próxima função
    (*proxEstado)();
}

void finalizaOuVaiParaEstadoInicial(void (*estadoInicial)()) {
    proximaLetra();
    if (f[p] == 0) { // não existe mais nada para analisar
        aceita();
    } else { // existe string para ser analisada
        (*estadoInicial)(); // manda para o começo
    }
}

void e0() {
    if (f[p] == 'a') { // estado inicial e final
        finalizaOuVaiParaEstadoInicial(&e0);
    } else if (f[p] == 'x') { // estado inicial
        proximoEstado(&e1);
    } else {
        rejeita();
    }
}

void e1() { // estado intermediário
    if (f[p] == 'y') {
        proximoEstado(&e2);
    } else {
        rejeita();
    }
}

void e2() { // pode ser estado final
    if (f[p] == 'z') {
        finalizaOuVaiParaEstadoInicial(&e0);
    } else {
        rejeita();
    }
}

void aceita() {
    printf("aceita\n");
    exit(0);
}

void rejeita() {
    printf("rejeitada\n");
    exit(0);
}
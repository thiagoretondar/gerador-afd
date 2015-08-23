#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char f[200];
int p;
int aceito;

/* Cabeçalhos */
void e0(); // estado inicial e final
void e1(); // estado intermediário
void e2(); // estado intermediári
void e3(); // estado final
void e4(); // estado final

void rejeita();
void aceita();

void proximaLetra();
void proximoEstado();
void proximoEstadoFinal();

int main(int argc, char const *argv[]) {

    if (argc == 2) {
        strcpy(f, argv[1]);
    }

    p = 0;

    e0();

    if (!aceito) {
        printf("%s\n", argv[1]);
        printf("%*s" "%s\n", p - 1, " ", "^");
        int i;
        for (i = 0; i < p - 1; ++i) {
            putchar('_');
        }
        printf("|\n");
    }

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
    } else if (f[p] == 'b') { // estado inicial e final
       finalizaOuVaiParaEstadoInicial(&e0);
    } else if (f[p] == 'e') { // estado inicial
        proximoEstado(&e1);
    } else if (f[p] == 'i') { // estado inicial
        proximoEstado(&e4);
    } else {
        rejeita();
    }
}

void e1() { // estado intermediário

    if (f[p] == 'l') {
        proximoEstado(&e2);
    } else {
        rejeita();
    }
}

void e2() { // estado intermediário

    if (f[p] == 's') {
        proximoEstado(&e3);
    } else {
        rejeita();
    }
}

void e3() { // pode ser estado final

    if (f[p] == 'e') {
        finalizaOuVaiParaEstadoInicial(&e0);
    } else {
        rejeita();
    }
}

void e4() { // pode ser estado final

    if (f[p] == 'f') {
        finalizaOuVaiParaEstadoInicial(&e0);
    } else {
        rejeita();
    }
}

void aceita() {

    printf("A palavra foi aceita\n");
    aceito = 1;
}

void rejeita() {

    printf("A palavra foi rejeitada\n");
    aceito = 0;
}

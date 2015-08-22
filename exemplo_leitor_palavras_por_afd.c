#include <stdio.h>
#include <stdlib.h>

char f[200];
int p;

/* Cabeçalhos */
void e0();
void e1();
void e2();
void e3();
void e4();

void rejeita();
void aceita();

void proximaLetra();

void main(int argc, char const *argv[]) {

    if (argc == 2) {
        printf("A palavra %s foi ", argv[1]);
        strcpy(f, argv[1]);
    }

    p = 0;

    e0();

    return 0;
}

void proximaLetra() {
    p++;
}

void e0() {

    if (f[p] == 'a') { // estado inicial e final
        proximaLetra();
        if (f[p] == 0) { // se não tiver mais nada para ser analisado
            aceita();
        } else {
            e0();
        }
    } else if (f[p] == 'b') { // estado inicial e final
        proximaLetra();
        if (f[p] == 0) {
            aceita();
        } else {
            e0();
        }
    } else if (f[p] == 'e') { // estado inicial
        proximaLetra();
        e1();
    } else if (f[p] == 'i') { // estado inicial
        proximaLetra();
        e4();
    } else {
        rejeita();
    }
}

void e1() { // estado intermediário

    if (f[p] == 'l') {
        proximaLetra();
        e2();
    } else {
        rejeita();
    }
}

void e2() { // estado intermediário

    if (f[p] == 's') {
        proximaLetra();
        e3();
    } else {
        rejeita();
    }
}

void e3() { // pode ser estado final

    if (f[p] == 'e') {
        proximaLetra();
        if (f[p] == 0) { // não existe mais nada para analisar
            aceita();
        } else { // existe string para ser analisada
            e0(); // manda para o começo
        }
    } else {
        rejeita();
    }
}

void e4() { // pode ser estado final

    if (f[p] == 'f') {
        proximaLetra();
        if (f[p] == 0) { // não existe mais nada para analisar
            aceita();
        } else { // existe string para ser analisada
            e0(); // manda para o começo
        }
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define true 1
#define false 0

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

int temAlgoParaAnalisar();

int main(int argc, char const *argv[]) {

    if (argc == 2) {
        strcpy(f, argv[1]);
    }

    p = 0;

    e0();

    if (!aceito) {
        printf("%s\n", argv[1]);
        printf("%*s" "%s\n", p, " ", "^");
        int i;
        for (i = 0; i < p; ++i) {
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

void finalizaOuVaiParaEstadoInicial(void (*proxEstado)()) {

    proximaLetra();
    if (!temAlgoParaAnalisar()) { // não existe mais nada para analisar
        aceita();
    } else { // existe string para ser analisada
        (*proxEstado)(); // manda para o começo
    }
}

int temAlgoParaAnalisar() {
    if (f[p] == '\0') {
        return false;
    }

    return true;
}

void aceita() {

    printf("A palavra foi aceita\n");
    aceito = 1;
}

void rejeita() {

    printf("A palavra foi rejeitada\n");
    aceito = 0;
}


/*
 Regra: se não é FINAL, não pode ter temAlgoPraAnalisar()
 1 verifica se letra está correta
    1.1 vai para o próximo estado
 2 se não tiver, rejeita
 */
void e0() { // estado inicial

    if (f[p] == 'a') {
       proximoEstado(&e1);
    } else {
        rejeita();
    }
}

/*
 estado FINAL e INTERMEDIÁRIO:
 1 verificar se temAlgoPraAnalisar()
     1.1 faz verificações da letra
         1.1.1 vai para próximo estado
     1.2 ou rejeita se nenhuma letra for correta
 2 se não tiver, aceita
 */
void e1() { //   estado intermediário e estado final

    if (temAlgoParaAnalisar()) {
        if (f[p] == 'b') {
            proximoEstado(&e0);
        } else if (f[p] = 'c') {
            proximoEstado(&e2);
        } else {
            rejeita();
        }
    } else {
        aceita();
    }
}

/*
 apenas estado final
 1 verificar se não existe mais para analisar
    1.1 aceita()
 2 se tiver
    2.1 rejeita()
 */
void e2() { // estado final

    if (!temAlgoParaAnalisar()) {
        aceita();
    } else {
        rejeita();
    }
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define true 1
#define false 0

char f[200];
int p;
int aceito;

/* Cabeçalhos */
void rejeita();
void aceita();
void proximaLetra();
void proximoEstado();
void proximoEstadoFinal();
int temAlgoParaAnalisar();
int temAlgoParaAnalisarNoEstadoInicial();

void e0();
void e1();


int main(int argc, char const *argv[]) { 

	if (argc == 2) { 
		strcpy(f, argv[1]); 
	} 

	p = 0; 

	e0(); 

	if (!aceito && argc == 2) {
		printf("%s\n", argv[1]); 
		if (p <= 1) {
			printf("^\n");
		} else {
			printf("%*s" "%s\n", p - 1, " ", "^"); 
		}
	} 

	return 0; 
}

void proximaLetra() {

	// incrementa possição da letra
	p++;
}

void proximoEstado(void (*proxEstado)()) {

	// necessário incrementar posição de letra a ser lida
	proximaLetra();

	// chama a próxima função
	(*proxEstado)();
}

int temAlgoParaAnalisar() {

	// verifica se na posição atual existe algo para analisar
	if (f[p] == '\0') {
		return false;
	}

	return true;
}

int temAlgoParaAnalisarNoEstadoInicial() {

	// verifica se existe uma próxima letra para analisar
	if (f[p + 1] == '\0') {
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

void e0() {
	if (f[p] == 'a') {
		proximoEstado(&e1);
	} else if (f[p] == 'b') {
		if (temAlgoParaAnalisarNoEstadoInicial()) {
			proximoEstado(&e0);
		} else {
			aceita();
		}
	} else if (f[p] == 'c') {
		if (temAlgoParaAnalisarNoEstadoInicial()) {
			proximoEstado(&e0);
		} else {
			aceita();
		}
	} else if (!temAlgoParaAnalisar()) {
		aceita();
	} else  {
		rejeita();
	}
}

void e1() {
	if (temAlgoParaAnalisar()) {
		{
			rejeita();
		}
	} else {
		rejeita();
	}
}


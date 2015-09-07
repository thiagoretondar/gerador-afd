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
void e2();
void e3();


int main(int argc, char const *argv[]) { 

	if (argc == 2) { 
		strcpy(f, argv[1]); 
	} 

	p = 0; 

	e0(); 

	if (!aceito) { 
		printf("%s\n", argv[1]); 
		if (p == 0) {
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

void finalizaOuVaiParaEstadoInicial(void (*proxEstado)()) {

	proximaLetra();
	if (!temAlgoParaAnalisar()) { // não existe mais nada para analisar
		aceita();
	} else { // existe string para ser analisada
		(*proxEstado)(); // manda para o começo
	}
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
		proximoEstado(&e3);
	} else  {
		rejeita();
	}
}

void e1() {
	if (temAlgoParaAnalisar()) {
		if (f[p] == 'a') {
			proximoEstado(&e0);
		} else if (f[p] == 'b') {
			proximoEstado(&e2);
		} else {
			rejeita();
		}
	} else {
		aceita();
	}
}

void e2() { //estado intermediário
	if (temAlgoParaAnalisar()) {
		if (f[p] == 'a') {
			proximoEstado(&e3);
		} else if (f[p] == 'b') {
			proximoEstado(&e1);
		} else {
			rejeita();
		}
	} else {
		rejeita();
	}
}

void e3() { //estado intermediário
	if (temAlgoParaAnalisar()) {
		if (f[p] == 'a') {
			proximoEstado(&e2);
		} else if (f[p] == 'b') {
			proximoEstado(&e0);
		} else {
			rejeita();
		}
	} else {
		rejeita();
	}
}


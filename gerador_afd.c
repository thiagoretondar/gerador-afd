#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

// Enums
#define ESTADO 0
#define SIMBOLO 1
#define PROX_ESTADO 2
#define ESTADO_INEXISTENTE -1

int qtdSimbolos = 0,
    qtdEstados = 0,
    qtdEstadosFinais = 0;

int estadoInicial = 0;

char* simbolos[20];

// TODO: fazer um vetor de inteiro booleano, onde a posicao indica se é ou não estado final
int estadosFinais[20];

// [
//   [0][1][0] => estado0 ; simbolo1 ; vaiParaEstadoE0
//   [1][2][1] => estado1 ; simbolo2 ; vaiParaEstadoE1
// ]
/*
[
[0,0,-1]
[0,1,0]

[1,0,2]
[1,1,3]

[2,0,1]
[2,1,2]
]
*/
int sequenciaEstados[20][3];

// Cabeçalhos
void PerguntaQuantidadeSimbolos();
void PerguntaSimbolos();
void PerguntaQuantidadeEstados();
void PerguntaEstadoInicial();
void PerguntaQuantidadeEstadosFinais();
void PerguntaEstadosFinais();
void PerguntaSequenciaDeEstados();
void PerguntaTipoDePrograma();

void MontaMatrizEntrada();

void GeraProgramaGOTO();
void GeraProgramaFunc();

void ZerarVetorEstadosFinais();
void insereEstado();

void geraEstadoIntermediario();
void geraEstadosFinais();
void geraEstadoInicial();

int main (int argc, char const *argv[]) {
    setlocale(LC_ALL, "Portuguese");

    PerguntaQuantidadeSimbolos();
	PerguntaSimbolos();
    PerguntaQuantidadeEstados();
    PerguntaEstadoInicial();
    PerguntaQuantidadeEstadosFinais();
    PerguntaEstadosFinais();
    PerguntaSequenciaDeEstados();

    // imprime vetor de sequencia
    int i, j, total = 0;
    char numeroEstado[2];
    for (i = 0; i < qtdEstados; i++) {
        for (j = 0; j < qtdSimbolos; j++) {
            printf("[%d,%d,%d]\n", sequenciaEstados[total][0],sequenciaEstados[total][1], sequenciaEstados[total][2]);
            total++;
        }
    }
    /*int i;
    for (i = 0; i < qtdEstadosFinais; i++) {
        printf("%d ", estadosFinais[i]);
    }*/

    //geraEstadoIntermediario(0, 'l', 2);
    geraEstadoInicial();
    geraEstadosFinais();

    return 0;
}

void geraEstadoInicial() {
    printf("void e%d() {\n", estadoInicial);

        printf("\t");
        // índice é uma relação de multiplicação do estadoInicial indicado
        // e a quantidade de símbolos existentes
        int i = estadoInicial * qtdSimbolos;

        // quantidade de iterações é a soma do índice inicial mais a quantidade
        // de símbolos existentes
        int qtd = i + qtdSimbolos;

        for (i; i < qtd; i++) {
            int* estadoAtual = sequenciaEstados[i];

            if (estadoAtual[PROX_ESTADO] != ESTADO_INEXISTENTE) {
                printf("if (f[p] == '%c') {\n", simbolos[estadoAtual[SIMBOLO]]);

                // verifica se o estado o próximo estado é o mesmo estado que
                // está sendo analisado atualmente
                // se for, imprime função para verificar se existe algo ainda pra ler
                // caso contrário, apenas chama o próximo estado
                if (estadoAtual[ESTADO] == estadoAtual[PROX_ESTADO]) {
                    printf("\t\tif (temAlgoPraAnalisar()) {\n");
                        printf("\t\t\tproximoEstado(&e%d);\n", estadoAtual[ESTADO]);
                    printf("\t\t} else {\n");
                        printf("\t\t\taceita();\n");
                    printf("\t\t}\n");
                } else {
                    printf("\t\tproximoEstado(&e%d)\n", estadoAtual[PROX_ESTADO]);
                }

            printf("\t} else ");
            }

        }

        printf(" {\n");
            printf("\t\trejeita();\n");
        printf("\t}\n");

    printf("}\n");
}

/*
0 = a
1 = b
2 = c
3 = x

e = 1 * 3
            [0,0,1] => vai para e1 se letra = a
            [0,1,-1] => rejeita
            [0,2,-1] => rejeita

            [1,0,-1] => não faz nada
            [1,1,0] => é estado final, mas pode ir para e0 se letra = b
            [1,2,2] => é estado final, mas pode ir para e2 se letra = c
            
            [2,0,-1] => não faz nada 
            [2,1,-1] => não faz nada
            [2,2,-1] => não faz nada
            */
void geraEstadoFinal(int numEstado, char* simbolo) {    

    
    printf("void e%d() {\n", numEstado);
        printf("\tif (f[p] == '%c') {\n", simbolo);
            printf("\t\taceita();\n");
        printf("\t} else {\n");
            printf("\t\trejeita();\n");
        printf("\t}\n");
    printf("}\n");
    
    /*int i;
    for (i = 0; i < qtdEstadosFinais; i++) {
        int* estadoAtual = sequenciaEstados[estadosFinais[i] * qtdSimbolos];

        printf("void e%d() {\n", estadoAtual[ESTADO]); 
            printf("\tif (f[p] == '%c') {\n", simbolos[estadoAtual[ESTADO]]);
                if (estadoAtual[PROX_ESTADO] == ESTADO_INEXISTENTE) {
                    printf("aceita\n");
                }

                printf("\t\tfinalizaOuVaiParaEstado(&e%d);\n", simbolos[estadoAtual[PROX_ESTADO]]);
            printf("\t} else {\n");
                printf("\t\trejeita();\n");
            printf("\t}\n");
        printf("}\n");
    }*/
}

void geraEstadoIntermediarioOuFinal(int numEstado, char* estadoAtual, int numProxEstado) {
    /*
    printf("void e%d() {", numEstado);

        printf("if (f[p] != 0) {");
            if (f[p] == 'b') {
                proximoEstado(&e0);
            } else if(f[p] == 'c') {
                proximoEstado(&e2);
            } else {
                rejeita();
            }
        } else {
            aceita();
        }
    }
    */
}

void PerguntaQuantidadeSimbolos() {
    printf("Quantos símbolos tem o alfabeto? R: ");
    scanf("%d", &qtdSimbolos);
}

void PerguntaSimbolos() {
    int i;
    for (i = 0; i < qtdSimbolos && i < sizeof(simbolos) ; i++) {
        //Qual o simbolo será inputado no alfabeto
        printf("\t%d. Qual é o símbolo %d? R: ", i + 1, i);
        scanf("\t%c", &simbolos[i]);
    }
}

void PerguntaQuantidadeEstados() {
    printf("Quantos estados? R: ");
    scanf("%d", &qtdEstados);
}

void PerguntaEstadoInicial() {
    printf("Qual o estado inicial? R: ");
    scanf("%d", &estadoInicial);
}

void PerguntaQuantidadeEstadosFinais() {
    printf("Quantos estados finais? R: ");

    int qtd;
    scanf("%d", &qtd);

    if (qtd > qtdEstados) {
        printf("ERRO: quantidade de estados finais maior do que a quantidade de estados totais!\n");
        printf("Digite novamente\n");
        PerguntaQuantidadeEstadosFinais();
    } else if (qtd <= 0) {
        printf("ERRO: quantidade de estados finais menor do que zero!\n");
        printf("Digite novamente\n");
        PerguntaQuantidadeEstadosFinais();
    } else {
        qtdEstadosFinais = qtd;
    }
}

void PerguntaEstadosFinais() {
    ZerarVetorEstadosFinais();

    int i;
    for (i = 0; i < qtdEstadosFinais; i++) {
        printf("\t%d. Qual o estado final %d? R: ", i + 1, i);
        scanf("%d", &estadosFinais[i]);
    }
}

void PerguntaSequenciaDeEstados() {
    int i, j, total = 0;
    char numeroEstado[2];
    for (i = 0; i < qtdEstados; i++) {
        for (j = 0; j < qtdSimbolos; j++) {
            printf("\tPara o estado e%d e símbolo %c qual o próximo estado? ", i, simbolos[j]);
            scanf("%s", numeroEstado);

            int proxEstado = atoi(numeroEstado);

            insereEstado(&total, i, j, proxEstado);
        }
        printf("\n");
    }
}

void insereEstado(int *posicao, int estado, int simbolo, int proxEstado) {
    sequenciaEstados[*posicao][0] = estado;
    sequenciaEstados[*posicao][1] = simbolo;
    sequenciaEstados[*posicao][2] = proxEstado;

    // incrementa para a próxima posição
    (*posicao)++;
}

void ZerarVetorEstadosFinais() {
    int i;
    for (i = 0; i < sizeof(estadosFinais); i++) {
        estadosFinais[i] = 0;
    }
}

/*void GeraPrograma(){
    int gerar;
    char * NomeArq[50];
    printf("Qual o nome do programa?\n");
    scanf("%s", &NomeArq);
    printf("Como gostaria de gerar? ([1] = GOTO: [2] = Função)\n");
    scanf("%d", &gerar);

    switch (gerar) {
        case 1:
            GeraProgramaGOTO(NomeArq);
            break;
        case 2:
            GeraProgramaFunc(NomeArq);
            break;
        default:
            printf("Opção inválida!\n");
            break;
    }

    printf("Programa criado! Consulte o diretório do programa.");
}

void GeraProgramaGOTO(char * NomeArq){

    int i=0;
	strcat(NomeArq,".c");
	FILE * NovoPrograma;
    NovoPrograma = fopen(NomeArq, "w");

    fputs("#include <stdio.h>\r#include <conio.h>\r#include <stdlib.h>\n\r",NovoPrograma);
    fputs("int main(){\r\tchar f[200];\r\tint p;\r\t",NovoPrograma);

    fclose(NovoPrograma);

}*/

/*
void e1() { // estado intermediário

    if (f[p] == 'l') {
        proximoEstado(&e2);
    } else {
        rejeita();
    }
}
*/

void GeraProgramaFunc(char * NomeArq){

    int i=0;
	strcat(NomeArq,".c");
	FILE * NovoPrograma;
    NovoPrograma = fopen(NomeArq, "w");

    fputs("#include <stdio.h>\r#include <conio.h>\r#include <stdlib.h>\n\r",NovoPrograma);
    fputs("int main(){\r\tchar f[200];\r\tint p=0;\r\tputs(\"Palavra:\");\r\t}",NovoPrograma);



    //fputs("aceita:\r\t", NovoPrograma);
    fclose(NovoPrograma);
}

void MontaMatrizEntrada(){


}

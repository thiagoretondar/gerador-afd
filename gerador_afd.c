#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

int qtdSimbolos = 0,
    qtdEstados = 0,
    qtdEstadosFinais = 0;

int estadoInicial = 0;

char simbolos[20];

// TODO: fazer um vetor de inteiro booleano, onde a posicao indica se é ou não estado final
char estadosFinais[20];

// [
//   [0][1][0] => estado0 ; simbolo1 ; vaiParaEstadoE0
//   [1][2][1] => estado1 ; simbolo2 ; vaiParaEstadoE1
// ]
int sequenciaEstados[20][3];

// Cabeçalhos
void PerguntaQuantidadeSimbolos();
void PerguntaSimbolos();
void PerguntaQuantidadeEstados();
void PerguntaEstadoInicial();
void PerguntaQuantidadeEstadosFinais();
void PerguntaEstadosFinais();
void PerguntaSequenciaDeEstados();
void MontaMatrizEntrada();
void PerguntaTipoDePrograma();
void GeraProgramaGOTO();
void GeraProgramaFunc();

int main (int argc, char const *argv[]) {
    setlocale(LC_ALL, "Portuguese");
    PerguntaQuantidadeSimbolos();
	PerguntaSimbolos();
    PerguntaQuantidadeEstados();
    //PerguntaEstadoInicial();
	//PerguntaQuantidadeEstadosFinais();
    //PerguntaEstadosFinais();
    PerguntaSequenciaDeEstados();

    int i, j, total = 0;
    char numeroEstado[2];
    for (i = 0; i < qtdEstados; i++) {
        for (j = 0; j < qtdSimbolos; j++) {
            printf("[%d,%d,%d]\n", sequenciaEstados[total][0],sequenciaEstados[total][1], sequenciaEstados[total][2]);
            total++;
        }
    }

    return 0;
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
        scanf("\t%s", &simbolos[i]);
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
    scanf("%d", &qtdEstadosFinais);
}

void PerguntaEstadosFinais() {
    int i;
    for (i = 0; i < qtdEstadosFinais; i++) {
        printf("\t%d. Qual o estado final %d? R: ", i + 1, i);
        scanf("%s", &estadosFinais[i]);
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
            // TODO: se existir um próximo estado
            //if (proxEstado != -1) {
                sequenciaEstados[total][0] = i;
                sequenciaEstados[total][1] = j;
                sequenciaEstados[total][2] = proxEstado;

                total++;
            //}
        }
        printf("\n");
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

}

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


}*/

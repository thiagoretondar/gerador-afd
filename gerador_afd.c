#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

// Enums
#define true 1
#define false 0

#define NUM_ESTADO 0
#define NUM_SIMBOLO 1
#define PROX_ESTADO 2
#define ESTADO_INEXISTENTE -1

FILE* novoPrograma;
char nomeArq[150];

int qtdSimbolos = 0,
    qtdEstados = 0,
    qtdEstadosFinais = 0;

int estadoInicial = 0;

char* simbolos[60];

// TODO: fazer um vetor de inteiro booleano, onde a posicao indica se é ou não estado final
int estadosFinais[60];

// [
//   [0][1][0] => estado0 ; simbolo1 ; vaiParaEstadoE0
//   [1][2][1] => estado1 ; simbolo2 ; vaiParaEstadoE1
// ]
int sequenciaEstados[60][3];

// Cabeçalhos
void perguntaQuantidadeSimbolos();
void perguntaSimbolos();
void perguntaQuantidadeEstados();
void perguntaEstadoInicial();
void perguntaQuantidadeEstadosFinais();
void perguntaEstadosFinais();
void perguntaSequenciaDeEstados();
void perguntaTipoDePrograma();

void geraPrograma();
void geraProgramaGOTO();
void geraProgramaFunc();

void zerarVetorEstadosFinais();
void insereEstado();
int ehEstadoFinal();
int ehApenasEstadoFinal();

void geraEstadoInicial();
void geraEstadoIntermediario();
void geraEstadoIntermediarioFinal();
void geraEstadoFinal();

int main (int argc, char const *argv[]) {
    setlocale(LC_ALL, "Portuguese");

    perguntaQuantidadeSimbolos();
    perguntaSimbolos();
    perguntaQuantidadeEstados();
    perguntaEstadoInicial();
    perguntaQuantidadeEstadosFinais();
    perguntaEstadosFinais();
    perguntaSequenciaDeEstados();

    geraPrograma();

    // percorre pela matriz para chamar as funções que criam 
    // estados intermediários, estados intermediários finais
    // e estados finais
    int i;
    for (i; i < qtdEstados * qtdSimbolos; i++) {
        int* estadoAtual = sequenciaEstados[i];

        // se o loop estiver analisando a faixa relacionada ao
        // estado inicial, podemos pular as próximas x quantidade
        // de símbolos (qtdSimbolos)
        if (estadoAtual[NUM_ESTADO] == estadoInicial) {
            geraEstadoInicial();
            i += qtdSimbolos;
            continue; // ignora o resto dos comandos dessa iteração
        } else {
            if (ehEstadoFinal(estadoAtual[NUM_ESTADO])) { // estados finais (intermediários ou não)
                if (ehApenasEstadoFinal(estadoAtual[NUM_ESTADO])) { // estado final
                    geraEstadoFinal(estadoAtual[NUM_ESTADO]);
                } else { // estado intermediário e final
                    geraEstadoIntermediarioFinal(estadoAtual[NUM_ESTADO]);
                }
            } else { // estado intermediário
                geraEstadoIntermediario(estadoAtual[NUM_ESTADO]);
            }
            i += qtdSimbolos;
        }
    }

    fclose(novoPrograma);
    return 0;
}

void geraEstadoInicial() {

    fprintf(novoPrograma,"void e%d() {\n", estadoInicial);

        fprintf(novoPrograma,"\t");
        // índice é uma relação de multiplicação do estadoInicial indicado
        // e a quantidade de símbolos existentes
        int i = estadoInicial * qtdSimbolos;

        // quantidade de iterações é a soma do índice inicial mais a quantidade
        // de símbolos existentes
        int qtd = i + qtdSimbolos;

        for (i; i < qtd; i++) {
            int* estadoAtual = sequenciaEstados[i];

            if (estadoAtual[PROX_ESTADO] != ESTADO_INEXISTENTE) {
                fprintf(novoPrograma,"if (f[p] == '%c') {\n", simbolos[estadoAtual[NUM_SIMBOLO]]);

                // verifica se o estado o próximo estado é o mesmo estado que
                // está sendo analisado atualmente
                // se for, imprime função para verificar se existe algo ainda pra ler
                // caso contrário, apenas chama o próximo estado
                if (estadoAtual[NUM_ESTADO] == estadoAtual[PROX_ESTADO]) {
                    fprintf(novoPrograma,"\t\tif (temAlgoParaAnalisarNoEstadoInicial()) {\n");
                        fprintf(novoPrograma,"\t\t\tproximoEstado(&e%d);\n", estadoAtual[NUM_ESTADO]);
                    fprintf(novoPrograma,"\t\t} else {\n");
                        fprintf(novoPrograma,"\t\t\taceita();\n");
                    fprintf(novoPrograma,"\t\t}\n");
                } else {
                    fprintf(novoPrograma,"\t\tproximoEstado(&e%d);\n", estadoAtual[PROX_ESTADO]);
                }

            fprintf(novoPrograma,"\t} else ");
            }

        }

        fprintf(novoPrograma," {\n");
            fprintf(novoPrograma,"\t\trejeita();\n");
        fprintf(novoPrograma,"\t}\n");

    fprintf(novoPrograma,"}\n\n");
}

void geraEstadoIntermediario(int numEstado) {

    fprintf(novoPrograma,"void e%d() { //estado intermediário\n", numEstado);

        // índice é uma relação de multiplicação do numEstado indicado
        // e a quantidade de símbolos existentes
        int i = numEstado * qtdSimbolos;

        // quantidade de iterações é a soma do índice inicial mais a quantidade
        // de símbolos existentes
        int qtd = i + qtdSimbolos;

        fprintf(novoPrograma,"\tif (temAlgoParaAnalisar()) {\n");
            fprintf(novoPrograma,"\t\t");

            // percorre todos os estados do subarray do numEstado
            for (i; i < qtd; i++) {
                // armazena na variável estadoAtual o subarray
                int* estadoAtual = sequenciaEstados[i];

                // imprime a chamada para o próximo estado caso essa exista
                if (estadoAtual[PROX_ESTADO] != ESTADO_INEXISTENTE) {
                    fprintf(novoPrograma,"if (f[p] == '%c') {\n", simbolos[estadoAtual[NUM_SIMBOLO]]);
                        fprintf(novoPrograma,"\t\t\tproximoEstado(&e%d);\n", estadoAtual[PROX_ESTADO]);
                    fprintf(novoPrograma,"\t\t} else ");
                } 
            }

                // se nenhuma letra combinar, rejeita a sequencia
                fprintf(novoPrograma,"{\n");
                    fprintf(novoPrograma,"\t\t\trejeita();\n");
                fprintf(novoPrograma,"\t\t}\n");

        // se não tem mais nada para analisar, rejeita, pois não é um estado final
        fprintf(novoPrograma,"\t} else {\n");
            fprintf(novoPrograma,"\t\trejeita();\n");
        fprintf(novoPrograma,"\t}\n");

    fprintf(novoPrograma,"}\n\n");
}

void geraEstadoIntermediarioFinal(int numEstado) {
    
    fprintf(novoPrograma,"void e%d() {\n", numEstado);

        // índice é uma relação de multiplicação do numEstado indicado
        // e a quantidade de símbolos existentes
        int i = numEstado * qtdSimbolos;

        // quantidade de iterações é a soma do índice inicial mais a quantidade
        // de símbolos existentes
        int qtd = i + qtdSimbolos;

        fprintf(novoPrograma,"\tif (temAlgoParaAnalisar()) {\n");
            fprintf(novoPrograma,"\t\t");

            // percorre todos os estados do subarray do numEstado
            for (i; i < qtd; i++) {
                // armazena na variável estadoAtual o subarray
                int* estadoAtual = sequenciaEstados[i];

                // imprime a chamada para o próximo estado caso essa exista
                if (estadoAtual[PROX_ESTADO] != ESTADO_INEXISTENTE) {
                    fprintf(novoPrograma,"if (f[p] == '%c') {\n", simbolos[estadoAtual[NUM_SIMBOLO]]);
                        fprintf(novoPrograma,"\t\t\tproximoEstado(&e%d);\n", estadoAtual[PROX_ESTADO]);
                    fprintf(novoPrograma,"\t\t} else ");
                } 
            }

                // se nenhuma letra combinar, rejeita a sequencia
                fprintf(novoPrograma,"{\n");
                    fprintf(novoPrograma,"\t\t\trejeita();\n");
                fprintf(novoPrograma,"\t\t}\n");

        // se não tem mais nada para analisar, aceita, pois é um estado final
        fprintf(novoPrograma,"\t} else {\n");
            fprintf(novoPrograma,"\t\taceita();\n");
        fprintf(novoPrograma,"\t}\n");

    fprintf(novoPrograma,"}\n\n");
}

void geraEstadoFinal(int numEstado) {

    // verifica se não existe mais nada para analisar, e se não tiver, aceita
    fprintf(novoPrograma,"void e%d() {\n", numEstado);
        fprintf(novoPrograma,"\tif (!temAlgoParaAnalisar()) {\n");
            fprintf(novoPrograma,"\t\taceita();\n");
        fprintf(novoPrograma,"\t} else {\n");
            fprintf(novoPrograma,"\t\trejeita();\n");
        fprintf(novoPrograma,"\t}\n");
    fprintf(novoPrograma,"}\n\n");
}

void perguntaQuantidadeSimbolos() {

    printf("Quantos símbolos tem o alfabeto? R: ");
    scanf("%d", &qtdSimbolos);
}

void perguntaSimbolos() {

    int i;
    for (i = 0; i < qtdSimbolos && i < sizeof(simbolos) ; i++) {
        //Qual o simbolo será inputado no alfabeto
        printf("\t%d. Qual é o símbolo %d? R: ", i + 1, i);
        scanf("\t%c", &simbolos[i]);
    }
}

void perguntaQuantidadeEstados() {

    printf("Quantos estados? R: ");
    scanf("%d", &qtdEstados);
}

void perguntaEstadoInicial() {

    printf("Qual o estado inicial? R: ");
    scanf("%d", &estadoInicial);
}

void perguntaQuantidadeEstadosFinais() {

    printf("Quantos estados finais? R: ");

    int qtd;
    scanf("%d", &qtd);

    // quantidade de estados finais não pode ser maior que quantidade de estados totais
    if (qtd > qtdEstados) {
        printf("ERRO: quantidade de estados finais maior do que a quantidade de estados totais!\n");
        printf("Digite novamente\n");
        perguntaQuantidadeEstadosFinais();
    } else if (qtd <= 0) { // deve exister um estado final
        printf("ERRO: quantidade de estados finais menor do que zero!\n");
        printf("Digite novamente\n");
        perguntaQuantidadeEstadosFinais();
    } else {
        qtdEstadosFinais = qtd;
    }
}

void perguntaEstadosFinais() {

    zerarVetorEstadosFinais();

    int i;
    for (i = 0; i < qtdEstadosFinais; i++) {
        printf("\t%d. Qual o estado final %d? R: ", i + 1, i);
        scanf("%d", &estadosFinais[i]);
    }
}

void perguntaSequenciaDeEstados() {

    int i, j, total = 0;
    char numeroEstado[2];
    for (i = 0; i < qtdEstados; i++) {
        for (j = 0; j < qtdSimbolos; j++) {
            printf("\tPara o estado e%d e símbolo %c qual o próximo estado? ", i, simbolos[j]);
            scanf("%s", numeroEstado);

            // realiza o casting de string para inteiro
            int proxEstado = atoi(numeroEstado);

            insereEstado(&total, i, j, proxEstado);
        }
        printf("\n");
    }
}

void geraPrograma(){

    int gerar;

    printf("Qual o nome do programa?\n");
    scanf("%s", nomeArq);
    strcat(nomeArq,".c");

    printf("Como gostaria de gerar? ([1] = GOTO: [2] = Função)\n");
    scanf("%d", &gerar);

    switch (gerar) {
        case 1:
            //geraProgramaGOTO(nomeArq);
            break;
        case 2:
            geraProgramaFunc(nomeArq);
            break;
        default:
            printf("Opção inválida!\n");
            break;
    }

    printf("Programa criado! Consulte o diretório do programa.\n");
}

void insereEstado(int *posicao, int estado, int simbolo, int proxEstado) {

    sequenciaEstados[*posicao][NUM_ESTADO] = estado;
    sequenciaEstados[*posicao][NUM_SIMBOLO] = simbolo;
    sequenciaEstados[*posicao][PROX_ESTADO] = proxEstado;

    // incrementa para a próxima posição
    (*posicao)++;
}

void zerarVetorEstadosFinais() {

    int i;
    for (i = 0; i < sizeof(estadosFinais); i++) {
        estadosFinais[i] = 0;
    }
}

int ehEstadoFinal(int numEstado) {

    // percorre vetores de estados finais para 
    // verificar se numEstado é final
    int i;
    for (i = 0; i < qtdEstadosFinais; i++) {
        if (numEstado == estadosFinais[i]) {
            return true;
        }
    }

    return false;
}

int ehApenasEstadoFinal(int numEstado) {

    // percorre sequencia de estados e verifica se o estado é apenas final
    int i = numEstado * qtdSimbolos;
    int j = i;
    for (i; i < j + qtdSimbolos; i++) {
        int* estadoAtual = sequenciaEstados[i];
        if (estadoAtual[PROX_ESTADO] != ESTADO_INEXISTENTE) {
            return false;
        }
    }

    return true;
}

void geraProgramaFunc(){

    char* includes = "#include <stdio.h>\n"
                     "#include <stdlib.h>\n"
                     "#include <string.h>\n\n";

    char* defines = "#define true 1\n"
                    "#define false 0\n\n";


    char* variaveisDeControle = "char f[200];\n"
                                "int p;\n"
                                "int aceito;\n\n";

    char cabecalhos[1000] = "/* Cabeçalhos */\n"
                       "void rejeita();\n"
                       "void aceita();\n"
                       "void proximaLetra();\n"
                       "void proximoEstado();\n"
                       "void proximoEstadoFinal();\n"
                       "int temAlgoParaAnalisar();\n"
                       "int temAlgoParaAnalisarNoEstadoInicial();\n\n";
    int i = 0;
    for (i; i < qtdEstados; i++) {
        char estado[15];
        sprintf(estado, "void e%d();\n", i);
        strcat(cabecalhos, estado);
    }


    char *main_function = "\n\nint main(int argc, char const *argv[]) { \n"
                    "\n"
                    "\tif (argc == 2) { \n"
                        "\t\tstrcpy(f, argv[1]); \n"
                    "\t} \n"
                    "\n"
                    "\tp = 0; \n";

    char chamada_estado_inicial[10];
    sprintf(chamada_estado_inicial, "\n\te%d(); \n\n", estadoInicial);

    char *main_function2 = "\tif (!aceito) { \n"
                        "\t\tprintf(\"%%s\\n\", argv[1]); \n"
                        "\t\tif (p == 0) {\n"
                        "\t\t\tprintf(\"^\\n\");\n"
                        "\t\t} else {\n"
                        "\t\t\tprintf(\"%%*s\" \"%%s\\n\", p - 1, \" \", \"^\"); \n"
                        "\t\t}\n"
                    "\t} \n"
                    "\n"
                    "\treturn 0; \n"
                "}\n\n";

    char* funcoes = "void proximaLetra() {\n"
                        "\n"
                        "\t// incrementa possição da letra\n"
                        "\tp++;\n"
                    "}\n"
                    "\n"
                    "void proximoEstado(void (*proxEstado)()) {\n"
                        "\n"
                        "\t// necessário incrementar posição de letra a ser lida\n"
                        "\tproximaLetra();\n"
                        "\n"
                        "\t// chama a próxima função\n"
                        "\t(*proxEstado)();\n"
                    "}\n"
                    "\n"
                    "void finalizaOuVaiParaEstadoInicial(void (*proxEstado)()) {\n"
                    "\n"
                        "\tproximaLetra();\n"
                        "\tif (!temAlgoParaAnalisar()) { // não existe mais nada para analisar\n"
                            "\t\taceita();\n"
                        "\t} else { // existe string para ser analisada\n"
                            "\t\t(*proxEstado)(); // manda para o começo\n"
                        "\t}\n"
                    "}\n"
                    "\n"
                    "int temAlgoParaAnalisar() {\n"
                    "\n"
                        "\t// verifica se na posição atual existe algo para analisar\n"
                        "\tif (f[p] == '\\0') {\n"
                            "\t\treturn false;\n"
                        "\t}\n"
                        "\n"
                        "\treturn true;\n"
                    "}\n"
                    "\n"
                    "int temAlgoParaAnalisarNoEstadoInicial() {\n"
                    "\n"
                        "\t// verifica se existe uma próxima letra para analisar\n"
                        "\tif (f[p + 1] == '\\0') {\n"
                            "\t\treturn false;\n"
                        "\t}\n"
                        "\n"
                        "\treturn true;\n"
                    "}\n"
                    "\n"
                    "void aceita() {\n"
                    "\n"
                        "\tprintf(\"A palavra foi aceita\\n\");\n"
                        "\taceito = 1;\n"
                    "}\n"
                    "\n"
                    "void rejeita() {\n"
                    "\n"
                        "\tprintf(\"A palavra foi rejeitada\\n\");\n"
                        "\taceito = 0;\n"
                    "}\n\n";

    novoPrograma = fopen(nomeArq, "w+");

    fprintf(novoPrograma, includes);
    fprintf(novoPrograma, defines);
    fprintf(novoPrograma, variaveisDeControle);
    fprintf(novoPrograma, cabecalhos);
    fprintf(novoPrograma, main_function);
    fprintf(novoPrograma, chamada_estado_inicial);
    fprintf(novoPrograma, main_function2);
    fprintf(novoPrograma, funcoes);
}
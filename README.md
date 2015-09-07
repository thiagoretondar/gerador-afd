### Desenvolvimento de um gerador de programas a partir de A.F.D's

Os programas gerados devem atuar como reconhecedores. Exemplo do que será exigido:

Dado o A.F. (autômato finito)

![Alt Text](https://docs.google.com/drawings/d/1ebUl1RggpTV6uWzpMJBIasWnf7W59EvBpErUT5EVn1U/pub?w=567&h=154)

Ao executar o programa...


**Σ)** Quantos símbolos tem o alfabeto?  *R:3*

  1. Qual o símbolo 0? *R: a*
  2. Qual o símbolo 1? *R: b*
  3. Qual o símbolo 2? *R: c*
  
**Q)** Quantos estados? *R: 3*

**q0)** Qual o estado inicial? *R: 0*

**F)** Quantos estados finais? *R: 2*
  
  1. Qual o estado final 0? *R: 1*
  2. 2. Qual o estado final 1? *R: 2*

**δ)**
* Para o estado **e0** e símbolo **a** qual o próximo estado? **1**
* Para o estado **e0** e símbolo **b** qual o próximo estado? **-1**
* Para o estado **e0** e símbolo **c** qual o próximo estado? **-1**
* Para o estado **e1** e símbolo **a** qual o próximo estado? **-1**
* Para o estado **e1** e símbolo **b** qual o próximo estado? **0**
* Para o estado **e1** e símbolo **c** qual o próximo estado? **2**
* Para o estado **e2** e símbolo **a** qual o próximo estado? **-1**
* Para o estado **e2** e símbolo **b** qual o próximo estado? **-1**
* Para o estado **e2** e símbolo **c** qual o próximo estado? **-1**
 
*Obs.: -1 representa um estado que não existe*

Qual o nome do programa? *R:Aula*
Comor quer gerar (1=goto, 2=funcao)? *R: 1*
Programa aula.c gerado

#### HOW TO USE
```bash
gcc gerador_afd.c -o gerador_afd.o
./gerador_afd.o
```

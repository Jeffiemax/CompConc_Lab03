//Soma todos os elementos de um vetor de inteiro
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include "timer.h"

long long int n; //dimensao do vetor de entrada
int nthreads; //numero de threads
double *vetor; //vetor de entrada com dimensao n 
long long int Li, Ls, ValorS, ValorC;

//fluxo das threads
void * tarefa(void * arg) {
   long int id = (long int) arg; //identificador da thread
   double *aux; //variavel local da soma de elementos
   aux = (double*) malloc(sizeof(double));
   if(aux==NULL) {exit(1);}
   long int tamBloco = n/nthreads;  //tamanho do bloco de cada thread 
   long int ini = id * tamBloco; //elemento inicial do bloco da thread
   long int fim; //elemento final(nao processado) do bloco da thread
   if(id == nthreads-1) fim = n;
   else fim = ini + tamBloco; //trata o resto se houver
   for(long int i=ini; i<fim; i++){
      if(vetor[i] > Li && vetor[i] < Ls){
      //printf("%lf\n", vetor[i]);
      *aux+= 1;
      }
   }
   //retorna o resultado da soma local
   pthread_exit((void *) aux); 
}

//fluxo principal
int main(int argc, char *argv[]) {
   double ini, fim; //tomada de tempo
   pthread_t *tid; //identificadores das threads no sistema
   double *retorno; //valor de retorno das threads

   //recebe e valida os parametros de entrada (dimensao do vetor, numero de threads)
   if(argc < 5) {
       fprintf(stderr, "Digite: %s <numero de elemento do vetor> <numero threads> <Limiar inferior> < Limiar superior >\n", argv[0]);
       return 1; 
   }
   n = atoll(argv[1]);
   nthreads = atoi(argv[2]);
   Li = atoi(argv[3]);
   Ls = atoi(argv[4]);

   //aloca o vetor de entrada
   vetor = (double*) malloc(sizeof(double)*n);
   if(vetor == NULL) {
      fprintf(stderr, "ERRO--malloc\n");
      return 2;
   }
   //preenche o vetor de entrada
   srand(time(NULL));
   for(long int i=0; i<n; i++)
      vetor[i] = rand() % 100;
  
   //encontrar a quantidade de valores de um vetor  que estao dentro de uma faixa de valores (parte sequencial dos elementos)
   GET_TIME(ini);
   for(long int i=0; i<n; i++){
      if(vetor[i] > Li && vetor[i] < Ls){
      //printf("%lf\n", vetor[i]);
      ValorS+= 1;
      }
   }
   GET_TIME(fim);
   printf("Tempo sequencial:  %lf\n", fim-ini);

   //encontrar a quantidade de valores de um vetor  que estao dentro de uma faixa de valores (parte sequencial dos elementos)
   GET_TIME(ini);
   tid = (pthread_t *) malloc(sizeof(pthread_t) * nthreads);
   if(tid==NULL) {
      fprintf(stderr, "ERRO--malloc\n");
      return 2;
   }
   //criar as threads
   for(long int i=0; i<nthreads; i++) {
      if(pthread_create(tid+i, NULL, tarefa, (void*) i)){
         fprintf(stderr, "ERRO--pthread_create\n");
         return 3;
      }
   }
   //aguardar o termino das threads
   for(long int i=0; i<nthreads; i++) {
      if(pthread_join(*(tid+i), (void**) &retorno)){
         fprintf(stderr, "ERRO--pthread_create\n");
         return 3;
      }
   }
   ValorC = *retorno;
   
  /*  printf("%lld é o valor encontrado em tempo sequencial\n",ValorS);
   printf("%lld é o valor encontrado em tempo concorrente\n",ValorC); */

   GET_TIME(fim);
   printf("Tempo concorrente:  %lf\n", fim-ini);

   //exibir os resultados
    /* for(long int i=0; i<n; i++)
      printf("%lf \n", vetor[i]);  */

   //libera as areas de memoria alocadas
   free(vetor);
   free(tid);

   return 0;
}
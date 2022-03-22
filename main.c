/* main.c */
/* teste do tipo de dados meudouble */
#include <stdio.h>
#include "meu_complexo.h"
#include "meu_racional.h"
#include "matriz.h"

int main()
{

   /* ------ PARTE ORIGINAL DO PROGRAMA: MEU_COMPLEXO ------*/
   MeuComplexo_pt ptC1 = NULL, ptC2 = NULL, ptC3 = NULL;

   ptC1 = Complexo_constroi(ptC1, 10.0, 20.0);

   ptC2 = ptC1->Metodo->copia(ptC1);

   printf("Os dois numeros sao %s %s \n",
          ptC1->Metodo->imprime(ptC1),
          ptC2->Metodo->imprime(ptC2));

   ptC3 = Complexo_constroi(ptC3, 0.0, 0.0);
   ptC3 = ptC2->Metodo->atribui(ptC2, ptC3);
   printf("ptC3 recebeu o valor de Y2 = %s \n",
          ptC3->Metodo->imprime(ptC3));

   ptC3 = ptC1->Metodo->soma(ptC1, ptC2, ptC3);
   printf("ptC3 recebeu a soma de Y1 com Y2 = %s \n",
          ptC3->Metodo->imprime(ptC3));

   ptC3 = ptC3->Metodo->subt(ptC3, ptC2, ptC3);
   printf("ptC3 recebeu a subtracao de Y3 com Y2 = %s \n",
          ptC3->Metodo->imprime(ptC3));

   ptC3 = ptC1->Metodo->mult(ptC1, ptC2, ptC3);
   printf("ptC3 recebeu a multiplicacao de Y1 com Y2 = %s \n",
          ptC3->Metodo->imprime(ptC3));

   ptC3 = ptC1->Metodo->divd(ptC1, ptC2, ptC3);
   printf("ptC3 recebeu a divisão de Y1 com Y2 = %s \n",
          ptC3->Metodo->imprime(ptC3));

   ptC3 = ptC1->Metodo->ac_soma(ptC3, ptC2);
   printf("ptC3 foi somado com Y2 = %s \n",
          ptC3->Metodo->imprime(ptC3));

   ptC3 = ptC3->Metodo->ac_subt(ptC3, ptC2);
   printf("ptC3 foi subtraido de Y2 = %s \n",
          ptC3->Metodo->imprime(ptC3));

   ptC3 = ptC1->Metodo->ac_mult(ptC3, ptC2);
   printf("ptC3 foi multiplicado por Y2 = %s \n",
          ptC3->Metodo->imprime(ptC3));

   ptC3 = ptC1->Metodo->ac_divd(ptC3, ptC2);
   printf("ptC3 foi dividido por Y2 = %s \n",
          ptC3->Metodo->imprime(ptC3));

   if (ptC1->Metodo->compara(ptC1, ptC2) == 0)
   {
      printf("Y1 eh igual a Y2 = %s\n", ptC1->Metodo->imprime(ptC1));
   }
   if (ptC1->Metodo->compara(ptC2, ptC3) > 0)
   {
      printf("Y2 eh maior que Y3 \n");
   }
   if (ptC1->Metodo->compara(ptC2, ptC3) < 0)
   {
      printf("Y2 eh menor que Y3 \n");
   }

   ptC1->Metodo->destroi(ptC1);
   ptC2->Metodo->destroi(ptC2);
   ptC3->Metodo->destroi(ptC3);

   printf("\n\nPARTE DO RACIONAL:\n\n");
   /* ------ MEU_RACIONAL ------*/

   /* foi copiado o código acima e feito alterações para mostrar as funções com racionais
      essa parte do código também inclui o uso da função implementada Simplifica antes de
      liberar o heap de memória */

   MeuRacional_pt ptR1 = NULL, ptR2 = NULL, ptR3 = NULL;

   ptR1 = Racional_constroi(ptR1, 10, 20);

   ptR2 = ptR1->Metodo->copia(ptR1);

   printf("Os dois numeros sao %s %s \n",
          ptR1->Metodo->imprime(ptR1),
          ptR2->Metodo->imprime(ptR2));

   ptR3 = Racional_constroi(ptR3, 0, 0);
   ptR3 = ptR2->Metodo->atribui(ptR2, ptR3);
   printf("ptR3 recebeu o valor de Y2 = %s \n",
          ptR3->Metodo->imprime(ptR3));

   ptR3 = ptR1->Metodo->soma(ptR1, ptR2, ptR3);
   printf("ptR3 recebeu a soma de Y1 com Y2 = %s \n",
          ptR3->Metodo->imprime(ptR3));

   ptR3 = ptR3->Metodo->subt(ptR3, ptR2, ptR3);
   printf("ptR3 recebeu a subtracao de Y3 com Y2 = %s \n",
          ptR3->Metodo->imprime(ptR3));

   ptR3 = ptR1->Metodo->mult(ptR1, ptR2, ptR3);
   printf("ptR3 recebeu a multiplicacao de Y1 com Y2 = %s \n",
          ptR3->Metodo->imprime(ptR3));

   ptR3 = ptR1->Metodo->divd(ptR1, ptR2, ptR3);
   printf("ptR3 recebeu a divisão de Y1 com Y2 = %s \n",
          ptR3->Metodo->imprime(ptR3));

   ptR3 = ptR1->Metodo->ac_soma(ptR3, ptR2);
   printf("ptR3 foi somado com Y2 = %s \n",
          ptR3->Metodo->imprime(ptR3));

   ptR3 = ptR3->Metodo->ac_subt(ptR3, ptR2);
   printf("ptR3 foi subtraido de Y2 = %s \n",
          ptR3->Metodo->imprime(ptR3));

   ptR3 = ptR1->Metodo->ac_mult(ptR3, ptR2);
   printf("ptR3 foi multiplicado por Y2 = %s \n",
          ptR3->Metodo->imprime(ptR3));

   ptR3 = ptR1->Metodo->ac_divd(ptR3, ptR2);
   printf("ptR3 foi dividido por Y2 = %s \n",
          ptR3->Metodo->imprime(ptR3));

   if (ptR1->Metodo->compara(ptR1, ptR2) == 0)
   {
      printf("Y1 eh igual a Y2 = %s\n", ptR1->Metodo->imprime(ptR1));
   }
   if (ptR1->Metodo->compara(ptR2, ptR3) > 0)
   {
      printf("Y2 eh maior que Y3 \n");
   }
   if (ptR1->Metodo->compara(ptR2, ptR3) < 0)
   {
      printf("Y2 eh menor que Y3 \n");
   }

   ptR1 = ptR1->Metodo->simplifica(ptR1);
   ptR2 = ptR2->Metodo->simplifica(ptR2);
   ptR3 = ptR3->Metodo->simplifica(ptR3);

   printf("ptR1 foi simplificado = %s \n",ptR1->Metodo->imprime(ptR1));   
   printf("ptR2 foi simplificado = %s \n",ptR2->Metodo->imprime(ptR2));
   printf("ptR3 foi simplificado = %s \n",ptR3->Metodo->imprime(ptR3));

   ptR1->Metodo->destroi(ptR1);
   ptR2->Metodo->destroi(ptR2);
   ptR3->Metodo->destroi(ptR3);

   /*  Parte MATRIZ   */
     printf("\n\nPARTE Da Matriz:\n\n");
   Matriz_pt ptM1 =NULL, ptM2 = NULL, ptM3 = NULL;
   unsigned int tam[2];
   tam[0] = 3;
   tam[1] = 3;

   double valores[9] = {2,1,3,4,5,6,4,3,2};

   ptM1 = Matriz_2D_criar(ptM1,tam,valores);

   ptM2 = ptM1->Metodo->copia(ptM1);

   printf("as duas matrizes sao \n\n");
   ptM1->Metodo->imprime(ptM1);
   printf("\n");
   ptM2->Metodo->imprime(ptM2);
   printf("\n");

   ptM3 = Matriz_2D_criar(ptM3,tam,valores);
   ptM3 = ptM2->Metodo->atribui(ptM2, ptM3);
   printf("ptM3 recebeu o valor de ptM2\n");
   ptM3->Metodo->imprime(ptM3);

   printf("\n");
   ptM3 = ptM1->Metodo->soma(ptM1, ptM2, ptM3);
   printf("ptM3 recebeu a soma de M1 com M2 \n");
   ptM3->Metodo->imprime(ptM3);   
   
   printf("\n");
   ptM3 = ptM3->Metodo->ac_subt(ptM3, ptM1);
   printf("ptM3 recebeu a subtracao de M3 com M1 \n");
   ptM3->Metodo->imprime(ptM3);
   printf("\n");

   ptM3 = ptM1->Metodo->mult(ptM1, ptM2, ptM3);
   printf("ptM3 recebeu a multiplicacao de M1 com M2\n");
   ptM3->Metodo->imprime(ptM3);

   printf("\n");
   ptM3 = ptM1->Metodo->divd(ptM1, ptM2, ptM3);
   printf("ptM3 recebeu a divisão de M1 com M2\n");
   ptM3->Metodo->imprime(ptM3);

   printf("\n");
   printf("Transpondo M3 pela diagonal secundaria\n");
   ptM3 = ptM3->Metodo->transpor_Diag2(ptM3);
   ptM3->Metodo->imprime(ptM3); 
   printf("\n");
   
   printf("\n");
   ptM3 = ptM3->Metodo->multPorEscalar(ptM3,2);
   printf("ptM3 recebeu a multiplicacao de M3 por 2\n");
   ptM3->Metodo->imprime(ptM3);
   printf("\n");

   printf("\n");
   ptM3 = ptM3->Metodo->identidade(ptM3, ptM3->tam);
   printf("M3 virou identidade\n");
   ptM3->Metodo->imprime(ptM3);
   printf("\n");

   printf("\n");
   ptM3 = ptM3->Metodo->ones(ptM3);
   printf("M3 virou matriz de 1s\n");
   ptM3->Metodo->imprime(ptM3);
   printf("\n");

   printf("M2:\n");
   ptM2->Metodo->imprime(ptM2);
   printf("\nM2 reverse vertical:\n");
   ptM2 = ptM2->Metodo->reverseVertical(ptM2);
   ptM2->Metodo->imprime(ptM2);
   printf("\n");

   printf("M1:\n");
   ptM1->Metodo->imprime(ptM1);
   printf("\nM1 reverse horizontal:\n");
   ptM1 = ptM1->Metodo->reverseHorizontal(ptM1);
   ptM1->Metodo->imprime(ptM1);
   printf("\n");
  
   printf("\nM1 Adiciona linha e coluna:\n");
   ptM1 = ptM1->Metodo->acrescentaColuna(ptM1);
   ptM1 = ptM1->Metodo->acrescentaLinha(ptM1);
   ptM1->Metodo->imprime(ptM1);
   printf("\n");


   return (0);
}
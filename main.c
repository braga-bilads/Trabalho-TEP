/* main.c */
/* teste do tipo de dados meudouble */
#include <stdio.h>
#include "meu_complexo.h"
#include "meu_racional.h"

int main ()
{

/* ------ PARTE ORIGINAL DO PROGRAMA: MEU_COMPLEXO ------*/
	MeuComplexo_pt ptC1=NULL, ptC2=NULL, ptC3=NULL;

	ptC1 = Complexo_constroi (ptC1, 10.0, 20.0);

	ptC2 = ptC1->Metodo->copia (ptC1);

	printf ("Os dois numeros sao %s %s \n",
				ptC1->Metodo->imprime (ptC1),
				ptC2->Metodo->imprime (ptC2));

    ptC3 = Complexo_constroi (ptC3, 0.0, 0.0);
    ptC3 = ptC2->Metodo->atribui (ptC2, ptC3);
    printf ("ptC3 recebeu o valor de Y2 = %s \n",
				ptC3->Metodo->imprime (ptC3));


    ptC3 = ptC1->Metodo->soma(ptC1, ptC2, ptC3);
    printf ("ptC3 recebeu a soma de Y1 com Y2 = %s \n",
				ptC3->Metodo->imprime (ptC3));

    ptC3 = ptC3->Metodo->subt(ptC3, ptC2, ptC3);
    printf ("ptC3 recebeu a subtracao de Y3 com Y2 = %s \n",
				ptC3->Metodo->imprime (ptC3));

    ptC3 = ptC1->Metodo->mult(ptC1, ptC2, ptC3);
    printf ("ptC3 recebeu a multiplicacao de Y1 com Y2 = %s \n",
                 ptC3->Metodo->imprime (ptC3));

    ptC3 = ptC1->Metodo->divd(ptC1, ptC2, ptC3);
    printf ("ptC3 recebeu a divisão de Y1 com Y2 = %s \n",
                 ptC3->Metodo->imprime (ptC3));

    ptC3 = ptC1->Metodo->ac_soma(ptC3, ptC2);
    printf ("ptC3 foi somado com Y2 = %s \n",
				ptC3->Metodo->imprime (ptC3));

    ptC3 = ptC3->Metodo->ac_subt(ptC3, ptC2);
    printf ("ptC3 foi subtraido de Y2 = %s \n",
				ptC3->Metodo->imprime (ptC3));

    ptC3 = ptC1->Metodo->ac_mult(ptC3, ptC2);
    printf ("ptC3 foi multiplicado por Y2 = %s \n",
                 ptC3->Metodo->imprime (ptC3));

    ptC3 = ptC1->Metodo->ac_divd(ptC3, ptC2);
    printf ("ptC3 foi dividido por Y2 = %s \n",
                 ptC3->Metodo->imprime (ptC3));

    if (ptC1->Metodo->compara(ptC1,ptC2)==0)
    {
       printf ("Y1 eh igual a Y2 = %s\n", ptC1->Metodo->imprime(ptC1));
    }
    if (ptC1->Metodo->compara(ptC2,ptC3)>0)
    {
       printf ("Y2 eh maior que Y3 \n");
    }
    if (ptC1->Metodo->compara(ptC2,ptC3)<0)
    {
       printf ("Y2 eh menor que Y3 \n");
    }

	ptC1->Metodo->destroi (ptC1);
	ptC2->Metodo->destroi (ptC2);
   ptC3->Metodo->destroi (ptC3);

   /* ------ PARTE ORIGINAL DO PROGRAMA: MEU_RACIONAL ------*/
	MeuRacional_pt ptR1=NULL, ptR2=NULL, ptR3=NULL;


	ptR1 = Racional_constroi(ptR1, 10, 20);

	ptR2 = ptR1->Metodo->copia(ptR1);

	printf ("Os dois numeros sao %s %s \n",
				ptR1->Metodo->imprime(ptR1),
				ptR2->Metodo->imprime(ptR2));

    ptR3 = Racional_constroi (ptR3, 0, 0);
    ptR3 = ptR2->Metodo->atribui(ptR2, ptR3);
    printf ("ptR3 recebeu o valor de Y2 = %s \n",
				ptR3->Metodo->imprime(ptR3));


    ptR3 = ptR1->Metodo->soma(ptR1, ptR2, ptR3);
    printf ("ptR3 recebeu a soma de Y1 com Y2 = %s \n",
				ptR3->Metodo->imprime(ptR3));

    ptR3 = ptR3->Metodo->subt(ptR3, ptR2, ptR3);
    printf ("ptR3 recebeu a subtracao de Y3 com Y2 = %s \n",
				ptR3->Metodo->imprime(ptR3));

    ptR3 = ptR1->Metodo->mult(ptR1, ptR2, ptR3);
    printf ("ptR3 recebeu a multiplicacao de Y1 com Y2 = %s \n",
                 ptR3->Metodo->imprime(ptR3));

    ptR3 = ptR1->Metodo->divd(ptR1, ptR2, ptR3);
    printf ("ptR3 recebeu a divisão de Y1 com Y2 = %s \n",
                 ptR3->Metodo->imprime(ptR3));

    ptR3 = ptR1->Metodo->ac_soma(ptR3, ptR2);
    printf ("ptR3 foi somado com Y2 = %s \n",
				ptR3->Metodo->imprime(ptR3));

    ptR3 = ptR3->Metodo->ac_subt(ptR3, ptR2);
    printf ("ptR3 foi subtraido de Y2 = %s \n",
				ptR3->Metodo->imprime(ptR3));

    ptR3 = ptR1->Metodo->ac_mult(ptR3, ptR2);
    printf ("ptR3 foi multiplicado por Y2 = %s \n",
                 ptR3->Metodo->imprime(ptR3));

    ptR3 = ptR1->Metodo->ac_divd(ptR3, ptR2);
    printf ("ptR3 foi dividido por Y2 = %s \n",
                 ptR3->Metodo->imprime(ptR3));

    if (ptR1->Metodo->compara(ptR1,ptR2)==0)
    {
       printf ("Y1 eh igual a Y2 = %s\n", ptR1->Metodo->imprime(ptR1));
    }
    if (ptR1->Metodo->compara(ptR2,ptR3)>0)
    {
       printf ("Y2 eh maior que Y3 \n");
    }
    if (ptR1->Metodo->compara(ptR2,ptR3)<0)
    {
       printf ("Y2 eh menor que Y3 \n");
    }

	ptR1->Metodo->destroi (ptR1);
	ptR2->Metodo->destroi (ptR2);
   ptR3->Metodo->destroi (ptR3);

	return (0);
}









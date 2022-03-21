
#include <float.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "matriz.h"


static  Numero_pt copia_ (Numero_t const * const  me);

static  Numero_pt atribui_ (Numero_t const * const  me,
							Numero_t       * const  outro) ;

static  Numero_pt soma_  (Numero_t const * const  me,
						  Numero_t const * const  outro,
						  Numero_t       * const  res);

static  Numero_pt subt_  (	Numero_t const * const  me,
						    Numero_t const * const  outro,
							Numero_t       * const  res);

static  Numero_pt mult_  ( Numero_t const * const  me,
									Numero_t const * const  outro,
									Numero_t       * const  res);

static  Numero_pt ac_soma_ (Numero_t       * const  me,
									 Numero_t const * const  outro);

static  Numero_pt ac_subt_ (Numero_t       * const  me,
									 Numero_t const * const  outro);

static  Numero_pt ac_mult_ (Numero_t       * const  me,
									 Numero_t const * const  outro);

static  Numero_pt ac_divd_ (Numero_t       * const  me,
									 Numero_t const * const  outro);

static  Numero_pt divd_  ( Numero_t const * const  me,
									Numero_t const * const  outro,
									Numero_t       * const  res);

static  int	compara_ 	(Numero_t const * const  me,
							 Numero_t const * const  outro);

static  char * imprime_  (Numero_t const * const  me);

static  void destroi_ (Numero_t   *   me);



/*---------------------------------------------------------------------*
 * IMPLEMENTAÇÃO DA INTERFACE PÚBLICA das funções virtuais de Matriz*
 * -------------------------------------------------------------------*/
static  Matriz_pt Copia_ (Matriz_t const * const  me);

static  Matriz_pt Atribui_ (Matriz_t const * const  me,
							     Matriz_t       * const  outro) ;

static  Matriz_pt Soma_  (Matriz_t const * const  me,
							   Matriz_t const * const  outro,
							   Matriz_t       * const  res);

static  Matriz_pt Subt_  (Matriz_t const * const  me,
							   Matriz_t const * const  outro,
							   Matriz_t       * const  res);

static  Matriz_pt Mult_  ( Matriz_t const * const  me,
								Matriz_t const * const  outro,
								Matriz_t       * const  res);

static  Matriz_pt Divd_  ( Matriz_t const * const  me,
								Matriz_t const * const  outro,
								Matriz_t       * const  res);

static  char *    Imprime_  (Matriz_t const * const  me);

static  void        Destroi_ (Matriz_t  *   me);

static  Matriz_pt  Modulo_ (Matriz_t   const * const me);

static  Matriz_pt Ac_Soma_ (Matriz_t       * const  me,
								 Matriz_t const * const  outro);

static  Matriz_pt Ac_Subt_ (Matriz_t       * const  me,
								 Matriz_t const * const  outro);

static  Matriz_pt Ac_Mult_ (Matriz_t       * const  me,
								 Matriz_t const * const  outro);

static  Matriz_pt Ac_Divd_ (Matriz_t       * const  me,
								 Matriz_t const * const  outro);

static Matriz_pt  Modulo_ (Matriz_t  * me);

static Matriz_pt Transpor_ (Matriz_t * me);

static Matriz_pt AcrescentaLinha (Matriz_t * me);

static Matriz_pt AcrescentaColuna (Matriz_t * me);

static Matriz_pt ReverseVertical (Matriz_t * me);

static Matriz_pt ReverseHorizontal (Matriz_t * me);

static Matriz_pt Identidade (Matriz_t * me, unsigned int * tam);

static Matriz_pt Ones (Matriz_t * me);

static Matriz_pt Transpor_Diag2 (Matriz_t * me);
 /*---------------------------------------------*
 * 		implementação do construtor             *
 * ---------------------------------------------*/
Matriz_pt Matriz_2D_criar (Matriz_pt  me,unsigned int* tam,double *valores)
{
	                                

    static struct NumeroVtbl const vtbl = {
        &copia_,   //
        &atribui_, //
        &soma_,    // 
        &subt_,    //
        &mult_,    //
        &divd_,    //
        &ac_soma_, //
        &ac_subt_, //
        &ac_mult_, //
        &ac_divd_, //
        &compara_, //
        &imprime_, //
        &destroi_  //
     };

        me = (Matriz_pt) Num_constroi ((Numero_pt) me);
                        	/*constroi o Numero_t  */
                        /* no início de Matriz_t  */

        me->super.metodo = &vtbl;
            
		
    static struct Matriz_Interface_st const interface = {
        &Copia_,    
        &Atribui_,  
        &Soma_,     
        &Subt_,     
        &Mult_,     
        &Divd_,		
		&Ac_Soma_,	
		&Ac_Subt_,	
		&Ac_Mult_,  
		&Ac_Divd_,   
        &Imprime_,  
        &Destroi_,  
        &Get_,      
        &Set_,      
		&GetValores_,
		&GetTam_,     
		&Modulo_,
		&Transpor_,
		&AcrescentaLinha,
		&AcrescentaColuna,
		&ReverseVertical,
		&ReverseHorizontal,
		&Identidade,
		&Ones,
		&Transpor_Diag2,
		&MultPorEscalar,
		&Resize
    };

    me->Metodo = &interface;
    me->tam = (unsigned int *)malloc(2*sizeof(unsigned int));
	me->tam[0] = (unsigned int)tam[0];
	me->tam[1] = (unsigned int)tam[1];
	
	int k =0;

	me->mat = (double**)malloc(me->mat,tam[0]*sizeof(double*));
	for (int i = 0; i < me->tam[0]; i++)
	{
		me->mat[i] = (double*)malloc(me->mat,tam[1]*sizeof(double));
		for (int j = 0; j < me->tam[1]; j++)
		{
			me->mat[i][j] = valores[k];
			k++;
		}
		
	}
     

     return (me);

}

/*funções basicas de Get e Set*/

static inline double Get_ (Matriz_t  const * const me,static int *posicao);
{
	return me->mat[posicao[0]][posicao[1]];
}

static inline void Set_ (Matriz_t * const me,static int *posicao, double valor)
{
	me->mat[posicao[0],posicao[1]] = valor;
}

static inline unsigned int* GetTam_(Matriz_t * me){
	static unsigned int tam[2];

	tam[0] = me->tam[0];
	tam[1] = me->tam[1];

	return tam;
}

static inline double * GetValores_(Matriz_t * me){
	static double *valores;
	valores = malloc(me->tam[0]* me->tam[1] * sizeof(double));
	int k =0;
	for (int i = 0; i < me->tam[0]; i++)
	{
		for (int j = 0; j < me->tam[1]; j++)
		{
			valores[k] = me->mat[i][j];
			k++;
			
		}
		
	}
	return valores;
}

/*------------------------------------------------------*
 * IMPLEMENTAÇÃO DAS FUNÇÕES VIRTUAIS           *
 * -----------------------------------------------------*/


static inline Matriz_pt Copia_ (Matriz_t const * const  me)
{
	return ( (Matriz_pt)
	          copia_ ((Numero_t *) me));
}

static Numero_pt copia_ (Numero_t const * const  me)
{
	assert (me != NULL);
	Numero_pt outro = NULL;
	outro = (Numero_pt) Matriz_2D_criar ((Matriz_pt) outro, GetTam_(me),GetValores_(me));
	return outro;
}

/*-----------------------------------------------------------------*/
static inline Matriz_pt Atribui_(Matriz_t const * const me,
					  Matriz_t       * const  outro )
{
	return ( (Matriz_pt)
	          atribui_ ((Numero_t*) me,
								 (Numero_t*) outro));
}

static Numero_pt atribui_ (Numero_t const * const  me, Numero_t * const  outro)
{
	outro->tam[0] = me->tam[0];
	outro->tam[1] = me->tam[1];
	outro->mat = (double**)realloc(outro->mat,me->tam[0]*sizeof(double*));
	for (int i = 0; i < me->tam[0]; i++)
	{
		outro->mat[i] = (double*)realloc(outro->mat,me->tam[0]*sizeof(double));
		for (int j = 0; j < me->tam[1]; j++)
		{
			outro->mat[i][j] = me->mat[i][j];
		}
		
	}

	return (Numero_pt) outro;
}
/*-----------------------------------------------------------------*/
static inline Matriz_pt Soma_  ( Matriz_t const * const  me,
						   		 Matriz_t const * const  outro,
						  		 Matriz_t       * const  res)
{
	return ( (Matriz_pt)
	          soma_ ((Numero_t*) me,
					 (Numero_t*) outro,
					 (Numero_t*) res));
}

static  Numero_pt soma_  ( Numero_t const * const  me,
						   Numero_t const * const  outro,
						   Numero_t       * const  res)
{
	if(me->tam[0] != outro->tam[0] || me->tam[1] != outro->tam[1] || 
	   me->tam[0] != res->tam[0]   || me->tam[1] != res->tam[1]    )
	{
		printf("ERRO NA SOMA: AS MATRIZES PRECISAM TER O MESMO NUMERO DE LINHAS E COLUNAS\n");
		return(res);
	}
	for (int i = 0; i < me->tam[0]; i++)
	{
		for (int j = 0; j < me->tam[1]; j++)
		{
			Set_((Matriz_t *)res,[i,j],me->mat[i][j] + outro[i][j]);
		}
	}
}


/*-----------------------------------------------------------------*/
static inline
Matriz_pt Subt_  (      Matriz_t const * const  me,
						   Matriz_t const * const  outro,
						   Matriz_t       * const  res)
{
	return ( (Matriz_pt)
	          subt_ ((Numero_t*) me,
							  (Numero_t*) outro,
							  (Numero_t*) res));
}
static  Numero_pt subt_  (	Numero_t const * const  me,
								    Numero_t const * const  outro,
								    Numero_t       * const  res)
{	
	if(me->tam[0] != outro->tam[0] || me->tam[1] != outro->tam[1] || 
	   me->tam[0] != res->tam[0]   || me->tam[1] != res->tam[1]    )
	{
		printf("ERRO NA SOMA: AS MATRIZES PRECISAM TER O MESMO NUMERO DE LINHAS E COLUNAS\n");
		return(res);
	}
	for (int i = 0; i < me->tam[0]; i++)
	{
		for (int j = 0; j < me->tam[1]; j++)
		{
			Set_((Matriz_t *)res,[i,j],me->mat[i][j] - outro[i][j]);
		}
	}
}

/*-----------------------------------------------------------------*/
static inline
Matriz_pt Mult_  ( Matriz_t const * const  me,
						   Matriz_t const * const  outro,
						   Matriz_t       * const  res)
{
	return ( (Matriz_pt)
	          mult_ ((Numero_t*) me,
			         (Numero_t*) outro,
			         (Numero_t*) res));
}

static  Numero_pt mult_  ( Numero_t const * const  me,
						   Numero_t const * const  outro,
						   Numero_t       * const  res)
{
    if (me->tam[0] != outro->tam[1] || me->tam[0] != res->tam[0] || outro->tam[1] != res->tam[1])
	{
		printf("ERRO: MATRIZES NÂO COMPATIVEIS\n");
		return res;
	}
	for(int linha=0; linha < me->tam[0] ; linha++){
    	
		for(int coluna=0; coluna < M2C; coluna++){
      		
			int somapro=0;
      		
			for(int i=0; i<me->tam[0] ; i++) {

				somapro += Get_(me,[linha,i]) * Get_(outro,[i,coluna]);

			}
      		
			Set_((Matriz_t *)res,[linha,coluna],somapro);
    	}
	}

	
	return ( (Numero_pt) res);
}

/*-----------------------------------------------------------------*/
static inline
Matriz_pt Divd_  ( Matriz_t const * const  me,
						   Matriz_t const * const  outro,
						   Matriz_t       * const  res)
{
	return ( (Matriz_pt)
	          divd_ ((Numero_t*) me,
                     (Numero_t*) outro,
                     (Numero_t*) res));
}

static  Numero_pt divd_  (	Numero_t const * const  me,
								Numero_t const * const  outro,
								Numero_t       * const  res)
{
	Mult_((Matriz_t*)me,Transpor_((Matriz_t*)outro),(Matriz_t*) res);

	return ( (Numero_pt) res);
}
/*-----------------------------------------------------------------*/
static  Matriz_pt Ac_Soma_ (Matriz_t       * const  me,
								 Matriz_t const * const  outro)
{
	return((Matriz_pt)ac_soma_((Numero_t*)me ,(Numero_t*)outro));
}

static  Numero_pt ac_soma_ (Numero_t       * const  me,
									 Numero_t const * const  outro)
{
	return((Numero_pt)Soma_((Matriz_pt)me,
							(Matriz_pt)outro,
							(Matriz_pt)me));
}


/*-----------------------------------------------------------------*/
static  Matriz_pt Ac_Subt_ (Matriz_t       * const  me,
								 Matriz_t const * const  outro)
{
	return((Matriz_pt)ac_subt_((Numero_t*)me ,(Numero_t*)outro));
}

static  Numero_pt ac_subt_ (Numero_t       * const  me,
									 Numero_t const * const  outro)
{
	return((Numero_pt)Subt_((Matriz_pt)me,
							(Matriz_pt)outro,
							(Matriz_pt)me));
}

/*-----------------------------------------------------------------*/
static  Matriz_pt Ac_Mult_ (Matriz_t       * const  me,
								 Matriz_t const * const  outro)
{
	return((Matriz_pt)ac_mult_((Numero_t*)me ,(Numero_t*)outro));
}

static  Numero_pt ac_mult_ (Numero_t       * const  me,
									 Numero_t const * const  outro)
{
	return((Numero_pt)Mult_((Matriz_pt)me, (Matriz_pt)outro , (Matriz_pt)me));
}

/*-----------------------------------------------------------------*/
static  Matriz_pt Ac_Divd_ (Matriz_t       * const  me,
								 Matriz_t const * const  outro)
{
	return((Matriz_pt)ac_divd_((Numero_t*)me ,(Numero_t*)outro));
}

static  Numero_pt ac_divd_ (Numero_t       * const  me,
									 Numero_t const * const  outro)
{
	return((Numero_pt)Divd_((Matriz_pt)me,
							Transpor_((Matriz_pt)outro),
							(Matriz_pt)me));
}

/*-----------------------------------------------------------------*/
static inline char * Imprime_  ( Matriz_t const * const  me)
{
	static char * s[4] = "ok\n";
	imprime_((Numero_t *) me);
	return s;
}
static  char * imprime_  (Numero_t const * const  me)
{
	static char * r[4] = "ok\n";

	for (int i = 0; i < me->tam[0]; i++)
	{
		printf("|");
		for (int j = 0; j< me->tam[1]; j++)
		{
			printf("%.02lf ", me->mat[i][j]);
		}
		printf("|\n");
	}

	return r;
}

 /*-----------------------------------------------------------------*/
static inline
void Destroi_  ( Matriz_t  *   me)
{
	  destroi_ ((Numero_t *)  me);

}

static void destroi_ (Numero_t *  me)
{
	
	for (int i = 0; i < me->tam[0]; i++){

		for (int j = 0; j < me->tam[1]; j++){
	
			free(me->mat[i][j]);
		}
		free(me->mat[i]);
	}


	free(me->tam); 
}
 /*-----------------------------------------------------------------*/
/*Modulo (deixa a matriz com todos as posições > 0)*/
static Matriz_pt  Modulo_ (Matriz_t  * me)
{
   for ( int i = 0; i < me->tam[0]; i++)
   {
	   for (int j = 0; j < me->tam[1]; j++)
	   {
		   Set_(me,[i,j],fabs(Get_(me),[i,j]));
	   }
	   
   }
   return me;
}
// Transpôe a Matriz
static Matriz_pt Transpor_ (Matriz_t * me){
	unsigned int tamlinhas0 = me->tam[0];
	unsigned int tamcolunas0 = me->tam[1];

	if(tamcolunas0 != tamlinhas0){
		if (tamlinhas0 < tamcolunas0)
		{
			me->mat = (double**)realloc(me->mat,tamcolunas0*sizeof(double*));

			for ( j = 0; j < tamcolunas0; j++)
			{
				for ( i = 0; i < tamlinhas0; i++)
				{
					me->mat[j][i] = me->mat[i][j];
				}

			}
			

			for (int i = 0; i < tamlinhas0; i++)
			{
				me->mat[i] = (double *) realloc(me->mat[i],tamlinhas0*sizeof(double))
			}
		}
		else{
			for (int i = 0; i < tamlinhas0; i++)
			{
				me->mat[i] = (double *) realloc(me->mat[i],tamlinhas0*sizeof(double))
			}
			
			for ( j = 0; j < tamlinhas0; j++)
			{
				for ( i = 0; i < tamcolunas0; i++)
				{
					me->mat[j][i] = me->mat[i][j];
				}

			}

			me->mat = (double**)realloc(me->mat,colunas0*sizeof(double*));
		} 
	}

	me->tam[0] = tamcolunas0;
	me->tam[1] = tamlinhas0;

	return me;
}
//Multiplica por Escalar
static Matriz_pt MultPorEscalar (Matriz_t * me,int a){
	for (int i = 0; i < me->tam[0]; i++)
	{
		for (j = 0; j < me->tam[1]; j++)
		{
			Set_(me,[i,j],Get_(me,[i,j])* a);
		}
		
	}
	
}
//Resize matriz
static Matriz_pt Resize (Matriz_t * me, unsigned int * tam){

	me->mat = (double**)realloc(me->mat,tam[0]*sizeof(double*));

	for (int i = 0; i < tam[0]; i++)
	{
		me->mat[i] = (double *) realloc(me->mat[i],tam[1]*sizeof(double));
		for ( j = me->tam[1] - 1; j < tam[1]; j++)
		{
			me->mat[i][j] = 0.0;
		}
		
	}
	me->tam[0] = tam[0];
	me->tam[1] = tam[1];

	return me;
}
// Acrescenta Linha
static Matriz_pt AcrescentaLinha (Matriz_t * me){
	me->tam[0] = me->tam[0]+1;
	me->mat = (double**)realloc(me->mat,me->tam[0]*sizeof(double*));
	return me;
}
// Acrescenta Coluna
static Matriz_pt AcrescentaColuna (Matriz_t * me){
	me->tam[1] = me->tam[1] +1;

	for (int i = 0; i < me->tam[0]; i++)
	{
		me->mat[i] = (double*)realloc(me->mat[i],(me->tam[1])*sizeof(double));
		for ( j = me->tam[1] - 1; j < me->tam[1]; j++)
		{
			me->mat[i][j] = 0.0;
		}
		
	}

	return me;
}
// Reverse Vertical (Colunas)
static Matriz_pt ReverseVertical (Matriz_t * me){

	double linha[me->tam[1]];

	int k = 0;

	for (int i = 0; i < me->tam[0]; i++)
	{
		k = 0;
		for (int j = 0; j < me->tam[1]; j++)
		{
			linha[k] = me->mat[i][j];
			k++;
		}
		for (int l = me->tam[1]-1 ; l >= 0 ; l--)
		{
			for (int j = 0; j < me->tam[1]; j++)
			{
				me->mat[i][j] = linha[l]
			}
		}		
	}
	
	return me;
}
// Reverse Horizontal (Linhas)
static Matriz_pt ReverseHorizontal (Matriz_t * me){

	Matriz_pt temp;
	
	Matriz_2D_criar(temp,me->tam,GetValores_(me));


	for (int i = me->tam[0] -1; i >= 0; i--)
	{
		for (int j = me->tam[1]-1; j >= 0 ; j--)
		{
			for (int l = 0; l < me->tam[0]; l++)
			{
				for (int m = 0; m < me->tam[1]; m++)
				{
					
					me->mat[l][m] = temp->mat[i][j];

				}
			}
		}
	}


	Destroi_(temp);

	return me;
}
// Identidade
static Matriz_pt Identidade (Matriz_t * me, unsigned int * tam){
	if (tam[0] != tam[1])
	{
		printf("ERRO: MATRIZ DEVE SER QUADRADA!!\n");
		return me;
	}
	for (int i = 0; i < tam[0]; i++)
	{
		for (int j = 0; j < tam[1]; j++)
		{
			me->mat[i][j] = 0.0;

		}
		
		me->mat[1][1] = 1.0;
	}
	return me;
}
// Ones
static Matriz_pt Ones (Matriz_t * me){
	for (int i = 0; i < me->tam[1]; i++)
	{
		for (int j = 0; j < me->tam[0]; j++)
		{
			me->mat[i][j] = 1.0;
		}
		
	}
	return me;
}
//
static Matriz_pt Transpor_Diag2 (Matriz_t * me){
	return Transpor_(me);
}

static  int	compara_ 	(Numero_t const * const  me,
							 Numero_t const * const  outro)
{
	printf("ERRO FUNÇÂO NÂO UTILIZADA PARA MATRIZES\n");
	return 1;
}

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


static  int	Compara_ 	    (Matriz_t const * const  me,
							 Matriz_t const * const  outro);

static  char *      Imprime_  (Matriz_t const * const  me);

static  void        Destroi_ (Matriz_t  *   me);

static  Matriz_pt  Simplifica_ (Matriz_pt me);


static 	void     Get_ (Matriz_t  const * const me,
					 long int * valorNum,
					 long int * valorDen);

static 	void     Set_ (Matriz_t   * const me,
					 long int valorNum,
					 long int valorDen);


static  Matriz_pt  Modulo_ (Matriz_t   const * const me);

static  Matriz_pt Ac_Soma_ (Matriz_t       * const  me,
								 Matriz_t const * const  outro);

static  Matriz_pt Ac_Subt_ (Matriz_t       * const  me,
								 Matriz_t const * const  outro);

static  Matriz_pt Ac_Mult_ (Matriz_t       * const  me,
								 Matriz_t const * const  outro);

static  Matriz_pt Ac_Divd_ (Matriz_t       * const  me,
								 Matriz_t const * const  outro);

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
        &Copia_,     // ok
        &Atribui_,   //
        &Soma_,      //
        &Subt_,      //
        &Mult_,      //
        &Divd_,		 //
		&Ac_Soma_,	 //
		&Ac_Subt_,	 //
		&Ac_Mult_,   // 
		&Ac_Divd_,   //  
        &Compara_,   //
        &Imprime_,   //
        &Destroi_,   //
        &Get_,       // ok
        &Set_,       // ok
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
	long int mmc;
	long int num;
	long int den;
	long int x = 1;
	long int den1 = labs(GetDen_((Matriz_pt)me));
	long int den2 = labs(GetDen_((Matriz_pt)outro));

	
	if (den2 > den1){
		x = den2;
		
	} else {
		x = den1;
	}
		
	while (x > 1) {
		if (x % den2 == 0 && x % den1 == 0)
		break;
		x++;
	}
	

	mmc = x;
	den = mmc;

	num = (GetNum_((Matriz_pt)me)*mmc/GetDen_((Matriz_pt)me)) - 
			(GetNum_((Matriz_pt)outro)*mmc/(GetDen_((Matriz_pt)outro)));
	
	
	Set_((Matriz_pt)res,num,den);

	return (Numero_pt) Simplifica_((Matriz_pt)res);
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
    Set_((Matriz_pt)res,GetNum_((Matriz_pt)me) * GetNum_((Matriz_pt)outro),
							 GetDen_((Matriz_pt)me) * GetDen_((Matriz_pt)outro));

	
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
	Set_((Matriz_pt)res,GetNum_((Matriz_pt)me) * GetDen_((Matriz_pt)outro),
							 GetDen_((Matriz_pt)me) * GetNum_((Matriz_pt)outro));

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
	return((Numero_pt)Mult_((Matriz_pt)me,
							(Matriz_pt)outro,
							(Matriz_pt)me));
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
							(Matriz_pt)outro,
							(Matriz_pt)me));
}

/*-----------------------------------------------------------------*/
static inline
int Compara_  ( Matriz_t const * const  me,
				Matriz_t const * const  outro)
{
	return ( compara_ ((Numero_t*) me,
                       (Numero_t*) outro));
}

static  int	compara_ 	(Numero_t const * const  me,
                         Numero_t const * const  outro)
{
	//estabelecendo que os numeros devem ser comparados simplificados
	Numero_pt numero1 = (Numero_pt) Simplifica_((Matriz_pt)me);
    Numero_pt numero2 = (Numero_pt) Simplifica_((Matriz_pt)outro);

	numero1 = (Numero_pt)Modulo_((Matriz_pt)numero1);
	numero2 = (Numero_pt)Modulo_((Matriz_pt)numero2);

    double num1 = ((double) GetNum_((Matriz_pt) numero1)) / 
					((double) GetDen_((Matriz_pt) numero1));

	double num2 = ((double) GetNum_((Matriz_pt) numero2)) / 
					((double) GetDen_((Matriz_pt) numero2));

	if(num1>num2){
		return 1;
	}
	else if(num2>num1){
		return -1;
	}
	return 0;
}

/*-----------------------------------------------------------------*/
static inline
char * Imprime_  ( Matriz_t const * const  me)
{
	return ( imprime_ ((Numero_t*) me));
}
static  char * imprime_  (Numero_t const * const  me)
{
    static char buffer[50];
	buffer[0] = '\n';
    if(GetNum_((Matriz_pt) me)> 0){   
		sprintf(buffer, "%ld/%ld",GetNum_((Matriz_pt) me),GetDen_((Matriz_pt) me)) ;
	}
	else sprintf(buffer, "-%ld/%ld",GetNum_((Matriz_pt) me),GetDen_((Matriz_pt) me));
	
	return buffer;
}


 /*---------------------------------------------*
 * implementação do destrutor                   *
 * ---------------------------------------------*/
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
/*função adicional de Modulo (deixa a matriz com todos as posições > 0)*/
static Matriz_pt  Modulo_ (Matriz_t   const * const me)
{
   for ( int i = 0; i < me->tam[0]; i++)
   {
	   for (int j = 0; j < me->tam[1]; j++)
	   {
		   me->mat[i][j] = fabs(Get_(me),[i,j]);
	   }
	   
   }
   return me;
}

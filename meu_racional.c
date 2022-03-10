/**********************************************************************
* Baseado no código disponibilizado em
*  Application Note: "Object-Oriented Programming in C"
* https://www.state-machine.com/doc/AN_OOP_in_C.pdf
*
* Aqui se implementa o número do tipo "racional"
*
* numero.h definiu a interface do "número_t virtual"
* que é usada aqui
* ********************************************************************/
#include <float.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "meu_racional.h"


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

static  Numero_pt divd_  ( Numero_t const * const  me,
									Numero_t const * const  outro,
									Numero_t       * const  res);

static  int	compara_ 	(Numero_t const * const  me,
							 Numero_t const * const  outro);

static  char * imprime_  (Numero_t const * const  me);

static  void destroi_ (Numero_t   *   me);



/*---------------------------------------------------------------------*
 * IMPLEMENTAÇÃO DA INTERFACE PÚBLICA das funções virtuais de MeuDouble*
 * -------------------------------------------------------------------*/
static  MeuRacional_pt Copia_ (MeuRacional_t const * const  me);

static  MeuRacional_pt Atribui_ (MeuRacional_t const * const  me,
							     MeuRacional_t       * const  outro) ;

static  MeuRacional_pt Soma_  (MeuRacional_t const * const  me,
							   MeuRacional_t const * const  outro,
							   MeuRacional_t       * const  res);

static  MeuRacional_pt Subt_  (MeuRacional_t const * const  me,
							   MeuRacional_t const * const  outro,
							   MeuRacional_t       * const  res);

static  MeuRacional_pt Mult_  ( MeuRacional_t const * const  me,
								MeuRacional_t const * const  outro,
								MeuRacional_t       * const  res);

static  MeuRacional_pt Divd_  ( MeuRacional_t const * const  me,
								MeuRacional_t const * const  outro,
								MeuRacional_t       * const  res);


static  int	Compara_ 	    (MeuRacional_t const * const  me,
							 MeuRacional_t const * const  outro);

static  char *      Imprime_  (MeuRacional_t const * const  me);

static  void        Destroi_ (MeuRacional_t  *   me);

/* ------------------------------------------------------- *
 * funções que são típicas do numero complexo, mas não são *
 * funcoes da classe virtual básica número                 *
 * protótipos das funçoes get e set, por exemplo           *
 *---------------------------------------------------------*/
static 	void     Get_ (MeuRacional_t  const * const me,
					 double * valorReal,
					 double * valorImag);

static 	void     Set_ (MeuRacional_t   * const me,
					 double valorReal,
					 double valorImag);

static 	double   GetReal_ (MeuRacional_t  const * const me);

static 	void     SetReal_ (MeuRacional_t   * const me,
					     double valorReal);

static 	double   GetImag_ (MeuRacional_t  const * const me);

static 	void     SetImag_ (MeuRacional_t   * const me,
					       double valorImag);

static double  Modulo_ (MeuRacional_t   const * const me);


 /*---------------------------------------------*
 * implementação do construtor                  *
 * ---------------------------------------------*/
MeuRacional_pt Racional_constroi (MeuRacional_pt  me, double Num,double Den)
{
	/* tabela de funções virtuais da classe Numero_t *
	 * Esta tabela estática será compartilhada por todos os números *
	 * da classe MeuRacional_t                                        */

    static struct NumeroVtbl const vtbl = {
        &copia_,
        &atribui_,
        &soma_,
        &subt_,
        &mult_,
        &divd_,
        0,      //essas funções com 0 não exitem para numeros racionais
        0,      //por isso foram  excluidas
        0,
        0,
        &compara_,
        &imprime_,
        &destroi_
     };

         me = (MeuRacional_pt) Num_constroi ((Numero_pt) me);
                        /*constroi o Numero_t  */
                        /* no início de MeuRacional_t  */

         me->super.metodo = &vtbl;
            /* metodo aponta para vtbl de MeuRacional_t */
            /* as operações do "numero", a partir de agora,     */
            /* são as operações sobre long int                    */

     /* Agora, mais uma tabela estática a ser compartilhada pelos     *
      * "MeuRacional_t": a tabela de interface                          *
      * note que a estrutura Interface incorpora os métodos Get e Set */
     static struct MeuRacional_Interface_st const interface = {
        &Copia_,
        &Atribui_,
        &Soma_,
        &Subt_,
        &Mult_,
        &Divd_,
        &Compara_,
        &Imprime_,
        &Destroi_,
        &Get_,
        &Set_,
        &GetReal_,
        &SetReal_,
        &GetImag_,
        &SetImag_,   
        &Modulo_,
     };

     me->Metodo = &interface;
            /* metodo aponta para vtbl de MeuRacional_t */
            /* as operações do "numero", a partir de agora,     */
            /* são as operações sobre double                    */

    /* aloca dinamicamente uma area de memoria para um double  */
    /* e atribui o endereço de memória alocada para o ponteiro */
    /* valor que está dentro da estrutura MeuRacional_st         */
	me->valor = (double *) malloc (2*sizeof(double));
	if (me->valor == NULL)
	{	/*erro!!! não conseguiu alocar */
	    printf ("Erro na alocação de memória em Num_Constroi");
	    printf ("Nao alocou o valor double");
	    exit (1);
	}

	/* copia o double passado como parâmetro */
    /* no endereco de memoria recém alocado  */
     me->valor[0] = valorReal;
     me->valor[1] = valorImag;

     return (me);

	/* ------------------------------------------------------------
	 * quando implementarmos o "meu_float", valor apontará para float
     * quando implementarmos o racional,   valor apontará para
     * um vetor com dois "long int"
     * quando implementarmos o complexo,   valor apontará para
     * um vetor com dois "double"
     * quando implementarmos o quaternion, valor apontará para
     * um vetor com quatro "double"
     * Por isso, cada tipo específico de número terminará de implementar
     * o seu construtor....
     *---------------------------------------------------------------*/
}


 /*---------------------------------------------*
 * implementação do set e get                   *
 * ---------------------------------------------*/
 static inline
void Get_ (MeuRacional_t  const * const me,
			double               * ptReal,
	        double 				 * ptImag)

{
	 *ptReal = (me->valor[0]);
	 *ptImag = (me->valor[1]);

}


static inline
void Set_ (MeuRacional_t       * const me,
			double                valorReal,
	        double 				  valorImag)
{
	me->valor[0] = valorReal;
	me->valor[1] = valorImag;

}

static inline
double GetReal_ (MeuRacional_t  const * const me)
{
	 return ( (me->valor[0]));

}


static inline
void SetReal_ (MeuRacional_t     * const me,
			double                valorReal)
{
	me->valor[0] = valorReal;

}

static inline
double  GetImag_ (MeuRacional_t  const * const me)
{
	 return (me->valor[1]);
}


static inline
void SetImag_ (MeuRacional_t       * const me,
	           double 				  valorImag)
{
	me->valor[1] = valorImag;
}

static
MeuRacional_pt  (Conjugado_)  (MeuRacional_t   const * const me,
	                      MeuRacional_t         * const conj)
{
	conj->valor[0] =   me->valor[0];
	conj->valor[1] = - (me->valor[1]);
	return (conj);
}

static
double  Modulo_ (MeuRacional_t   const * const me)
{
   return( sqrt(GetReal_(me)*(GetReal_(me)) + (GetImag_(me)*(GetImag_(me))  )));
}

static
double Argumento_ (MeuRacional_t   const * const me)
{
    return (atan (GetImag_(me) / GetReal_(me) ));
}
/*------------------------------------------------------*
 * IMPLEMENTAÇÃO DAS FUNÇÕES VIRTUAIS           *
 * -----------------------------------------------------*/
static inline MeuRacional_pt Copia_ (MeuRacional_t const * const  me)
{
	return ( (MeuRacional_pt)
	          copia_ ((Numero_pt) me));
}

static Numero_pt copia_ (Numero_t const * const  me)
{
	assert (me != NULL);
	Numero_pt outro = NULL;
	outro = (Numero_pt) Complexo_constroi
							((MeuRacional_pt) outro,
							  GetReal_((MeuRacional_pt) me),
							  GetImag_((MeuRacional_pt) me));
	return outro;
}

/*-----------------------------------------------------------------*/
static inline
MeuRacional_pt Atribui_(MeuRacional_t const * const me,
					  MeuRacional_t       * const  outro )
{
	return ( (MeuRacional_pt)
	          atribui_ ((Numero_pt) me,
								 (Numero_pt) outro));
}

static
 Numero_pt atribui_ (Numero_t const * const  me,
						  Numero_t       * const  outro)
 {
	 Set_( (MeuRacional_pt) outro,
	       GetReal_((MeuRacional_pt) me),
	       GetImag_ ( (MeuRacional_pt) me) );

	 return (Numero_pt) outro;
 }
/*-----------------------------------------------------------------*/
static inline
MeuRacional_pt Soma_  ( MeuRacional_t const * const  me,
						   MeuRacional_t const * const  outro,
						   MeuRacional_t       * const  res)
{
	return ( (MeuRacional_pt)
	          soma_ ((Numero_pt) me,
					 (Numero_pt) outro,
					 (Numero_pt) res));
}

static  Numero_pt soma_  ( Numero_t const * const  me,
								Numero_t const * const  outro,
								Numero_t       * const  res)
{
	Set_((MeuRacional_pt) res,
				GetReal_((MeuRacional_pt) me) +
				GetReal_((MeuRacional_pt) outro),
				GetImag_((MeuRacional_pt) me) +
				GetImag_((MeuRacional_pt) outro) );

	return (Numero_pt) res;
}


/*-----------------------------------------------------------------*/
static inline
MeuRacional_pt Subt_  (      MeuRacional_t const * const  me,
						   MeuRacional_t const * const  outro,
						   MeuRacional_t       * const  res)
{
	return ( (MeuRacional_pt)
	          subt_ ((Numero_pt) me,
							  (Numero_pt) outro,
							  (Numero_pt) res));
}
static  Numero_pt subt_  (	Numero_t const * const  me,
								    Numero_t const * const  outro,
								    Numero_t       * const  res)
{
		Set_((MeuRacional_pt) res,
				GetReal_((MeuRacional_pt) me) -
				GetReal_((MeuRacional_pt) outro),
				GetImag_((MeuRacional_pt) me) -
				GetImag_((MeuRacional_pt) outro) );
		return (Numero_pt) res;
}

/*-----------------------------------------------------------------*/
static inline
MeuRacional_pt Mult_  ( MeuRacional_t const * const  me,
						   MeuRacional_t const * const  outro,
						   MeuRacional_t       * const  res)
{
	return ( (MeuRacional_pt)
	          mult_ ((Numero_pt) me,
									  (Numero_pt) outro,
									  (Numero_pt) res));
}

static  Numero_pt mult_  ( Numero_t const * const  me,
								Numero_t const * const  outro,
								Numero_t       * const  res)
{
     MeuRacional_pt  temp = NULL;
     temp = Complexo_constroi(temp, 0.0,0.0);

	 SetReal_(temp,
				(GetReal_((MeuRacional_pt) me) *
				 GetReal_((MeuRacional_pt) outro) ) -
				(GetImag_((MeuRacional_pt) me) *
				 GetImag_((MeuRacional_pt) outro) )  );

	 SetImag_ (temp,
				(GetReal_((MeuRacional_pt) me) *
				 GetImag_((MeuRacional_pt) outro) ) +
				(GetImag_((MeuRacional_pt) me) *
				 GetReal_((MeuRacional_pt) outro) ) );

     SetReal_ ((MeuRacional_pt)res, GetReal_(temp));
     SetImag_ ((MeuRacional_pt)res, GetImag_(temp));
	 Destroi_(temp);

	 return ( (Numero_pt) res);
}

/*-----------------------------------------------------------------*/
static inline
MeuRacional_pt Divd_  ( MeuRacional_t const * const  me,
						   MeuRacional_t const * const  outro,
						   MeuRacional_t       * const  res)
{
	return ( (MeuRacional_pt)
	          divd_ ((Numero_pt) me,
                     (Numero_pt) outro,
                     (Numero_pt) res));
}

static  Numero_pt divd_  (	Numero_t const * const  me,
								Numero_t const * const  outro,
								Numero_t       * const  res)
{
	double quociente;
	quociente = GetReal_((MeuRacional_pt) outro) *
	            GetReal_((MeuRacional_pt) outro)    +
	            GetImag_((MeuRacional_pt) outro) *
	            GetImag_((MeuRacional_pt) outro) ;

	MeuRacional_pt  temp = NULL;
	temp = Complexo_constroi(temp, 0.0,0.0);

	 SetReal_(temp,
				((GetReal_((MeuRacional_pt) me) *
				 GetReal_((MeuRacional_pt) outro) ) -
				(GetImag_((MeuRacional_pt) me) *
				 GetImag_((MeuRacional_pt) outro) ) )/quociente );

	 SetImag_ (temp,
               ((GetReal_((MeuRacional_pt) me) *
				 GetImag_((MeuRacional_pt) outro) ) +
				(GetImag_((MeuRacional_pt) me) *
				 GetReal_((MeuRacional_pt) outro) ) )/quociente );

     SetReal_ ((MeuRacional_pt)res, GetReal_(temp));
     SetImag_ ((MeuRacional_pt)res, GetImag_(temp));	 Destroi_(temp);
	 return ( (Numero_pt) res);
}

/*-----------------------------------------------------------------*/


static  Numero_pt ac_soma_  (Numero_t       * const  me,
                             Numero_t const * const  outro)
{
	
}

/*-----------------------------------------------------------------*/


static  Numero_pt ac_subt_  (Numero_t       * const  me,
								  Numero_t const * const  outro)
{
	;
}

/*-----------------------------------------------------------------*/


static  Numero_pt ac_mult_  (Numero_t       * const  me,
                             Numero_t const * const  outro)
{
	
}

/*-----------------------------------------------------------------*/


static  Numero_pt ac_divd_  (Numero_t       * const  me,
								  Numero_t const * const  outro)
{

}

/*-----------------------------------------------------------------*/
static inline
int Compara_  ( MeuRacional_t const * const  me,
				MeuRacional_t const * const  outro)
{
	return ( compara_ ((Numero_pt) me,
                       (Numero_pt) outro));
}

static  int	compara_ 	(Numero_t const * const  me,
                         Numero_t const * const  outro)
{
   double diff_real, diff_imag;
   diff_real = abs(GetReal_((MeuRacional_pt)me) - GetReal_((MeuRacional_pt)outro));
   diff_imag = abs(GetImag_((MeuRacional_pt)me) - GetImag_((MeuRacional_pt)outro));

    if (   (    diff_real < (DBL_TRUE_MIN * 256.0))
        && (    diff_imag < (DBL_TRUE_MIN * 256.0)))
    {return (0);}

	if( Modulo_((MeuRacional_pt)me) > Modulo_((MeuRacional_pt)outro) )
	{ return (1);}
	else if( Modulo_((MeuRacional_pt)me) < Modulo_((MeuRacional_pt)outro) )
	{  return (-1);};

	return(0);
}

/*-----------------------------------------------------------------*/
static inline
char * Imprime_  ( MeuRacional_t const * const  me)
{
	return ( imprime_ ((Numero_pt) me));
}
static  char * imprime_  (Numero_t const * const  me)
{
    static char buffer[50];
    if (GetImag_((MeuRacional_pt) me) > 0.0)
	{   sprintf(buffer, "%f + %f i",GetReal_((MeuRacional_pt) me),fabs(GetImag_((MeuRacional_pt) me)) );
	}
	else
	{   sprintf(buffer, "%f - %f i",GetReal_((MeuRacional_pt) me),fabs(GetImag_((MeuRacional_pt) me)) );
	}
	return buffer;
}


 /*---------------------------------------------*
 * implementação do destrutor                   *
 * ---------------------------------------------*/
 /*-----------------------------------------------------------------*/
static inline
void Destroi_  ( MeuRacional_t  *   me)
{
	  destroi_ ((Numero_t *)  me);
}
static void destroi_ (Numero_t *  me)
{
	/* primeiro destroi o valor double */
	free (((MeuRacional_pt) me)->valor);
	/*... e só agora destroi-se o número virtual da classe base */
	free ((Numero_t *) me);
}

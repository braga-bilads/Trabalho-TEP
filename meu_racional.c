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
 * IMPLEMENTAÇÃO DA INTERFACE PÚBLICA das funções virtuais de MeuRacional*
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
 * funções que são típicas do numero Racional, mas não são *
 * funcoes da classe virtual básica número                 *
 * protótipos das funçoes get e set, por exemplo           *
 *---------------------------------------------------------*/
static 	void     Get_ (MeuRacional_t  const * const me,
					 long int * valorNum,
					 long int * valorDen);

static 	void     Set_ (MeuRacional_t   * const me,
					 long int valorNum,
					 long int valorDen);

static 	long int   GetNum_ (MeuRacional_t  const * const me);

static 	void     SetNum_ (MeuRacional_t   * const me,
					      long int valorNum);

static 	long int   GetDen_ (MeuRacional_t  const * const me);

static 	void     SetDen_ (MeuRacional_t   * const me,
					       long int valorDen);

static  MeuRacional_pt  Modulo_ (MeuRacional_t   const * const me);

static  MeuRacional_pt Ac_Soma_ (MeuRacional_t       * const  me,
								 MeuRacional_t const * const  outro);

static  MeuRacional_pt Ac_Subt_ (MeuRacional_t       * const  me,
								 MeuRacional_t const * const  outro);

static  MeuRacional_pt Ac_Mult_ (MeuRacional_t       * const  me,
								 MeuRacional_t const * const  outro);

static  MeuRacional_pt Ac_Divd_ (MeuRacional_t       * const  me,
								 MeuRacional_t const * const  outro);

 /*---------------------------------------------*
 * implementação do construtor                  *
 * ---------------------------------------------*/
MeuRacional_pt Racional_constroi (MeuRacional_pt  me, long int valorNum,long int valorDen)
{
	/* tabela de funções virtuais da classe Numero_t *
	 * Esta tabela estática será compartilhada por todos os números *
	 * da classe MeuRacional_t                                        */

    static struct NumeroVtbl const vtbl = {
        &copia_,   //ok
        &atribui_, //ok
        &soma_,    //ok  
        &subt_,    //ok
        &mult_,    //
        &divd_,    //
        &ac_soma_, //
        &ac_subt_, //
        &ac_mult_, //
        &ac_divd_, //
        &compara_, //ok
        &imprime_, //ok
        &destroi_  //ok
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
        &Copia_,     // parece ok
        &Atribui_,   // parece ok
        &Soma_,      // implementada
        &Subt_,      // implementada
        &Mult_,      // implementada
        &Divd_,		 // implementada
		&Ac_Soma_,	 //
		&Ac_Subt_,	 //
		&Ac_Mult_,   //
		&Ac_Divd_,   //  
        &Compara_,   // implementada
        &Imprime_,   // parece ok
        &Destroi_,   // parece ok
        &Get_,       // parece ok
        &Set_,       // parece ok
        &GetNum_,    // parece ok
        &SetNum_,    // parece ok
        &GetDen_,    // parece ok
        &SetDen_,    // parece ok
        &Modulo_,    // parece ok
		&Simplifica_ // implementada
     };

     me->Metodo = &interface;
            /* metodo aponta para vtbl de MeuRacional_t */
            /* as operações do "numero", a partir de agora,     */
            /* são as operações sobre long int                    */

    /* aloca dinamicamente uma area de memoria para um long int  */
    /* e atribui o endereço de memória alocada para o ponteiro */
    /* valor que está dentro da estrutura MeuRacional_st         */
	me->valor = (long int*) malloc (2*sizeof(long int));

	if (me->valor == NULL)
	{	/*erro!!! não conseguiu alocar */
	    printf ("Erro na alocação de memória em Num_Constroi");
	    printf ("Nao alocou o valor long int");
	    exit (1);
	}

	/* copia o long int passado como parâmetro */
    /* no endereco de memoria recém alocado  */
     me->valor[0] = valorNum;
     me->valor[1] = valorDen;

     return (me);

}


 /*---------------------------------------------*
 * implementação do set e get                   *
 * ---------------------------------------------*/
 static inline
void Get_ (MeuRacional_t  const * const me, long int * ptNum,long int * ptDen)

{
	 *ptNum = (me->valor[0]);
	 *ptDen = (me->valor[1]);

}


static inline void Set_ (MeuRacional_t * const me,long int valorNum, long int valorDen)
{
	me->valor[0] = valorNum;
	me->valor[1] = valorDen;

}

static inline long int GetNum_ (MeuRacional_t  const * const me)
{
	 return ( (me->valor[0]));

}


static inline void SetNum_ (MeuRacional_t * const me,long int valorNum)
{
	me->valor[0] = valorNum;
}


static inline long int  GetDen_ (MeuRacional_t  const * const me)
{
	 return (me->valor[1]);
}


static inline void SetDen_ (MeuRacional_t * const me,long int valorDen)
{
	me->valor[1] = valorDen;
}


static MeuRacional_pt  Modulo_ (MeuRacional_t   const * const me)
{
   MeuRacional_pt resposta = Racional_constroi(resposta,labs(GetNum_(me)),labs(GetDen_(me)));
   return(resposta);
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
	outro = (Numero_pt) Racional_constroi
							((MeuRacional_pt) outro,
							  GetNum_((MeuRacional_pt) me),
							  GetDen_((MeuRacional_pt) me));
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
	       GetNum_((MeuRacional_pt) me),
	       GetDen_ ( (MeuRacional_pt) me) );

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
	long int den;
	long int num;
	long int mc;

	mc = GetDen_((MeuRacional_pt)me) * GetDen_((MeuRacional_pt)outro);
	den = mc;
	num = (GetNum_((MeuRacional_pt)me)*(GetDen_((MeuRacional_pt)me)/mc)) + 
		  (GetNum_((MeuRacional_pt)outro)*(GetDen_((MeuRacional_pt)outro)/mc));

	Set_((MeuRacional_pt)res, num, den);

	res = (Numero_pt)Simplifica_((MeuRacional_pt)res);

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
	long int mc;
	long int num;
	long int den;
	mc = GetDen_((MeuRacional_pt)me) * GetDen_((MeuRacional_pt)outro);
	num = (GetNum_((MeuRacional_pt)me)*(GetDen_((MeuRacional_pt)me)/mc)) - 
		  (GetNum_((MeuRacional_pt)outro)*(GetDen_((MeuRacional_pt)outro)/mc));

	den = mc;

	Set_((MeuRacional_pt)res, num, den);

	res = (Numero_pt)Simplifica_((MeuRacional_pt)res);

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
    Set_((MeuRacional_pt)res,GetNum_((MeuRacional_pt)me) * GetNum_((MeuRacional_pt)outro),
							 GetDen_((MeuRacional_pt)me) * GetDen_((MeuRacional_pt)outro));


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
	Set_((MeuRacional_pt)res,GetNum_((MeuRacional_pt)me) * GetDen_((MeuRacional_pt)outro),
							 GetDen_((MeuRacional_pt)me) * GetNum_((MeuRacional_pt)outro));

	return ( (Numero_pt) res);
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
	//estabelecendo que os numeros devem ser comparados simplificados
	Numero_pt numero1 = (Numero_pt) Simplifica_((MeuRacional_pt)me);
    Numero_pt numero2 = (Numero_pt) Simplifica_((MeuRacional_pt)outro);

    if(GetNum_((MeuRacional_pt)numero1) == GetNum_((MeuRacional_pt)numero2)){
		if (GetDen_((MeuRacional_pt)numero1) == GetDen_((MeuRacional_pt)numero2)){
			return 1 ;                  //1 vai valer como se eles fossem iguais
		}
		else return 0;
	}
	else{
		return 0;                       //0 vai valer como se fossem diferentes
	}
}

/*-----------------------------------------------------------------*/
static inline
char * Imprime_  ( MeuRacional_t const * const  me)
{
	return ( imprime_ ((Numero_pt) me));
}
static  char * imprime_  (Numero_t const * const  me)
{
    char buffer[50];
	buffer[0] = '\n';
    if (GetDen_((MeuRacional_pt) me) > 0.0)
	{   
		sprintf(buffer, "%f + %f i",GetNum_((MeuRacional_pt) me),GetDen_((MeuRacional_pt) me)) ;
	}
	else
	{   
		sprintf(buffer, "%f - %f i",GetNum_((MeuRacional_pt) me),GetDen_((MeuRacional_pt) me)) ;
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
	/* primeiro destroi o valor long int */
	free (((MeuRacional_pt) me)->valor);
	/*... e só agora destroi-se o número virtual da classe base */
	free ((Numero_t *) me);
}
 /*-----------------------------------------------------------------*/
static inline MeuRacional_pt  Simplifica_ (MeuRacional_pt me){
	long int den = labs(GetDen_(me));
	long int num = labs(GetNum_(me));
	int condi = 1;
	long int mod = 1;
	
	int num1, num2, GCD;
    printf("Enter the value for num1 /num2:");
    
    if (num < den){
      	x = num;
    } else {
      	x = den;
    }
    
    while (x > 1) {
        if (num % x == 0 && den % x == 0)
          break;
        x--;
    }
    
	den = den/GCD;
	num = num/GDC;

	if(GetNum_(me)>=0) MeuRacional_pt resposta = Racional_constroi(resposta,num,den);
	else MeuRacional_pt resposta = Racional_constroi(resposta,-num,den);

   	return resposta;
}



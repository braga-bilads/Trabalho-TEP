
/* Comentario de Gabriel Braga Ladislau: Ola professor Saulo, nesse trabalho eu implementei a função de simplificação
   achei mais conveniente usa-la nas funções de Soma e Subtração para ter um resultado exato da soma, ela não é usada
   todavia em funções de Divisão e Multiplicação por minha escolha simplesmente, espero que goste do meu trabalho!*/

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

static  MeuRacional_pt  Simplifica_ (MeuRacional_pt me);

/* ------------------------------------------------------- *
 * funções que são típicas do numero Racional, mas não são *
 * funcoes da classe virtual básica número                 *
 * protótipos das funçoes get e set, por exemplo           *
 *---------------------------------------------------------*/
static 	void     Get_ (MeuRacional_t  const * const me, long int * valorNum, long int * valorDen);

static 	void     Set_ (MeuRacional_t   * const me, long int valorNum, long int valorDen);

static 	long int   GetNum_ (MeuRacional_t  const * const me);

static 	void     SetNum_ (MeuRacional_t   * const me, long int valorNum);

static 	long int   GetDen_ (MeuRacional_t  const * const me);

static 	void     SetDen_ (MeuRacional_t   * const me, long int valorDen);

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
	me = (MeuRacional_pt) malloc(sizeof(MeuRacional_t));
    static struct NumeroVtbl const vtbl = {
        &copia_,   //ok
        &atribui_, //ok
        &soma_,    //ok  
        &subt_,    //ok
        &mult_,    //ok
        &divd_,    //ok
        &ac_soma_, //ok
        &ac_subt_, //ok
        &ac_mult_, //ok
        &ac_divd_, //ok
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
		&Ac_Soma_,	 // implementada
		&Ac_Subt_,	 // implementada
		&Ac_Mult_,   // implementada 
		&Ac_Divd_,   // implementada  
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
static inline void Get_ (MeuRacional_t  const * const me, long int * ptNum,long int * ptDen)
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
   MeuRacional_pt resposta = NULL;
   resposta = Racional_constroi(resposta,labs(GetNum_(me)),labs(GetDen_(me)));
   return(resposta);
}


/*------------------------------------------------------*
 * IMPLEMENTAÇÃO DAS FUNÇÕES VIRTUAIS           *
 * -----------------------------------------------------*/
static inline MeuRacional_pt Copia_ (MeuRacional_t const * const  me)
{
	return ( (MeuRacional_pt)
	          copia_ ((Numero_t *) me));
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
	          atribui_ ((Numero_t*) me,
								 (Numero_t*) outro));
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
	          soma_ ((Numero_t*) me,
					 (Numero_t*) outro,
					 (Numero_t*) res));
}

static  Numero_pt soma_  ( Numero_t const * const  me,
						   Numero_t const * const  outro,
						   Numero_t       * const  res)
{
	long int den=1;
	long int num=1;
	long int mmc=1;
	long int x = 1;
	long int den1 = labs(GetDen_((MeuRacional_pt)me));
	long int den2 = labs(GetDen_((MeuRacional_pt)outro));

	
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
	
	
	x = den1;
	
	mmc = x;
	den = mmc;
	num = (GetNum_((MeuRacional_pt)me)*mmc/GetDen_((MeuRacional_pt)me)) + 
			(GetNum_((MeuRacional_pt)outro)*mmc/(GetDen_((MeuRacional_pt)outro)));
	
	Set_((MeuRacional_pt)res,num,den);

	return (Numero_pt)res;
}


/*-----------------------------------------------------------------*/
static inline
MeuRacional_pt Subt_  (      MeuRacional_t const * const  me,
						   MeuRacional_t const * const  outro,
						   MeuRacional_t       * const  res)
{
	return ( (MeuRacional_pt)
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
	long int den1 = labs(GetDen_((MeuRacional_pt)me));
	long int den2 = labs(GetDen_((MeuRacional_pt)outro));

	
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

	num = (GetNum_((MeuRacional_pt)me)*mmc/GetDen_((MeuRacional_pt)me)) - 
			(GetNum_((MeuRacional_pt)outro)*mmc/(GetDen_((MeuRacional_pt)outro)));
	
	
	Set_((MeuRacional_pt)res,num,den);

	return (Numero_pt)res;
}

/*-----------------------------------------------------------------*/
static inline
MeuRacional_pt Mult_  ( MeuRacional_t const * const  me,
						   MeuRacional_t const * const  outro,
						   MeuRacional_t       * const  res)
{
	return ( (MeuRacional_pt)
	          mult_ ((Numero_t*) me,
			         (Numero_t*) outro,
			         (Numero_t*) res));
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
	          divd_ ((Numero_t*) me,
                     (Numero_t*) outro,
                     (Numero_t*) res));
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
static  MeuRacional_pt Ac_Soma_ (MeuRacional_t       * const  me,
								 MeuRacional_t const * const  outro)
{
	return((MeuRacional_pt)ac_soma_((Numero_t*)me ,(Numero_t*)outro));
}

static  Numero_pt ac_soma_ (Numero_t       * const  me,
									 Numero_t const * const  outro)
{
	return((Numero_pt)Soma_((MeuRacional_pt)me,
							(MeuRacional_pt)outro,
							(MeuRacional_pt)me));
}


/*-----------------------------------------------------------------*/
static  MeuRacional_pt Ac_Subt_ (MeuRacional_t       * const  me,
								 MeuRacional_t const * const  outro)
{
	return((MeuRacional_pt)ac_subt_((Numero_t*)me ,(Numero_t*)outro));
}

static  Numero_pt ac_subt_ (Numero_t       * const  me,
									 Numero_t const * const  outro)
{
	return((Numero_pt)Subt_((MeuRacional_pt)me,
							(MeuRacional_pt)outro,
							(MeuRacional_pt)me));
}

/*-----------------------------------------------------------------*/
static  MeuRacional_pt Ac_Mult_ (MeuRacional_t       * const  me,
								 MeuRacional_t const * const  outro)
{
	return((MeuRacional_pt)ac_mult_((Numero_t*)me ,(Numero_t*)outro));
}

static  Numero_pt ac_mult_ (Numero_t       * const  me,
									 Numero_t const * const  outro)
{
	return((Numero_pt)Mult_((MeuRacional_pt)me,
							(MeuRacional_pt)outro,
							(MeuRacional_pt)me));
}

/*-----------------------------------------------------------------*/
static  MeuRacional_pt Ac_Divd_ (MeuRacional_t       * const  me,
								 MeuRacional_t const * const  outro)
{
	return((MeuRacional_pt)ac_divd_((Numero_t*)me ,(Numero_t*)outro));
}

static  Numero_pt ac_divd_ (Numero_t       * const  me,
									 Numero_t const * const  outro)
{
	return((Numero_pt)Divd_((MeuRacional_pt)me,
							(MeuRacional_pt)outro,
							(MeuRacional_pt)me));
}

/*-----------------------------------------------------------------*/
static inline
int Compara_  ( MeuRacional_t const * const  me,
				MeuRacional_t const * const  outro)
{
	return ( compara_ ((Numero_t*) me,
                       (Numero_t*) outro));
}

static  int	compara_ 	(Numero_t const * const  me,
                         Numero_t const * const  outro)
{
	//estabelecendo que os numeros devem ser comparados simplificados
	Numero_pt numero1 = (Numero_pt) Simplifica_((MeuRacional_pt)me);
    Numero_pt numero2 = (Numero_pt) Simplifica_((MeuRacional_pt)outro);

	numero1 = (Numero_pt)Modulo_((MeuRacional_pt)numero1);
	numero2 = (Numero_pt)Modulo_((MeuRacional_pt)numero2);

    double num1 = ((double) GetNum_((MeuRacional_pt) numero1)) / 
					((double) GetDen_((MeuRacional_pt) numero1));

	double num2 = ((double) GetNum_((MeuRacional_pt) numero2)) / 
					((double) GetDen_((MeuRacional_pt) numero2));

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
char * Imprime_  ( MeuRacional_t const * const  me)
{
	return ( imprime_ ((Numero_t*) me));
}
static  char * imprime_  (Numero_t const * const  me)
{
    static char buffer[50];
	buffer[0] = '\n';
    if(GetNum_((MeuRacional_pt) me)> 0){   
		sprintf(buffer, "%ld/%ld",GetNum_((MeuRacional_pt) me),GetDen_((MeuRacional_pt) me)) ;
	}
	else sprintf(buffer, "-%ld/%ld",GetNum_((MeuRacional_pt) me),GetDen_((MeuRacional_pt) me));
	
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
	long int n = GetNum_(me);

	long int  x=1;
    if(num!=1 && den!=1 && num!=0 &&den!=0){
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
	
    
		den = den/x;
		num = num/x;
	}
	static MeuRacional_pt resposta;
	
	
	if(n < 0) {
		num = -num;
		resposta = Racional_constroi(resposta,num,den);
		return resposta;
	}
	resposta = Racional_constroi(resposta,num,den);
	return resposta;
}



/**********************************************************************
* Baseado no código disponibilizado em
*  Application Note: "Object-Oriented Programming in C"
* https://www.state-machine.com/doc/AN_OOP_in_C.pdf
*
* Aqui se apresenta a interface do número do tipo "complexo"
*
* numero.h definiu a interface do "número_t virtual"
* ********************************************************************/

#ifndef MEURACIONAL_H
#define MEURACIONAL_H

#include "numero.h" /*a interface da classe básica */

struct MeuRacional_Interface_st;

 struct MeuRacional_st {
    struct Numero_st super;
                     /* <== herda a "super-classe Numeros",
                      * isto é, a classe superior a MeuDouble na
                      * hierarquia dos números
                      * Com isso, herda as operações da
                      * tabela de métodos comuns a todos os Numeros
                      * assim como os atributos desta classe base,
                      * (caso houvessem)       */

    struct MeuRacional_Interface_st const *  Metodo;
                      /* o ponteiro para a tabela de
                       * ponteiros para funções
                       * que são apenas as chamadas para os métodos
                       * da super-classe, porém fazendo as
                       * devidas conversões na "entrada" e na
                       * saída               */

    /* o atributo  desta classe é o ponteiro para dois long ints */
    long int *valor;
}  ;
/* ----------------------------------------------------------*
 * declaro o ponteiro para o número do tipo MeuRacional_t      *
 * que não estão "dentro" da tabela de funções virtuais      *
 * ----------------------------------------------------------*/
typedef struct MeuRacional_st *MeuRacional_pt;
typedef struct MeuRacional_st  MeuRacional_t;



struct MeuRacional_Interface_st {
    
	MeuRacional_pt (*copia)	(MeuRacional_t const * const me);

    MeuRacional_pt (*atribui)	(MeuRacional_t const * const  me,
							 MeuRacional_t       * const  outro);

    MeuRacional_pt (*soma)	(MeuRacional_t const * const  me,
							 MeuRacional_t const * const  outro,
							 MeuRacional_t       * const res);

    MeuRacional_pt (*subt)	(MeuRacional_t const * const  me,
							 MeuRacional_t const * const  outro,
							 MeuRacional_t       * const res);

    MeuRacional_pt (*mult)	(MeuRacional_t const * const  me,
							 MeuRacional_t const * const  outro,
							MeuRacional_t        * const res);

    MeuRacional_pt (*divd)	(MeuRacional_t const * const  me,
							 MeuRacional_t const * const  outro,
							 MeuRacional_t       * const res);


    int			(*compara)	(MeuRacional_t const * const  me,
							 MeuRacional_t const * const  outro);

    char *      (*imprime)  (MeuRacional_t const * const  me);

    void        (*destroi)  (MeuRacional_t       *        me);
    /*------------------------------------------------------*/
    void       (*get     ) (MeuRacional_t  const * const me,
							double               * ptNum,
	                        double 				 * ptDen);

	void   	   (*set     ) (MeuRacional_t        * const me,
	                          double             valorNum,
	                          double 		     valorDen);

	double       (*getNum ) (MeuRacional_t  const * const me);

	void   	   (*setNum ) (MeuRacional_t        * const me,
	                          double             valorNum);


	double       (*getDen ) (MeuRacional_t  const * const me);

	void   	   (*setDen ) (MeuRacional_t        * const me,
	                          double             valorNum);


    double  (*modulo) (MeuRacional_t   const * const me);

    MeuRacional_pt  (*simplifica) (MeuRacional_pt me);
    /*------------------------------------------------------*/
};

typedef struct MeuRacional_Interface_st *MeuRacional_Interface_pt;


/* protótipo do construtor   */
MeuRacional_pt Racional_constroi (MeuRacional_pt  me,
								  long int valorNum,
								  long int valorDen);



#endif /* MeuRacional_H */

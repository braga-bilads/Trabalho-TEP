#ifndef Matriz_H
#define Matriz_H

#include "numero.h" 

struct Matriz_Interface_st;

struct Matriz_st {

    struct Numero_st super;

    struct Matriz_Interface_st const *  Metodo;

	unsigned int *tam;

	double ** mat;
    
};


typedef struct Matriz_st *Matriz_pt;
typedef struct Matriz_st  Matriz_t;



struct Matriz_Interface_st {
    
	Matriz_pt (*copia)	(Matriz_t const * const me);

    Matriz_pt (*atribui)	(Matriz_t const * const  me,
							 Matriz_t       * const  outro);

    Matriz_pt (*soma)	(Matriz_t const * const  me,
						 Matriz_t const * const  outro,
						 Matriz_t       * const res);

    Matriz_pt (*subt)	(Matriz_t const * const  me,
						 Matriz_t const * const  outro,
						 Matriz_t       * const res);

    Matriz_pt (*mult)	(Matriz_t const * const  me,
						 Matriz_t const * const  outro,
						 Matriz_t        * const res);

    Matriz_pt (*divd)	(Matriz_t const * const  me,
						 Matriz_t const * const  outro,
						 Matriz_t       * const res);

    Matriz_pt (*ac_soma)	(Matriz_t       * const  me,
							 Matriz_t const * const  outro);

    Matriz_pt (*ac_subt)	(Matriz_t       * const  me,
							 Matriz_t const * const outro);

    Matriz_pt (*ac_mult)	(Matriz_t       * const  me,
							 Matriz_t const * const outro);

    Matriz_pt (*ac_divd)	(Matriz_t        * const  me,
							 Matriz_t const * const outro);

    char *      (*imprime)  (Matriz_t const * const  me);

    void        (*destroi)  (Matriz_t       *        me);
    
	double     (*get) (Matriz_t  const * const me, int posicao[2]);

	void   	   (*set ) (Matriz_t * const me, int posicao[2], double valor);

	double *   	   (*getValores) (Matriz_t * me);

	unsigned int*   (*getTam) (Matriz_t * me);

	Matriz_pt  (*modulo_ ) (Matriz_t  * me);

    Matriz_pt (*transpor_) (Matriz_t * me);

	Matriz_pt (*acrescentaLinha) (Matriz_t * me);	

	Matriz_pt (*acrescentaColuna) (Matriz_t * me);	

	Matriz_pt (*reverseVertical) (Matriz_t * me);	

	Matriz_pt (*reverseHorizontal) (Matriz_t * me);	

	Matriz_pt (*identidade) (Matriz_t * me, unsigned int * tam);	

	Matriz_pt (*ones) (Matriz_t * me);	

	Matriz_pt (*transpor_Diag2) (Matriz_t * me);

	Matriz_pt (*multPorEscalar) (Matriz_t * me,int a);
	
	Matriz_pt (*resize)  (Matriz_t * me, unsigned int * tam);
    /*------------------------------------------------------*/
};

typedef struct Matriz_Interface_st *Matriz_Interface_pt;

Matriz_pt Matriz_2D_criar (Matriz_pt  me,unsigned int tam[2],double *valores);

#endif /* Matriz_H */
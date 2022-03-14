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

    int			(*compara)	(Matriz_t const * const  me, Matriz_t const * const  outro);

    char *      (*imprime)  (Matriz_t const * const  me);

    void        (*destroi)  (Matriz_t       *        me);
    
    void       (*get_at) (Matriz_t  const * const me, int *posicao,double *valor);

	double     (*get) (Matriz_t  const * const me);

	void   	   (*set ) (Matriz_t * const me, int * posicao, double valor);

    Matriz_pt  (*)

    /*------------------------------------------------------*/
};

typedef struct Matriz_Interface_st *Matriz_Interface_pt;


/* protótipo do construtor   */
Matriz_pt Racional_constroi (Matriz_pt  me,
								  long int valorNum,
								  long int valorDen);



#endif /* Matriz_H */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N_ELM 5

typedef int TipoElemLista;

struct StructListaConcat{

    TipoElemLista info;
    struct StructListaConcat *next;

};

typedef struct StructListaConcat TipoNodoLista;
typedef TipoNodoLista *TipoLista;
//TipoLista testa;
//TipoLista paux;

void InitList(TipoLista *ls)
{
    *ls = NULL;

}

int IsEmpty (TipoLista ls)
{
    return (ls == NULL);
}



void InsertNodoLista (TipoLista *ls, int num_elem, TipoElemLista elem)
{
    TipoLista testa;
    TipoLista paux;
    int k;

            paux = (TipoLista)malloc(sizeof(TipoNodoLista));
            paux->info = elem;
            paux->next = testa;
            testa = paux;


}

TipoLista CreaLista(int num)
{
    TipoLista lista, testa;
    if (num == 0)
    {
        return NULL;
    }
    else
    {
            lista = CreaLista(num-1);
            testa = (TipoLista)malloc(sizeof(TipoNodoLista));
            testa->info = num;
            testa->next = lista;

       return testa;
    }
}

TipoLista InsertTestaLista(TipoLista *ls, TipoElemLista elm )
{
    if (ls != NULL)
    {
        TipoLista paux;

        paux = (TipoLista)malloc(sizeof(TipoNodoLista));
        paux->info = elm;
        paux->next = ls;
       // printf("aaa %d %d",ls,*ls);
        return paux;
    }
    else
    {
        printf("\nOperazione impossibile: la lista non esiste!");
    }


}

void DeleteTestaLista (TipoLista *ls)
{
    TipoLista lstaux;
    if(!IsEmpty(*ls))
    {
        lstaux = *ls;
        *ls = (*ls)->next;
        free(ls);

    }
      else
        printf("\nLista vuota!");
}



void InsertCodaLista(TipoLista *ls, TipoElemLista elem)
{
    TipoLista last;
    TipoLista paux;

    paux = (TipoLista)malloc(sizeof(TipoNodoLista));
    paux->info = elem;
    paux->next = NULL;
    if (*ls == NULL)
    {
        *ls = paux;
    }
    else
    {
        last = ls;

        while ( last->next != 0)
        {
            last = last->next;
            printf("\n Next = %d", last->next);
        }

        last->next = paux;

    /*

        do
        {
            printf("\nLista[%d] = %d", num , ls->info);
            ls = ls->next;
            num++;

        } while (ls !=  NULL);
        */

    }

}

bool EqualElem(TipoElemLista val1, TipoElemLista val2)
{
    /// la funzione restituisce TRUE solo se val1 == val2
   return (val1 == val2);
}


bool ExistInConcatList( TipoLista ls, TipoElemLista elem)
{
    int k = -1;
       while(ls != NULL)
       {
           k++;
           if (EqualElem(ls->info, elem))
           {
               printf("\n Elemento Trovato in posizione [%d]", k);
               return true ;
           }
           else
           {
               ls = ls->next;
           }

       }
       printf("\n Elemento NON trovato");
       return false;
}

int StampaTestaLista (TipoNodoLista *ls)
{
    return(ls->info);
}

void StampaListaConcat (TipoNodoLista *ls)
{
    int num = 0;
    if ( ls == NULL)
    {
        printf("\nLa lista e' vuota o non esiste.");
    }
    else
    {
        do
        {
            printf("\nLista[%d] = %d", num , ls->info);
            ls = ls->next;
            num++;

        } while (ls !=  NULL);
    }

}

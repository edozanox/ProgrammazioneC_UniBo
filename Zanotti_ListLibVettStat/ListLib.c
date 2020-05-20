#include <stdio.h>
#include <stdlib.h>

#define N 3
#define EMPTYLIST -1
#define UNDEFINED -2

//Tutte le funzioni ritornano un valore int: 1 se l'operazione viene eseguita correttamente oppure 0 se si presentano dei warning, altrimenti  mostra direttamente un messaggio di alert.
// definizione del tipo di elemento della lista
typedef int TipoElementoLista;

// definizione della struttura della lista
struct StructLista {
   TipoElementoLista valori[N];
   int last;
} ;

// dichiarazione di una nuova struttura della lista
typedef struct StructLista TipoLista;

int IsEmpty(TipoLista l)
{
    return (l.last == EMPTYLIST);
}

int IsFull(TipoLista l)
{
    return (l.last == N-1);

}

int insertTesta (TipoLista *l, TipoElementoLista val)
{
    if(!IsFull(*l))
    {

        int pos = l->last+1;
        //l->valori[pos] = 0;

        for (int k = pos; k>0; k--)
        {
            l->valori[k] = l->valori[k-1];

        }
        l->valori[0] = val;
        l->last++;
        return 0;
    }
    else
    {
        printf("\nNon e\'possibile aggiungere elementi in testa...la lista e\' piena!");
        return 1;
    }

}

int insertCoda(TipoLista *l, TipoElementoLista val)
{
   if(!IsFull(*l))
   {
           int posizione=l->last+1;

           l->last=posizione;
           l->valori[posizione]=val;
           return 1;
   }
   else
   {
       printf("\nImpossibiel aggiunger un elemento in coda....lista piena!");
      return 0;
   }

}

int insertPosition(TipoLista *l, int pos, TipoElementoLista val)
{
    //VERIFICARE SE LA LISTA
    int new_pos = l->last+1;
    if((pos >= 0) && (pos <= l->last))
    {
        for(int k = new_pos; k > pos; k--)
        {
            l->valori[k] = l->valori[k-1];
            //l->valori[k-1] = 0;
        }

        l->valori[pos] = val;
        l->last++;

        return 1;
    }else
        printf("\nValore posizione non corretto!");
        return 0;

}



int deleteCoda(TipoLista *l)
{
    if(!IsEmpty(*l))
    {
         l->last=l->last-1;
         return 1;
    }
    else
        return 0;

}

int deleteFirstOccurrence(TipoLista *l, TipoElementoLista val)
{
  if(!IsEmpty(*l))
  {
    int cnt = -1;
    int found = 0;
    int j;

    do
    {
            cnt++;
            if (l->valori[cnt] == val)
            {
                found = 1;
            }

     } while (found != 1);

    //l->valori[cnt] = 0;

    for(j=cnt; j<l->last; j++)
    {
       l->valori[j] = l->valori[j+1];
       //l->valori[j+1] = 0;
    }
    l->last--;
    return 1;

  }else
    return 0;
}


void deleteElemPos(TipoLista *l, TipoElementoLista val)
{
//    int i;
    if(!IsEmpty(*l))
    {
        if((val<0)||(val > l->last))
        {
            printf("\nPosizione inserita non valida!");
        }
        else
        {
            if (val==l->last)
            {
                deleteCoda(l);
            }

            if((val>-1) && (val < l->last))
            {
                for (int i = val; i< l->last; i++)
                {
                    l->valori[i] = l->valori[i+1];
                }
                l->last--;
            }
        }
    }
    else
        printf("\nLista vuota!");
}


int deleteTesta (TipoLista *l)
{
   if(!IsEmpty(*l))
   {
      for( int c = 0; c < l->last; c++)
      {
         l->valori[c] = l->valori[c+1];
         //l->valori[c+1] = 0;
      }
      l->last--;
       return 1;

    }else
        return 0;

}

int deleteLista (TipoLista *l)
{
    if(!IsEmpty(*l))
    {
        l->last = EMPTYLIST;
        return 1;
    }


}


void stampaLista(TipoLista *l)
{
   printf("\nStampa Lista di %d  elementi\n",l->last+1);
   for (int x=0; x<=l->last; x++) {
     printf("Lista[%d] = %d \n", x, l->valori[x]);
   }
   return;

}




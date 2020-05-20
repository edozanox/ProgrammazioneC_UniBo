#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 5
#define EMPTYLIST -1
#define UNDEFINED -2

//Tutte le funzioni ritornano un valore int: 1 se l'operazione viene eseguita correttamente,
//oppure 0 se si presentano dei warning, altrimenti  mostra direttamente un messaggio di alert.
// definizione del tipo di elemento della lista

typedef int TipoElementoLista;

// definizione della struttura della lista
struct StructLista {
   TipoElementoLista *values;
   int size;
   int last;
} ;

// dichiarazione di una nuova struttura della lista
typedef struct StructLista TipoLista;
//TipoLista tmp_ls;

//void stampaLista(TipoLista *l, );

int IsEmpty(TipoLista l)
{
    return (l.last == EMPTYLIST);
}

int IsFull(TipoLista l)
{
    return (l.last == l.size-1);

}

TipoLista create_list()
{
    TipoLista tmp_ls;

    tmp_ls.values = NULL;
    tmp_ls.size = 0;
    tmp_ls.last = -1;

    tmp_ls.values = (TipoElementoLista*) calloc (N, sizeof (TipoElementoLista) );

    if(tmp_ls.values != NULL )
    tmp_ls.size = N;
    tmp_ls.last = -1;

  return tmp_ls;
}

void deleteLista (TipoLista *l)
{
    if(l!=NULL)
        free(l->values);
    l->size = 0;
    l->last = -1;

}

int extend_lista(TipoLista *l)
{
    TipoElementoLista *tmp_ls = realloc(l->values, (l->size+N)*sizeof(TipoElementoLista));
    ///anzich� raddoppiare i valori della lista ne viene aggiunta una una quantit� pari a quella precedente
    if(tmp_ls != NULL)
    {
        l->size = l->size + N;
        l->values = tmp_ls;
        return 1;
    } else {
        return 0;
    }
}

void reduce_list (TipoLista *l)
{
    //controllo se posso ridurre la lista ovver il numero di elementi contenuti e inferiore alla sua dimensione
    if((l->size-N) > l->last)
    {
        //riduco la dimensione della lista di N elementi
        TipoElementoLista *tmp_ls = realloc(l->values, (l->size-N)*sizeof(TipoElementoLista));

        //se la realloc va a buon fine imposto la dimensione della lista al valore corretto
        if(tmp_ls != NULL)
        {
            l->size = l->size - N;
            l->values = tmp_ls;

        }
    }

}

int insertTesta (TipoLista *l, TipoElementoLista val)
{
    int esito = 1;
    if(IsFull(*l))
    {
        esito = extend_lista(l);
    }
    printf("dimensione lista %d",l->size);
    if (esito) {
        int pos = l->last+1;
        for (int k = pos; k>0; k--)
        {
            l->values[k] = l->values[k-1];

        }
        l->values[0] = val;
        l->last++;
        return 0;
    } else {
        printf("Attenzione: si e' verificato un errore nella estensione della lista.");
    }
}

int insertCoda(TipoLista *l, TipoElementoLista val)
{
    int added = 0;
    do
    {
        if(!IsFull(*l))
           {
                   int posizione=l->last+1;
                   l->last=posizione;
                   l->values[posizione]=val;
                   added=1;
           }
           else
           {
               printf("\nEstensione lista in corso...");
               extend_lista(l);
               added=0;
           }
    } while (!added);
    return 1;
}

int insertPosition(TipoLista *l, int pos, TipoElementoLista val)
{
  int new_pos = l->last+1;
    if((pos >= 0) && (pos <= l->last))
    {
        for(int k = new_pos; k > pos; k--)
        {
            l->values[k] = l->values[k-1];
            //l->valori[k-1] = 0;
        }

        l->values[pos] = val;
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
            if (l->values[cnt] == val)
            {
                found = 1;
            }

     } while (found != 1);

    //l->valori[cnt] = 0;

    for(j=cnt; j<l->last; j++)
    {
       l->values[j] = l->values[j+1];
       //l->valori[j+1] = 0;
    }
    l->last--;
    return 1;

  }else
    return 0;
}


void deleteElemPos(TipoLista *l, int val)
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
                    l->values[i] = l->values[i+1];
                }
                l->last--;
            }
        }
    }
    else
        printf("\nLista vuota!");
}


void deleteTesta (TipoLista *l)
{
     if(!IsEmpty(*l))
    {
          for (int i = 0; i< l->last; i++)
          {
             l->values[i] = l->values[i+1];
           }
                l->last--;
     }
      else
        printf("\nLista vuota!");
}



int EqualElem(TipoElementoLista val1, TipoElementoLista val2)
{
    /// la funzione restituisce TRUE solo se val1 == val2
   return (val1 == val2);
}


int ExistsInList(TipoLista l, TipoElementoLista val)
{
    int found = 0;
    int n = 0;
    TipoElementoLista elem = l.values[n];

    while ((!found) && (elem != NULL))
    {
        if(EqualElem(elem, val))
        {
            found = 1;
        }

        n++;
        elem = l.values[n];
    }

  return found;
}

int deleteAllOcc(TipoLista *l, TipoElementoLista val) ///nuova funzione da testare
{
    int count = 0;
    int n = 0;
    int paux = 0;
    TipoElementoLista valore = l->values[n];

    while((valore != NULL) && (n <= l->last))
    {
        if (EqualElem(val, valore))
        {
          count++;
          deleteElemPos(l, n);
        }

        n++;
        valore = l->values[n];
    }

    return count;
}

void stampaLista(TipoLista *l, FILE *file_lista)
{
   file_lista = fopen("./FileListaDinamica.txt", "w");
   if( file_lista == NULL)
   {
       printf("\nErrore apertura file.\n");
   }
   else
   {
       printf("\nFile di salvataggio aperto/creato correttamente.\n");
   }

   printf("\nStampa Lista di %d  elementi\n",l->last+1);
   for (int x=0; x<=l->last; x++)
   {
        printf("Lista[%d] = %d \n", x, l->values[x]);
        fputc(l->values[x], &file_lista);
   }

fclose(file_lista);

}





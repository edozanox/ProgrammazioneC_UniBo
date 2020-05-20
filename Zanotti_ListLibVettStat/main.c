#include <stdio.h>
#include <stdlib.h>

#include "./ListLib.c"


int main() {

   // dichiaro una variabile di tipo TipoLista
   TipoLista lista;

//   TipoElementoLista l[10] = {5,15,25};
  // lista.valori[0]=5;
  // lista.valori[1]=15;
  // lista.valori[2]=25;
   //lista->valori={20,22,23};
   lista.last=-1;


   int sel = 0;
   int val_ins = 0;
   int num_loop = 0;
   int fine = 0;
   char val_ch;

   //ciclo ideato in maniare tale da poter effettuare più operazioni nella stessa sessione
   do
   {
       printf("\nBenvenuto nel GESTORE LISTE - VETTORE STATICO");
       printf("\n");
       printf("\n1 - TEST LISTA VUOTA/PIENA");
       printf("\n2 - INSERISCI IN TESTA");
       printf("\n3 - INSERISCI IN CODA");
       printf("\n4 - INSERISCI IN POSIZIONE N");
       printf("\n5 - ELIMINA PRIMA OCCORRENZA");
       printf("\n6 - ELIMINA TESTA");
       printf("\n7 - ELIMINA CODA");
       printf("\n8 - ELIMINA LISTA");
       printf("\n");
       printf("\nSeleziona un'operazione:");
       scanf("%d", &sel);

       switch (sel)
       {

           case 1:
               {
                    if(IsFull(lista) > -1)
                    {

                       printf("\nIn Lista sono presenti %d elementi.", lista.last+1);
                       stampaLista(&lista);

                    }
                    else
                    {
                            printf("\nLISTA VUOTA");
                            stampaLista(&lista);
                    }

                    break;
               }

           case 2:
            {
                printf("\n");
                printf("\nDigita l'elemento da inserire in testa:");
                scanf("%d", &val_ins);
                insertTesta(&lista, val_ins);
                stampaLista(&lista);
                break;
            }


           case 3:
            {
                printf("\n");
                printf("Quanti elementi desideri inserire in lista?");
                scanf("%d", &num_loop);

                for (int k = 0; k < num_loop; k++)
                {
                    printf("\nDigita l'elemento %d da inserire in coda:", k);
                    scanf("%d", &val_ins);
                    insertCoda(&lista, val_ins);
                }

                printf("\n");
                stampaLista(&lista);
                break;
            }

           case 4:
            {
                int num_pos = 0;
                printf("\n");
                printf("\nDigita la posizione e l'elemento da inserire:");
                scanf("%d%d", &num_pos, &val_ins);
                insertPosition(&lista, num_pos, val_ins);
                stampaLista(&lista);
                break;
            }

           case 5:
            {
                printf("\n");
                printf("\nDigita l'elemento da eliminare (solo prima occorrenza):");
                scanf("%d", &val_ins);
                deleteFirstOccurrence(&lista, val_ins);
                stampaLista(&lista);
                break;
            }

        case 6:
            {
                printf("\nELIMINAZIONE TESTA...");
                deleteTesta(&lista);
                stampaLista(&lista);
                break;
            }

        case 7:
            {
                printf("\nELIMINAZIONE CODA...");
                deleteCoda(&lista);
                stampaLista(&lista);
                break;
            }

          case 8:
            {
               if(!IsEmpty(lista))
               {
                   printf("\nELIMINAZIONE LISTA...");
                   deleteLista(&lista);
                   stampaLista(&lista);
               }
               else
               {
                    stampaLista(&lista);
                    printf("\nLa lista e\' gia\' vuota!");
               }
            break;
            }

          default:
            {
                printf("\ERRORE!");
            }

       }

        system("\npause");

    }while(fine != 1);

    return 0;
}
/*
   insertCoda(&lista, 5);
   insertCoda(&lista, 15);
   insertCoda(&lista, 25);
   insertCoda(&lista, 252) ;
   insertCoda(&lista, 253);
   insertCoda(&lista, 254);
   insertCoda(&lista, 256);
   insertCoda(&lista, 257);
   insertCoda(&lista, 258);
   insertCoda(&lista, 35);
  /* if (!insertCoda(&lista, 2523)){
      printf("\nImpossibile inserire elemento %d...la lista e\'  piena!",2523);
   };
   if (!insertCoda(&lista, 999)){
      printf("\nImpossibile inserire elemento %d...la lista e\'  piena!",999);
   }

   printf("\nLISTA DEFAULT");
   stampaLista(&lista);
   deleteCoda(&lista);
   printf("\nCANCELLA CODA");
   stampaLista(&lista);
   insertTesta(&lista, 454); ///problema con stampa ultimo elemento
   printf("\nINSERIMENTO TESTA - Error last elem!");
   stampaLista(&lista);
   deleteFirstOccurrence(&lista, 5);
   printf("\nCANCELLA PRIMA OCCORRENZA - Da sistemare");
   stampaLista(&lista);
   insertPosition(&lista, 3 ,64);
    printf("\nINSERIMENTO IN POSIZIONE N");
   stampaLista(&lista);
   deleteTesta(&lista);
   printf("\nCANCELLA TESTA LISTA");
   stampaLista(&lista);
}


   for (int j = 0; j<14; j++)
   {
        if(deleteCoda(&lista))
        {
           printf("\nElemento eliminato correttamente!");
        }
        else
            printf("\nImpossibile eliminare elemento ... lista vuota!");


   }

*/




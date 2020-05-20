#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "./ListLibDinam.c"

int main()
{

    TipoLista list = create_list();
    //TipoLista list2 = create_list();
    //list.last = -1;
    FILE *f;
    TipoElementoLista val_ins;
    bool rtrn_ls = false;
   int sel = 0;
   int num_loop = 0;
   int fine = 0;
   int result = 0;
   char val_ch;

   insertCoda(&list, 25);
   insertCoda(&list, 35);
   insertCoda(&list, 45);
   insertCoda(&list, 25);
   insertCoda(&list, 92);
   insertCoda(&list, 45);

        printf("\nBenvenuto/a nel GESTORE LISTE - VETTORE DINAMICO");
    do
    {
        printf("\n");
       printf("\n1 - TEST LISTA VUOTA/PIENA");
       printf("\n2 - INSERISCI IN TESTA");
       printf("\n3 - INSERISCI IN CODA");
       printf("\n4 - INSERISCI IN POSIZIONE N");
       printf("\n5 - ELIMINA PRIMA OCCORRENZA");
       printf("\n6 - ELIMINA TESTA");
       printf("\n7 - ELIMINA CODA");
       printf("\n8 - ELIMINA LISTA");
       printf("\n9 - VERIFICA PRESENZA ELEMENTO");
       printf("\n10 - ELIMINA TUTTE LE OCCORRENZE");
       printf("\n");
       printf("\nSeleziona un'operazione:");
       scanf("%d", &sel);


       switch (sel)
       {
            case 1:
               {
                    if(IsEmpty(list))
                    {
                        printf("\nLa lista e' vuota.");

                    } else
                    {
                        if(IsFull(list))
                        {
                            printf("\nLa lista e' piena.");
                        } else
                        {
                            printf("\nIn Lista sono presenti %d elementi.", list.last+1);
                        }
                        stampaLista(&list, );
                    }

                    break;
               }

           case 2:
            {
                printf("\n");
                printf("Quanti elementi desideri inserire in lista?");
                scanf("%d", &num_loop);

                for (int k = 0; k < num_loop; k++)
                {
                    printf("\nDigita l'elemento %d da inserire in testa:", k);
                    scanf("%d", &val_ins);
                    insertTesta(&list, val_ins);
                }

                printf("\n");
                stampaLista(&list);
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
                    insertCoda(&list, val_ins);
                }

                printf("\n");
                stampaLista(&list);
                break;
            }

           case 4:
            {
                int num_pos = 0;
                printf("\n");
                printf("\nDigita la posizione e l'elemento da inserire:");
                scanf("%d%d", &num_pos, &val_ins);
                insertPosition(&list, num_pos, val_ins);
                stampaLista(&list);
                break;
            }

           case 5:
            {
                printf("\n");
                printf("\nDigita l'elemento da eliminare (solo prima occorrenza):");
                scanf("%d", &val_ins);
                deleteFirstOccurrence(&list, val_ins);
                stampaLista(&list);
                break;
            }

        case 6:
            {
                printf("\nELIMINAZIONE TESTA...");
                deleteTesta(&list);
                stampaLista(&list);
                break;
            }

        case 7:
            {
                printf("\nELIMINAZIONE CODA...");
                deleteCoda(&list);
                stampaLista(&list);
                break;
            }

          case 8:
            {
               if(!IsEmpty(list))
               {
                   printf("\nELIMINAZIONE LISTA...");
                   deleteLista(&list);
                   stampaLista(&list);
               }
               else
               {
                    stampaLista(&list);
                    printf("\nLa lista e\' gia\' vuota!");
               }
            break;
            }
           case 9:
           {

               printf("\n-----------------------");
               printf("\nDigita l'elemento da trovare in lista:");
               scanf("%d", &val_ins);
               rtrn_ls = ExistsInList(list, val_ins);

               if (rtrn_ls == 1)
               {
                   printf("\n");
                   printf("\nElemento TROVATO");
               }
               else
               {
                   printf("\n");
                   printf("\nElemento NON TROVATO");
               }

                break;
           }

           case 10:
            {
                printf("\n-----------------------");
                printf("\nDigita il valore da eliminare per tutte le occorrenze:");
                scanf("%d", &val_ins);
                result = deleteAllOcc(&list, val_ins);
                if (result != 0)
                {
                    printf("\nElemento eliminato %d volte", result);
                    stampaLista(&list);
                }
                else
                    printf("\nImpossibile eliminare l'elemento perche' non presente in lista.");

                break;

            }

          default:
            {
                printf("\ERRORE!");
            }


       }

        printf("\n");
       system("\npause");

    }while(1);
}










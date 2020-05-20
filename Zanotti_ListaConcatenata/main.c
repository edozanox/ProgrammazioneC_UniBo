#include <stdio.h>
#include <stdlib.h>

#include "./LibListConc.c"

int main()
{
    TipoLista lst ;

    int selezione = 0;
    int valore = 0;
    int rtrn = 0;

    printf("\nBenvenuto nel gestore LISTA CONCATENATA");
    printf("\n");
    InitList(&lst);
    printf("\nLista inizializzata!");

do {
    printf("\n");
    printf("\n1 - Crea lista");
    printf("\n2 - Inserisci in testa");
    printf("\n3 - Inserisci in coda");
    printf("\n4 - Elimina testa");
    printf("\n5 - Verifica presenza elemento");
    printf("\n6 - Stampa elemento in testa");
    printf("\nSeleziona un'operazione:");
    scanf("%d", &selezione);

    switch(selezione)
    {
    case 1:
        {
            printf("\n----------------------------------");
            printf("\nNumero desiderato di record: ");
            scanf("%d", &valore);
            lst = CreaLista(valore);
            printf("\nLista di %d elementi creata.", valore);
            StampaListaConcat(lst);

            break;
        }

    case 2:
        {

            printf("\n----------------------------------");
            printf("\nValore da inserire in TESTA: ");
            scanf("%d", &valore);
            lst=InsertTestaLista(lst, valore);
            StampaListaConcat(lst);
            break;

        }

    case 3:
        {
            printf("\n----------------------------------");
            printf("\nValore da inserire in CODA: ");
            scanf("%d", &valore);
            InsertCodaLista(lst, valore);
            StampaListaConcat(lst);
            break;
        }

    case 4:
        {
            printf("\n----------------------------------");
            DeleteTestaLista(&lst);
            printf("\nTesta eliminata!");
            StampaListaConcat(lst);

            break;
        }
    case 5:
        {
            printf("\n----------------------------------");
            printf("\nValore da ricercare:");
            scanf("%d", &valore);
            ExistInConcatList(lst, valore);
            break;
        }

    case 6:
        {

            printf("\n----------------------------------");
            TipoElemLista rtrn_head = StampaTestaLista(lst);
            printf("\nELEMENTO IN TESTA: [%d]", rtrn_head);
            break;
        }


    default:
        {

            printf("\n----------------------------------");
            printf("\nErrore selezione voce menu!");
        }



      }


    }while(1);
}

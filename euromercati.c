#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

struct ProdListino
{
    int codice_prodotto;
    int codice_fornitore;    
    int quantita_minima;
    float prezzo_unitario;  
};

struct Prodotto
{
    int codice_prodotto;
    int codice_fornitore;
    int quantita_presente;    
};

struct Supermercato
{
    int size_prodotti;
    int codice_supermercato;
    struct Prodotto *prodotti;  
};

// Creazione/modifica listino con tutti i prodotti commerciabili
// Creazione di alcuni market
// Inserimento prodotti e relative quantità per ogni market
// chiudi_supermercato => trasferisci elementi ad altro market
// stampa_prodotti_in_esaurimento => quantita_presente < quantita_mimima per ogni market
// miglior_supermercato => 
// individua il codice market al cui interno è mantenuto l’insieme di prodotti con valore maggiore

int compareProdListino(const void *a, const void *b)
{
    struct ProdListino *structA = (struct ProdListino *)a;
    struct ProdListino *structB = (struct ProdListino *)b;

    if (structA->codice_prodotto < structB->codice_prodotto)
    {
        return -1;
    }
    else if (structA->codice_prodotto > structB->codice_prodotto)
    {
        return 1;
    }
    else
    {
        return 0; // Gli ID sono uguali
    }
}
 
int main()
{    
    struct ProdListino *listino = NULL;
    struct Supermercato *supermercati = NULL;

    int num_prod_in_listino = 0;
    int num_market_aperti = 0;
    
    int codice_operazione = 0;
    
    start:

    printf("\n");
    printf("\nBenvenuti in EUROMERCATI");    
    printf("\n1 - Crea listino");
    printf("\n2 - Crea supermercato");    
    printf("\n3 - Collega prodotti a market");
    printf("\n4 - Chiudi punto vendita");
    printf("\n5 - Vedi prodotti in esaurimento");
    printf("\n6 - Miglior supermercato");
    printf("\n7 - Panoramica punti vendita");

    printf("\nSeleziona un'operazione da eseguire:");
    scanf("%d", &codice_operazione);

    switch (codice_operazione)
    {        
        //CREAZIONE LISTINO
        case 1:
    
            int quantita_prodotti = 0;
            printf("Inserire quantità elementi da aggiungere:");
            scanf("%d", &quantita_prodotti);
                       
            //Controllo se listino è vuoto
            if(sizeof(listino) == 0) {
                //se listino è vuoto istanzio la memoria per la quantità di prodotti da inserire
                listino = (struct ProdListino *) malloc(quantita_prodotti * sizeof(struct ProdListino));
                if (listino == NULL) {
                    printf("Errore nell'allocazione di memoria.\n");
                    return 1;
                }           
            }
            else
            {
                //se listino ha già dei prodotti allora realloc
                listino = (struct ProdListino *) realloc(listino, quantita_prodotti * sizeof(struct ProdListino));
                if (listino == NULL) {
                    printf("Errore nell'allocazione di memoria.\n");
                    return 1;
                }
            }
           
            //ciclo per il popolamento del listino con i dati effettivi dei prodotti
            for(int qta = 0; qta < quantita_prodotti; qta++){
                num_prod_in_listino++;
                printf("\n%d - [Codice prodotto]  [Codice fornitore] [Quantità minima] [Prezzo unitario] ............. ", qta); 
                scanf("%d %d %d %f", &listino[qta].codice_prodotto, &listino[qta].codice_fornitore, 
                        &listino[qta].quantita_minima, &listino[qta].prezzo_unitario);                
            }

            //algoritmo di ordinamento
            qsort(listino, num_prod_in_listino, sizeof(struct ProdListino), compareProdListino);

            //termino il processo visualizzando tutto il listino ordinato
            for (int i = 0; i < num_prod_in_listino; i++)
            {
                printf("\n%d - Prod. %d........... %f€ (min. %d pz.)", i, listino[i].codice_prodotto, listino[i].prezzo_unitario, listino[i].quantita_minima);
            }                
            
            goto start;
                    
        //CREAZIONE MARKET
        case 2: 
            int num_elem = 0;
            printf("\nCreazione supermercati");
            printf("\nQuanti market vuoi creare?");
            scanf("%d", &num_elem);

            int sizeLstMrk = sizeof(supermercati) / sizeof(struct Supermercato);

            if(sizeLstMrk == 0) {
                //se supermercati è vuoto istanzio la memoria per la quantità di prodotti da inserire              
                supermercati = (struct Supermercato *)malloc(num_elem * sizeof(struct Supermercato));
                if (supermercati == NULL) {
                    printf("Errore nell'allocazione di memoria.\n");
                    return 1;
                }                 
            }
            else
            {
                //se supermercati ha già dei market allora realloc
                supermercati = (struct Supermercato *)realloc(supermercati, num_elem * sizeof(struct Supermercato));
                if (supermercati == NULL) {
                    printf("Errore nell'allocazione di memoria.\n");
                    return 1;
                }
            }

            for (int i = 0; i < num_elem; i++)
            {
                printf("\n%d [Codice].........", i);
                scanf("%d", &supermercati[i].codice_supermercato);
                num_market_aperti++;
            }
            goto start;            

        //AGGIUNTA PRODOTTI A MARKET
        case 3:
                int qta_prod = 0;
                int cod_mrkt_sel = 0;
                int pos_market = 0;
                bool cod_mrkt_ok = false;

                printf("\nMarket disponibili");
                for (int u = 0; u < num_market_aperti; u++){
                    printf("\n%d - [%d]", u, supermercati[u].codice_supermercato);
                }
                while(cod_mrkt_ok == false)
                {
                    printf("\nSeleziona un market");
                    scanf("%d", &cod_mrkt_sel);
                    for (int y = 0; y < num_market_aperti; y++) {
                        if(cod_mrkt_sel == supermercati[y].codice_supermercato) {
                            cod_mrkt_ok = true;
                            pos_market = y;
                            break;
                        }
                    }
                }

                printf("\nProdotti disponibili in listino:");
                for (int w = 0; w < num_prod_in_listino; w++){
                    printf("\n[%d]......min. %d", listino[w].codice_prodotto, listino[w].quantita_minima);
                }

                printf("\nQuanti prodotti, tra quelli disponibili, vuoi aggiungere?");
                scanf("%d", &qta_prod);
                
                supermercati[pos_market].prodotti = (struct Prodotto *)malloc(qta_prod * sizeof(struct Prodotto));

                for(int x = 0; x < qta_prod; x++){

                    bool prod_ok = false;
                    while(prod_ok == false) {         
                        int cod_prod_sel = 0;
                        int qta_prod_sel = 0;                
                        printf("\n%d - [codice prodotto] [quantità]...........", x);
                        scanf("%d %d", &cod_prod_sel, &qta_prod_sel);
                                                                
                        //Controllo che il codice_prodotto corrisponda effettivamente ad un prodotto
                        for(int k = 0; k < num_prod_in_listino; k++) {
                            if(cod_prod_sel == listino[k].codice_prodotto) {                                
                                prod_ok = true;
                                supermercati[pos_market].size_prodotti++;
                                supermercati[pos_market].prodotti[x].codice_prodotto = listino[k].codice_prodotto;
                                supermercati[pos_market].prodotti[x].codice_fornitore = listino[k].codice_fornitore;
                                supermercati[pos_market].prodotti[x].quantita_presente = qta_prod_sel;                            
                            }
                        }
                    }
                }

            goto start;
           
            break;
        case 4:
            break;
        // Vedi prodotti in esaurimento
        case 5:     
            bool market_exists = false; 
            while(market_exists == false){
                printf("\nCodice supermercato:");
                scanf("%d", &cod_mrkt_sel);
                for(int x = 0; x < num_market_aperti; x++){
                    if(supermercati[x].codice_supermercato == cod_mrkt_sel) {
                        pos_market = x;
                        market_exists = true;
                        printf("\nProdotti in esaurimento nel market %d:", cod_mrkt_sel);
                        break;
                    }
                }
            }
                     
            for(int y = 0; y < supermercati[pos_market].size_prodotti; y++){ 
                
            
                //Cerco nel listino la quantità minima per il prodotto
                for(int x = 0; x < num_prod_in_listino; x++) {
                    if(listino[x].codice_prodotto == supermercati[pos_market].prodotti[y].codice_prodotto) {
                        int cod_prod = listino[x].codice_prodotto;
                        //e confronto i valori con la soglia minima
                        if(supermercati[pos_market].prodotti[y].quantita_presente < listino[x].quantita_minima)  {
                            printf("\n !!! - Prod. %d.......presenti %d pz, min. %d", cod_prod, supermercati[pos_market].prodotti[y].quantita_presente, listino[x].quantita_minima);
                        }
                    }
                } 
            
            }
            goto start;            
        case 6:
            break;
        
        //PANORAMICA PUNTI VENDITA
        case 7:
            printf("\nTotale punti vendita: %d", num_market_aperti);
            for(int v = 0; v < num_market_aperti; v++) {
               
               printf("\n%d", supermercati[v].codice_supermercato);
                
                for(int z = 0; z < supermercati[v].size_prodotti; z++){
                    printf("\n[%d]...........%d pz.", supermercati[v].prodotti[z].codice_prodotto, supermercati[v].prodotti[z].quantita_presente);
                }
            }
            goto start;
        default:
            break;
    }
}

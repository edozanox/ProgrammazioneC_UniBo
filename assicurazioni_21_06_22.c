#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

struct Appuntamento
{
    char id_cliente[10];
    char id_agente[10];
    char codice_richiesta_prestazione[15];    
};

//Struttura che dev'essere generata
//solo al richiamo della funzione leggi_appuntamenti
struct Agente
{
    char nome_cognome_agente[70];
    char id_agente[10];
    int n_clienti_agente;
    struct Appuntamento *appuntamenti;
    int size_appuntamenti;
};

struct AgenteNomi
{
    char nome_cognome_agente[70];
    int id_agente;    
};


struct Agente *agenti = NULL;
struct AgenteNomi *id_nomi_agenti; //Vettore ordinato per id_agente crescente
int *totale_agenti = NULL;
FILE *file_appuntamenti;

int inserisci_agente(int id, char nome_cognome[70]);
int inserisci_appuntamento(char codice_cliente[10], char codice_agente[10], char codice_prestazione[15]);
void leggi_appuntamenti(char filename);
void stampa_agenti_ricorsiva(/*lista agenti*/);
void premio_agente_anno();

int main()
{   
    start:
    int result = 1;
    int codice_operazione = 0;
    
    printf("\n");
    printf("\nBenvenuti in ASSICURAZIONI v1");    
    printf("\n1 - Inserisci nuovo agente");
    printf("\n2 - Inserisci nuovo appuntamento");
    printf("\n3 - Leggi appuntamenti");    
    printf("\n4 - Stampa agenti");
    printf("\n5 - Verifica agente dell\'anno");

    printf("\nSeleziona un'operazione da eseguire:");
    scanf("%d", &codice_operazione);

    switch (codice_operazione)
    {        
        //NUOVO AGENTE
        case 1:            
            while (result == 1) {
                int id;
                char nome_cognome_agente[70];
                printf("\nInserimento nuovo agente");
                printf("\nID:");
                scanf("%d", &id);
                printf("\nNome Cognome:");
                scanf("%s", nome_cognome_agente);
                result = inserisci_agente(id, nome_cognome_agente);
                if(result == 1) {
                    printf("\nRipetere operazione causa errore in fase di esecuzione");
                }
            }
            goto start;
        break;

        //NUOVO APPUNTAMENTO
        //Creazione elemento Appuntamento
        //1) Richiedo ID agente (mostro lista)
        //2) Richiedo codice prestazione
        //3) Richiedo codice cliente
        //4) Salvo su file  
        case 2:
            char codice_agente[10];
            char codice_cliente[10];
            char codice_prestazione[15];
            while (result == 1) {                
                printf("\nInserimento nuovo appuntamento");
                printf("\nCodice cliente:");
                scanf("%s", codice_cliente);
                printf("\nAgenti disponibili:");                
                for(int x = 0; x >= totale_agenti; x++){
                    printf("\n [%d] - %s", id_nomi_agenti[x].id_agente, id_nomi_agenti[x].nome_cognome_agente);
                }
                printf("\nCodice agente:");
                scanf("%s", codice_agente);
                printf("\nCodice prestazione:");
                scanf("%s", codice_prestazione);
                result = inserisci_appuntamento(codice_cliente, codice_agente, codice_prestazione);
                if(result == 1) {
                    printf("\nRipetere operazione causa errore in fase di esecuzione");
                }
            }    
        break;

        //LEGGI APPUNTAMENTI
        case 3:
        break;

        //STAMPA AGENTI
        case 4:
        break;

        //AGENTE DELL'ANNO
        case 5:
        break;

        default:
        break;  

    }
}

//Aggiunge un elemento nella lista ordinata per id_agente crescente
int inserisci_agente(int id, char nome_cognome[70])
{       
    if(totale_agenti == 0) {
        //se lista agenti è vuota istanzio la memoria per il primo agente
        id_nomi_agenti =  malloc(sizeof(struct AgenteNomi));
        if (id_nomi_agenti == NULL) {
            printf("Errore nell'allocazione di memoria.\n");
            return 1;
        }
        memset(id_nomi_agenti, 0, sizeof(struct AgenteNomi));
    }
    else
    {
        //se lista ha già almeno un agente effettuo realloc
        id_nomi_agenti = realloc(id_nomi_agenti, sizeof(struct AgenteNomi));
        if (id_nomi_agenti == NULL) {
            printf("Errore nell'allocazione di memoria.\n");
            return 1;
        }
        memset(id_nomi_agenti, 0, sizeof(struct AgenteNomi));
    }

    // for (int i = 0; i < sizeof(id_nomi_agenti) / sizeof(id_nomi_agenti[0]); i++) {
    //     totale_agenti++;
    // }

    if(totale_agenti > 0) {
        for(int x = 0; x < totale_agenti; x++) {
            //Se esiste già un agente con lo stesso id, annullo l'inserimento in corso
            if(id_nomi_agenti[x].id_agente == id) {
                return 1;
            }
        }

        int pos = 0;

        //Trovo la posizione in cui inserire l'elemento
        while (pos < totale_agenti && id_nomi_agenti[pos].id_agente < id) {
            pos++;
        }
        
        for (int j = totale_agenti - 1; j >= pos; j--) {
            id_nomi_agenti[j + 1] = id_nomi_agenti[j];
        }
        
        //Aggiungo l'elemento nella posizione corretta della lista
        id_nomi_agenti[pos].id_agente = id;
        strcpy(id_nomi_agenti[pos].nome_cognome_agente, nome_cognome);        
        
        
    }
    else
    {
        id_nomi_agenti[0].id_agente = id;
        strcpy(id_nomi_agenti[0].nome_cognome_agente, nome_cognome);
    }

    totale_agenti++;

    //Visualizzo la lista
    for(int y = 0; y <= totale_agenti; y++) {
        printf("\n[%d] - %s", id_nomi_agenti[y].id_agente, id_nomi_agenti[y].nome_cognome_agente);
    }
    return 0;
}

//Aggiunge in sequenza un appuntamento nel file
//Salvare gli appuntamenti di uno stesso Agente in elementi consecutivi adiacenti
int inserisci_appuntamento(char codice_cliente[10], char codice_agente[10], char codice_prestazione[15])
{    
    file_appuntamenti = fopen("./Appuntamenti2024.txt", "a");
    if(file_appuntamenti == NULL)
    {
        printf("\n");
        printf("\nErrore apertura file.");
        printf("\n");
        return 1;
    }
    else
    {
        printf("\nFile aperto o creato correttamente.");
        printf("\n");
    }

    char *appuntamento = codice_agente;
    strcat(appuntamento, " ");
    strcat(appuntamento, codice_cliente);
    strcat(appuntamento, " ");
    strcat(appuntamento, codice_prestazione);
    fputs(appuntamento, file_appuntamenti);
    fflush(stdin);
    return 0;
}

//Legge la lista e costruisce la struct Agente (con struttura collegata Appuntamento)
void leggi_appuntamenti(char filename)
{
    
}

void stampa_agenti_ricorsiva(/*lista agenti*/)
{

}

void premio_agente_anno()
{

}

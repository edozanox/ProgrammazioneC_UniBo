#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

#define NEW_INS "Inserisci nuovo studente"
#define RIC_MATRICOLA "Ricerca per matricola"
#define MODIFICA_INFO "Modifica informazioni (ricerca x matricola)"
#define INFO_MEDIA "Media voti pesati con CFU"
#define RICHIESTA_NAVIGAZIONE "\nVuoi procedere con la navigazione? (Y/N)"


#define VOTOMAX 30
#define VOTOMIN 5
#define ES_NON_SOST 0
#define MAX_STUD 5
#define MIN_SUFF 18
#define NUM_INS 5
#define NUM_ESAMI 5

//insegnamento
struct insegnamento
{
    char codice[50];
    unsigned char nome[50];
    unsigned char docente[50];
    int crediti;
    int anno_somm;

};

typedef struct insegnamento TipoInsegnamento;

TipoInsegnamento insegnamenti[NUM_INS] ={
                                                {"MAT/05", "Analisi Matematica", " Prof. G. Cupini", 15, 2019},
                                                {"PRG-012", "Programmazione", "Prof.ssa A. Carbonaro", 25, 2019},
                                                {"ING-014", "Idoneita\' lingua inglese B1", "Prof. Smith", 5, 2019},
                                                {"MAT/02", "Algebra e geometria", "Prof.ssa Cantarini", 12, 2020},
                                                {"ING-INF/05", "Architetture degli elaboratori", "Prof. Maltoni", 12, 2020},

                                              };

struct esame
{
    char codice[20];
    int voto;

}  ;

struct studente
{
    char nome[50];
    char cognome[50];
    struct esame piano_studi[NUM_ESAMI];
    char matricola[11];
    int anno_corso;
    //int voto[NUM_INS];

};

struct studente std[MAX_STUD];


int main()
{
    system("pause");

    FILE *f,*f2;
    int ins;
    char tmp_mat[11];
    char sel[11];
    _Bool trovato = false;
    _Bool ok_data = false;
    int selezione = 0, valido = 0, tmp_voto = 0, count = 0, j = 0, k, i;
    struct studente stud, stud_vuoto;


  while (1)
  {


    printf("\n----------------------------------------");
    //strcpy(std[0].piano_studi[0].codice, "PRG-014");
    //printf("\nStudente[0] insegnamento[0] : %s", std[0].piano_studi[0].codice);
    printf("\n----------------------------------------");
    //printf("\nBenvenuto nel gestore corsi di studio!");
    printf("\nSeleziona l'operazione da effettuare: ");
    printf("\n1 - " NEW_INS);
    printf("\n2 - " RIC_MATRICOLA);
    printf("\n3 - " MODIFICA_INFO);
    printf("\n4 - " INFO_MEDIA);
    printf("\nOperazione selezionata: ");
    scanf("%d", &selezione);

    switch(selezione)
    {
        case 1:   ///AGGIUNTA NUOVO STUDENTE///
        {

            printf("\nNumero nuovi inserimenti (max.%d): ", MAX_STUD);
            scanf("%d", &ins);

            if(ins>MAX_STUD)
            {
                printf("\nERRORE! E' possible inserire al massimo %d studenti a sessione.", NUM_INS);
                printf("\n--------------------------------------");
                return(main());
            }
            else
            {
                f = fopen("./DatiStudenti.txt", "a");
                f2 = fopen("./DatiStudenti2.txt", "ab");
                if(f==NULL)
                {
                    printf("\n");
                    printf("\nErrore apertura file.");
                    printf("\n");
                }
                else
                {
                    printf("\nFile aperto o creato correttamente.");
                    printf("\n");
                }
                if(f2==NULL)
                {
                    printf("\n");
                    printf("\nErrore apertura file.");
                    printf("\n");
                }
                else
                {
                    printf("\nFile aperto o creato correttamente.");
                    printf("\n");
                }

                for(i=0; i<ins; i++)
                {

                        printf("\n--------------------------------------");
                        printf("\nINSERIMENTO NUOVO STUDENTE");

                    do       ///verifica che la matricola non sia gi� stata digitata, altrimenti il sistema chiede di ridigitarla
                    {
                        trovato = 0;
                        printf("\nMatricola: ");

                        scanf("%s", tmp_mat);

                            for (count=0; count<ins; count++)
                            {
                                if (tmp_mat == std[count].matricola)
                                {
                                    printf("ATTENZIONE, matricola gia\' inserita!");
                                    trovato = 1;
                                }
                            }

                    } while (trovato != 0);

                    strcpy(std[i].matricola, tmp_mat);
                    fputs(tmp_mat, f);
                    fflush(stdin);

                    //fputs(' ', f);

                    printf("\nNome: ");
                    scanf("%s",std[i].nome);
                    fputs(std[i].nome, f);
                    fflush(stdin);

                    printf("\nCognome: ");
                    scanf("%s", std[i].cognome);
                    fputs(std[i].cognome, f);
                    fflush(stdin);

                    printf("\nAnno immatricolazione: ");
                    scanf("%d", &(std[i].anno_corso));
                    if (std[i].anno_corso < 2021) {
                        char sanno[10];
                        sprintf(sanno, "%d", std[i].anno_corso );
                        fputs( sanno, f);
                        fflush(stdin);
                    }

                    printf("\nEcco gli insegnamenti disponibili per il piano di studi:");
                    for(k = 0; k<NUM_ESAMI; k++)
                    {
                        printf("\n  %s - %s", insegnamenti[k].codice, insegnamenti[k].nome);
                    }


                    trovato = false;
                    printf("\nQuanti insegnamenti vuoi inserire nel piano di studi? (MAX %d)", NUM_ESAMI);
                    scanf("%d", &count);

                    for (k = 0; k<count; k++)
                    {
                        printf("\nDigita codice insegnamento:");
                        scanf("%s", sel);

                        j=0;
                        trovato=false;
                        while (trovato == false)
                        {
                            if(*(sel) == *(insegnamenti[j].codice))
                            {
                                trovato = true;
                                strcpy(std[i].piano_studi[k].codice, sel);
                                std[i].piano_studi[k].voto = ES_NON_SOST;
                                printf("trace 1: %s",std[i].piano_studi[k].codice);
                            }

                          fflush(stdin);
                          j++;

                        }
                     }

                    printf("\n----------------------------------------");
                    printf("\nEcco i dati inseriti per lo studente %2d", i);
                    printf("\nMatricola: %s", std[i].matricola);
                    printf("\nNome: %s", std[i].nome);
                    printf("\nCognome: %s", std[i].cognome);
                    printf("\nAnno immatricolazione: %d", std[i].anno_corso);
                    printf("\nInsegnamenti selezionati:");
                    for(j = 0; j<NUM_ESAMI; j++)
                    {
                        printf("\n >> %s", std[i].piano_studi[j].codice);
                        fflush(stdin);
                    }

                    fwrite (&std[i], sizeof(struct studente), 1, f2);
                    printf("\nDati salvati");
                    fputs("\n", f);
                 }
                    printf("\nCompilazione completata");
                    /*
                    printf("\nSeleziona gli insegnamenti per il piano di studi:");

                    for (int i = 0; i<NUM_INS; i++)
                    {
                        printf(
                               )
                    }
                    */

            }
            printf("\nChiusura dei file");

            fclose(f);
            fclose(f2);
            system("\npause");
            break;
        }
    case 2:     ///RICERCA STUDENTE PER MATRICOLA///
        {
            printf("\n----------------------------------------");
            printf("\nRICERCA STUDENTE PER MATRICOLA");
            fflush(stdin);

            i=0;
            stud = (const struct studente){0};


                f2 = fopen("./DatiStudenti2.txt", "rb");
                if(f2==NULL)
                {
                    perror("\nErrore apertura file.");
                    printf("\n");
                }
                else
                {
                    printf("\nFile aperto o creato correttamente.");
                    printf("\n");
                }

                 printf("\n");
                 printf("\nDigita matricola da ricercare:");
                 scanf("%s", tmp_mat);
                trovato = false;

                while (fread(&stud, sizeof(struct studente), 1, f2))
                {

                     if(strcmp(tmp_mat,stud.matricola) == 0)
                        {
                            trovato = true;
                            printf("\nEcco i dati dello studente [mat. %s]:", stud.matricola);
                            printf("\nNome: %s", stud.nome);
                            printf("\nCognome: %s", stud.cognome);
                            printf("\nVoti per insegnamento:");
                            for(j = 0; j<NUM_ESAMI; j++)
                            {
                                printf("\n[%s]..........[%d]", stud.piano_studi[j].codice, stud.piano_studi[j].voto);
                            }
                            //ATTENZIONE - il programma senza break cicla tutti gli elementi nel vettore a partire da quello ricercato

                        }

                   stud = (const struct studente){0};
                }

                if(trovato == false)
                {
                    printf("\nStudente non trovato o lista studenti vuota.");

                }

            fclose(f2);
             printf("\nFine operazione.");
             system("\npause");

        break;

    }


                //count=i;
//                if (count == 0)
//                {
//                    printf("\n");
//                    printf("\nNessuno studente registrato!");
//                    return(main());
//                }
//                else
//                {
//                    printf("\nNumero studenti attualmente registrati: %d", count);
//
//                    for (i = 0; i<count; i++)
//                    {
//
//                        if(*tmp_mat == *(std[i].matricola))
//                        {
//                            trovato = 1;
//                            printf("\nEcco i dati dello studente:");
//                            printf("\nNome: %s", std[i].nome);
//                            printf("\nCognome: %s", std[i].cognome);
//                        }
//
//                    }
//
//                    if (trovato == 0)
//                    {
//                        printf("\n");
//                        printf("\nAlla matricola [%s] non corrisponde alcuno studente. Riprova...", tmp_mat);
//                    }
//                }


    case 3:  ///MODIFICA INFO STUDENTE (ricerca x matricola)///
             ///7 marzo - sostituzione di std[i] con stud
        {
            i = 0;
            f2 = fopen("./DatiStudenti2.txt", "r+b");
            if (f2 == NULL)
            {
                printf("\nErrore apertura file studenti oppure nessun voto disponibile");
                break;
            }
            else
            {
                printf("\nFile studenti aperto correttamente");
            }

            printf("\n-------------------------------");
            printf("\nINSERISCI VOTI STUDENTE");
            printf("\nDigita matricola:");
            scanf("%s", tmp_mat);
            trovato=false;

            while( fread(&stud, sizeof(struct studente), 1, f2))  //del file f2 leggo una struttura alla volta
            {

                if(strcmp(tmp_mat,stud.matricola) == 0)
                {
                    printf("\nInsegnamenti presenti:");
                    ///Ciclo per stampare tutti gli insegnamenti presenti nel piano di studio dello studente[i]
                     for(j = 0; j<NUM_ESAMI; j++)
                    {
                        printf("\n>>%s %s", stud.matricola, stud.piano_studi[j].codice);

                    }
                    ///lettura codice insegnamento
                    printf("\nPer inserire un voto, digita il codice di riferimento:");
                    scanf("%s", sel);

                    ///ricerca se il codice digitato corrisponde ad un insegnamento;

                     for (k = 0; k<NUM_ESAMI; k++)
                     {
                         ///se il codice corrisponde, si inserisce il voto dell'esame all'insegnamento corrispondente;
                         if(strcmp(sel, stud.piano_studi[k].codice) == 0)
                         {
                             trovato = true;
                             do
                             {
                                 printf("\n>>Voto da assegnare per [%s]:  ", sel);
                                 scanf("%d", &tmp_voto);

                                 if ( (tmp_voto <= VOTOMAX) && (tmp_voto>= VOTOMIN))
                                 {
                                    ok_data = true;
                                    stud.piano_studi[k].voto = tmp_voto;
                                    printf("\n>> Assegnato voto [%d] per [%s] allo studente [%s %s].", stud.piano_studi[k].voto, stud.piano_studi[k].codice, stud.nome, stud.cognome);
                                    fseek(f2,-sizeof(struct studente),SEEK_CUR);
                                    fwrite (&stud, sizeof(struct studente), 1, f2);
                                    fseek(f2,sizeof(struct studente),SEEK_CUR);
                                 }
                                 else
                                    printf("\n !!! --> Il voto dev'essere compreso tra [%d] e [%d]", VOTOMIN, VOTOMAX);

                            } while (ok_data == false);
                       }
                   }
             }


         }

              if(trovato != true)
                {
                    printf("\n !!! --> Lista studenti vuota, oppure la matricola non esiste.");

                }


        fclose(f2);
        printf("\nFine operazione");
        printf("\n");
        system("pause");
        break;
    }

    case 4: ///CALCOLO E STAMPA VOTI PESATI CON CFU///
        {
            f2 = fopen("./ListaStudenti2.txt", "rb");
            if(f2 == NULL)
            {
                printf("\n Errore apertura file");
            }
            else
            {
                printf("\n File aperto correttamente");
            }



            break;
        }


    default:
        {
            printf("\nErrore inserimento codice menu!");
            break;
        }
    }
  }
}
















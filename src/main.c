/*
 * MIT License
 *
 * Copyright (c) 2024-2025 Andrea Michael M. Molino
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "mostri.h"
#include "player.h"
#include "util.h"

#define PW_AUTH "master"


void menu_stampa_classifica(classifica classifica)
{
	system("clear");

	printf_centro(120, 0, "Classifica");
	printf_spazio(2);
	printf_centro(120 , 0, "Personaggio   Classe   N.Avventure       Punti Avventura\n");
	stampa_classifica(classifica);
}


void menu_master(struct giocatore** avventuriero, queue coda_mostri, classifica classifica, struct avventura** avventura)
{
	char buffer[4] = {0};
	char password[21] = {0};
	int scelta = 0;

	system("clear");
	printf_centro(120, 0, "Benvenuto Master");
	printf_centro(120, 0, "Inserire la password:");

	fgets(password, sizeof(password), stdin);
	password[strcspn(password, "\n")] = 0;

	int ret_password = strcmp(password, PW_AUTH);
	if(ret_password != 0){
		printf("[\033[0;31mATTENZIONE\033[0m] Password Errata.\n");
		return;
	}

	while(scelta != 4){
		system("clear");
		
		printf_centro(120, 0, "Funzioni Disponibili:");
		printf("\n");
		printf_centro(120, 0, "1. Crea Avventura");
		printf_centro(120, 0, "2. Classifica");
		printf_centro(120, 0, "3. Giocatori Nel Sistema");
		printf("\n");
		printf_centro(120, 0, "4. Esci");
		
		fgets(buffer, sizeof(buffer), stdin);
		sscanf(buffer, "%d", &scelta);
		
		switch(scelta){
			case 1:
				crea_avventura(coda_mostri, avventura, avventuriero, classifica);
				scelta = 0;
				break;
			
			case 2:
				menu_stampa_classifica(classifica);
				scelta = 0;
				break;
			
			case 3:
				while (scelta != 4){
					system("clear");
					printf_centro(120,0, ".:: Menu ::.");
					printf("\n");
					printf_centro(120,0, "1. Mostra Giocatori");
					printf_centro(120,0, "2. Ricerca Giocatore");
					printf_centro(120,0, "3. Elimina Giocatore");
					printf("\n");
					printf_centro(120,0, "4. Torna Indietro");
					
					fgets(buffer, sizeof(buffer), stdin);
					sscanf(buffer, "%d", &scelta);

					switch(scelta){
						case 1:
							stampa_giocatori_sistema(avventuriero);
							scelta = 0;
							break;

						case 2:
							char nome_giocatore[21];
							printf("Inserire Il Nome Del Personaggio Da Cercare: \n");
							fgets(nome_giocatore, sizeof(nome_giocatore), stdin);
							nome_giocatore[strcspn(nome_giocatore, "\n")] = 0;
							ricerca_player(classifica,nome_giocatore);

							scelta = 0;
							break;

						
						case 3:
							char nome_personaggio_elim[21];
							printf("Inserire Il Nome Del Personaggio Da Eliminare: \n");
							fgets(nome_personaggio_elim, sizeof(nome_personaggio_elim), stdin);
							nome_personaggio_elim[strcspn(nome_personaggio_elim, "\n")] = 0;
							
							elimina_personaggio(avventuriero, nome_personaggio_elim);
							elimina_player(classifica, nome_personaggio_elim);

							scelta = 0;
							break;

						case 4:
							break;
						
						default:
							if(scelta != 0){
								printf("[\033[0;31mATTENZIONE\033[0m] Scelta non supportata\n");
								sleep(3);
								system("clear");
							}
					}
				}
				scelta = 0;
				break;

			case 4:
				printf("Arrivederci... Master\n");
				sleep(3);
				break;

			default:
				if(scelta != 0){
					printf("[\033[0;31mATTENZIONE\033[0m] Scelta non supportata\n");
					sleep(3);
					system("clear");
				}
		}
	}

}



int interfaccia_combattimento(struct giocatore** avventuriero, queue coda_mostri, struct avventura** avventura, classifica classifica)
{
	int azione = 0;
	int flag_titolo = 0;

	int colpo_dado = 0;
	int colpo_dado_mostro = 0;
	int dado_armatura = 0;
	int dado_guarigione = 0;

    //Variabili Mostro
	char arma_mostro[4] [21] = {"Spada","Pugnale","Balestra","Ascia"};
	int iRetNum = -1;
	iRetNum = lancio_d4() - 1;

	char nome_mostro[21] = {0};
	int punti_vita_mostro = 0;
	int punti_vita_mostro_2 = 0, armatura_mostro = 0, exp_mostro = 0, livello_mostro = 0, punti_avventura = 0;

	//Init Mostro
	preleva_mostro(coda_mostri, nome_mostro, &punti_vita_mostro, &armatura_mostro, &exp_mostro, &livello_mostro, &punti_avventura);
	punti_vita_mostro_2 = punti_vita_mostro;

	//Variabili Giocatore
	char nome_player[21] = {0}, nome_classe[21] = {0};
	char nome_arma_personaggio[21] = {0};
	int danno_arma_giocatore = 0, punti_ferita_giocatore = 0, armatura_giocatore = 0, exp_giocatore = 0, livello_giocatore = 0, punti_avventura_giocatore = 0;
	int punti_ferita_giocatore_max = 0, avventure_completate_giocatore = 0;
	
	//Variabili Classifica
	char nome_avventuriero[21] = {0};
	char nome_player_classifica[21] = {0};
	char nome_classifica_player[21] = {0};

	//Init Giocatore
	get_nome_player(avventuriero, nome_player);
	get_nome_classe(avventuriero, nome_classe);
	get_nome_arma(avventuriero, nome_arma_personaggio);
	get_punti_ferita_player(avventuriero, &punti_ferita_giocatore);
	get_armatura_player(avventuriero, &armatura_giocatore);
	get_exp_player(avventuriero, &exp_giocatore);	
	get_punti_avventura_player(avventuriero, &punti_avventura_giocatore);
	get_avventure_player(avventuriero, &avventure_completate_giocatore);
	livello_giocatore = exp_in_livello(avventuriero);	
	punti_ferita_giocatore_max = punti_ferita_giocatore;

	for(;;){

		if(flag_titolo == 0){
			char titolo[21];
			get_avventura_titolo(avventura, titolo);

			printf_centro(120, 0, "Titolo:");
			printf_centro(120, 0, titolo);
			flag_titolo++;
			printf_spazio(3);
			sleep(5);
			system("clear");
		}
		
		if((punti_vita_mostro <= 0) && is_empty_queue(coda_mostri) == 1){
			printf_vittoria();
			printf_centro(120, 1, "Hai Completato L'avventura!!!\n");
			
			get_classfica_nome_giocatore(classifica, nome_classifica_player);
			
			if(strcmp(nome_player, nome_classifica_player) == 0)
				elimina_player(classifica, nome_classifica_player);
			
			inserisci_player(classifica, avventuriero);

			inserisci_punti_avventura(avventuriero, punti_avventura);
			inserisci_avventura_completata(avventuriero);
			
			inserisci_punti_classifica(avventuriero, classifica);
			insersci_avventura_classifica(classifica);
			sleep(5);
			system("clear");
			return 0;
		}

		if(punti_ferita_giocatore <= 0){
			printf_sconfitta();
			printf_spazio(3);
			printf_centro(120, 0, "SEI STATO SCONFITTO");
			sleep(5);

			while(!is_empty_queue(coda_mostri) == 1)
				preleva_mostro(coda_mostri, nome_mostro, &punti_vita_mostro, &armatura_mostro, &exp_mostro, &livello_mostro, &punti_avventura);
			
			break;
		}
		if(punti_vita_mostro <= 0){
			printf_vittoria();
			inserisci_punti_avventura(avventuriero, punti_avventura);
			inserisci_exp(avventuriero, exp_mostro);
			int livello_giocatore = exp_in_livello(avventuriero);
			inserisci_livello_giocatore(avventuriero, livello_giocatore);
			
			preleva_mostro(coda_mostri, nome_mostro, &punti_vita_mostro, &armatura_mostro, &exp_mostro, &livello_mostro, &punti_avventura);
			punti_vita_mostro_2 = punti_vita_mostro;

			char arma_mostro[4] [21] = {"Spada","Pugnale","Balestra","Ascia"};
			iRetNum = lancio_d4() - 1;

		}

		system("clear");
		printf_banner_combat();
		printf_spazio(2);
		printf("		 ___________________________________________________________________________________\n");
		printf("		|	%s	Livello: %d                   |            %s Livello: %d           |\n",nome_player, livello_giocatore, nome_mostro, livello_mostro);
		printf("		|	Armatura: %d                         |            Armatura: %d              |\n",armatura_giocatore, armatura_mostro);
		printf("		|	Vita: %d/%d                           |            Vita: %d/%d               |\n",punti_ferita_giocatore, punti_ferita_giocatore_max, punti_vita_mostro, punti_vita_mostro_2);
		printf("		|	Arma: %s                          |            Arma: %s              |\n",nome_arma_personaggio, arma_mostro[iRetNum]);
		printf("		|___________________________________________________________________________________|\n");
		printf("\n");
		printf_centro(120, 0,"[1] Attacco");
		printf_centro(120, 0,"[2] In Guardia");
		printf_centro(120, 0,"[3] Cura\n");
		printf("Azione -> ");
		scanf("%d", &azione);
		switch(azione){
			case 1:
				colpo_dado = lancio_d20();
				if((colpo_dado >= armatura_mostro) && (colpo_dado_mostro < 20)){

					if(strcmp(nome_arma_personaggio, "Spada") == 0){
						int danno = lancio_d8() + danno_arma_giocatore;
						punti_vita_mostro = punti_vita_mostro - danno;
						printf("Hai Inflitto %d Danni\n",danno);
					}

					if(strcmp(nome_arma_personaggio, "Pugnale") == 0){
						int danno = lancio_d4() + danno_arma_giocatore;
						punti_vita_mostro = punti_vita_mostro - danno;
						printf("Hai Inflitto %d Danni\n",danno);
					}

					if(strcmp(nome_arma_personaggio, "Bastone") == 0){
						int danno = lancio_d6() + danno_arma_giocatore;
						punti_vita_mostro = punti_vita_mostro - danno;
						printf("Hai Inflitto %d Danni\n",danno);
					}
 
					colpo_dado_mostro = lancio_d20();
					if((colpo_dado_mostro  >= armatura_giocatore) && (colpo_dado_mostro < 20)){

						if(strcmp(arma_mostro[iRetNum], "Spada") == 0){
							int danno_mostro = lancio_d8();
							punti_ferita_giocatore = punti_ferita_giocatore - danno_mostro;
							printf("Il Mostro Ti Ha Inflitto %d Danni\n",danno_mostro);
						}

						if(strcmp(arma_mostro[iRetNum], "Pugnale") == 0){
							int danno_mostro = lancio_d4();
							punti_ferita_giocatore = punti_ferita_giocatore - danno_mostro;
							printf("Il Mostro Ti Ha Inflitto %d Danni\n",danno_mostro);
						}

						if(strcmp(arma_mostro[iRetNum], "Balestra") == 0){
							int danno_mostro = lancio_d6();
							punti_ferita_giocatore = punti_ferita_giocatore - danno_mostro;
							printf("Il Mostro Ti Ha Inflitto %d Danni\n",danno_mostro);
						}

						if(strcmp(arma_mostro[iRetNum], "Ascia") == 0){
							int danno_mostro = lancio_d8();
							punti_ferita_giocatore = punti_ferita_giocatore - danno_mostro;
							printf("Il Mostro Ti Ha Inflitto %d Danni\n",danno_mostro);
						}
					}
					
					if(colpo_dado_mostro == 20){

						if(strcmp(arma_mostro[iRetNum], "Spada") == 0){
							int danno_mostro = lancio_d8();
							int danno_mostro_2 = lancio_d8();
							punti_ferita_giocatore = punti_ferita_giocatore - danno_mostro  - danno_mostro_2;
							printf("Il Mostro Ti Ha Inflitto %d Danni\n",danno_mostro + danno_mostro_2);
						}

						if(strcmp(arma_mostro[iRetNum], "Pugnale") == 0){
							int danno_mostro = lancio_d4();
							int danno_mostro_2 = lancio_d4();
							punti_ferita_giocatore = punti_ferita_giocatore - danno_mostro  - danno_mostro_2;
							printf("Il Mostro Ti Ha Inflitto %d Danni\n",danno_mostro + danno_mostro_2);
						}

						if(strcmp(arma_mostro[iRetNum], "Balestra") == 0){
							int danno_mostro = lancio_d6();
							int danno_mostro_2 = lancio_d6();
							punti_ferita_giocatore = punti_ferita_giocatore - danno_mostro  - danno_mostro_2;
							printf("Il Mostro Ti Ha Inflitto %d Danni\n",danno_mostro + danno_mostro_2);
						}

						if(strcmp(arma_mostro[iRetNum], "Ascia") == 0){
							int danno_mostro = lancio_d8();
							int danno_mostro_2 = lancio_d8();
							punti_ferita_giocatore = punti_ferita_giocatore - danno_mostro  - danno_mostro_2;
							printf("Il Mostro Ti Ha Inflitto %d Danni\n",danno_mostro + danno_mostro_2);
						}
					}
					
					if(colpo_dado_mostro < armatura_giocatore){
						printf("Hai Schivato L'Attacco Del Mostro!\n");
					}
				}

				if(colpo_dado == 20){
					printf("Hai Inflitto Un Colpo Critico\n");


					if(strcmp(nome_arma_personaggio, "Spada") == 0){
						int danno = lancio_d8() + danno_arma_giocatore;
						int danno_2 = lancio_d4() + danno_arma_giocatore;
						punti_vita_mostro = punti_vita_mostro - danno - danno_2;
						printf("Hai Inflitto %d Danni\n",danno + danno_2);
					}

					if(strcmp(nome_arma_personaggio, "Pugnale") == 0){
						int danno = lancio_d8() + danno_arma_giocatore;
						int danno_2 = lancio_d6() + danno_arma_giocatore;
						punti_vita_mostro = punti_vita_mostro - danno - danno_2;
						printf("Hai Inflitto %d Danni\n",danno + danno_2);
					}

					if(strcmp(nome_arma_personaggio, "Bastone") == 0){
						int danno = lancio_d6() + danno_arma_giocatore;
						int danno_2 = lancio_d6() + danno_arma_giocatore;
						punti_vita_mostro = punti_vita_mostro - danno - danno_2;
						printf("Hai Inflitto %d Danni\n",danno + danno_2);
					}

					int colpo_dado_mostro = lancio_d20();
					if((colpo_dado_mostro  >= armatura_giocatore) && (colpo_dado_mostro < 20)){

						if(strcmp(arma_mostro[iRetNum], "Spada") == 0){
							int danno_mostro = lancio_d8();
							punti_ferita_giocatore = punti_ferita_giocatore - danno_mostro;
							printf("Il Mostro Ti Ha Inflitto %d Danni\n",danno_mostro);
						}

						if(strcmp(arma_mostro[iRetNum], "Pugnale") == 0){
							int danno_mostro = lancio_d4();
							punti_ferita_giocatore = punti_ferita_giocatore - danno_mostro;
							printf("Il Mostro Ti Ha Inflitto %d Danni\n",danno_mostro);
						}

						if(strcmp(arma_mostro[iRetNum], "Balestra") == 0){
							int danno_mostro = lancio_d6();
							punti_ferita_giocatore = punti_ferita_giocatore - danno_mostro;
							printf("Il Mostro Ti Ha Inflitto %d Danni\n",danno_mostro);
						}

						if(strcmp(arma_mostro[iRetNum], "Ascia") == 0){
							int danno_mostro = lancio_d8();
							punti_ferita_giocatore = punti_ferita_giocatore - danno_mostro;
							printf("Il Mostro Ti Ha Inflitto %d Danni\n",danno_mostro);
						}
					}
					
					if(colpo_dado_mostro == 20){

						if(strcmp(arma_mostro[iRetNum], "Spada") == 0){
							int danno_mostro = lancio_d8();
							int danno_mostro_2 = lancio_d8();
							punti_ferita_giocatore = punti_ferita_giocatore - danno_mostro  - danno_mostro_2;
							printf("Il Mostro Ti Ha Inflitto %d Danni\n",danno_mostro + danno_mostro_2);
						}

						if(strcmp(arma_mostro[iRetNum], "Pugnale") == 0){
							int danno_mostro = lancio_d4();
							int danno_mostro_2 = lancio_d4();
							punti_ferita_giocatore = punti_ferita_giocatore - danno_mostro  - danno_mostro_2;
							printf("Il Mostro Ti Ha Inflitto %d Danni\n",danno_mostro + danno_mostro_2);
						}

						if(strcmp(arma_mostro[iRetNum], "Balestra") == 0){
							int danno_mostro = lancio_d6();
							int danno_mostro_2 = lancio_d6();
							punti_ferita_giocatore = punti_ferita_giocatore - danno_mostro  - danno_mostro_2;
							printf("Il Mostro Ti Ha Inflitto %d Danni\n",danno_mostro + danno_mostro_2);
						}

						if(strcmp(arma_mostro[iRetNum], "Ascia") == 0){
							int danno_mostro = lancio_d8();
							int danno_mostro_2 = lancio_d8();
							punti_ferita_giocatore = punti_ferita_giocatore - danno_mostro  - danno_mostro_2;
							printf("Il Mostro Ti Ha Inflitto %d Danni\n",danno_mostro + danno_mostro_2);
						}
					}
					
					if(colpo_dado_mostro < armatura_giocatore){
						printf("Hai Schivato L'Attacco Del Mostro!\n");
					}

				}
				
				else if(colpo_dado < armatura_mostro){
					printf("Il Tuo Nemico Ha Parato Il Colpo!!!\n");

					int colpo_dado_mostro = lancio_d20();
					if((colpo_dado_mostro  >= armatura_giocatore) && (colpo_dado_mostro < 20)){

						if(strcmp(arma_mostro[iRetNum], "Spada") == 0){
							int danno_mostro = lancio_d8();
							punti_ferita_giocatore = punti_ferita_giocatore - danno_mostro;
							printf("Il Mostro Ti Ha Inflitto %d Danni\n",danno_mostro);
						}

						if(strcmp(arma_mostro[iRetNum], "Pugnale") == 0){
							int danno_mostro = lancio_d4();
							punti_ferita_giocatore = punti_ferita_giocatore - danno_mostro;
							printf("Il Mostro Ti Ha Inflitto %d Danni\n",danno_mostro);
						}

						if(strcmp(arma_mostro[iRetNum], "Balestra") == 0){
							int danno_mostro = lancio_d6();
							punti_ferita_giocatore = punti_ferita_giocatore - danno_mostro;
							printf("Il Mostro Ti Ha Inflitto %d Danni\n",danno_mostro);
						}

						if(strcmp(arma_mostro[iRetNum], "Ascia") == 0){
							int danno_mostro = lancio_d8();
							punti_ferita_giocatore = punti_ferita_giocatore - danno_mostro;
							printf("Il Mostro Ti Ha Inflitto %d Danni\n",danno_mostro);
						}
					}
					
					if(colpo_dado_mostro == 20){

						if(strcmp(arma_mostro[iRetNum], "Spada") == 0){
							int danno_mostro = lancio_d8();
							int danno_mostro_2 = lancio_d8();
							punti_ferita_giocatore = punti_ferita_giocatore - danno_mostro  - danno_mostro_2;
							printf("Il Mostro Ti Ha Inflitto %d Danni\n",danno_mostro + danno_mostro_2);
						}

						if(strcmp(arma_mostro[iRetNum], "Pugnale") == 0){
							int danno_mostro = lancio_d4();
							int danno_mostro_2 = lancio_d4();
							punti_ferita_giocatore = punti_ferita_giocatore - danno_mostro  - danno_mostro_2;
							printf("Il Mostro Ti Ha Inflitto %d Danni\n",danno_mostro + danno_mostro_2);
						}

						if(strcmp(arma_mostro[iRetNum], "Balestra") == 0){
							int danno_mostro = lancio_d6();
							int danno_mostro_2 = lancio_d6();
							punti_ferita_giocatore = punti_ferita_giocatore - danno_mostro  - danno_mostro_2;
							printf("Il Mostro Ti Ha Inflitto %d Danni\n",danno_mostro + danno_mostro_2);
						}

						if(strcmp(arma_mostro[iRetNum], "Ascia") == 0){
							int danno_mostro = lancio_d8();
							int danno_mostro_2 = lancio_d8();
							punti_ferita_giocatore = punti_ferita_giocatore - danno_mostro  - danno_mostro_2;
							printf("Il Mostro Ti Ha Inflitto %d Danni\n",danno_mostro + danno_mostro_2);
						}
					}
					
					if(colpo_dado_mostro < armatura_giocatore){
						printf("Hai Schivato L'Attacco Del Mostro!\n");
					}
				}
				sleep(3);
				break;

			case 2:
				dado_armatura = lancio_d6();
				colpo_dado_mostro = lancio_d20();

				if(colpo_dado_mostro  >= armatura_giocatore + dado_armatura){

					if(strcmp(arma_mostro[iRetNum], "Spada") == 0){
						int danno_mostro = lancio_d8();
						punti_ferita_giocatore = punti_ferita_giocatore - danno_mostro;
						printf("Il Mostro Ti Ha Inflitto %d Danni\n",danno_mostro);
					}

					if(strcmp(arma_mostro[iRetNum], "Pugnale") == 0){
						int danno_mostro = lancio_d4();
						punti_ferita_giocatore = punti_ferita_giocatore - danno_mostro;
						printf("Il Mostro Ti Ha Inflitto %d Danni\n",danno_mostro);
					}

					if(strcmp(arma_mostro[iRetNum], "Balestra") == 0){
						int danno_mostro = lancio_d6();
						punti_ferita_giocatore = punti_ferita_giocatore - danno_mostro;
						printf("Il Mostro Ti Ha Inflitto %d Danni\n",danno_mostro);
					}

					if(strcmp(arma_mostro[iRetNum], "Ascia") == 0){
						int danno_mostro = lancio_d8();
						punti_ferita_giocatore = punti_ferita_giocatore - danno_mostro;
						printf("Il Mostro Ti Ha Inflitto %d Danni\n",danno_mostro);
					}
				}
					
				if(colpo_dado_mostro == 20){

					if(strcmp(arma_mostro[iRetNum], "Spada") == 0){
						int danno_mostro = lancio_d8();
						int danno_mostro_2 = lancio_d8();
						punti_ferita_giocatore = punti_ferita_giocatore - danno_mostro  - danno_mostro_2;
						printf("Il Mostro Ti Ha Inflitto %d Danni\n",danno_mostro + danno_mostro_2);
					}

					if(strcmp(arma_mostro[iRetNum], "Pugnale") == 0){
						int danno_mostro = lancio_d4();
						int danno_mostro_2 = lancio_d4();
						punti_ferita_giocatore = punti_ferita_giocatore - danno_mostro  - danno_mostro_2;
						printf("Il Mostro Ti Ha Inflitto %d Danni\n",danno_mostro + danno_mostro_2);
					}

					if(strcmp(arma_mostro[iRetNum], "Balestra") == 0){
						int danno_mostro = lancio_d6();
						int danno_mostro_2 = lancio_d6();
						punti_ferita_giocatore = punti_ferita_giocatore - danno_mostro  - danno_mostro_2;
						printf("Il Mostro Ti Ha Inflitto %d Danni\n",danno_mostro + danno_mostro_2);
					}

					if(strcmp(arma_mostro[iRetNum], "Ascia") == 0){
						int danno_mostro = lancio_d8();
						int danno_mostro_2 = lancio_d8();
						punti_ferita_giocatore = punti_ferita_giocatore - danno_mostro  - danno_mostro_2;
						printf("Il Mostro Ti Ha Inflitto %d Danni\n",danno_mostro + danno_mostro_2);
					}
				}
					
				if(colpo_dado_mostro < armatura_giocatore + dado_armatura){
					printf("Hai Parato Il Colpo.\n");
				}
				
				sleep(3);
				break;

			case 3:

				dado_guarigione = lancio_d8();
				printf("Ti Sei Curato Di %d\n", dado_guarigione);
				punti_ferita_giocatore = punti_ferita_giocatore + dado_guarigione;

				int colpo_dado_mostro = lancio_d20();
				if((colpo_dado_mostro  >= armatura_giocatore) && (colpo_dado_mostro < 20)){

					if(strcmp(arma_mostro[iRetNum], "Spada") == 0){
						int danno_mostro = lancio_d8();
						punti_ferita_giocatore = punti_ferita_giocatore - danno_mostro;
						printf("Il Mostro Ti Ha Inflitto %d Danni\n",danno_mostro);
					}

					if(strcmp(arma_mostro[iRetNum], "Pugnale") == 0){
						int danno_mostro = lancio_d4();
						punti_ferita_giocatore = punti_ferita_giocatore - danno_mostro;
						printf("Il Mostro Ti Ha Inflitto %d Danni\n",danno_mostro);
					}

					if(strcmp(arma_mostro[iRetNum], "Balestra") == 0){
						int danno_mostro = lancio_d6();
						punti_ferita_giocatore = punti_ferita_giocatore - danno_mostro;
						printf("Il Mostro Ti Ha Inflitto %d Danni\n",danno_mostro);
					}

					if(strcmp(arma_mostro[iRetNum], "Ascia") == 0){
						int danno_mostro = lancio_d8();
						punti_ferita_giocatore = punti_ferita_giocatore - danno_mostro;
						printf("Il Mostro Ti Ha Inflitto %d Danni\n",danno_mostro);
					}
				}
					
				if(colpo_dado_mostro == 20){

					if(strcmp(arma_mostro[iRetNum], "Spada") == 0){
						int danno_mostro = lancio_d8();
						int danno_mostro_2 = lancio_d8();
						punti_ferita_giocatore = punti_ferita_giocatore - danno_mostro  - danno_mostro_2;
						printf("Il Mostro Ti Ha Inflitto %d Danni\n",danno_mostro + danno_mostro_2);
					}

					if(strcmp(arma_mostro[iRetNum], "Pugnale") == 0){
						int danno_mostro = lancio_d4();
						int danno_mostro_2 = lancio_d4();
						punti_ferita_giocatore = punti_ferita_giocatore - danno_mostro  - danno_mostro_2;
						printf("Il Mostro Ti Ha Inflitto %d Danni\n",danno_mostro + danno_mostro_2);
					}

					if(strcmp(arma_mostro[iRetNum], "Balestra") == 0){
						int danno_mostro = lancio_d6();
						int danno_mostro_2 = lancio_d6();
						punti_ferita_giocatore = punti_ferita_giocatore - danno_mostro  - danno_mostro_2;
						printf("Il Mostro Ti Ha Inflitto %d Danni\n",danno_mostro + danno_mostro_2);
					}

					if(strcmp(arma_mostro[iRetNum], "Ascia") == 0){
						int danno_mostro = lancio_d8();
						int danno_mostro_2 = lancio_d8();
						punti_ferita_giocatore = punti_ferita_giocatore - danno_mostro  - danno_mostro_2;
						printf("Il Mostro Ti Ha Inflitto %d Danni\n",danno_mostro + danno_mostro_2);
					}
				}
					
				if(colpo_dado_mostro < armatura_giocatore){
					printf("Hai Schivato L'Attacco Del Mostro!\n");
				}

				sleep(3);
				break;

			default:
				printf("[\033[0;31mATTENZIONE\033[0m] Azione Non Valida.\n");
				sleep(3);
		}
    }
	return 0;
}


bool crea_personaggio(struct giocatore** avventuriero)
{
	char nome_personaggio[21] = {0};
	char password[21] = {0};
	char nome_classe_personaggio[21] = {0}, nome_arma_personaggio[21] = {0};
	int classe = 0, punti_ferita_personaggio = 0, armatura_personaggio = 0;


	system("clear");
	printf_centro(120, 0, "Creazione Personaggio");
	printf("\n");
	printf("Inserisci Il Nickname:\n");
	fgets(nome_personaggio, sizeof(nome_personaggio), stdin);
	fgets(nome_personaggio, sizeof(nome_personaggio), stdin);
	nome_personaggio[strcspn(nome_personaggio, "\n")] = 0;
	
	/*if(cerca_personaggio(avventuriero, nome_personaggio) == 0){
		printf("[\033[0;31mATTENZIONE\033[0m] Personaggio Gia' Esistente.\n");
		sleep(3);
		//system("clear");
		return false;
	}*/
	
	printf("\n");
	printf("Inserisci La Classe:\n");
	printf("1. Guerriero\n");
	printf("2. Ladro\n");
	printf("3. Mago\n");
	scanf("%d",&classe);
	
	if(classe == 1){
		strcpy(nome_classe_personaggio, "Guerriero");
		strcpy(nome_arma_personaggio, "Spada");
		punti_ferita_personaggio = 10;
		armatura_personaggio = 17;
	}

	if(classe == 2){
		strcpy(nome_classe_personaggio, "Ladro");
		strcpy(nome_arma_personaggio, "Pugnale");
		punti_ferita_personaggio = 8;
		armatura_personaggio = 17;
	}

	if(classe == 3){
		strcpy(nome_classe_personaggio, "Mago");
		strcpy(nome_arma_personaggio, "Bastone");
		punti_ferita_personaggio = 6;
		armatura_personaggio = 17;
	}

	printf("\n");
	printf("Inserire La Password:\n");
	fgets(password, sizeof(password), stdin);
	fgets(password, sizeof(password), stdin);
	password[strcspn(password, "\n")] = 0;

	
	int iRet_PG = inserisci_personaggio(avventuriero, password, nome_personaggio, nome_classe_personaggio, nome_arma_personaggio, 0, punti_ferita_personaggio, armatura_personaggio, 0, 0);
    
	if(iRet_PG == 0){
		printf_centro(125, 0, "[\033[32mOK\033[0m] Personaggio Creato Con Successo!!!");
		sleep(3);
	}

	return true;
}

void menu_avventuriero(struct giocatore** avventuriero, queue coda_mostri, struct avventura** avventura, classifica classifica)
{
	char buffer[3] = {0};
	int scelta = 0;
	
	while(scelta != 99){
		char nome_personaggio[21] = {0};
		get_nome_player(avventuriero, nome_personaggio);
		system("clear");

		printf_centro(119, 1, "Benvenuto ");
		printf("%s\n", nome_personaggio);
		printf("\n");
		printf_centro(120, 0, "1. Nuova Avventura");
		printf_centro(120, 0, "2. Classifica");
		printf("\n");
		printf_centro(120, 0, "3. Esci");
		
		fgets(buffer, sizeof(buffer), stdin);
		sscanf(buffer, "%d",&scelta);
		
		switch(scelta){
			case 1:
				if(is_empty_queue(coda_mostri) == 1){
					system("clear");
					printf_centro(120, 1, "Nessuna Avventura Disponibile\n");
					sleep(5);
					scelta = 0;
					break;
				}
				interfaccia_combattimento(avventuriero, coda_mostri, avventura, classifica);
				scelta = 0;
				break;
			
			case 2:
				menu_stampa_classifica(classifica);
				scelta = 0;
				break;
			
			case 3:
				printf("Arrivederci... Avventuriero\n");
				sleep(3);
				break;
			
			default:
				if(scelta != 0){
					printf("[\033[0;31mATTENZIONE\033[0m] Scelta non supportata\n");
					sleep(3);
					system("clear");
				}
		}
	}
}

void pre_menu_avventuriero(struct giocatore** avventuriero, queue coda_mostri, struct avventura** avventura, struct classifica** classifica)
{
	char buffer[3] = {0}; 
	char nome_player[21] = {0};
	char password[21] = {0};
	int opzione = 0;
	int flag_pw_errata = 0;

	while(opzione != 3){
		system("clear");
		printf_centro(120, 0, "Benvenuto Avventuriero");
		printf("\n");
		printf_centro(120, 0, "[1] Continua Con Un Personaggio gia esistente");
		printf_centro(120, 0, "[2] Crea Personaggio");
		printf("\n");
		printf_centro(120, 0, "[3] Esci");
		printf("\n");

		fgets(buffer, sizeof(buffer), stdin);
		sscanf(buffer, "%d", &opzione);

		switch(opzione){
			case 1:
				system("clear");
				printf("Inserisci Il Nome Del Personaggio:\n");
				fgets(nome_player, sizeof(nome_player), stdin);
				nome_player[strcspn(nome_player, "\n")] = 0;
				
				int iRet_Pg = cerca_personaggio(avventuriero, nome_player);

				if(iRet_Pg == 1){
					printf("[\033[0;31mATTENZIONE\033[0m] Nome Del Personaggio Non Valido O Inesistente\n");
					sleep(3);
					opzione = 0;
					break;
				}

				printf("Inserisci La Password Del Personaggio:\n");
				fgets(password, sizeof(password), stdin);
				password[strcspn(password, "\n")] = 0;
				int IRet_Pw = login(avventuriero, password);

				if(IRet_Pw == 1){
					if(flag_pw_errata == 3){
						printf("[\033[0;31mATTENZIONE\033[0m] Tentativi Esauriti\n");
						sleep(3);
						return;
					}

					printf("[\033[0;31mATTENZIONE\033[0m] Password Errata\n");
					sleep(3);
					flag_pw_errata++;

				}

				else{
					printf_centro(125, 1, "[\033[32mOK\033[0m] Dati Corretti Caricamento Personaggio...\n");
					sleep(3);
				
					menu_avventuriero(avventuriero, coda_mostri, avventura, classifica);
					opzione = 0;
					break;
				}
				
				opzione = 0;
				break;
			case 2:
				if(crea_personaggio(avventuriero)){
					return;
				}
				else{
					opzione = 0;
					break;
				}
			
			case 3:
				printf_centro(120, 1, "Arrivederci... Avventuriero\n");
				sleep(3);
				break;
			
			default:
				if(opzione != 0){
					printf("[\033[0;31mATTENZIONE\033[0m] Scelta non supportata\n");
					sleep(3);
					system("clear");
				}
		}

	}
}

void menu_principale(struct giocatore** avventuriero, queue coda_mostri, classifica classifica, struct avventura** avventura)
{
	char buffer[3] = {0};
	int scelta = 0;

	while(scelta != 3){
		system("clear");
		printf_spazio(2);
		print_banner();
		printf_spazio(3);
		printf_centro(120, 0, "BENVENUTO PLAYER");
		printf_spazio(1);
		printf_centro(120, 0, "Scegli Il tuo Ruolo:");
		printf("\n");
		printf_centro(120, 0, "1. Master");
		printf_centro(120, 0, "2. Avventuriero");
		printf("\n");
		printf_centro(120, 0, "3. Esci");
		
		fgets(buffer, sizeof(buffer), stdin);
		sscanf(buffer, "%d", &scelta);
		
		switch(scelta){
			
			case 1:
				menu_master(avventuriero, coda_mostri, classifica, avventura);
				scelta = 0;//reset
				break;
			
			case 2:
				pre_menu_avventuriero(avventuriero, coda_mostri, avventura, classifica);
				scelta = 0;//reset
				break;
			
			case 3:
				break;
			
			default:
				if(scelta != 0){
					printf("[\033[0;31mATTENZIONE\033[0m] Scelta non supportata\n");
					sleep(3);
					system("clear");
				}
		}
	}
	printf("Chiusura del gioco in corso...\n");
	sleep(3);
}

void cleanup(struct giocatore** avventuriero, queue coda_mostri, classifica classifica, struct avventura** avventura)
{
	char ctitolo_avventura[21] = {0};

	salva_classifica(classifica);

	if(!(*avventura)->titolo){
		get_avventura_titolo(avventura, ctitolo_avventura);
		salva_avventura(coda_mostri, ctitolo_avventura);
	}

	while(!is_empty_queue(coda_mostri) == 1){
		char nome_mob[21];
		int punti_vita = 0, armatura = 0, exp = 0, livello = 0, punti_avventura = 0;		
		
		preleva_mostro(coda_mostri, nome_mob, &punti_vita, &armatura, &exp, &livello, &punti_avventura);
	}

	while(!is_empty(avventuriero) == 1){
		if((*avventuriero)->next == NULL) break;
		
		char nome_avventuriero[21] = {0};
		
		get_nome_player(avventuriero, nome_avventuriero);
		//printf("\n[DEBUG] Nome Player: %s\n", nome_avventuriero);
		elimina_personaggio(avventuriero, nome_avventuriero);
		(*avventuriero)->next;
	}
	
	while(!is_empty_classifica(classifica) == 1){
		if((*classifica)->testa == NULL && (*classifica)->testa->next == NULL) break;
		
		char nome_avventuriero[21] = {0};
		
		get_classfica_nome_giocatore(classifica, nome_avventuriero);
		elimina_player(classifica, nome_avventuriero);
		(*classifica)->testa->next;
	}

	free(*avventuriero);
	free(coda_mostri);
	free(*classifica);
	free(*avventura);

}

int main(void)
{
	char titolo_avventura[21] = {0};
	
	system("clear");
	srand(time(NULL));

	struct giocatore* avventuriero = crea_lista_personaggi();
	controllo_malloc(avventuriero);

	struct classifica* classifica = crea_classifica();
	controllo_malloc(classifica);

	queue coda_mostri = crea_coda_mostri();
	controllo_malloc(coda_mostri);

	struct avventura* avventura = (struct avventura*)malloc(sizeof(struct avventura));
	controllo_malloc(avventura);
	
	bool avventura_caricata = carica_avventura_file(coda_mostri, titolo_avventura);
	if(avventura_caricata)
		inserisci_titolo_avventura(&avventura, titolo_avventura);
	
	menu_principale(&avventuriero, coda_mostri, &classifica, &avventura);

	cleanup(&avventuriero, coda_mostri, &classifica, &avventura);

	return 0;
}

//Creato Da Michael
#ifndef PLAYER_H
#define PLAYER_H
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "util.h"
#include "mostri.h"

enum iRet_Player_def
{
	SUCCESSO = 0, //SUCCESSO GENERALE
	ERRORE_AVV_VUOTO = 1,
	ERRORE_GENERICO = -1,
	ERRORE_MALLOC = -2, //ERRORE NELLA MALLOC
	MAGIC_ERROR = -9, //ERRORE MAGICO
	PG_NOT_FOUND  = 2
};

//struttura giocatore
struct giocatore{
	char password[21];
	char nome_player[21];
	char nome_classe[11];
	char nome_arma[21];
	int danno_arma;
	int punti_ferita;
	int armatura;
	int exp, livello;
	int punti_avventura;
	int avventure_completate;

	struct giocatore* next;
};

struct nodo{
	char nome_giocatore[21];
	char classe_giocatore[21];
	int avventure_svolte;
	int punti_avventura;

	struct nodo* next;
	struct nodo* prec;	
};

struct classifica{
	struct nodo* testa;
	struct nodo* coda;
};

typedef struct classifica** classifica;

struct avventura{
	char titolo[21];
};

int crea_avventura(queue coda_mostri, struct avventura** avventura, struct giocatore** avventuriero, classifica classifica);
int exp_in_livello(struct giocatore** avventuriero);

//Giocatore
struct giocatore* crea_lista_personaggi();
int inserisci_personaggio(struct giocatore** avventuriero, char* password, char* nome_player, char* nome_classe, char* nome_arma, int danno_arma, int punti_ferita, int armatura, int exp, int punti_avventura);
int elimina_personaggio(struct giocatore** avventuriero, char* nome_player);
int cerca_personaggio(struct giocatore** avventuriero, char* nome_player);
int login(struct giocatore** avventuriero, char* password);
int stampa_giocatori_sistema(struct giocatore** avventuriero);
int is_empty(struct giocatore** avventuriero);

//Giocatore
int get_nome_player(struct giocatore** avventuriero, char* nome_player);
int get_nome_classe(struct giocatore** avventuriero, char* nome_classe);
int get_nome_arma(struct giocatore** avventuriero, char* nome_arma);
int get_punti_ferita_player(struct giocatore** avventuriero, int* punti_ferita);
int get_armatura_player(struct giocatore** avventuriero, int* armatura);
int get_exp_player(struct giocatore** avventuriero, int* exp);
int get_punti_avventura_player(struct giocatore** avventuriero, int* punti_avventura);
int get_avventure_player(struct giocatore** avventuriero, int* avventure_completate);
int inserisci_avventura_completata(struct giocatore** avventuriero);
int inserisci_punti_avventura(struct giocatore** avventuriero, int punti);
int inserisci_exp(struct giocatore** avventuriero, int exp);
int inserisci_livello_giocatore(struct giocatore** avventuriero, int livello);

//Classifica
int get_classfica_nome_giocatore(classifica classifica, char* nome_giocatore);
int inserisci_punti_classifica(struct giocatore** avventuriero, classifica lista_classifica);
int insersci_avventura_classifica(classifica lista_classifica);

//Avventura
int get_avventura_titolo(struct avventura** avventura, char* titolo);
int inserisci_titolo_avventura(struct avventura** avventura, char* titolo);


//Classifica
struct classifica* crea_classifica();
int inserisci_player(classifica lista_classifica, struct giocatore** avventuriero);
int elimina_player(classifica lista_classifica, char* parametro_nome_player);
int ricerca_player(classifica classifica, char* parametro_nome_player);
int stampa_classifica(classifica lista_classifica);
int is_empty_classifica(classifica lista_classifica);
int clean_classifica(classifica lista_classifica);
int salva_classifica(classifica lista_classifica);

#endif

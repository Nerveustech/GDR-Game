//Creato Da Michael
#ifndef MOSTRI_H
#define MOSTRI_H
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct mostri{
	char nome_mostro[21];
	int punti_vita;
	int armatura;
	int exp, livello;
	int punti_avventura;
	struct mostri* next;
};

struct queue{
	struct mostri* head;
	struct mostri* tail;
};

typedef struct queue* queue;

queue crea_coda_mostri();
int inserisci_mostro(queue coda, char* parametro_nome_mostro, int parametro_punti_vita, int parametro_armatura, int parametro_exp, int livello, int punti_avventura);
int preleva_mostro(queue coda, char* parametro_nome_mostro, int* parametro_punti_vita , int* parametro_armatura, int* parametro_exp, int* parametro_livello, int* parametro_punti_avventura);
int is_empty_queue(queue coda);
void print_coda(queue coda);
int salva_avventura(queue coda, char* titolo_avventura);
int carica_avventura_file(queue coda, char* titolo_avventura);
#endif

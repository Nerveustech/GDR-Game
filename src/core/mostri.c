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

#include "../../include/core/mostri.h"

queue crea_coda_mostri(){
    queue coda_mostri = (queue)malloc(sizeof(struct queue));
    if(coda_mostri == NULL) return NULL;

    coda_mostri->head = NULL;
    coda_mostri->tail = NULL;

    return coda_mostri;
}

int inserisci_mostro(queue coda, char* parametro_nome_mostro, int parametro_punti_vita, int parametro_armatura, int parametro_exp, int parametro_livello, int punti_avventura){
    if(coda == NULL) return 1;

    struct mostri* mostro = (struct mostri*)malloc(sizeof(struct mostri));
    if(mostro == NULL) return 1;
    
    strcpy(mostro->nome_mostro, parametro_nome_mostro);
    mostro->punti_vita = parametro_punti_vita;
    mostro->armatura = parametro_armatura;
    mostro->exp = parametro_exp;
    mostro->livello = parametro_livello;
    mostro->punti_avventura = punti_avventura;

    mostro->next = NULL;
    if(is_empty_queue(coda) == 1)
        coda->head = mostro;
    else
        coda->tail->next = mostro;
    coda->tail = mostro;
    return 0;

}

int preleva_mostro(queue coda, char* parametro_nome_mostro, int* parametro_punti_vita , int* parametro_armatura, int* parametro_exp, int* parametro_livello, int* parametro_punti_avventura){

    if(coda == NULL) return 2;
    if(is_empty_queue(coda) == 1) return 1;

    strcpy(parametro_nome_mostro, coda->head->nome_mostro);
    *parametro_punti_vita = coda->head->punti_vita;
    *parametro_armatura = coda->head->armatura;
    *parametro_exp = coda->head->exp;
    *parametro_livello = coda->head->livello;
    *parametro_punti_avventura = coda->head->punti_avventura;

    struct mostri* temp = coda->head;
    if(coda->head->next == NULL)
        coda->tail = NULL;
    coda->head = coda->head->next;
    free(temp);
    return 0;
}

int is_empty_queue(queue coda){
    if(coda == NULL) return 2;

    if(coda->head == NULL && coda->tail == NULL)
        return 1;
    else
        return 0;
}

void print_coda(queue coda){
    if(coda == NULL)
        printf("Coda non correttamente creata!\n");
    if(is_empty_queue(coda) == 1)
        printf("Coda vuota!\n");

    printf("Mostri Attualmente In Coda:\n");
    
    struct mostri* p = coda->head;
    while(p != NULL){
        printf("Nome Mostro: %s\n Punti Vita: %d\n Armatura: %d\n Exp: %d\n Punti Avventura:%d\n\n", p->nome_mostro, p->punti_vita, p->armatura, p->exp, p->punti_avventura);
        p = p->next;			
    } 
    printf("\n");
}

int salva_avventura(queue coda, char* titolo_avventura){
    if(coda == NULL) return -1;
    if(is_empty_queue(coda) == 1) return -1;

    FILE* fpCoda;
    fpCoda = fopen("Avventura.txt","w");
    if(fpCoda == NULL) return -1;

    fprintf(fpCoda, "%s\n", titolo_avventura);

    struct mostri* pCoda = coda->head;
    while(pCoda != NULL){
        fprintf(fpCoda, "%s %d %d %d %d %d\n", pCoda->nome_mostro, pCoda->punti_vita, pCoda->armatura, pCoda->exp, pCoda->livello, pCoda->punti_avventura);
        pCoda = pCoda->next;
    }

    fclose(fpCoda);
    return 0;
}


bool carica_avventura_file(queue coda, char* titolo_avventura){
    char nome_mostro[21];
    char ctitolo_avventura[21];
    int punti_vita = 0, armatura = 0, exp = 0, livello = 0, punti_avventura = 0;
    
    FILE* fpCoda;
    fpCoda = fopen("Avventura.txt","r");
    if(fpCoda == NULL) return false;

    fscanf(fpCoda, "%s\n", ctitolo_avventura);
    strcpy(titolo_avventura, ctitolo_avventura);

    struct mostri* pCoda = coda->head;
    while(fscanf(fpCoda, "%s %d %d %d %d %d\n", nome_mostro, &punti_vita, &armatura, &exp, &livello, &punti_avventura) != EOF){
        inserisci_mostro(coda, nome_mostro, punti_vita, armatura, exp, livello, punti_avventura);
    }
    fclose(fpCoda);
    
    if(remove("Avventura.txt") != 0){
        return false;
    }

    return true;
}
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

#include "../../include/core/player.h"

struct giocatore* crea_lista_personaggi(){

    struct giocatore* player;
    player = (struct giocatore*)malloc(sizeof(struct giocatore));
    
    if(player == NULL)
        return NULL;
    
    else{
        
        strcpy(player->password, "dummypass");
        strcpy(player->nome_player, "dummy");
        strcpy(player->nome_classe, "classe_dummy");
        strcpy(player->nome_arma, "dummy_arma");

        player->danno_arma = 0;
        player->punti_ferita = 1;
        player->armatura = 1;
        player->exp = 0;
        player->punti_avventura = 0;

        player->next = NULL;


        return player;
    }
}


int inserisci_personaggio(struct giocatore** avventuriero, char* password, char* nome_player, char* nome_classe, char* nome_arma, int danno_arma, int punti_ferita, int armatura, int exp, int punti_avventura){
    struct giocatore* player = NULL;
    
    player = (struct giocatore*)malloc(sizeof(struct giocatore));
    if(player == NULL) return 1;

    strcpy(player->password, password);
    strcpy(player->nome_player, nome_player);
    strcpy(player->nome_classe, nome_classe);
    strcpy(player->nome_arma, nome_arma);

    
    player->danno_arma = danno_arma;
    player->punti_ferita = punti_ferita;
    player->armatura = armatura;
    player->exp = exp;
    player->punti_avventura = punti_avventura;
    player->avventure_completate = 0;

    player->next = *avventuriero;
    *avventuriero = player;

    return 0;

}

int elimina_personaggio(struct giocatore** avventuriero, char* nome_player){
    struct giocatore* pPrec = *avventuriero;
    struct giocatore* pSucc = *avventuriero;

    if(is_empty(avventuriero) == 1){
        printf_centro(120, 0, "Personaggio Non Presente!");
        return 1;
    }
    if((*avventuriero)->next == NULL){
        printf_centro(120, 0, "Personaggio Non Presente!");
        return 1;
    }

    while((pSucc != NULL) && (strcmp(pSucc->nome_player, nome_player) != 0)){
        pPrec = pSucc;
        pSucc = pSucc->next;
    }
    if(strcmp(pSucc->nome_player, nome_player) == 0){
        if(pSucc == *avventuriero){
            *avventuriero = pSucc->next;
            free(pSucc);
            return 0;
        }
        pPrec->next = pSucc->next;
        free(pSucc);
        return 0;
    }
    else
        return 1;
}

int cerca_personaggio(struct giocatore** avventuriero, char* nome_player){
    if(is_empty(avventuriero) == 1) return 2;

    while(1){

        if((*avventuriero)->next == NULL){
            break;
        }

        if((avventuriero != NULL) && strcmp((*avventuriero)->nome_player, nome_player) != 0)
            *(avventuriero) = (*avventuriero)->next;
        
        if(strcmp((*avventuriero)->nome_player, nome_player) == 0)
            return 0;
        
        if(avventuriero == NULL)
            break;
    }
    return 1;
}


int login(struct giocatore** avventuriero, char* password){
    if(is_empty(avventuriero) == 1) return 2;
    if(strlen(password) > 21) return 1;

    if(strcmp((*avventuriero)->password, password) == 0)
        return 0;
    else
        return 1;
}


int stampa_giocatori_sistema(struct giocatore** avventuriero){
    if(is_empty(avventuriero) == 1) return 2;

    //system("clear");
    printf_centro(120, 1, "Giocatori/Personaggi Presenti Nel Sistema:\n");

    while(avventuriero != NULL){
        if((*avventuriero)->next == NULL){
            break;
        }

        printf("%s\n", (*avventuriero)->nome_player);
        *(avventuriero) = (*avventuriero)->next;
    }
    printf("\n");
    return 0;
}

int is_empty(struct giocatore** avventuriero){
    if(*avventuriero == NULL)
        return 1;
    else
        return 0;
}

//classifica
struct classifica* crea_classifica(){
    struct classifica* class;
    
    class = (struct classifica*)malloc(sizeof(struct classifica));
    if(class == NULL) return NULL;

    class->testa = NULL;
    class->coda = NULL;

    return class;
}

int inserisci_player(classifica lista_classifica, struct giocatore** avventuriero){
    if(is_empty(avventuriero) == 1) return 2;
    
        
    if((*avventuriero)->next == NULL){
        return 1;
    }

    struct nodo* new_player;

    new_player = (struct nodo*)malloc(sizeof(struct nodo));
    if(new_player == NULL) return 1;

    strcpy(new_player->nome_giocatore, (*avventuriero)->nome_player);
    strcpy(new_player->classe_giocatore, (*avventuriero)->nome_classe);
    new_player->avventure_svolte = (*avventuriero)->avventure_completate;
    new_player->punti_avventura = (*avventuriero)->punti_avventura;


    struct nodo* tmp = (*lista_classifica)->testa;

    if(is_empty_classifica(lista_classifica) == 1){
        new_player->next = NULL;
        new_player->prec = NULL;
        (*lista_classifica)->testa = new_player;
        (*lista_classifica)->coda = new_player;
        return 0;
    }

    while((tmp != NULL) && (tmp->avventure_svolte) < (new_player->avventure_svolte))
        tmp = tmp->next;

    if(tmp == (*lista_classifica)->testa){
        (*lista_classifica)->testa = new_player;
        tmp->prec = new_player;
        new_player->next = tmp;
        new_player->prec = NULL;
            
    }
    else if(tmp == NULL){
        (*lista_classifica)->coda->next = new_player;
        new_player->prec = (*lista_classifica)->coda;
        new_player->next = NULL;
        (*lista_classifica)->coda = new_player;
            
    }
    else{
        new_player->next = tmp;
        new_player->prec = tmp->prec;
        tmp->prec->next = new_player;
        tmp->prec = new_player;
            
    }
    return 0;
}

int elimina_player(classifica lista_classifica, char* parametro_nome_player){
    if(is_empty_classifica(lista_classifica) == 1) return 1;

    struct nodo* pDelete = (*lista_classifica)->testa;

    while((pDelete != NULL) && (strcmp(pDelete->nome_giocatore, parametro_nome_player) != 0))
        pDelete = pDelete->next;
    
    if(pDelete == NULL) return 1;

    if(strcmp(pDelete->nome_giocatore, parametro_nome_player) == 0){
        if((pDelete == (*lista_classifica)->testa) && (pDelete == (*lista_classifica)->coda)){
            (*lista_classifica)->coda = NULL;
            (*lista_classifica)->testa = NULL;
        }
        else if(pDelete == (*lista_classifica)->testa){
            (*lista_classifica)->testa->next->prec = NULL;
            (*lista_classifica)->testa = (*lista_classifica)->testa->next;
        }
        else if(pDelete == (*lista_classifica)->coda){
            (*lista_classifica)->coda->prec->next = NULL;
            (*lista_classifica)->coda = (*lista_classifica)->coda->prec;
        }
        else{
            pDelete->prec->next = pDelete->next;
            pDelete->next->prec = pDelete->prec;
        }
        
    }
    free(pDelete);
    return 0;

}

int ricerca_player(classifica classifica, char* parametro_nome_player){
    if(is_empty_classifica(classifica) == 1){ 
        printf_centro(120, 0, "[\033[0;31mATTENZIONE\033[0m] Classifica Non Presente!!!");
        sleep(3);
        system("clear");
        return 2;
    }
    
    while((classifica != NULL) && (strcmp((*classifica)->testa->nome_giocatore, parametro_nome_player) != 0)){
        (*classifica)->testa->next;
    }

    if(strcmp((*classifica)->testa->nome_giocatore, parametro_nome_player) == 0){
        system("clear");
        printf_centro(120, 1, "Personaggio Trovato!\n");
        printf("Nome: %s \n", (*classifica)->testa->nome_giocatore);
        printf("Avventure: %d \n", (*classifica)->testa->avventure_svolte);
        printf("Punti Avventura: %d \n", (*classifica)->testa->punti_avventura);
        sleep(3);
        system("clear");
        return 0;
    }
    else{
        printf("Personaggio Non Trovato!\n");
        sleep(3);
        system("clear");
        return 1;
    }
}


int stampa_classifica(classifica lista_classifica){
    if(is_empty_classifica(lista_classifica) == 1) return 2;

    struct nodo* tmp=(*lista_classifica)->testa;
    if(tmp == NULL) return 1;

    while(tmp != NULL){
        printf("                               %s          %s        %d            %d\n", tmp->nome_giocatore, tmp->classe_giocatore, tmp->avventure_svolte, tmp->punti_avventura);
        tmp = tmp->next;
    }
    printf("\n");
}

int clean_classifica(classifica lista_classifica){
    if(is_empty_classifica(lista_classifica) == 1) return 2;
    char nome_player[21];

    struct nodo* clean = (*lista_classifica)->testa;
    if(clean == NULL) return 1;

    while(clean != NULL){
        if(clean->next == NULL) return 1;

        get_classfica_nome_giocatore(lista_classifica, nome_player);
        elimina_player(lista_classifica, nome_player);
        
        clean = clean->next;
    }
    return 0;
}

int is_empty_classifica(classifica lista_classifica){
    if((*lista_classifica)->testa == NULL)
        return 1;
    else
        return 0;
}

int salva_classifica(classifica lista_classifica){
    if(is_empty_classifica(lista_classifica) == 1) return -1;
    
    FILE* fpClassifica;
    fpClassifica = fopen("Classifica.txt","w");
    if(fpClassifica == NULL) return -1;

    struct nodo* pnClassfica = (*lista_classifica)->testa;
    if(pnClassfica == NULL) return 1;

    fprintf(fpClassifica, "%s  %s  %s  %s\n", "Nome Player", "Classe Player", "Avv. Svolte", "Punti Avventura");

    while(pnClassfica != NULL){
        fprintf(fpClassifica, "%s   ||   %s   ||   %d   ||   %d\n", pnClassfica->nome_giocatore, pnClassfica->classe_giocatore, pnClassfica->avventure_svolte, pnClassfica->punti_avventura);
        pnClassfica = pnClassfica->next;
    }

    fclose(fpClassifica);
    return 0;
}

int exp_in_livello(struct giocatore** avventuriero){
    int livello_convertito = 1;
    int livello_exp;

    livello_exp = (*avventuriero)->exp;
    if (livello_exp >= 300){
        livello_convertito++;
    };
        if (livello_exp >= 900){
            livello_convertito++;
        };
            if (livello_exp >= 2700){
                livello_convertito++;
            };
                if (livello_exp >= 6500){
                    livello_convertito++;
                };
                    if (livello_exp >= 14000){
                        livello_convertito++;
                    };
                        if (livello_exp >= 23000){
                            livello_convertito++;
                        };
                            if (livello_exp >= 34000){
                                livello_convertito++;
                            };
                                if (livello_exp >= 48000){
                                    livello_convertito++;
                                };
                                    if (livello_exp == 64000){
                                        livello_convertito++;
                                    };
    return livello_convertito;
}


int crea_avventura(queue coda_mostri, struct avventura** avventura, struct giocatore** avventuriero, classifica classifica){
    char titolo_avventura[21];
    int mostro_scelto = -1;

    system("clear");

    printf_centro(120, 0, "Menu Creazione Avventura");
    printf_spazio(3);
    printf("Inserire Il Titolo Dell'Avventura:\n");
    fgets(titolo_avventura, sizeof(titolo_avventura), stdin);
    fgets(titolo_avventura, sizeof(titolo_avventura), stdin);
    titolo_avventura[strcspn(titolo_avventura, "\n")] = 0;
    strcpy((*avventura)->titolo, titolo_avventura);

    while(mostro_scelto != 99 || mostro_scelto != 0){
        system("clear");
        printf_centro(120, 0, "Menu Mostri");
        printf_spazio(2);
        printf_mostri();
        scanf("%d",&mostro_scelto);

        if(mostro_scelto == 1){
            int iRetMostro = inserisci_mostro(coda_mostri, "Iena", 5, 11, 10, 1, 1);
            if(iRetMostro == 0)
                printf("Mostro Inserito\n");
            sleep(3);
        }

        if(mostro_scelto == 2){
            int iRetMostro = inserisci_mostro(coda_mostri, "Lupo", 11, 13, 50, 1, 1);
            if(iRetMostro == 0)
                printf("Mostro Inserito\n");
            sleep(3);
        }

        if(mostro_scelto == 3){
            int iRetMostro = inserisci_mostro(coda_mostri, "Zombie", 22, 8, 50, 2, 2);
            if(iRetMostro == 0)
                printf("Mostro Inserito\n");
            sleep(3);
        }

        if(mostro_scelto == 4){
            int iRetMostro = inserisci_mostro(coda_mostri, "Goblin", 7, 15, 50, 2, 2);
            if(iRetMostro == 0)
                printf("Mostro Inserito\n");
            sleep(3);
        }

        if(mostro_scelto == 5){
            int iRetMostro = inserisci_mostro(coda_mostri, "Scheletro", 13, 13, 50, 2, 2);
            if(iRetMostro == 0)
                printf("Mostro Inserito\n");
            sleep(3);
        }

        if(mostro_scelto == 6){
            int iRetMostro = inserisci_mostro(coda_mostri, "Banshee", 58, 12, 100, 4, 15);
            if(iRetMostro == 0)
                printf("Mostro Inserito\n");
            sleep(3);
        }

        if(mostro_scelto == 7){
            int iRetMostro = inserisci_mostro(coda_mostri, "Fantasma", 45, 11, 100, 4, 15);
            if(iRetMostro == 0)
                printf("Mostro Inserito\n");
            sleep(3);
        }

        if(mostro_scelto == 8){
            int iRetMostro = inserisci_mostro(coda_mostri, "Armatura Animata", 33, 18, 200, 4, 20);
            if(iRetMostro == 0)
                printf("Mostro Inserito\n");
            sleep(3);
        }

        if(mostro_scelto == 9){
            int iRetMostro = inserisci_mostro(coda_mostri, "Assassino", 28, 17, 150, 5, 25);
            if(iRetMostro == 0)
                printf("Mostro Inserito\n");
            sleep(3);
        }

        if(mostro_scelto == 10){
            int iRetMostro = inserisci_mostro(coda_mostri, "Golem Di Pietra", 178, 17, 900, 10, 100);
            if(iRetMostro == 0)
                printf("Mostro Inserito\n");
            sleep(3);
        }

        if(mostro_scelto == 11){
            int iRetMostro = inserisci_mostro(coda_mostri, "BeHolder", 189, 18, 10000, 13, 200);
            if(iRetMostro == 0)
                printf("Mostro Inserito\n");
            sleep(3);
        }

        if(mostro_scelto == 12){
            int iRetMostro = inserisci_mostro(coda_mostri, "Lich", 135, 17, 33000, 21, 300);
            if(iRetMostro == 0)
                printf("Mostro Inserito\n");
            sleep(3);
        }

        if(mostro_scelto == 13){
            int iRetMostro = inserisci_mostro(coda_mostri, "Illithilich", 135, 17, 41000, 22, 300);
            if(iRetMostro == 0)
                printf("Mostro Inserito\n");
            sleep(3);
        }

        if(mostro_scelto == 14){
            int iRetMostro = inserisci_mostro(coda_mostri, "Drago Oro", 546, 22, 62000, 50, 500);
            if(iRetMostro == 0)
                printf("Mostro Inserito\n");
            sleep(3);
        }

        if(mostro_scelto == 15){
            int iRetMostro = inserisci_mostro(coda_mostri, "Alucard", 2048, 20, 99999, 99, 800);
            if(iRetMostro == 0)
                printf("Mostro Inserito\n");
            sleep(3);
        }

        if(mostro_scelto == 0)
            return 0;

        if(mostro_scelto == 98){
            char nome_mostro_custom[21];
            int vita_mostro_custom, armatura_mostro_custom, exp_mostro_custom, punti_avventura_mostro_custom, livello_mostro_custom;

            system("clear");
            printf("Inserire Il Nome del Mostro:\n");
            fgets(nome_mostro_custom, sizeof(nome_mostro_custom), stdin);
            fgets(nome_mostro_custom, sizeof(nome_mostro_custom), stdin);
            nome_mostro_custom[strcspn(nome_mostro_custom, "\n")] = 0;

            printf("Inserire La Vita Del Mostro:\n");
            scanf("%d",&vita_mostro_custom);

            printf("Inserire L'Armatura Del Mostro:\n");
            scanf("%d",&armatura_mostro_custom);

            printf("Inserire L'Esperienza Ottenuta Dal Mostro:\n");
            scanf("%d",&exp_mostro_custom);
            
            printf("Inserire Il Livello Del Mostro:\n");
            scanf("%d",&livello_mostro_custom);

            printf("Inserire I Punti Avventura Ottenuti Dal Mostro:\n");
            scanf("%d",&punti_avventura_mostro_custom);

            inserisci_mostro(coda_mostri, nome_mostro_custom, vita_mostro_custom, armatura_mostro_custom, exp_mostro_custom, livello_mostro_custom, punti_avventura_mostro_custom);
        }

        if(mostro_scelto == 99){
            char nome_mob;
            int punti_vita = 0, armatura = 0, exp = 0, livello = 0, punti_avventura = 0;

            while(!is_empty_queue(coda_mostri) == 1)
                preleva_mostro(coda_mostri, &nome_mob, &punti_vita, &armatura, &exp, &livello, &punti_avventura);

            
            break;
        }
    }
}

//Player
int get_nome_player(struct giocatore** avventuriero, char* nome_player){
    if(is_empty(avventuriero) == 1) return 2;
    if(nome_player == NULL) return MAGIC_ERROR;

    strcpy(nome_player, (*avventuriero)->nome_player);
    return 0;
}

int get_nome_classe(struct giocatore** avventuriero, char* nome_classe){
    if(is_empty(avventuriero) == 1) return 2;
    if(nome_classe == NULL) return MAGIC_ERROR;

    strcpy(nome_classe, (*avventuriero)->nome_classe);
    return 0;
}

int get_nome_arma(struct giocatore** avventuriero, char* nome_arma){
    if(is_empty(avventuriero) == 1) return 2;
    if(nome_arma == NULL) return MAGIC_ERROR;

    strcpy(nome_arma, (*avventuriero)->nome_arma);
    return 0;
}

int get_punti_ferita_player(struct giocatore** avventuriero, int* punti_ferita){
    if(is_empty(avventuriero) == 1) return 2;

    *punti_ferita = (*avventuriero)->punti_ferita;
    return 0;
}

int get_armatura_player(struct giocatore** avventuriero, int* armatura){
    if(is_empty(avventuriero) == 1) return 2;

    *armatura = (*avventuriero)->armatura;
    return 0;
}

int get_exp_player(struct giocatore** avventuriero, int* exp){
    if(is_empty(avventuriero) == 1) return 2;

    *exp = (*avventuriero)->exp;
    return 0;
}

int get_punti_avventura_player(struct giocatore** avventuriero, int* punti_avventura){
    if(is_empty(avventuriero) == 1) return 2;

    *punti_avventura = (*avventuriero)->punti_avventura;
    return 0;
}

int get_avventure_player(struct giocatore** avventuriero, int* avventure_completate){
    if(is_empty(avventuriero) == 1) return 2;

    *avventure_completate = (*avventuriero)->avventure_completate;
    return 0;
}

int inserisci_avventura_completata(struct giocatore** avventuriero){
    if(is_empty(avventuriero) == 1) return 2;

    (*avventuriero)->avventure_completate++;
    return 0;
}

int inserisci_punti_avventura(struct giocatore** avventuriero, int punti){
    if(is_empty(avventuriero) == 1) return 2;
    if(punti <= 0) return MAGIC_ERROR;//errore magico

    (*avventuriero)->punti_avventura = (*avventuriero)->punti_avventura + punti;
    return 0;
}

int inserisci_exp(struct giocatore** avventuriero, int exp){
    if(is_empty(avventuriero) == 1) return 2;
    if(exp <= 0) return MAGIC_ERROR;//errore magico

    (*avventuriero)->exp = (*avventuriero)->exp + exp;
    return 0;
}

int inserisci_livello_giocatore(struct giocatore** avventuriero, int livello){
    if(is_empty(avventuriero) == 1) return 2;
    if(livello <= 0) return MAGIC_ERROR;//errore magico

    (*avventuriero)->livello = livello;
    return 0;
}

//Classifica
int get_classfica_nome_giocatore(classifica classifica, char* nome_giocatore){
    if(is_empty_classifica(classifica) == 1) return 2;


    strcpy(nome_giocatore, (*classifica)->testa->nome_giocatore);
    return 0;
}

int inserisci_punti_classifica(struct giocatore** avventuriero, classifica lista_classifica){
    if(is_empty(avventuriero) == 1) return 1;
    if((*avventuriero)->punti_avventura <= 0) return MAGIC_ERROR;//errore magico

    (*lista_classifica)->testa->punti_avventura = (*avventuriero)->punti_avventura;
    return 0;
}

int insersci_avventura_classifica(classifica lista_classifica){
    if(is_empty_classifica(lista_classifica) == 1) return 1;

    (*lista_classifica)->testa->avventure_svolte++;
    return 0;
}

//Avventura
int get_avventura_titolo(struct avventura** avventura, char* titolo){
    if(avventura == NULL) return 2;

    strcpy(titolo, (*avventura)->titolo);
    return 0;
}

int inserisci_titolo_avventura(struct avventura** avventura, char* titolo){
    strcpy((*avventura)->titolo, titolo);
    return 0;
}
//Creato Da Michael
#ifndef UTIL_H
#define UTIL_H
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "mostri.h"
#include "player.h"

int lancio_d4();
int lancio_d6();
int lancio_d8();
int lancio_d20();


int printf_spazio(int num);
void printf_centro(int spazio, int preset, char* buffer);
void printf_mostri();
void print_banner();
void printf_sconfitta();
void printf_banner_combat();
void printf_vittoria();

#endif
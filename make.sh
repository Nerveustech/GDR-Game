#!/bin/bash

gcc -c -g mostri.c
gcc -c -g player.c
gcc -c -g util.c
gcc -c -g main.c
gcc -o gioco main.o mostri.o player.o util.o
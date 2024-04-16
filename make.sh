#!/bin/bash

set -xe

GCC_FLAGS="-c -g"

compile(){
    gcc $GCC_FLAGS src/mostri.c src/player.c src/util.c src/main.c
    gcc -o ./gioco main.o mostri.o player.o util.o
}

cleanup(){
    rm -rf main.o mostri.o player.o util.o
}

compile
cleanup
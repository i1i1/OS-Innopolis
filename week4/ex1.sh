#!/bin/sh
gcc -Wall -Wextra -o ex1 ex1.c
for i in $(seq 10); do
    echo
    echo TRY $i
    echo
    ./ex1
done

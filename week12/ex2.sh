#!/bin/sh
gcc ex2.c -o ex2
cat /proc/cpuinfo | ./ex2 ex2.txt

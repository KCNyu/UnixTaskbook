#!/bin/bash

cd ../
./recomplie.sh

cd sample
../TaskChecker -t B14 -l ch -p ../test/B14.c
echo "Press enter for the next test"
read -n 1
../TaskChecker -t D1 -p ../test/D1.c -l ru
echo "Press enter for the next test"
read -n 1
../TaskChecker -t D6 -p ../test/D6.c -l ru
echo "Press enter for the next test"
read -n 1
../TaskChecker -t C14 -p ../test/C14_t.c -l ch
echo "Press enter for the next test"
read -n 1
../TaskChecker -t D4 -p ../test/D4.c
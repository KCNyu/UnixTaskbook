#!/bin/bash

cd ../
./recomplie.sh

cd sample
../TaskChecker -t D4 -p ../test/D4.c

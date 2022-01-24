#!/bin/bash

cd ../
./recomplie.sh

cd sample
../TaskChecker -t D6 -p ../test/D6.c -l ru

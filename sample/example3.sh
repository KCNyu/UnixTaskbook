#!/bin/bash

cd ../
./recomplie.sh

cd sample
../TaskChecker -t D1 -p ../test/D1.c -l ru

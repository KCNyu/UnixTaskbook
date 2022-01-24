#!/bin/bash

cd ../
./recomplie.sh

cd sample
../TaskChecker -t C14 -p ../test/C14.c -l ch

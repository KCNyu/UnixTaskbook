#!/bin/bash

cd ../
./recomplie.sh

cd sample
../TaskChecker -t B14 -l ch -p ../test/B14.c

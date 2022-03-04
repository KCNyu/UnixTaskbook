#!/bin/bash

cd ../
./recomplie.sh

cd sample
for ((i = 1; i <= 16; i++)); do
	taskchecker -t C$i
	taskchecker -t C$i -l ch
done

#!/bin/bash

cd ../
./recomplie.sh

cd sample
for ((i = 1; i <= 17; i++)); do
	taskchecker -t B$i
	taskchecker -t B$i -l ch
done

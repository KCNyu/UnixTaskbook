#!/bin/bash

cd ../
./recomplie.sh

cd sample
for ((i = 1; i <= 9; i++)); do
	taskchecker -t A$i
	taskchecker -t A$i -l ch
done
#!/bin/bash

cd ../
./recomplie.sh

cd sample
for ((i = 1; i <= 9; i++)); do
	unixTaskbook -t D$i
	unixTaskbook -t D$i -l ch
done

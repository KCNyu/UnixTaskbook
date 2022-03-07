#!/bin/bash

cd ../
./recomplie.sh

cd sample
for ((i = 1; i <= 16; i++)); do
	unixTaskbook -t C$i
	unixTaskbook -t C$i -l ch
done

#!/bin/bash

cd ../
./recomplie.sh

cd sample
for ((i = 1; i <= 17; i++)); do
	unixTaskbook -t B$i
	unixTaskbook -t B$i -l ch
done

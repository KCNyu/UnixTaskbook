#!/bin/bash

cd ../
./recomplie.sh

cd sample
for ((i = 1; i <= 9; i++)); do
	unixTaskbook -t A$i
	unixTaskbook -t A$i -l ch
done
#!/bin/bash

for((i = 1; i <= 16; i++))
do
	../TaskChecker -t C$i
	../TaskChecker -t C$i -l ch
done
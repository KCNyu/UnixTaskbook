#!/bin/bash

for((i = 1; i <= 9; i++))
do
	../TaskChecker -t D$i
	../TaskChecker -t D$i -l ch
done
#!/bin/bash

for((i = 1; i <= 17; i++))
do
	../TaskChecker -t B$i
	../TaskChecker -t B$i -l ch
done
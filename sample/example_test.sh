#!/bin/bash

cd ../
sudo ./recomplie.sh

cd sample

unixTaskbook -t B14 -l ch -p ../test/B14.c
echo "Press enter for the next test"
read -n 1

unixTaskbook -t D1 -p ../test/D1.c -l ru
echo "Press enter for the next test"
read -n 1

unixTaskbook -t D6 -p ../test/D6.c -l ru
echo "Press enter for the next test"
read -n 1

unixTaskbook -t C14 -p ../test/C14_t.c -l ch
echo "Press enter for the next test"
read -n 1

unixTaskbook -t D4 -p ../test/D4.c
echo "Press enter for the next test"
read -n 1

unixTaskbook -t A9 -p ../test/A9.c
echo "Press enter for the next test"
read -n 1

unixTaskbook -t E8 -p ../test/E8.c
echo "Press enter for the next test"
read -n 1

echo
echo "All existing test files passed the test!!!" 
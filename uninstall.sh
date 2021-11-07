#!/bin/bash

if [ -d lib ]
then
    cd lib
else
    echo -e "\e[1;33mlib not exist! \e[0m"; exit 1;
fi

WORKSPACE=$(pwd)
echo -e "\e[1;34mWORKSPACE:${WORKSPACE}\e[0m"

make clean

cd ..
WORKSPACE=$(pwd)
echo -e "\e[1;34mWORKSPACE:${WORKSPACE}\e[0m"
make clean

rm -rf /usr/local/lib/TaskChecker

if ! [ -a /etc/ld.so.conf.d/taskchecker.conf ]
then
	rm /etc/ld.so.conf.d/taskchecker.conf
fi

echo -e "\e[1;32mUninstall completed!\e[0m"
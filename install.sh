#!/bin/bash

mkdir obj

if [ -d lib ]
then
    cd lib
else
    echo -e "\e[1;33mlib not exist! \e[0m"; exit 1;
fi

WORKSPACE=$(pwd)
echo -e "\e[1;34mWORKSPACE:${WORKSPACE}\e[0m"

echo -e "\e[1;33mDynamic library file is being compiled\e[0m"

if  ! make
then
    echo -e "\e[1;33m make failed! \e[0m"; exit 1;
else
    if ! [ -d /usr/local/lib/TaskChecker ]; then mkdir /usr/local/lib/TaskChecker; fi;\
    cp ./*.so /usr/local/lib/TaskChecker;
fi

if ! [ -a /etc/ld.so.conf.d/taskchecker.conf ]
then
    cp ./taskchecker.conf /etc/ld.so.conf.d;
fi

if ! ldconfig
then
    echo "config error"
fi

echo -e "\e[1;32mDynamic library installation and configuration completed\e[0m"

cd ..
WORKSPACE=$(pwd)
echo -e "\e[1;34mWORKSPACE:${WORKSPACE}\e[0m"

echo -e "\e[1;33mCompile the project kernel\e[0m"
if ! make
then
    echo -e "\e[1;33m make failed! \e[0m"; exit 1;
fi
echo -e "\e[1;32mCompiling the project kernel is complete\e[0m"

echo -e "\e[1;32mInstall completed!\e[0m"

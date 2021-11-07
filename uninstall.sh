#!/bin/bash

NORMAL=$(tput sgr0)
RED=$(tput setaf 1)
GREEN=$(
	tput setaf 2
	tput bold
)
YELLOW=$(tput setaf 3)
BLUE=$(tput setaf 4)

function red() {
	echo -e "$RED$*$NORMAL"
}

function green() {
	echo -e "$GREEN$*$NORMAL"
}

function yellow() {
	echo -e "$YELLOW$*$NORMAL"
}

function blue() {
	echo -e "$BLUE$*$NORMAL"
}

if [ -d lib ]; then
	cd lib
else
	red "lib not exist!"
	exit 1
fi

WORKSPACE=$(pwd)
blue "WORKSPACE: ${WORKSPACE}"

if ! make clean; then
	red "make failed!"
	exit 1
fi

cd ..
WORKSPACE=$(pwd)
blue "WORKSPACE: ${WORKSPACE}"

if ! make clean; then
	red "make failed!"
	exit 1
fi

if [ "$(uname)" == "Linux" ]; then
	rm -rf /usr/local/lib/TaskChecker

	if ! [ -a /etc/ld.so.conf.d/taskchecker.conf ]; then
		rm /etc/ld.so.conf.d/taskchecker.conf
	fi
elif [ "$(uname)" == "Darwin" ]; then
	echo "ababa"
fi
green "Uninstall completed!"

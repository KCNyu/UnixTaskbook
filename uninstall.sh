#!/bin/bash

FLINES="========================================="
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

function printWorkSpace() {
	echo $FLINES
	WORKSPACE=$(pwd)
	blue "WORKSPACE: ${WORKSPACE}"
	echo $FLINES
}

if [ -d lib ]; then
	cd lib
else
	red "lib not exist!"
	exit 1
fi

printWorkSpace

if ! make clean; then
	red "make failed!"
	exit 1
fi

cd ..
printWorkSpace

if ! make clean; then
	red "make clean failed!"
	exit 1
fi

if [ "$(uname)" == "Linux" ]; then
	if [ -d /usr/local/lib/TaskChecker ]; then
		rm -rf /usr/local/lib/TaskChecker
	fi
	if [ -a /etc/ld.so.conf.d/taskchecker.conf ]; then
		rm /etc/ld.so.conf.d/taskchecker.conf
	fi
elif [ "$(uname)" == "Darwin" ]; then

	files=$(ls *.so | wc -l)

	if (($files != 0)); then
		rm /usr/local/lib/libtask*.so
	fi

fi
green "Uninstall completed!"

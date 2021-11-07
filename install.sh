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
yellow "Dynamic library file is being compiled"

if ! [ -d obj ]; then mkdir obj; fi
if ! make; then
	red "make failed!"
	exit 1
fi
if [ "$(uname)" == "Linux" ]; then

	if ! [ -d /usr/local/lib/TaskChecker ]; then mkdir /usr/local/lib/TaskChecker; fi

	cp ./*.so /usr/local/lib/TaskChecker

	if ! [ -a /etc/ld.so.conf.d/taskchecker.conf ]; then cp ./taskchecker.conf /etc/ld.so.conf.d; fi

	if ! ldconfig; then
		echo "config error"
		exit 1
	fi

elif [ "$(uname)" == "Darwin" ]; then
	cp ./*.so /usr/local/lib/
fi

green "Dynamic library installation and configuration completed"

cd ..
printWorkSpace

yellow "Compile the project kernel"
if ! [ -d obj ]; then mkdir obj; fi
if ! make; then
	red "make failed!"
	exit 1
fi

green "Compiling the project kernel is complete"

green "Install success!"

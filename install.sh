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

yellow "Dynamic library file is being compiled"

if ! [ -d obj ]; then mkdir obj; fi
if ! make; then
	red "make failed!"
	exit 1
fi
if [ "$(uname)"=="Linux" ]; then

	if ! [ -d /usr/local/lib/TaskChecker ]; then mkdir /usr/local/lib/TaskChecker; fi

	cp ./*.so /usr/local/lib/TaskChecker

	if ! [ -a /etc/ld.so.conf.d/taskchecker.conf ]; then cp ./taskchecker.conf /etc/ld.so.conf.d; fi

	if ! ldconfig; then
		echo "config error"
		exit 1
	fi

	green "Dynamic library installation and configuration completed"

	cd ..
	WORKSPACE=$(pwd)
	blue "WORKSPACE: ${WORKSPACE}"

	yellow "Compile the project kernel"
	if ! [ -d obj ]; then mkdir obj; fi
	if ! make; then
		red "make failed!"
		exit 1
	fi

	green "Compiling the project kernel is complete"
	green "Install completed!"

elif [ "$(uname)"=="Darwin" ]; then
fi

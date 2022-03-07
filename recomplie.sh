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
	if [ -d /usr/local/lib/UnixTaskbook ]; then
		rm -rf /usr/local/lib/UnixTaskbook
	fi
	if [ -a /etc/ld.so.conf.d/unixTaskbook.conf ]; then
		rm /etc/ld.so.conf.d/unixTaskbook.conf
	fi

elif [ "$(uname)" == "Darwin" ]; then
	if [ -d /usr/local/lib ]; then
		cd /usr/local/lib
	else
		exit 1
	fi
	printWorkSpace

	files=$(ls libtask*.so | wc -l)

	if (($files != 0)); then
		rm /usr/local/lib/libtask*.so
	fi

	cd -
fi

if [ -a /usr/local/bin/unixTaskbook ]; then
	rm /usr/local/bin/unixTaskbook
fi

green "Uninstall completed!"

if [ -d lib ]; then
	cd lib
else
	red "lib not exist!"
	exit 1
fi

printWorkSpace
yellow "Dynamic library file is being compiled"

if ! [ -d obj ]; then mkdir obj; fi
if ! [ -d ../shared/obj ]; then mkdir ../shared/obj; fi
if ! make; then
	red "make failed!"
	exit 1
fi

if [ "$(uname)" == "Linux" ]; then

	if ! [ -d /usr/local/lib/UnixTaskbook ]; then mkdir /usr/local/lib/UnixTaskbook; fi

	cp ./*.so /usr/local/lib/UnixTaskbook

	if ! [ -a /etc/ld.so.conf.d/unixTaskbook.conf ]; then cp ./unixTaskbook.conf /etc/ld.so.conf.d; fi

	if ! ldconfig; then
		red "config error"
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

if ! [ -a /usr/local/bin/unixTaskbook ]; then
	cp ./unixTaskbook /usr/local/bin
fi

green "Install success!"

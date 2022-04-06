#!/bin/bash

GREEN=$(
	tput setaf 2
	tput bold
)
function green() {
	echo -e "$GREEN$*$NORMAL"
}

if [ "$(uname)" == "Linux" ]; then
	if [ -d /usr/local/lib/UnixTaskbook ]; then
		sudo rm -rf /usr/local/lib/UnixTaskbook
	fi
	if [ -a /etc/ld.so.conf.d/unixTaskbook.conf ]; then
		sudo rm /etc/ld.so.conf.d/unixTaskbook.conf
	fi
elif [ "$(uname)" == "Darwin" ]; then
	if [ -d /usr/local/lib ]; then
		cd /usr/local/lib
	else
		exit 1
	fi

	files=$(ls libutb*.dylib | wc -l)

	if (($files != 0)); then
		sudo rm /usr/local/lib/libutb*.dylib
	fi

fi

if [ -a /usr/local/bin/unixTaskbook ]; then
	sudo rm /usr/local/bin/unixTaskbook
fi

green "Uninstall completed!"

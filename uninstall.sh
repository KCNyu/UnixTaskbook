#!/bin/bash

GREEN=$(
	tput setaf 2
	tput bold
)
function green() {
	echo -e "$GREEN$*$NORMAL"
}

if [ "$(uname)" == "Linux" ]; then
	if [ -d /usr/local/lib/TaskChecker ]; then
		rm -rf /usr/local/lib/TaskChecker
	fi
	if [ -a /etc/ld.so.conf.d/taskchecker.conf ]; then
		rm /etc/ld.so.conf.d/taskchecker.conf
	fi
elif [ "$(uname)" == "Darwin" ]; then
	if [ -d /usr/local/lib ]; then
		cd /usr/local/lib
	else
		exit 1
	fi

	files=$(ls libtask*.so | wc -l)

	if (($files != 0)); then
		rm /usr/local/lib/libtask*.so
	fi

fi

if [ -a /usr/local/bin/taskchecker ]; then
	rm /usr/local/bin/taskchecker
fi

green "Uninstall completed!"

#!/bin/bash
NORMAL=$(tput sgr0)
RED=$(tput setaf 1)
GREEN=$(
	tput setaf 2
	tput bold
)

function red() {
	echo -e "$RED$*$NORMAL"
}

function green() {
	echo -e "$GREEN$*$NORMAL"
}

if [ "$(uname)" == "Linux" ]; then

	if [ "$(arch)" == "x86_64" ]; then

		curl -L https://github.com/KCNyu/TaskChecker/releases/download/v1.0.0/TaskChecker-linux-x86_64.tar.gz > TaskChecker-linux-x86_64.tar.gz

		tar -zxvf TaskChecker-linux-x86_64.tar.gz

		cd TaskChecker-linux-x86_64

	elif [ "$(arch)" == "arm64" ]; then

		curl -L https://github.com/KCNyu/TaskChecker/releases/download/v1.0.0/TaskChecker-linux-arm64.tar.gz > TaskChecker-linux-arm64.tar.gz

		tar -zxvf TaskChecker-linux-arm64.tar.gz

		cd TaskChecker-linux-arm64

	fi

	if ! [ -d /usr/local/lib/TaskChecker ]; then sudo mkdir /usr/local/lib/TaskChecker; fi

	sudo cp ./*.so /usr/local/lib/TaskChecker

	if ! [ -a /etc/ld.so.conf.d/taskchecker.conf ]; then sudo cp ./taskchecker.conf /etc/ld.so.conf.d; fi

	if ! sudo ldconfig; then
		red "config error"
		exit 1
	fi

elif [ "$(uname)" == "Darwin" ]; then

	if ["$(arch)" == "x86_64" ]; then

		curl -L https://github.com/KCNyu/TaskChecker/releases/download/v1.0.0/TaskChecker-drawin-x86_64.tar.gz > TaskChecker-drawin-x86_64.tar.gz

		tar -zxvf TaskChecker-drawin-x86_64.tar.gz

		cd TaskChecker-drawin-x86_64

	elif [ "$(arch)" == "arm64" ]; then

		curl -L https://github.com/KCNyu/TaskChecker/releases/download/v1.0.0/TaskChecker-drawin-arm64.tar.gz > TaskChecker-drawin-arm64.tar.gz

		tar -zxvf TaskChecker-drawin-arm64.tar.gz

		cd TaskChecker-drawin-arm64
	fi

	sudo cp ./*.so /usr/local/lib/

fi

if ! [ -a /usr/local/bin/taskchecker ]; then

	sudo cp ./taskchecker /usr/local/bin

	sudo chmod +x /usr/local/bin/taskchecker
fi

green "Install success!"

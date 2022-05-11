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

		curl -L https://github.com/KCNyu/UnixTaskbook/releases/download/v1.0.0/UnixTaskbook-Linux-x86_64.tar.gz > UnixTaskbook-Linux-x86_64.tar.gz

		tar -zxvf UnixTaskbook-Linux-x86_64.tar.gz

		cd UnixTaskbook-Linux-x86_64

	elif [ "$(arch)" == "arm64" ]; then

		curl -L https://github.com/KCNyu/UnixTaskbook/releases/download/v1.0.0/UnixTaskbook-Linux-arm64.tar.gz > UnixTaskbook-Linux-arm64.tar.gz

		tar -zxvf UnixTaskbook-Linux-arm64.tar.gz

		cd UnixTaskbook-Linux-arm64

	fi

	if ! [ -d /usr/local/lib/UnixTaskbook ]; then sudo mkdir /usr/local/lib/UnixTaskbook; fi

	sudo cp ./*.so /usr/local/lib/UnixTaskbook

	if ! [ -a /etc/ld.so.conf.d/unixTaskbook.conf ]; then sudo cp ./unixTaskbook.conf /etc/ld.so.conf.d; fi

	if ! sudo ldconfig; then
		red "config error"
		exit 1
	fi

elif [ "$(uname)" == "Darwin" ]; then

	if ["$(arch)" == "x86_64" ]; then

		curl -L https://github.com/KCNyu/UnixTaskbook/releases/download/v1.0.0/UnixTaskbook-Darwin-x86_64.tar.gz > UnixTaskbook-Darwin-x86_64.tar.gz

		tar -zxvf UnixTaskbook-Darwin-x86_64.tar.gz

		cd UnixTaskbook-Darwin-x86_64

	elif [ "$(arch)" == "arm64" ]; then

		curl -L https://github.com/KCNyu/UnixTaskbook/releases/download/v1.0.0/UnixTaskbook-Darwin-arm64.tar.gz > UnixTaskbook-Darwin-arm64.tar.gz

		tar -zxvf UnixTaskbook-Darwin-arm64.tar.gz

		cd UnixTaskbook-Darwin-arm64
	fi

	sudo cp ./*.so /usr/local/lib/

fi

if ! [ -a /usr/local/bin/unixTaskbook ]; then

	sudo cp ./unixTaskbook /usr/local/bin

	sudo chmod +x /usr/local/bin/unixTaskbook
fi

# set vscode workspace 
cp -r ./.vscode ../utbWork/
cd ../utbWork/
mkdir .vscode
mv * .vscode/

# ask for input username
echo -n "Please input your username: "
UTB_USERNAME=$(
	read -r UTB_USERNAME
	echo $UTB_USERNAME
)
# ask for input password
echo -n "Please input your password: "
UTB_PASSWORD=$(
	read -r UTB_PASSWORD
	echo $UTB_PASSWORD
)

# export UTB_SERVICE UTB_USERNAME UTB_PASSWORD to .bashrc
echo "export UTB_SERVICE=true" >> ~/.bashrc
echo "export UTB_USERNAME=$UTB_USERNAME" >> ~/.bashrc
echo "export UTB_PASSWORD=$UTB_PASSWORD" >> ~/.bashrc
green "Install success!"

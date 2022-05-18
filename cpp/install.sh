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

		curl -L https://github.com/KCNyu/UnixTaskbook/releases/download/v1.0.0/UnixTaskbook-Linux-x86_64.tar.gz >UnixTaskbook-Linux-x86_64.tar.gz

		tar -zxvf UnixTaskbook-Linux-x86_64.tar.gz

		cd UnixTaskbook-Linux-x86_64

	elif [ "$(arch)" == "arm64" ]; then

		curl -L https://github.com/KCNyu/UnixTaskbook/releases/download/v1.0.0/UnixTaskbook-Linux-arm64.tar.gz >UnixTaskbook-Linux-arm64.tar.gz

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

		curl -L https://github.com/KCNyu/UnixTaskbook/releases/download/v1.0.0/UnixTaskbook-Darwin-x86_64.tar.gz >UnixTaskbook-Darwin-x86_64.tar.gz

		tar -zxvf UnixTaskbook-Darwin-x86_64.tar.gz

		cd UnixTaskbook-Darwin-x86_64

	elif [ "$(arch)" == "arm64" ]; then

		curl -L https://github.com/KCNyu/UnixTaskbook/releases/download/v1.0.0/UnixTaskbook-Darwin-arm64.tar.gz >UnixTaskbook-Darwin-arm64.tar.gz

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
mv launch.json tasks.json .vscode/

LOGIN_URL=https://unixtaskbook.com/accounts/login/
COOKIES=cookies.txt
CURL_BIN="curl -s -c $COOKIES -b $COOKIES -e $LOGIN_URL"

# ask if you want to login with user until you input y or n
while true; do
	read -p "Do you want to login with user? (y/n) " yn
	case $yn in
	[Yy]*)
		while true; do
			$CURL_BIN $LOGIN_URL >/dev/null
			CSRF=$(grep 'csrf' $COOKIES | awk '{print $NF}')
			DJANGO_TOKEN="csrfmiddlewaretoken=$CSRF"
			# ask for input username
			echo -n "Please input your username: "
			UTB_USERNAME=$(
				read -r UTB_USERNAME
				echo $UTB_USERNAME
			)
			# ask for input password with not seen password
			echo -n "Please input your password: "
			UTB_PASSWORD=$(
				stty -echo
				read -r UTB_PASSWORD
				stty echo
				echo $UTB_PASSWORD
			)
			# check if username and password is not correct
			if $CURL_BIN -d "$DJANGO_TOKEN&username=$UTB_USERNAME&password=$UTB_PASSWORD" https://unixtaskbook.com/accounts/login/ | grep -q "Your username and password didn't match."; then
				echo
				red "username or password is not correct"
				rm -f $COOKIES
				continue
			else
				rm -f $COOKIES
				break
			fi
		done
		# export UTB_SERVICE UTB_USERNAME UTB_PASSWORD to .bashrc if not exist
		if ! grep -q "UTB_SERVICE" ~/.bashrc; then
			echo "export UTB_SERVICE=true" >>~/.bashrc
		fi
		if ! grep -q "UTB_USERNAME" ~/.bashrc; then
			echo "export UTB_USERNAME=$UTB_USERNAME" >>~/.bashrc
		fi
		if ! grep -q "UTB_PASSWORD" ~/.bashrc; then
			echo "export UTB_PASSWORD=$UTB_PASSWORD" >>~/.bashrc
		fi
		break
		;;
	[Nn]*)
		break
		;;
	*)
		echo "Please answer yes or no."
		;;
	esac
done
# new line output
echo
green "Install success!"

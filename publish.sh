#!/bin/bash

sudo ./recomplie.sh

struct=$(uname -m)
platform=$(uname)

packagename="UnixTaskbook-$platform-$struct"

cd ..
rm -rf "$packagename"
mkdir "$packagename"

cd -
# unixTaskbook配置文件
cp ./unixTaskbook ../"$packagename" 
cp ./lib/*.so ../"$packagename"

# vscode任务配置文件
cp ./.vscode/launch.json ../"$packagename"
cp ./.vscode/tasks.json ../"$packagename" 

cd ..
tar -zcvf "$packagename".tar.gz "$packagename"

rm -rf "$packagename"

echo "pubilsh success"
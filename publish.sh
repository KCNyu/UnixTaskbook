#!/bin/bash

struct=$(uname -m)
platform=$(uname)

packagename="UnixTaskbook-$platform-$struct"

mkdir "$packagename"

# unixTaskbook配置文件
cp ./build/bin/unixTaskbook ./"$packagename"
if [ "$platform" == "Darwin" ]; then
    cp ./build/lib/*.dylib ./"$packagename"
fi
if [ "$platform" == "Linux" ]; then
    cp ./build/lib/*.so ./"$packagename"
    cp ./lib/unixTaskbook.conf ./"$packagename"
fi

# vscode任务配置文件
cp ./.vscode/launch.json ./"$packagename"
cp ./.vscode/tasks.json ./"$packagename" 

tar -zcvf "$packagename".tar.gz "$packagename"

rm -rf "$packagename"

echo "pubilsh success"
#!/bin/bash

sudo mkdir /usr/local/lib/TaskChecker
sudo cp ./lib/*.so /usr/local/lib/TaskChecker
sudo cp ./lib/taskchecker.conf /etc/ld.so.conf.d
sudo ldconfig
